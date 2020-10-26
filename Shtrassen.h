#ifndef MODULAR_H
#define MODULAR_H

#include "BigInteger.h"
#include<vector>
#include <string>


class Shtrassen {
public:
    Shtrassen();
    Shtrassen(const Shtrassen& orig);
    virtual ~Shtrassen();

    BigInteger multiply(BigInteger x, BigInteger y);
private:
    std::vector<std::string> getCoefficientsOfMultiplyingResult(std::vector<std::string> digitsX,
            std::vector<std::string> digitsY);
    void makePlacesCorrect(std::vector<std::string> &target);
    BigInteger combineToNumber(const std::vector<std::string>& polinom);
};

#endif /* MODULAR_H */

