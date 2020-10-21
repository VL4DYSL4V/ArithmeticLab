#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <list>
#include <vector>
#include "BigInteger.h"

class Utils {
public:
    Utils();
    Utils(const Utils& orig);
    virtual ~Utils();

    static void makeLengthMultiple(std::string &s, int multipleOfWhat);
    static std::string getPart(std::string s, int indexOfPart, int lengthOfPart);
    static void equalize(std::string &valueX, std::string &valueY);
    static std::list<BigInteger> getEqualParts(BigInteger number, int amount);
    static BigInteger naiveMultiplying(BigInteger x, BigInteger y);
    static BigInteger naiveDivision(BigInteger x, BigInteger divisor);
    static BigInteger pow(BigInteger bigInteger, int exponent);
    static BigInteger multiplyByTenInExponent(BigInteger x, int exponent);
    static BigInteger naiveMod(BigInteger x, BigInteger divisor);
    static std::vector<std::string> splitIntoDigits(BigInteger x);  
    static void insertZerosToEqualize(std::vector<std::string> &x, std::vector<std::string> &y, bool insertInStart);
    
private:
    static BigInteger getDivisionResult(BigInteger x, BigInteger divisor);
    static BigInteger divideBySingleDigit(BigInteger x, BigInteger divisor);
    static BigInteger divideByNotSingleDigit(BigInteger x, BigInteger divisor);
    static BigInteger searchByBruteForce(BigInteger x, BigInteger divisor);
    static void removeZerosInStart(std::string &s);
};

#endif /* UTILS_H */

