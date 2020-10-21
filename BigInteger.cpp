#include <string>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "BigInteger.h"
#include "Utils.h"
#include "Karazuba.h"

BigInteger::BigInteger(std::string value) {
    std::string prefix("-");
    if (value.compare(0, prefix.size(), prefix) == 0) {
        setNegative(true);
        this->value = value.substr(1);
    } else {
        this->value = value;
    }
}

BigInteger::BigInteger(const BigInteger& orig) {
    this->value = orig.value;
    this->isNegativeNumber = orig.isNegativeNumber;
}

BigInteger::~BigInteger() {
}

BigInteger BigInteger::operator+(BigInteger another) {
    std::string anotherValue = another.getUnsignedValue();
    std::string res;
    bool isNegative = false;
    if (!this->isNegativeNumber &&!another.isNegativeNumber) {
        if (value.length() >= anotherValue.length()) {
            res = getAddingResult(anotherValue, value);
        } else {
            res = getAddingResult(value, anotherValue);
        }
    } else if (this->isNegativeNumber && another.isNegativeNumber) {
        if (value.length() >= anotherValue.length()) {
            res = getAddingResult(anotherValue, value);
        } else {
            res = getAddingResult(value, anotherValue);
        }
        isNegative = true;
    } else if (this->isNegativeNumber && !another.isNegativeNumber) {
        BigInteger posSubst(value);
        if (posSubst.compareTo(another) == -1) {
            res = getDifferResult(value, anotherValue);
        } else {
            res = getDifferResult(anotherValue, value);
            isNegative = true;
        }
    } else {
        BigInteger posSubst(anotherValue);
        if (this->compareTo(posSubst) == -1) {
            res = getDifferResult(value, anotherValue);
            isNegative = true;
        } else {
            res = getDifferResult(anotherValue, value);
        }
    }
    BigInteger result(res);
    result.setNegative(isNegative);
    return result;
}

BigInteger BigInteger::operator-(BigInteger another) {
    std::string anotherValue = another.getUnsignedValue();
    std::string res;
    bool isNegative = false;
    if (this->compareTo(another) == 0) {
        BigInteger out("0");
        return out;
    }
    if (!this->isNegativeNumber && !another.isNegativeNumber) {
        if (this->compareTo(another) == -1) {
            res = getDifferResult(value, anotherValue);
            isNegative = true;
        } else {
            res = getDifferResult(anotherValue, value);
        }
    } else if (this->isNegativeNumber && another.isNegativeNumber) {
        BigInteger positiveSubstitutionThis(value);
        BigInteger positiveSubstitutionAnoter(anotherValue);
        if (positiveSubstitutionAnoter.compareTo(positiveSubstitutionThis) == -1) {
            res = getDifferResult(anotherValue, value);
            isNegative = true;
        } else {
            res = getDifferResult(value, anotherValue);
        }
        
    } else if (this->isNegativeNumber && !another.isNegativeNumber) {
        BigInteger substitution(value);
        if (substitution.compareTo(another) == 1) {
            res = getAddingResult(anotherValue, value);
        } else {
            res = getAddingResult(value, anotherValue);
        }
        isNegative = true;
    } else {
        BigInteger positiveSubstitution(anotherValue);
        if (this->compareTo(positiveSubstitution) == -1) {
            res = getAddingResult(value, anotherValue);
        } else {
            res = getAddingResult(anotherValue, value);
        }
    }
    BigInteger result(res);
    result.setNegative(isNegative);
    return result;
}

int BigInteger::compareTo(BigInteger another) {
    if (isNegativeNumber && !another.isNegativeNumber) {
        return -1;
    } else if (!isNegativeNumber && another.isNegativeNumber) {
        return 1;
    }//Дальше числа одного знака
    int thisValLength = value.length();
    int anotherValLength = another.value.length();
    if (thisValLength == anotherValLength) {
        if (!isNegativeNumber) {
            if (value < another.value) {
                return -1;
            } else if (value > another.value) {
                return 1;
            }
        } else {
            if (value < another.value) {
                return 1;
            } else if (value > another.value) {
                return -1;
            }
        }
    } else if (thisValLength > anotherValLength) {
        if (isNegativeNumber) {
            return -1;
        } else {
            return 1;
        }
    } else {
        if (isNegativeNumber) {
            return 1;
        } else {
            return -1;
        }
    }
    if (value == another.value) {
        return 0;
    }
    return -1;
}

std::string BigInteger::getAddingResult(std::string lowerModuloNumber,
        std::string higherModuloNumber) {
    int longerLength = higherModuloNumber.length();
    int shorterLength = lowerModuloNumber.length();
    std::string res = std::string(longerLength + 1, '0');
    for (int i = 0; i < shorterLength; i++) {
        int sum = (lowerModuloNumber[shorterLength - i - 1] - '0')
                + (higherModuloNumber[longerLength - i - 1] - '0')
                + (res[res.length() - i - 1] - '0');
        res[res.length() - i - 1] = (sum % 10) + '0';
        if (sum >= 10) {
            res[res.length() - i - 2] = (sum / 10) + '0';
        }
    }
    for (int i = longerLength - shorterLength; i > 0; i--) {
        int sum = (higherModuloNumber[i - 1] - '0') + (res[i] - '0');
        res[i] = (sum % 10) + '0';
        if (sum >= 10) {
            res[i - 1] = (sum / 10) + '0';
        }
    }
    while (res[0] == '0') {
        res = res.substr(1);
    }
    return res;
}

std::string BigInteger::getDifferResult(std::string lowerModuloNumber,
        std::string higherModuloNumber) {
    int longerLength = higherModuloNumber.length();
    int shorterLength = lowerModuloNumber.length();
    std::string res = std::string(longerLength + 1, '0');
    for (int i = 0; i < shorterLength; i++) {
        int differ = (higherModuloNumber[longerLength - i - 1] - '0')
                -(lowerModuloNumber[shorterLength - i - 1] - '0')
                -(res[res.length() - i - 1] - '0');
        if (differ >= 0) {
            res[res.length() - i - 1] = differ + '0';
        } else {
            res[res.length() - i - 1] = (differ + 10) + '0';
            res[res.length() - i - 2] = '1';
        }
    }
    for (int i = longerLength - shorterLength; i > 0; i--) {
        int differ = (higherModuloNumber[i - 1] - '0') - (res[i] - '0');
        if (differ >= 0) {
            res[i] = differ + '0';
        } else {
            res[res.length() - i - 1] = (differ + 10) + '0';
            res[res.length() - i - 2] = '1';
        }
    }
    while (res[0] == '0') {
        res = res.substr(1);
    }
    return res;
}

std::string BigInteger::toBinaryString() {
    std::string out = "";
    std::string val = std::string(value);
    BigInteger divisionResult(this->value);
    BigInteger two("2");
    bool firstTimeDivisionByOne = true;
    while(val != "0" && firstTimeDivisionByOne){
        if(val == "1"){
            firstTimeDivisionByOne = false;
        }
        if((val[val.length() - 1] -'0') % 2 == 0){
            out.insert(0, "0");
        }else{
            out.insert(0, "1");
        }
        divisionResult = Utils::naiveDivision(divisionResult, two);
        val = divisionResult.value;
    }  
    return out;
}

BigInteger BigInteger::of(std::string binaryValue) {
    BigInteger out("0");
    BigInteger two("2");
    for(int i = binaryValue.length() - 1; i >= 0; i--){
        std::string bit = binaryValue.substr(i, 1);
        if(bit == "0"){
            continue;
        }
        BigInteger result = Utils::pow(two, binaryValue.length() - 1 - i);
        out = out + result;
    }    
    return out;
}

std::string BigInteger::getUnsignedValue() {
    std::string out = std::string(this->value);

    return out;
}

bool BigInteger::isNegative() {
    return isNegativeNumber;
}

void BigInteger::setNegative(bool isNegative) {

    this->isNegativeNumber = isNegative;
}

std::string BigInteger::toString() {
    std::string out = std::string(this->value);
    if (isNegativeNumber) {
        out.insert(0, "-");
    }
    return out;
}

