#include <vector>
#include <math.h>
using namespace std;

template <class Comparable>
void mergeImproved( vector<Comparable> &a, vector<Comparable> &b, int first, int mid, int last) {
    // initialize the starting point of the first sub array
    int first1 = first;
    // initialize the starting point of the second sub array
    int first2 = mid;
    // initialize the indexing of temporary array which contains sorted sub array
    int index = first;

    while (first1 < mid && first2 < last) {
        // compare the elements of first sub array with second sub array
        // if the element from the first sub array is smaller, then copy
        // copy it into the temporary array
        // else copy right sub array element into the temporary array
        // increment index by 1
        if(a[first1] < a[first2]) {
            b[index] = a[first1];
            first1 = first1 + 1;
        } else {
            b[index] = a[first2];
            first2 = first2 + 1;
        }
        index = index + 1;
    }

    while (first1 < mid) {
        // if any first sub array remains to copy after above merging process
        // then copy remaining element of left sub array into temporary array
        // this process copies extra elements from left sub array to temporary array
        b[index] = a[first1];
        first1 = first1 + 1;
        index = index + 1;
    }

    while (first2 <= last) {
        // if any second sub array remains to copy after above merging process
        // then copy remaining element of right sub array into temporary array
        // this process copies extra elements from right sub array to temporary array
        b[index] = a[first2];
        first2 = first2 + 1;
        index = index + 1;
    }

    // copying the sorted temporary array to the original array
    for (first1 = first; first1 < last; first1++) {
        a[first1] = b[first1];
    }

}

template<class Comparable>
void mergeImproved(vector<Comparable> &a) {
    int size = a.size();
    vector<Comparable> b(size); // this is only one temporary array
    // implement a nonrecursive mergesort only using vector a and b
    for (int length = 1; length < size; length = 2 * length) {
        for(int first1 = 0; first1 < size; first1 = first1 + 2 * length) {
            int first2 = min(first1 + length, size); // index of the sub array
            int last = min(first1 + 2 * length, size); // last index of the sub array
            mergeImproved(a, b, first1, first2, last); // merge two sub arrays
        }
        a = b;
    }
}

