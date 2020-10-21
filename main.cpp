#include <cstdlib>
#include <iostream>
#include <vector>

#include "Karazuba.h"
#include "ToomKuk.h"
#include "Utils.h"
#include "Modular.h"

using namespace std;

int main(int argc, char **argv) {
    BigInteger x("46372");
    BigInteger y("1712");
    BigInteger divisor("43");

    Karazuba karazuba;
    cout << karazuba.multiply(x, y).toString() << endl;
    ToomKuk toomKuk;
    cout << toomKuk.multiply(x, y).toString() << endl;
    Modular modular;
    cout << modular.multiply(x, y).toString() << endl;

    return 0;
}

