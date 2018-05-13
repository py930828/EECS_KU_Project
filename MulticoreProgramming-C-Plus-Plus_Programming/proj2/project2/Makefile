project2: project2.o ../lib/libCOGLImageReader.so
	mpic++ -o project2 project2.o ../lib/libCOGLImageReader.so
project2.o: project2.cpp
	mpic++ -c -std=c++11 -I../Packed3DArray -I../ImageReader project2.cpp
../lib/libCOGLImageReader.so: ../ImageReader/ImageReader.h ../ImageReader/ImageReader.c++ ../Packed3DArray/Packed3DArray.h
	(cd ../ImageReader; make)

clean:
	rm *.o project2
