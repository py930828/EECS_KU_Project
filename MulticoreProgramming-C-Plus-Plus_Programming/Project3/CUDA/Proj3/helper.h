#include <fstream>
#include <iostream>
using namespace std;

unsigned char* readfile( char* file, int size )
{
	ifstream readfile( file );
	unsigned char *h_data = new unsigned char [size];
	readfile.read(reinterpret_cast<char*> (h_data), size);
	return h_data;
}


void writeTheFile(std::string fName, int xres, int yres, const unsigned char* imageBytes)
{
	unsigned char* row = new unsigned char[3*xres];
	ImageWriter* w = ImageWriter::create(fName,xres,yres);
	int next = 0;
	for (int r=0 ; r<yres ; r++)
	{
		for (int c=0 ; c<3*xres ; c+=3)
		{
			row[c] = row[c+1] = row[c+2] = imageBytes[next++];
		}
		w->addScanLine(row);
	}
	w->closeImageFile();
	delete w;
	delete [] row;
}


/*
 *  API function for cuda
 */
__device__ static float atomicMax(float* address, float val) // small change to allow atomicMax suppose float, from stackoverflow
{
    int* address_as_i = (int*) address;
    int old = *address_as_i, assumed;
    do {
        assumed = old;
        old = ::atomicCAS(address_as_i, assumed,
            __float_as_int(::fmaxf(val, __int_as_float(assumed))));
    } while (assumed != old);
    return __int_as_float(old);
}

void cudaCheck( cudaError_t cudaerr )
{
	if (cudaerr != cudaSuccess)
      printf("kernel launch failed with error \"%s\".\n", cudaGetErrorString(cudaerr));
}
