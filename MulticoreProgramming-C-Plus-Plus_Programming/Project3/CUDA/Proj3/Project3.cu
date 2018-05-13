#include <iostream>
#include <math.h>
#include <cuda.h>
#include <stdio.h>
#include <string>
#include <algorithm>    // std::swap

#include "ImageWriter.h"
#include "helper.h"
using namespace std;

int nRows = 0; int nCols = 0; int nSheets = 0;

__global__ void Max_Kernel( unsigned char *d_MaxData, unsigned char * d_data, float* d_WeightedSum, float* d_maxWeightedSum, int nSheets)
{
	int SheetsCount = 0; int Max = 0;
	/*
	 * blockDim.x*blockIdx.x+threadIdx.x
	 * is in row major, but we need to match up with the RAW data, which is column major
	 * blockDim is the nCols, gridDim is the nRows
	*/
	int threadNum = threadIdx.x*gridDim.x+blockIdx.x; // make it to colume major
	d_WeightedSum[threadNum] = 0.0;
	while( SheetsCount < nSheets )
	{
		int CurSheetPos = SheetsCount*gridDim.x*blockDim.x +
											blockDim.x*blockIdx.x+threadIdx.x;
											// follow the original logic because it is column major already

		if( Max < (unsigned int)d_data[CurSheetPos] ) {	Max = (unsigned int)d_data[CurSheetPos];	};

		d_WeightedSum[threadNum] +=  ( (nSheets - SheetsCount + 1)/(nSheets * 1.0) )  * d_data[CurSheetPos];
		SheetsCount++;
	}
	d_MaxData[threadNum] = Max;
	atomicMax( d_maxWeightedSum,  d_WeightedSum[threadNum] ); // cuda API function to prevent race condition
}

__global__ void Sum_Kernel( float* d_WeightedSum, unsigned char* d_FinalWeightedSum, float* d_maxWeightedSum )
{
	int threadNum = threadIdx.x*gridDim.x+blockIdx.x;
	float myMax = d_WeightedSum[threadNum];
	float globalMax = *d_maxWeightedSum;
	unsigned char result = (unsigned char)( ( myMax/globalMax )*255.0 );
	//printf("Thread %d: myMax is %f, globalMax is %f, storing %d\n", threadNum, myMax, globalMax,result);
	d_FinalWeightedSum[threadNum] = result;
}

/*
 * get the voxeldata's position after the nCols, nRows, nSheets changed.
*/
int OldData_CurPos_Handler( int projection, int CurRow, int CurCol, int CurSheet )
{
	int SheetSize = 0; // SheetSize of voxeldata, not projection's SheetSize!!!!
	switch( projection )
	{
		case 2: SheetSize = nRows * nCols;
						return ( nSheets - 1 - CurSheet ) * SheetSize + ( nCols - 1 - CurCol ) * nRows + CurRow;
		case 3: SheetSize = nSheets * nCols;
						return CurCol * SheetSize + ( nSheets - CurSheet - 1 ) * nRows + CurRow;
		case 4: SheetSize = nSheets * nCols;
						return (nCols - 1 - CurCol) * SheetSize + CurSheet * nRows + CurRow;
		case 5: SheetSize = nSheets * nCols;
						return CurRow *SheetSize + CurCol * nSheets + CurSheet;
		case 6: SheetSize = nSheets * nCols;
						return (nRows - 1 - CurRow) *SheetSize + CurCol * nSheets + CurSheet; // this is right
	}
	return -1;
}

/*
 * if the projection isn't 1, do the data swaping based on what projection it is
*/
unsigned char* ProjectionCaseHandler( int projection, unsigned char* h_data )
{
	switch( projection ) // change the value of nRows, nCols, nSheets depends on the projection
	{
		case 3:
		case 4: swap(nCols, nSheets); break;
		case 5:
		case 6: swap(nRows, nSheets); break;
	}
	int TotalImageSize = nRows * nCols * nSheets;
	//int SheetSize = nRows * nCols;
	unsigned char* h_NewData = new unsigned char[ TotalImageSize ];
	int NewData_CurPos = 0;
	for( int CurSheet = 0; CurSheet < nSheets; CurSheet++ )
	{
		for( int CurCol = 0; CurCol < nCols; CurCol++ )
		{
			for( int CurRow = 0; CurRow < nRows; CurRow++ )
			{
				int OldData_CurPos = OldData_CurPos_Handler( projection, CurRow, CurCol, CurSheet );
				h_NewData[ NewData_CurPos ] = h_data[ OldData_CurPos ];
				NewData_CurPos++;
			}
		}
	}
	delete h_data;
	return h_NewData;
}

int main(int argc, char** argv)
{
	if( argc < 7 )
	{
		cout<<"not enough arguments."<<endl;
		return -1;
	}
	nRows = atoi(argv[1]); nCols = atoi(argv[2]); nSheets = atoi(argv[3]); int projection = atoi(argv[5]); string filename = argv[6];
	int size = nRows * nCols * nSheets;
	unsigned char* h_data;
	unsigned char* h_MaxData = new unsigned char[nRows * nCols];
	unsigned char* h_FinalWeighedSum;
	unsigned char* d_data;
	unsigned char* d_MaxData;
	unsigned char* d_FinalWeightedSum;
	float* 				 d_WeightedSum;
	float*         d_maxWeightedSum;
	h_data = readfile( argv[4], size ); //read the raw file and returns pointer points to the raw h_data

	/*
	 * if projection isn't 1, change the RAW data to that projection
	*/
	if( projection > 1 )	{ 	h_data = ProjectionCaseHandler( projection, h_data ); 	}

	/*
	 * allocate memory on GPU and launch the Max_Kernelkernel
	*/
	cudaCheck( cudaMalloc( (void **)&d_MaxData, sizeof(unsigned char) * nRows * nCols ) ); // malloc the memory for the max data
	cudaCheck( cudaMalloc( (void **)&d_data, sizeof(unsigned char)*size ) );
	cudaCheck( cudaMalloc( (void **)&d_WeightedSum, sizeof(float) * nRows * nCols ) ); // malloc the memory for the sum value, but not the final sum data
	cudaCheck( cudaMalloc( (void **)&d_maxWeightedSum, sizeof(float) ) ); // store the maxvalue in graphics card since we have to get this data from kernel.
	cudaMemcpy( d_data, h_data, sizeof(unsigned char)*size, cudaMemcpyHostToDevice );
	Max_Kernel<<<nCols, nRows>>>(d_MaxData, d_data, d_WeightedSum, d_maxWeightedSum, nSheets);
	cudaCheck( cudaDeviceSynchronize() );

  /*
	 * copy data back to CPU and output the MAX image out
	*/
  cudaCheck( cudaMemcpy( h_MaxData, d_MaxData, nRows * nCols * sizeof(unsigned char), cudaMemcpyDeviceToHost ) );
	string name = filename+"MAX.png";
	writeTheFile(name, nCols, nRows, h_MaxData);

	/*
	 * running the sum kernel and output the sum image out
	*/
	h_FinalWeighedSum = h_MaxData; d_FinalWeightedSum = d_MaxData; // reuse the same area of d_MaxData since d_MaxData isn't needed anymore
	Sum_Kernel<<<nCols, nRows>>>( d_WeightedSum, d_FinalWeightedSum, d_maxWeightedSum );
	cudaCheck( cudaDeviceSynchronize() );
	cudaCheck( cudaMemcpy( h_FinalWeighedSum, d_FinalWeightedSum, nRows * nCols * sizeof(unsigned char), cudaMemcpyDeviceToHost ) );
	name = filename+"SUM.png";
	writeTheFile(name, nCols, nRows, h_MaxData);

	/*
	 * deallocate memory
	*/
	cudaCheck( cudaFree( d_FinalWeightedSum ) );
	cudaCheck( cudaFree( d_data ) );
	cudaCheck( cudaFree( d_WeightedSum ) ) ;
	cudaCheck( cudaFree( d_maxWeightedSum) );
	delete h_MaxData;
	delete h_data;
	return 1;
}
