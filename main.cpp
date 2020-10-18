#include <cstdlib>
#include <iostream>

#include "Karazuba.h"
#include "ToomKuk.h"
#include "Utils.h"

using namespace std;

int main(int argc, char** argv) {
    BigInteger x("125");
    BigInteger y("1044");
    BigInteger divisor("9");
    //    BigInteger res = x - y;
    //    cout<<res.getUnsignedValue()<<endl;
    //    cout<<y.getUnsignedValue()<<endl;
    //    cout << res.toString() << endl;
//    Karazuba karazuba;
//    cout << karazuba.multiply(x, y).toString() << endl;
//    ToomKuk toomKuk;
//    cout << toomKuk.multiply(x, y).toString() << endl;
    cout << Utils::naiveDivision(y, divisor).toString()<<endl;
    
    return 0;
}

