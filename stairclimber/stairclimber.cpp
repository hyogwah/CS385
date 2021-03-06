/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Eric Song
 * Date        : 9/30/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor system.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;


vector< vector<int> > get_ways(int num_stairs) {
    vector <vector <int>> ways = {};
    vector <int> empty = {}; // initializing base case

    if (num_stairs == 0) {
        ways.push_back(empty);
    }

    for (int i = 1; i < 4; i++) {
        if (num_stairs >= i) {
            vector< vector <int> >result = get_ways(num_stairs - i);

            // Prepending i to all solutions in result:
            int size = result.size();
            for (int j = 0; j < size; j++) {
                result[j].insert(result[j].begin(), i); // result[j] = [i] + result[j]
            }
            ways.insert(ways.end(), result.begin(), result.end()); // ways += result (entirety)
        }
    }
    return ways;
}


void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int count=0, total, nums;
    total = ways.size();

    // to get num_stairs
    int size = ways[0].size();
    for (int a=0; a<size; a++) {
    	int val = ways[0][a];
        nums += val;
    }

    int digit = total;
    // right align, getting digit places (taken from my sieve code)
    while (digit >= 10) {
        digit /= 10;
        count++;
    }

    if (total == 1) {
    	cout << total << " way to climb " << nums << " stair." << endl;
    }
    else {
    	cout << total << " ways to climb " << nums << " stairs." << endl;
    }
    int counter=1;
    int size1=ways.size();
    for (int i=0; i < size1; i++) {
        cout << setw(count+1) << counter << ". [";
        int size2=ways[i].size();
        for (int j=0; j < size2 ; j++) {
            if (j == size2 - 1) {
                cout << ways[i][j];
            } else {
            cout << ways[i][j] << ", ";
            }
        }
        cout << "]";
        cout << endl;
        if (counter < total) {
            counter++;
        }
    }
}

int main(int argc, char * const argv[]) {
    // Error test cases
    int num;
    istringstream iss;

    if (argc == 1 || !(argc == 2)) {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if (!(iss >> num)) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    iss >> num;
    if (num <= 0) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    // Main function execution
    vector < vector<int> > test = get_ways(num);
    display_ways(test);

}
