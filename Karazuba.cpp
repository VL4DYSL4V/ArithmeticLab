#include "Karazuba.h"
#include "BigIntegerUtils.h"
#include "Shtrassen.h"
#include<string>
#include<iostream>

Karazuba::Karazuba() {
}

Karazuba::Karazuba(const Karazuba &orig) {
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
    if (valueX.find_first_not_of('0') == std::string::npos ||
        valueY.find_first_not_of('0') == std::string::npos) {
        return BigInteger("0");
    }
    if ((valueX.length() == 1 || valueX.length() == 2)
        && (valueY.length() == 1 || valueY.length() == 2)) {
        return BigIntegerUtils::naiveMultiplying(x, y);
    }
    BigIntegerUtils::equalize(valueX, valueY);
    BigIntegerUtils::makeLengthMultiple(valueX, 2);
    BigIntegerUtils::makeLengthMultiple(valueY, 2);
    int exponent = std::max(valueX.length(), valueY.length());

    std::string x_l = BigIntegerUtils::getPart(valueX, 0, valueX.length() / 2);
    std::string x_r = BigIntegerUtils::getPart(valueX, 1, valueX.length() / 2);
    std::string y_l = BigIntegerUtils::getPart(valueY, 0, valueY.length() / 2);
    std::string y_r = BigIntegerUtils::getPart(valueY, 1, valueY.length() / 2);
    BigIntegerUtils::removeZerosInStart(x_l);
    BigIntegerUtils::removeZerosInStart(x_r);
    BigIntegerUtils::removeZerosInStart(y_l);
    BigIntegerUtils::removeZerosInStart(y_r);
    BigInteger leftX(x_l);
    BigInteger rightX(x_r);
    BigInteger leftY(y_l);
    BigInteger rightY(y_r);

//    BigInteger p1 = multiply(leftX, leftY);
//    BigInteger p2 = multiply(rightX, rightY);
//    BigInteger p3 = multiply(leftX + rightX, leftY + rightY);
//    std::cout<<"p1 = "<<p1.toString()<<std::endl;
//    std::cout<<"p2 = "<<p2.toString()<<std::endl;
//    std::cout<<"p3 = "<<p3.toString()<<std::endl;
//    BigInteger middle = p3 - p1 - p2;
//    BigInteger result = BigIntegerUtils::multiplyByTenInExponent(p1, exponent)
//            + BigIntegerUtils::multiplyByTenInExponent(middle, exponent / 2) + p2;

    Shtrassen modular;
    BigInteger p1 = modular.multiply(leftX, leftY);
    BigInteger p2 = modular.multiply(rightX, rightY);
    BigInteger p3 = modular.multiply(leftX + rightX, leftY + rightY);

    BigInteger middle = p3 - p1 - p2;
    BigInteger result = BigIntegerUtils::multiplyByTenInExponent(p1, exponent)
                        + BigIntegerUtils::multiplyByTenInExponent(middle, exponent / 2) + p2;
//    std::cout << "left x = " << leftX.toString() << std::endl;
//    std::cout << "left y = " << leftY.toString() << std::endl;
//    std::cout << "right x = " << rightX.toString() << std::endl;
//    std::cout << "right y = " << rightY.toString() << std::endl;
//    std::cout << "p1 = " << p1.toString() << std::endl;
//    std::cout << "p2 = " << p2.toString() << std::endl;
//    std::cout << "p3 = " << p3.toString() << std::endl;
//    std::cout << "middle = " << middle.toString() << std::endl;
//    std::cout << "exp = "<< exponent<< std::endl;
//    std::cout << "result = "<<result.toString()<< std::endl;
    bool isNegative = (x.isNegative() && !y.isNegative()) || (!x.isNegative() && y.isNegative());
    result.setNegative(isNegative);
    return result;
}

