#ifndef TOOMKUK_H
#define TOOMKUK_H

#include <list>
#include "BigInteger.h"


class ToomKuk {
public:
    ToomKuk();
    ToomKuk(const ToomKuk& orig);
    virtual ~ToomKuk();
    
    BigInteger multiply(BigInteger x, BigInteger y);
    
private:
    BigInteger getAPart(std::list<BigInteger> parts, int index);
    std::list<BigInteger> getOmegas(BigInteger x2, BigInteger x1, BigInteger x0,
                                    BigInteger y2, BigInteger y1, BigInteger y0);
    BigInteger getResult(std::list<BigInteger> omegas, int shift);
    
};

#endif /* TOOMKUK_H */

