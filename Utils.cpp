#include "Utils.h"
#include<iostream>

Utils::Utils() {
}

Utils::Utils(const Utils& orig) {
}

Utils::~Utils() {
}

std::list<BigInteger> Utils::getEqualParts(BigInteger number, int amount) {
    std::list<BigInteger> out;
    if (amount > number.getUnsignedValue().length()) {
        out.push_back(number);
        return out;
    }
    std::string value = number.getUnsignedValue();
    makeLengthMultiple(value, amount);
    int length = value.length() / amount;
    for (int i = 0; i < amount; i++) {
        out.push_back(BigInteger(getPart(value, i, length)));
    }
    return out;
}

void Utils::equalize(std::string& valueX, std::string& valueY) {
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

void Utils::makeLengthMultiple(std::string &s, int multipleOfWhat) {
    while (s.length() % multipleOfWhat != 0) {
        s.insert(0, "0");
    }
}

std::string Utils::getPart(std::string s, int indexOfPart, int lengthOfPart) {
    if (s.length() == 1) {
        return s;
    }
    return s.substr(indexOfPart*lengthOfPart, lengthOfPart);
}

//it must be used only if nubers between -99 and 99

BigInteger Utils::naiveMultiplying(BigInteger x, BigInteger y) {
    std::string res = std::to_string(std::stoi(x.getUnsignedValue()) * std::stoi(y.getUnsignedValue()));
    BigInteger out(res);
    bool isNegative = (x.isNegative() && !y.isNegative()) || (!x.isNegative() && y.isNegative());
    out.setNegative(isNegative);
    return out;
}

BigInteger Utils::naiveDivision(BigInteger x, BigInteger divisor) {
    if (x.compareTo(divisor) == -1
            || divisor.getUnsignedValue() == "0" || x.getUnsignedValue() == "0") {
        BigInteger out("0");
        return out;
    }
    bool isNegative = (x.isNegative() && !divisor.isNegative()) || (!x.isNegative() && divisor.isNegative());

    BigInteger out = getDivisionResult(x, divisor);
    std::cout << "result = " << out.toString() << std::endl;
    out.setNegative(isNegative);
    return out;
}

BigInteger Utils::getDivisionResult(BigInteger x, BigInteger divisor) {
    if (divisor.getUnsignedValue().length() == 1) {
        return divideBySingleDigit(x, divisor);
    } else {
        return divideByNotSingleDigit(x, divisor);
    }
}

BigInteger Utils::divideBySingleDigit(BigInteger x, BigInteger divisor) {
    int r = 0;
    std::string val = x.getUnsignedValue();
    int n = val.length();
    int v = std::stoi(divisor.getUnsignedValue());
    int radix = 10;
    std::string result = "";
    for (int j = 0; j < n; j++) {
        int u = val[j] - '0';
        result.push_back(((r * radix + u) / v) + '0');
        r = (r * radix + u) % v;
    }
    removeZerosInStart(result);
    BigInteger out(result);
    return out;
}

BigInteger Utils::divideByNotSingleDigit(BigInteger x, BigInteger divisor) {
    std::string val = x.getUnsignedValue();
    std::string divVal = divisor.getUnsignedValue();
    int t = divVal.length();
    int n = val.length();
    std::string result = std::string(n - t, '0');
    BigInteger u = x;
    BigInteger v = divisor;
    BigInteger vMultipliedByTenInExp = v.multiplyByTenInExponent(n - t);
    

    return result;
}

void Utils::removeZerosInStart(std::string& s) {
    while (s.at(0) == '0') {
        s = s.substr(1);
    }
}

