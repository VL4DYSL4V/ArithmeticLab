#include <vector>
#include <string>
#include "Shtrassen.h"
#include "BigInteger.h"
#include <iostream>
#include <complex>
#include "BigIntegerUtils.h"

Shtrassen::Shtrassen() {
}

Shtrassen::Shtrassen(const Shtrassen &orig) {
}

Shtrassen::~Shtrassen() {
}

BigInteger Shtrassen::multiply(BigInteger x, BigInteger y) {
    std::vector<std::string> digitsX = BigIntegerUtils::splitIntoDigits(x);
    std::vector<std::string> digitsY = BigIntegerUtils::splitIntoDigits(y);
    BigInteger out("0");
    if (x.getUnsignedValue() == "0" || y.getUnsignedValue() == "0") {
        return out;
    }
    std::vector<std::string> coeffs = getCoefficientsOfMultiplyingResult(digitsX, digitsY);
    makePlacesCorrect(coeffs);
    out = combineToNumber(coeffs);
    bool isNegative = (x.isNegative() && !y.isNegative()) || (!x.isNegative() && y.isNegative());
    out.setNegative(isNegative);
    return out;
}

std::vector<std::string>
Shtrassen::getCoefficientsOfMultiplyingResult(std::vector<std::string> digitsX, std::vector<std::string> digitsY) {
    std::vector<std::string> out;
    for (int i = 0; i < digitsX.size(); i++) {
        for (int j = 0; j < digitsY.size(); j++) {
            int res = std::stoi(digitsX[i]) * std::stoi(digitsY[j]);
            if (out.size() <= i + j) {
                out.push_back(std::to_string(res));
            } else {
                out[i + j] = std::to_string(std::stoi(out[i + j]) + res);
            }
        }
    }
    return out;
}

void Shtrassen::makePlacesCorrect(std::vector<std::string> &target) {
    for (unsigned long i = target.size() - 1; i > 0; i--) {
        int value = std::stoi(target[i]);
        if (value > 9) {
            target[i] = std::to_string(value % 10);
            target[i - 1] = std::to_string(std::stoi(target[i - 1]) + value / 10);
        }
    }
}

BigInteger Shtrassen::combineToNumber(const std::vector<std::string>& polinom) {
    std::string value;
    for (auto & i : polinom) {
        value.append(i);
    }
    BigInteger out(value);
    return out;
}
