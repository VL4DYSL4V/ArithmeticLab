#include <cstdlib>
#include <iostream>
#include <vector>

#include "Karazuba.h"
#include "ToomKuk.h"
#include "BigIntegerUtils.h"
#include "Shtrassen.h"
#include "InverseKuk.h"
#include "FactorDicson.h"
#include "Pollard.h"
#include "SquareSieve.h"
#include "DivisionKuk.h"

using namespace std;

void handleUnaryOperation(int input) {
    int x;
    cout << "Input x" << endl;
    cin >> x;
    if (input != 10) {
        if (input == 5) {
            InverseKuk inverseKuk;
            double inversed = inverseKuk.getInverse(x);
            cout << "InverseKuk: inversed = " << inversed << endl;
            cout << "Check: x * inversed = " << x * inversed << endl;
        } else if (input == 7) {
            FactorDicson factorDicson;
            cout << "Dicson: factor = " << factorDicson.getFactor(x) << endl;
        } else if (input == 8) {
            Pollard pollard;
            cout << "Pollard: factor = " << pollard.getFactor(x) << endl;
        } else if (input == 9) {
            SquareSieve squareSieve;
            cout << "Square sieve: factor = " << squareSieve.getFactor(x) << endl;
        }
    } else {
        cout << "Unsupported yet!!!" << endl;
    }
}

void handleBinaryOperation(int input) {
    int x, y;
    cout << "Input x" << endl;
    cin >> x;
    cout << "Input y" << endl;
    cin >> y;
    if (input != 3) {
        BigInteger bigX(to_string(x));
        BigInteger bigY(to_string(y));
        if (input == 1) {
            Karazuba karazuba;
            cout << "Karazuba: result = " << karazuba.multiply(bigX, bigY).toString() << endl;
        } else if (input == 2) {
            ToomKuk toomKuk;
            cout << "ToomKuk: result = " << toomKuk.multiply(bigX, bigY).toString() << endl;
        } else if (input == 4) {
            Shtrassen shtrassen;
            cout << "Shtrassen: result = " << shtrassen.multiply(bigX, bigY).toString() << endl;
        } else if (input == 6) {
            DivisionKuk divisionKuk;
            double result = divisionKuk.divide(x, y);
            cout << "DivisionKuk: result = " << result << endl;
            cout << "Check: x / y = " << x / y << endl;
        }
    } else {
        cout << "Unsupported yet!!!" << endl;
    }
}

void dispatchRequest(int input) {
    if ((1 <= input && input <= 4) || input == 6) {
        handleBinaryOperation(input);
    } else {
        handleUnaryOperation(input);
    }
}

void app() {
    cout << "Arzamastsev K-23 lab_2" << endl;
    string input;
    while (true) {
        cout << "input number (1 - 10 incl.) for desired algorithm" << endl;
        cin >> input;
        if (input == "exit") {
            break;
        }
        int number = stoi(input);
        if (1 <= number && number <= 10) {
            dispatchRequest(number);
        }
    }
}

int main(int argc, char **argv) {
    app();
    return 0;
}

