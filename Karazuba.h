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
    
};

#endif /* KARAZUBA_H */

