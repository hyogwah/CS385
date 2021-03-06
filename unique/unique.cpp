/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Eric Song
 * Date        : 9/25/21
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided with the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	int length = s.length();
    for (int i = 0; i < length; i++) {
        if (islower(s[i]) == 0) { // if islower == 0, s[i] is not lowercase.
            return false;
        }
    }
    return true;

}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

    unsigned int vector = 0;
    unsigned int setter;
    int length = s.length();
    for (int i = 0; i < length; i++) {
        setter = 1 << (s[i] - 'a');

        if ((vector & setter)> 0) {
            return false;
        }
        vector = vector | setter;
    }
    return true;
}

int main(int argc, char * const argv[]) {
    //error checks

    if (argc == 1 || !(argc == 2)) {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    string word = argv[1];

    if (is_all_lowercase(word) == false) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (all_unique_letters(word) == false) {
        cerr << "Duplicate letters found." << endl;

    }

    if (all_unique_letters(word) == true) {
        cerr << "All letters are unique." << endl;
    }

    return 0;
}
