#include "Karazuba.h"
#include<string>
#include<iostream>

Karazuba::Karazuba() {
}

Karazuba::Karazuba(const Karazuba& orig) {
}

Karazuba::~Karazuba() {
}
//Karatsuba_mul(X, Y):
//    // X, Y - целые числа длины n
//    n = max(size X, size Y)
//    if (n = 1){return X * Y}
//    X_l = левые n/2 цифр X
//    X_r = правые n/2 цифр X
//    Y_l = левые n/2 цифр Y
//    Y_r = правые n/2 цифр Y
//    Prod1 = Karatsuba_mul(X_l, Y_l)
//    Prod2 = Karatsuba_mul(X_r, Y_r)
//    Prod3 = Karatsuba_mul(X_l + X_r, Y_l + Y_r)
//    return Prod1 * 10 ^ n + (Prod3 - Prod1 - Prod2) * 10 ^ (n / 2) + Prod2

BigInteger Karazuba::multiply(BigInteger x, BigInteger y) {
    std::string valueX = x.getUnsignedValue();
    std::string valueY = y.getUnsignedValue();
    if(valueX.find_first_not_of('0') == std::string::npos || 
            valueY.find_first_not_of('0') == std::string::npos){
        return BigInteger("0");
    }
    if (valueX.length() == 1 && valueY.length() == 1) {
        return naiveMultiplying(x, y);
    } else if (valueX.length() == 2 && valueY.length() == 2) {
        return naiveMultiplying(x, y);
    }
    equalize(valueX, valueY);
    makeLengthMultipleOfTwo(valueX);
    makeLengthMultipleOfTwo(valueY);
    int exponent = std::max(valueX.length(), valueY.length());
    BigInteger leftX(getHalf(valueX, 1));
    BigInteger rightX(getHalf(valueX, 2));
    BigInteger leftY(getHalf(valueY, 1));
    BigInteger rightY(getHalf(valueY, 2));
//    std::cout << leftX.toString() << "\t|\t" << rightX.toString() << std::endl;
//    std::cout << leftY.toString() << "\t|\t" << rightY.toString() << std::endl;
    BigInteger p1 = multiply(leftX, leftY);
    BigInteger p2 = multiply(rightX, rightY);
    BigInteger p3 = multiply(leftX + rightX, leftY + rightY);

    BigInteger middle = p3 - p1 - p2;
    BigInteger result = p1.multiplyByTenInExponent(exponent)
            + middle.multiplyByTenInExponent(exponent / 2) + p2;
    return result;

}

void Karazuba::equalize(std::string &valueX, std::string &valueY) {
    if (valueX.size() == valueY.size()) {
        return;
    } else if (valueX.size() < valueY.size()) {
        do {
            valueX.insert(0, "0");
        } while (valueX.size() < valueY.size());
    } else if (valueX.size() > valueY.size()) {
        do {
            valueY.insert(0, "0");
        } while (valueX.size() > valueY.size());
    }
}

void Karazuba::makeLengthMultipleOfTwo(std::string& s) {
    if (s.length() % 2 == 0) {
        return;
    }
    s.insert(0, "0");
}

BigInteger Karazuba::naiveMultiplying(BigInteger x, BigInteger y) {
    std::string res = std::to_string(std::stoi(x.getUnsignedValue()) * std::stoi(y.getUnsignedValue()));
    BigInteger out(res);
    return out;
}

std::string Karazuba::getHalf(std::string s, int whichHalf) {
    if (s.length() == 1) {
        return s;
    }
    switch (whichHalf) {
        case 1:
            return s.substr(0, s.length() / 2);
        case 2:
            return s.substr(s.length() / 2);
    }
    return s;
}

