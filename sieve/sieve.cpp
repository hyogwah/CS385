/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Eric Song
 * Date        : 9/12/2021
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 2);

    int count = 0;
    if (num_primes_ < primes_per_row) {
    	for (int i = 0; i <= limit_; i++) {
    		if (is_prime_[i] == true) {
    			if (count !=0 ) {
    				cout << " "; //this fixes leading white spaces for the test case
    			}
    			cout << i; count++;
    		}

    	}
    }
    else {
    	for (int i = 0; i <= limit_; i++) {
    		if (count == primes_per_row) {
    			cout << "\n";
    			count = 0;
    		}

    		else if (is_prime_[i] == true) {
    			if (count != 0) {
    				cout << " ";
    			}
    			cout << setw(max_prime_width+1) << i;
    			count++;
    		}
    	}
    }
    cout << endl;
}

int PrimesSieve::count_num_primes() const {
    int count = 0;
    for (int i = 0; i <= limit_ ; i++) {
        if (is_prime_[i] == true) {
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    is_prime_[0] = false;
    is_prime_[1] = false;
    for (int i=2; i <= limit_; i++) {
        is_prime_[i] = true;
    }
    for (int i = 0; i < sqrt(limit_); i++) {
        if (is_prime_[i] == true) {
            for (int j = i*i; j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }
    int temp = limit_;
    while (is_prime_[temp] != true) {
        temp--;
    }
    max_prime_ = temp;
    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count=0;
    while (num >= 10) {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieveT(limit);
    int number = sieveT.num_primes();
    cout << "\nNumber of primes found: " << number << endl;
    cout << "Primes up to " << limit << ":" << endl;
    sieveT.display_primes();
    return 0;
}




