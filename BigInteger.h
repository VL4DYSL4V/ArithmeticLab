#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <string>
class BigInteger {
public:
    BigInteger(std::string value);
    BigInteger(const BigInteger& orig);
    virtual ~BigInteger();
    
    BigInteger operator+(BigInteger another);
    BigInteger operator-(BigInteger another);
    int compareTo(BigInteger another);
    std::string toBinaryString();
    static BigInteger of(std::string binaryValue);
    
    void setNegative(bool isNegative);
    bool isNegative();
    std::string getUnsignedValue();
    std::string toString();
    
private:
    std::string value = "0";
    bool isNegativeNumber = false;
    
    std::string getAddingResult(std::string lowerModuloNumber, std::string higherModuloNumber);
    std::string getDifferResult(std::string lowerModuloNumber, std::string higherModuloNumber);
};

#endif /* BIGINTEGER_H */

