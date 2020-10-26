#ifndef ARITHMETIC_INVERSEKUK_H
#define ARITHMETIC_INVERSEKUK_H

#include <vector>
#include <string>

class InverseKuk {

public:
    double getInverse(int number);

private:
    std::string getBinaryValueOfFractionalPart(double number);

    double doubleOf(const std::string &binaryValue);

    std::vector<int> getV(std::string binary);
};


#endif //ARITHMETIC_INVERSEKUK_H
