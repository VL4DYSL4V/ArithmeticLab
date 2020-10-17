#ifndef KARAZUBA_H
#define KARAZUBA_H

#include "BigInteger.h"


class Karazuba {
public:
    Karazuba();
    Karazuba(const Karazuba& orig);
    virtual ~Karazuba();
    BigInteger multiply(BigInteger x, BigInteger y);
private:
    BigInteger naiveMultiplying(BigInteger x, BigInteger y);
    void equalize(std::string &valueX, std::string &valueY);
    void makeLengthMultipleOfTwo(std::string &s);
    std::string getHalf(std::string s, int whichHalf);
};

#endif /* KARAZUBA_H */

