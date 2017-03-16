CC=g++
Version=-07
OBJ=AntsIBM$(Version).o
#CFLAGS=-Wall -g -std=c++11
CFLAGS= -g -std=c++11

antsibm$(Version):$(OBJ)
	$(CC) -o antsibm$(Version) $(OBJ) -lm

$(OBJ):AntsIBM$(Version).cpp
	$(CC) $(CFLAGS) -c AntsIBM$(Version).cpp 

clean:
	rm -f *.o;
	rm -f antsibm$(Version);

