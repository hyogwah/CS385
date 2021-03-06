/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Eric Song
 * Version     : 1.0
 * Date        : 10/26/2021
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor system -esong
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
//static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
static long mergesort(int array[], int scratch[], int low, int high) {
	long inversions = 0;

    if (low < high) {
    	int mid = (low + ((high - low) / 2));
    	int L = low;
    	int H = mid+1;
    	inversions += mergesort(array, scratch, low, mid);
    	inversions += mergesort(array, scratch, mid+1, high);

    	for (int k=low; k <= high; k++) {
    		if (L <= mid && (H > high || array[L] <= array[H])) {
    			scratch[k] = array[L];
    			L++;
    		} else {
    			scratch[k] = array[H];
    			H++;
    			inversions += (mid - L + 1);
    		}
    	}
    	for (int j=low; j <= high; j++) {
    		array[j] = scratch[j];
    	}
    }
	return inversions;
}

long count_inversions_slow(int array[], int length) {
	long inversions = 0;
	for (int i=0; i < length-1; i++) {
		for (int j=i+1; j < length; j++) {
			if (array[i] > array[j]) {
				inversions++;
			}
		}
	}
    return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    long inversions = 0;

    int *scratch = new int[length];
    inversions = mergesort(array, scratch, 0, length-1);

    delete scratch;
	return inversions;
}

// Modified version of mergesort in order to including inclusion count


//static long mergesort(int array[], int scratch[], int low, int high) {
//    if (low < high) {
//    	int mid = (low + ((high - low) / 2));
//    	mergesort(array, scratch, low, mid);
//    	mergesort(array, scratch, mid+1, high);
//    	int L = low;
//    	int H = mid+1;
//
//    	for (int k=low; k <= high; k++) {
//    		if (L <= mid && (H > high || array[L] <= array[H])) {
//    			scratch[k] = array[L];
//    			L++;
//    		} else {
//    			scratch[k] = array[H];
//    			H++;
//    		}
//    	}
//    	for (int j=low; j <= high; j++) {
//    		array[j] = scratch[j];
//    	}
//    }
//	return 0;
//}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	if (argc > 2) {
	    cerr << "Usage: " << argv[0] << " [slow]" << endl;
		return 1;
	}
	if (argc == 2) {
		string slow(argv[1]);
		if (slow.compare("slow") != 0) {
			cerr <<  "Error: Unrecognized option '" << slow << "'." << endl;
			return 1;
		}
	}
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    int *array = &values[0];
    int size = values.size();

    if (size == 0) {
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }
    if (argc == 2) {
    	long slow_inv = count_inversions_slow(array, size);
    	cout << "Number of inversions: " << slow_inv << endl;
    } else {
    	long fast_inv = count_inversions_fast(array, size);
    	cout << "Number of inversions: " << fast_inv << endl;
    }


    return 0;
}
