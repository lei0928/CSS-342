#include <iostream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include "mergeImproved.cpp"
#include "mergesort.cpp"
#include "quicksort.cpp"

using namespace std;

// array initialization with random numbers
void initArray( vector<int> &array, int randMax ) {
    int size = array.size( );

    for ( int i = 0; i < size; ) {
        int tmp = ( randMax == -1 ) ? rand( ) : rand( ) % randMax;
        bool hit = false;
        for ( int j = 0; j < i; j++ ) {
            if ( array[j] == tmp ) {
                hit = true;
                break;
            }
        }
        if ( hit )
            continue;
        array[i] = tmp;
        i++;
    }
}

// array printing
void printArray( vector<int> &array, char arrayName[] ) {
    int size = array.size( );

    for ( int i = 0; i < size; i++ )
        cout << arrayName << "[" << i << "] = " << array[i] << endl;
}

// returning the elapsed time for each sort method
int elapsed( timeval &startTime, timeval &endTime) {
    return (endTime.tv_sec - startTime.tv_sec) * 1000000
       + (endTime.tv_usec - startTime.tv_usec);
}

int main( int argc, char* argv[] ) {
    ofstream outfile;
    outfile.open("compare.txt"); // create and out file with "compare.txt" filename
    outfile<<"size \t mergesort \t quicksort \t mergeImproved \n";

    // array generation
    int size = 20;
    int rnd = 1;

    // to create the size of arrays from 20 to 1000, each time the size of array increases 20
    while(size <= 1000) {
    	// to change the seed, it generates the different random arrya each time
        srand(size);
        // prints out the size
    	outfile<<size<<"\t";
        vector<int> items1( size );
        initArray( items1, size );

        vector<int> items2 = items1;
        vector<int> items3 = items1;

        //timeval preparation
        timeval startTime, endTime;

        // merge sort
        gettimeofday( &startTime, 0); // records the start time
        mergesort(items1);
        gettimeofday( &endTime, 0); // records the end time
        int merge = elapsed( startTime, endTime); // calculate the time (end time - start time)
        outfile<<merge<<"\t"; // prints out the time by using merge sort

        // quick sort
        gettimeofday( &startTime, 0);
        quicksort(items2);
        gettimeofday( &endTime, 0);
        int quick = elapsed( startTime, endTime);
        outfile<<quick<<"\t";  // prints out the time by using quick sort

        // mergeImproved sort
        gettimeofday( &startTime, 0);
        mergeImproved(items3);
        gettimeofday( &endTime, 0);
        int mergeImproved = elapsed( startTime, endTime);
        outfile<<mergeImproved<<"\n"; // prints out the time by using improved merge sort

        size += 20;
    }
    outfile.close(); // close the compare.txt file

    return 0;
}
