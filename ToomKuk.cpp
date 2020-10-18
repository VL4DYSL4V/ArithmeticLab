#include "ToomKuk.h"
#include "Utils.h"
#include "Karazuba.h"
#include <iostream>
#include <complex>

ToomKuk::ToomKuk() {
}

ToomKuk::ToomKuk(const ToomKuk& orig) {
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
        return Utils::naiveMultiplying(x, y);
    }
    BigInteger out("0");

    Utils::equalize(valueX, valueY);
    Utils::makeLengthMultiple(valueX, 3);
    Utils::makeLengthMultiple(valueY, 3);
    std::list<BigInteger> partsX = Utils::getEqualParts(BigInteger(valueX), 3);
    std::list<BigInteger> partsY = Utils::getEqualParts(BigInteger(valueY), 3);

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
    Karazuba karazuba;

    BigInteger w0 = karazuba.multiply(x0, y0);
    BigInteger w4 = karazuba.multiply(x2, y2);

    BigInteger f2 = karazuba.multiply(x2 + x1 + x0, y2 + y1 + y0);
    BigInteger f3 = karazuba.multiply(x2 - x1 + x0, y2 - y1 + y0);

    BigInteger w2 = Utils::naiveDivision(f2 + f3, BigInteger("2")) - w0 - w4;

    BigInteger x2Mul4 = karazuba.multiply(BigInteger("4"), x2);
    BigInteger x1Mul2 = karazuba.multiply(BigInteger("2"), x1);
    BigInteger y2Mul4 = karazuba.multiply(BigInteger("4"), y2);
    BigInteger y1Mul2 = karazuba.multiply(BigInteger("2"), y1);
    BigInteger f4 = karazuba.multiply(x2Mul4 + x1Mul2 + x0, y2Mul4 + y1Mul2 + y0);
    BigInteger f2Mul2 = karazuba.multiply(BigInteger("2"), f2);
    BigInteger w4Mul14 = karazuba.multiply(w4, BigInteger("14"));

    BigInteger w2Mul2 = karazuba.multiply(w2, BigInteger("2"));
    BigInteger w3 = Utils::naiveDivision(f4 - f2Mul2 - w4Mul14 - w2Mul2 + w0, BigInteger("6"));

    BigInteger w1 = w4 - w3 + w2 + w0 - f3;

    out.push_back(w4);
    out.push_back(w3);
    out.push_back(w2);
    out.push_back(w1);
    out.push_back(w0);
    return out;
}

BigInteger ToomKuk::getResult(std::list<BigInteger> omegas, int shift) {
    BigInteger w4 = getAPart(omegas, 0).multiplyByTenInExponent((int) std::pow(shift, 4));
    BigInteger w3 = getAPart(omegas, 1).multiplyByTenInExponent((int) std::pow(shift, 3));
    BigInteger w2 = getAPart(omegas, 2).multiplyByTenInExponent((int) std::pow(shift, 2));
    BigInteger w1 = getAPart(omegas, 3).multiplyByTenInExponent(shift);
    BigInteger w0 = getAPart(omegas, 4);
    return w4 + w3 + w2 + w1 + w0;
}

