#include "Utils.h"
#include "Karazuba.h"
#include<iostream>
#include <vector>

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

    int n = val.length() - 1;
    int t = divVal.length() - 1;
    std::string result = std::string(n - t + 1, '0');
    BigInteger u = x;
    BigInteger v = divisor;
    BigInteger vMultipliedByTenInExp = multiplyByTenInExponent(v, n - t);
    Karazuba karazuba;
    int vt = divVal[0] - '0';
    int vtMinus1 = divVal[1] - '0';
    int currRes = 0;
    while (u.compareTo(vMultipliedByTenInExp) != -1) {
        currRes += 1;
        u = u - vMultipliedByTenInExp;
        val = u.getUnsignedValue();
    }
    result[n - t] = currRes + '0';
    for (int i = n, j = 1; i >= t + 1; i--, j++) {
        if (val.length() - divVal.length() <= 1) {
            BigInteger searched = searchByBruteForce(u, divisor);
            int res = std::stoi(searched.getUnsignedValue());
            result[j] = res + '0';
            break;
        }
        int u_i = val[n - i] - '0';
        int u_i_1 = val[n - (i - 1)] - '0';
        int u_i_2 = val[n - (i - 2)] - '0';
        int res = (u_i >= vt) ? 9 : (u_i * 10 + u_i_1) / vt;
        std::cout << "u_i = " << u_i << " vt = " << vt << std::endl;
        while (res * (vt * 10 + vtMinus1) > u_i * 100 + u_i_1 * 10 + u_i_2) {
            res -= 1;
        }
        u = u - karazuba.multiply(BigInteger(std::to_string(res)), multiplyByTenInExponent(v, i - t - 1));
        if (u.isNegative()) {
            u = u + multiplyByTenInExponent(v, i - t - 1);
            res -= 1;
        }
        val = u.getUnsignedValue();
        result[j] = res + '0';
    }
    removeZerosInStart(result);
    return result;
}

void Utils::removeZerosInStart(std::string& s) {
    while (s.at(0) == '0') {
        s = s.substr(1);
    }
}

BigInteger Utils::searchByBruteForce(BigInteger x, BigInteger divisor) {
    BigInteger out("0");
    Karazuba karazuba;
    BigInteger diff = x - divisor;
    for (int i = 1; diff.compareTo(divisor) != -1; i++) {
        BigInteger iHolder(std::to_string(i));
        BigInteger multiplicationRes = karazuba.multiply(divisor, iHolder);
        diff = x - multiplicationRes;
        if (diff.compareTo(divisor) != 1) {
            return iHolder;
        }
    }
    return out;
}

BigInteger Utils::pow(BigInteger bigInteger, int exponent) {
    if (exponent == 0) {
        return BigInteger("1");
    }
    BigInteger out(bigInteger.getUnsignedValue());
    std::string value = bigInteger.getUnsignedValue();
    if (exponent % 2 != 0 && bigInteger.isNegative()) {
        out.setNegative(true);
    }
    Karazuba karazuba;
    for (int i = 0; i < exponent - 1; i++) {
        out = karazuba.multiply(out, value);
    }
    return out;
}

BigInteger Utils::multiplyByTenInExponent(BigInteger x, int exponent) {
    std::string result = std::string(x.getUnsignedValue());
    if(result.find_first_not_of('0') == std::string::npos){
        return BigInteger("0");
    }

    for (int i = 0; i < exponent; i++) {
        result.append("0");
    }
    BigInteger out(result);
    return out;
}

BigInteger Utils::naiveMod(BigInteger x, BigInteger divisor) {
    BigInteger divRes = naiveDivision(x, divisor);
    Karazuba karazuba;
    BigInteger mulRes = karazuba.multiply(divisor, divRes);
    return x - mulRes; 
}

std::vector<std::string> Utils::splitIntoDigits(BigInteger x) {
    std::vector<std::string> out;
    std::string value = x.getUnsignedValue();
    for(int i = 0; i < value.length(); i++){
        out.push_back(getPart(value, i, 1));
    }
    return out;
}

void Utils::insertZerosToEqualize(std::vector<std::string> &x, std::vector<std::string> &y, bool insertInStart) {
    if(x.size() == y.size()){
        return;
    }
    if(x.size() > y.size()){
        auto index = insertInStart ? y.begin() : y.end();
        while(x.size() > y.size()){
            y.insert(index,x.size() - y.size() ,"0");
        }
    }else if(y.size() > x.size()){
        auto index = insertInStart ? x.begin() : x.end();
        while(y.size() > x.size()){
            x.insert(index, y.size() - x.size(),"0");
        }
    }
    
}
