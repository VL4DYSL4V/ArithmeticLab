#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <list>

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
private:
    static BigInteger getDivisionResult(BigInteger x, BigInteger divisor);
    static BigInteger divideBySingleDigit(BigInteger x, BigInteger divisor);
    static BigInteger divideByNotSingleDigit(BigInteger x, BigInteger divisor);
    static void removeZerosInStart(std::string &s);
};

#endif /* UTILS_H */

