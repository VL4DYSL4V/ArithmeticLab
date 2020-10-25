#include "ToomKuk.h"
#include "BigIntegerUtils.h"
#include "Karazuba.h"
#include "Shtrassen.h"
#include <iostream>

ToomKuk::ToomKuk() {
}

ToomKuk::ToomKuk(const ToomKuk &orig) {
}

ToomKuk::~ToomKuk() {
}

BigInteger ToomKuk::multiply(BigInteger x, BigInteger y) {
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
    BigInteger out("0");

    BigIntegerUtils::equalize(valueX, valueY);
    BigIntegerUtils::makeLengthMultiple(valueX, 3);
    BigIntegerUtils::makeLengthMultiple(valueY, 3);
    std::list<BigInteger> partsX = BigIntegerUtils::getEqualParts(BigInteger(valueX), 3);
    std::list<BigInteger> partsY = BigIntegerUtils::getEqualParts(BigInteger(valueY), 3);

    int exponentOfTen = std::max(valueX.length(), valueY.length()) / 3;

    BigInteger x2 = getAPart(partsX, 0);
    BigInteger x1 = getAPart(partsX, 1);
    BigInteger x0 = getAPart(partsX, 2);

    BigInteger y2 = getAPart(partsY, 0);
    BigInteger y1 = getAPart(partsY, 1);
    BigInteger y0 = getAPart(partsY, 2);
    std::list<BigInteger> omegas = getOmegas(x2, x1, x0, y2, y1, y0);
    out = getResult(omegas, exponentOfTen);
    bool isNegative = (x.isNegative() && !y.isNegative()) || (!x.isNegative() && y.isNegative());
    out.setNegative(isNegative);
    return out;
}

BigInteger ToomKuk::getAPart(std::list<BigInteger> parts, int index) {
    auto iter = parts.begin();
    for (int i = 0; i < index; i++) {
        iter++;
    }
    return *iter;
}

std::list<BigInteger> ToomKuk::getOmegas(BigInteger x2, BigInteger x1, BigInteger x0,
                                         BigInteger y2, BigInteger y1, BigInteger y0) {
    std::list<BigInteger> out;
    Shtrassen modular;

    BigInteger w0 = modular.multiply(x0, y0);
    BigInteger w4 = modular.multiply(x2, y2);

    BigInteger alpha_1 = modular.multiply(x2 + x1 + x0, y2 + y1 + y0);
    BigInteger alpha_2 = modular.multiply(x2 - x1 + x0, y2 - y1 + y0);

    BigInteger x2Mul4 = modular.multiply(BigInteger("4"), x2);
    BigInteger x1Mul2 = modular.multiply(BigInteger("2"), x1);
    BigInteger y2Mul4 = modular.multiply(BigInteger("4"), y2);
    BigInteger y1Mul2 = modular.multiply(BigInteger("2"), y1);

    BigInteger alpha_3 = modular.multiply(x2Mul4 + x1Mul2 + x0, y2Mul4 + y1Mul2 + y0);

    BigInteger sum_w4_w0 = w4 + w0;

    BigInteger f_0 = alpha_1 - sum_w4_w0;
    BigInteger f_1 = alpha_2 - sum_w4_w0;
    BigInteger f_2 = BigIntegerUtils::naiveDivision(alpha_3 - modular.multiply(BigInteger("16"), w4) - w0, BigInteger("2"));

    BigInteger sum_f1_f0 = f_0 + f_1;
    BigInteger sum_f1_f2 = f_1 + f_2;

    BigInteger w1 = f_0 - BigIntegerUtils::naiveDivision(sum_f1_f2, BigInteger("3"));
    BigInteger w2 = BigIntegerUtils::naiveDivision(sum_f1_f0, BigInteger("2"));
    BigInteger w3 = f_0 - w2 - w1;
//    std::cout<<"x 2 =" <<x2.toString()<<std::endl;
//    std::cout<<"x 1 =" <<x1.toString()<<std::endl;
//    std::cout<<"x 0 =" <<x0.toString()<<std::endl;
//    std::cout<<"y 2 =" <<y2.toString()<<std::endl;
//    std::cout<<"y 1 =" <<y1.toString()<<std::endl;
//    std::cout<<"y 0 =" <<y0.toString()<<std::endl;
//    std::cout<<"alpha 0 =" <<w0.toString()<<std::endl;
//    std::cout<<"alpha 1 =" <<alpha_1.toString()<<std::endl;
//    std::cout<<"alpha 2 =" <<alpha_2.toString()<<std::endl;
//    std::cout<<"alpha 3 =" <<alpha_3.toString()<<std::endl;
//    std::cout<<"alpha 4 =" <<w4.toString()<<std::endl;
//    std::cout<<"f 0 =" <<f_0.toString()<<std::endl;
//    std::cout<<"f 1 =" <<f_1.toString()<<std::endl;
//    std::cout<<"f 2 =" <<f_2.toString()<<std::endl;
//    std::cout<<"w 0 =" <<w0.toString()<<std::endl;
//    std::cout<<"w 1 =" <<w1.toString()<<std::endl;
//    std::cout<<"w 2 =" <<w2.toString()<<std::endl;
//    std::cout<<"w 3 =" <<w3.toString()<<std::endl;
//    std::cout<<"w 4 =" <<w4.toString()<<std::endl;
    out.push_back(w4);
    out.push_back(w3);
    out.push_back(w2);
    out.push_back(w1);
    out.push_back(w0);
    return out;
}

BigInteger ToomKuk::getResult(std::list<BigInteger> omegas, int shift) {
    BigInteger w4 = BigIntegerUtils::multiplyByTenInExponent(getAPart(omegas, 0), 4 * shift);
    BigInteger w3 = BigIntegerUtils::multiplyByTenInExponent(getAPart(omegas, 1), 3 * shift);
    BigInteger w2 = BigIntegerUtils::multiplyByTenInExponent(getAPart(omegas, 2), 2 * shift);
    BigInteger w1 = BigIntegerUtils::multiplyByTenInExponent(getAPart(omegas, 3), shift);
    BigInteger w0 = getAPart(omegas, 4);
    return w4 + w3 + w2 + w1 + w0;
}

