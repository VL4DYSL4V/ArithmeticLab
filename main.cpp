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

using namespace std;

void testAll() {
//    BigInteger x("65381");
//    BigInteger y("9800");
//    BigInteger divisor("7");
//    Karazuba karazuba;
//    cout << karazuba.multiply(x, y).toString() << endl;
//    ToomKuk toomKuk;
//    cout << toomKuk.multiply(x, y).toString() << endl;
//    Shtrassen modular;
//    cout << modular.multiply(x, y).toString() << endl;
//    FactorDicson factorDicson;
//    cout << "factor = " << factorDicson.getFactor(73) << endl;
//    Pollard pollard;
//    cout << "factor = " << pollard.getFactor(4) << endl;
//    SquareSieve squareSieve;
//    cout << "factor = " << squareSieve.getFactor(77) << endl;
}

void handleUnaryOperation(int input) {
    int x;
    cout << "Input x" << endl;
    cin >> x;
    if (input == 7 || input == 8 || input == 9) {
        if (input == 7) {
            FactorDicson factorDicson;
            cout << "Dicson: factor = " << factorDicson.getFactor(x) << endl;
        }else if(input == 8){
            Pollard pollard;
            cout << "Pollard: factor = " << pollard.getFactor(x) << endl;
        }else{
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
    if (input == 1 || input == 2 || input == 4) {
        BigInteger bigX(to_string(x));
        BigInteger bigY(to_string(y));
        if (input == 1) {
            Karazuba karazuba;
            cout << "Karazuba: result = "<<karazuba.multiply(bigX, bigY).toString() << endl;
        }else if(input == 2){
            ToomKuk toomKuk;
            cout << "ToomKuk: result = "<<toomKuk.multiply(bigX, bigY).toString() << endl;
        }else{
            Shtrassen shtrassen;
            cout << "Shtrassen: result = "<<shtrassen.multiply(bigX, bigY).toString() << endl;
        }
    } else {
        cout << "Unsupported yet!!!" << endl;
    }
}

void dispatchRequest(int input) {
    if ((1 <= input && input <= 4) || input == 6) {
        handleBinaryOperation(input);
    }else{
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
//    InverseKuk inverseKuk;
//    int number = 34;
//    double inversed = inverseKuk.getInverse(number);
//    cout << "inversed = "<< inversed << endl;
//    cout << "inversed * number = " <<number * inversed<<endl;
    app();
    return 0;
}

