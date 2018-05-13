//mpirun -np 2 project2 dog.jpg dog1.jpg
#include <mpi.h>
#include <iostream>
#include <math.h>
#include "ImageReader.h"
using namespace std;

float* do_rank_0_work( int communicatorSize, char* argv[] )
{
  MPI_Request sendReq[2];
  for( int i = 1; i < communicatorSize; i++ )
  {
    ImageReader* ir = ImageReader::create(argv[i+1]);
    auto pa = ir->getInternalPacked3DArrayImage();
    int size = pa->getTotalNumberElements();
    auto data = pa->getData();
    MPI_Isend( &size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &sendReq[0] );
    MPI_Isend( data, size, MPI_UNSIGNED_CHAR, i, 1, MPI_COMM_WORLD, &sendReq[1] );
  }
  /*
   *  finished sending all images to other ranks. Start processing image 0
  */
  ImageReader* ir = ImageReader::create(argv[1]);
  auto pa = ir->getInternalPacked3DArrayImage();
  auto data = pa->getData(); // get the data array
  int size = pa->getTotalNumberElements();
  float total_pixels = size / 3;
  /*
   *  Create and initialize the 2D array
  */
  float *RGB = (float*)calloc( 768, sizeof(float) );
  /*
   *
  */
  for( int i = 0; i < size; i = i + 3 ) // calculate the color and put into the array
  {
    RGB[ (int)data[i]         ] = RGB[ (int)data[i]       ] + 1.0; // processing the Red
    RGB[ (int)data[i+1] + 256 ] = RGB[ (int)data[i+1] + 256 ] + 1.0; // processing the Green
    RGB[ (int)data[i+2] + 512 ] = RGB[ (int)data[i+2] + 512 ] + 1.0; // processing the Blue
  }
  for( int i = 0; i < 768; i++ ) // convert the amount into float accuracy
  {
    RGB[i] = RGB[i] / total_pixels;
  }
  /*
   *  Successfully convert the image into RGB array, start broadcasting the array to all other rank
  */
  return RGB;

}

float* do_rank_i_work( int communicatorSize, int rank )
{
  MPI_Request answerReq[1];
  MPI_Status dataStatus[communicatorSize-1];
  int size;
  MPI_Recv( &size, sizeof(int), MPI_INT, 0, 0, MPI_COMM_WORLD, &dataStatus[0] );
  unsigned char *data = new unsigned char[size];
  MPI_Irecv( data, size, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD, &answerReq[0] );
  cout<<"Rank "<<rank<<" Receiving image now."<<endl;
  MPI_Waitall( 1, answerReq, dataStatus );
  cout<<"Rank "<<rank<<" Received image."<<endl;
  /*
   *  Received image from rank0, start processing
  */
  float total_pixels = size / 3;
  float *RGB = (float*)calloc( 768, sizeof(float) ); // Create and initialize the 2D array
  for( int i = 0; i < size; i = i + 3 ) // calculate the color and put into the array
  {
    RGB[ (int)data[i]         ] = RGB[ (int)data[i]       ] + 1.0; // processing the Red
    RGB[ (int)data[i+1] + 256 ] = RGB[ (int)data[i+1] + 256 ] + 1.0; // processing the Green
    RGB[ (int)data[i+2] + 512 ] = RGB[ (int)data[i+2] + 512 ] + 1.0; // processing the Blue
  }
  for( int i = 0; i < 768; i++ ) // convert the amount into float accuracy
  {
    RGB[i] = RGB[i] / total_pixels;
  }
  /*
   *  Successfully convert the image into RGB array, start broadcasting the array to all other ranks
  */
  return RGB;
}

void do_rank_work( int communicatorSize, char* argv[], int rank )
{
  float *RGB = (float *)malloc( sizeof( float ) * 768 );
  if( !rank )
  {
    RGB = do_rank_0_work( communicatorSize, argv );
  }
  else
  {
    RGB = do_rank_i_work( communicatorSize, rank );
  }
  float *AllImage = (float*)calloc( 256 * 3 * communicatorSize, sizeof(float) );  // create a 2D array for all imamges
  MPI_Allgather( RGB, 768, MPI_FLOAT, AllImage, 768, MPI_FLOAT, MPI_COMM_WORLD ); // broadcasting all images to every rank
  /*
   *  Successfully gathered all image data to every rank, start comparing!!!
  */
  float *RankDiff = (float*)calloc( communicatorSize - 1, sizeof(float) ); int count = 0;
  for( int i = 0; i < communicatorSize; i++ ) // making an array that calculate the difference between all other images with ranki
  {
    for( int j = 0; j < 768; j++ )
    {
      if( i == rank ) {   break;  }
      else{
        RankDiff[count] = RankDiff[count] + fabs( AllImage[rank * 768 + j]  - AllImage[ i * 768 + j ] );
      }
    }
    if( i != rank ) { count++; }
  }
  cout<<"rank "<<rank<<"'s difference array: ";
  for(int i = 0; i < communicatorSize - 1; i++)
  {
    cout<<(float)RankDiff[i]<<" ";
  }
  cout<<endl;
  MPI_Barrier( MPI_COMM_WORLD );
  int BiggestDiffRank = 0;
  if( communicatorSize > 2 ) // in order for the rank to compare, there must be at least 3 ranks so we can compare the two image beside itself
  {
    float ClosestRankDiffValue = RankDiff[0];
    for( int i = 0; i < communicatorSize-2; i++ ) // it's i < communicatorSize-2 because we are going to check one less time
    {
      if( ClosestRankDiffValue > RankDiff[i + 1] ) {   BiggestDiffRank = i+1; ClosestRankDiffValue = RankDiff[i+1];  }
    }
  }
  else if( communicatorSize == 2 )
  {
    BiggestDiffRank = 0;
  }
  if( rank >= BiggestDiffRank && rank != communicatorSize -1 ) {   BiggestDiffRank++;    } // consider the case that we don't compare the rank with itself
  int result[ communicatorSize ];
  MPI_Gather( &BiggestDiffRank, 1, MPI_INT, &result[0], 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Barrier( MPI_COMM_WORLD );
  if( !rank )
  {
    for( int i = 0; i < communicatorSize; i++ )
    {
      cout<<"rank "<<i<<" think it's closest image is : "<<result[i]<<endl;
    }
  }
  return;
}

int main(int argc, char* argv[])
{
  MPI_Init( &argc, &argv );
  int rank, communicatorSize;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // unique ID for this process; 0<=rank<N where:
	MPI_Comm_size(MPI_COMM_WORLD, &communicatorSize); // N=communicatorSize (size of "world")
	if (argc < 2)
		std::cerr << "Usage: " << argv[0] << " imageFileName\n";
	else
	{
    do_rank_work( communicatorSize, argv, rank );
	}
  MPI_Finalize();
	return 0;
}
