#include <cstdlib>
#include <iostream>

#include "Karazuba.h"

using namespace std;

int main(int argc, char** argv) {
    Karazuba karazuba;
    BigInteger x("150");
    BigInteger y("1234");
    //    BigInteger res = x - y;
    //    cout<<res.getUnsignedValue()<<endl;
    //    cout<<y.getUnsignedValue()<<endl;
    //    cout << res.toString() << endl;
    cout << karazuba.multiply(x, y).toString() << endl;
    return 0;
}

