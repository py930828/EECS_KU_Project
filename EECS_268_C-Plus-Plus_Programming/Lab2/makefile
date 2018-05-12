Lab02:Executive.o main.o DriversLicenseRecord.o
	g++ -g -Wall -o Lab02 Executive.o main.o DriversLicenseRecord.o

DriversLicenseRecord.o: DriversLicenseRecord.h DriversLicenseRecord.cpp
	g++ -c -g -Wall DriversLicenseRecord.cpp

main.o: Executive.h main.cpp
	g++ -c -g -Wall main.cpp

Executive.o: Executive.h Executive.cpp
	g++ -c -g -Wall Executive.cpp

clean:
	rm *.o Lab02
