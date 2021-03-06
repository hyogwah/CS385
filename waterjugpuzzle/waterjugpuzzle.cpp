/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Chang-Woo Ham and Eric Song
 * Date        : 10/16/2021
 * Description : runs the water jug puzzle using breadth-first search
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor system
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <queue>
using namespace std;


// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

string bfs(int a, int b, int c, State cap, State goal, bool** array, vector<State> solution) {
    queue<State> list;
    State curr = State(a, b, c, "");
    curr.parent = nullptr;
    list.push(curr);
    while (list.size() != 0) {
        curr = list.front();
        curr.parent = &curr;
        solution.push_back(curr);
        list.pop();
        if ((curr.a == goal.a) && (curr.b == goal.b)) {
            cout << "Initial state. " << State(a, b, c, "").to_string() << endl;
            return "sol";
        }
        if ((array[curr.a][curr.b]) == true) {
            continue;
        }
        array[curr.a][curr.b] = true;

        // try the 6 ways to pour water, pushing new States to the queue
        // pour c to a
        if ( ((cap.a - curr.a) > 0) && (curr.c > 0) ) {
            int tempA = curr.a;
            int tempB = curr.b;
            int tempC = curr.c;
            while((cap.a - tempA > 0)) { // still room
                if (tempC == 0) { // if c runs out of water
                    break;
                }
                tempA += 1;
                tempC -= 1;
            }
            State newState = State(tempA, tempB, tempC, "Pour");
            newState.parent = &curr;
            list.push(newState);
        }
        // pour b to a
        if ( ((cap.a - curr.a) > 0) && (curr.b > 0) ) {
            int tempA = curr.a;
            int tempB = curr.b;
            int tempC = curr.c;
            while((cap.a - tempA > 0)) { // still room
                if (tempB == 0) { // if b runs out of water
                    break;
                }
                tempA += 1;
                tempB -= 1;
            }
            State newState = State(tempA, tempB, tempC, "");
            newState.parent = &curr;
            list.push(newState);
        }
        // pour c to b
        if ( ((cap.b - curr.b) > 0) && (curr.c > 0) ) {
            int tempA = curr.a;
            int tempB = curr.b;
            int tempC = curr.c;
            while((cap.b - tempB > 0)) { // still room
                if (tempC == 0) { // if c runs out of water
                    break;
                }
                tempB += 1;
                tempC -= 1;
            }
            State newState = State(tempA, tempB, tempC, "");
            newState.parent = &curr;
            list.push(newState);
        }
        // pour a to b
        if ( ((cap.b - curr.b) > 0) && (curr.a > 0) ) {
            int tempA = curr.a;
            int tempB = curr.b;
            int tempC = curr.c;
            while((cap.b - tempB > 0)) { // still room
                if (tempA == 0) { // if a runs out of water
                    break;
                }
                tempB += 1;
                tempA -= 1;
            }
            State newState = State(tempA, tempB, tempC, "");
            newState.parent = &curr;
            list.push(newState);
        }
        // pour b to c
        if ( ((cap.c - curr.c) > 0) && (curr.b > 0) ) {
            int tempA = curr.a;
            int tempB = curr.b;
            int tempC = curr.c;
            while((cap.c - tempC > 0)) { // still room
                if (tempB == 0) { // if b runs out of water
                    break;
                }
                tempC += 1;
                tempB -= 1;
            }
            State newState = State(tempA, tempB, tempC, "");
            newState.parent = &curr;
            list.push(newState);
        }
        // pour a to c
        if ( ((cap.c - curr.c) > 0) && (curr.a > 0) ) {
            int tempA = curr.a;
            int tempB = curr.b;
            int tempC = curr.c;
            while((cap.c - tempC > 0)) { // still room
                if (tempA == 0) { // if a runs out of water
                    break;
                }
                tempC += 1;
                tempA -= 1;
            }
            State newState = State(tempA, tempB, tempC, "");
            newState.parent = &curr;
            list.push(newState);
        }
    }
    cout << "No solution." << endl;
    return "No solution.";
}

int main(int argc, char * const argv[]){
    // Checks if there are 6 input arguments
    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 0;
    }

    /**
     *  Checks if the values of the caps of A B C and returns an error
     *  if the value isn't an integer
     **/
    vector<int> inputs;
    for(int i = 1; i < 7; i++){
        int input;
        istringstream iss(argv[i]);
        if(i < 4){
            char jug = "ABC"[i-1];
            if(!(iss >> input) || input <= 0){
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug << "." << endl;
                return 0;
            }
            //pushes argv[1] to argv[3] into a queue labeled as inputs
            inputs.push_back(input);
            iss.clear();
            continue;
        } else {
            char jug = "ABC"[i-4];
            if(!(iss >> input) || input < 0){
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jug << ".";
                return 0;
            }
            //pushes argv[4] to argv[6] into a queue labeled as inputs
            inputs.push_back(input);
            iss.clear();
            continue;
        }
    }

    //Checks if the goal of a given jug exceeds its capacity
    for(unsigned int i = 0; i <= inputs.size(); i++){
        char jug = "ABC"[i];
        if(inputs[i] < inputs[i+3]){
            cerr << "Error: Goal cannot exceed capacity of jug " << jug << ".";
            return 0;
        }
    }

    //Checks if the goal state exceeds the capacity of Jug C
    if(inputs[2] != (inputs[3] + inputs[4] + inputs[5])){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return 0;
    }

    // Declaring a 2D array with A + 1 rows.
    bool **array = new bool*[inputs[0]+1];

    // Making an array
    for(int i = 0; i <= inputs[0]; i++){
        array[i] = new bool[inputs[1] + 1]; // B + 1
        fill(array[i], array[i] + (inputs[1] + 1), false);
    }

    State capacity = State(inputs[0], inputs[1], inputs[2], "");
    State goal = State(inputs[3], inputs[4], inputs[5], "");
    vector<State> solution;

    bfs(0, 0, inputs[2], capacity, goal, array, solution);

    // Deletes every row of the 2D array
    for(int i = 0; i <= inputs[0]; i++){
        delete [] array[i];
    }
    // Deletes the 2D array
    delete [] array;

    return 0;
}
