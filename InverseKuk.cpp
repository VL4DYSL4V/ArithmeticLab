#include <string>
#include <iostream>
#include "InverseKuk.h"
#include "math.h"


double InverseKuk::getInverse(double number) {
    std::string binary = getBinaryValueOfFractionalPart(number);
    std::vector<int> vectorV = getV(binary);
    int v1 = vectorV[0];
    int v2 = vectorV[1];
    int v3 = vectorV[2];
//    std::cout << "v1 = " << v1 << std::endl;
//    std::cout << "v2 = " << v2 << std::endl;
//    std::cout << "v3 = " << v3 << std::endl;
    double z = 0;
    for (int k = 0; k < 4; k++) {
        z = ((double) ((int) (32 / (4 * v1 + 2 * v2 + v3)))) / 4;
//        std::cout << "z = " << z << std::endl;
        double zSquare = pow(z, 2);
//        std::cout << "z square = " << zSquare << std::endl;
        double vk = doubleOf(binary.substr(0, pow(2, k + 1) + 5));
//        std::cout<<"vk = "<<vk<<std::endl;
        double vk_zSquare = vk * zSquare;
//        std::cout << "vk*z square = " << vk_zSquare << std::endl;
        z = (2 * z) - vk_zSquare;
//        std::cout << z << std::endl;
        double checkExpression = z / pow(2, (-1) * (pow(2, k + 1) + 1)); // must be int
        if (checkExpression != (int) checkExpression) {
            z = ((int) checkExpression + 1) * pow(2, (-1) * (pow(2, k + 1) + 1));
        }
//        std::cout <<"z = "<< z << std::endl;
    }
    return z;
}

std::string InverseKuk::getBinaryValueOfFractionalPart(double n) {
    std::string answer;
    while (n > 0 && answer.length() < 64) {
        // Multiply n by 2 to check it 1 or 0
        double b = n * 2;
        if (b >= 1) {
            answer.append("1");
            n = b - 1;
        } else {
            answer.append("0");
            n = b;
        }
    }
    if (answer == "") {
        return "0.0";
    } else if (answer.length() < 64) {
        do {
            answer.append("0");
        } while (answer.length() < 64);
    }
    answer.insert(0, "0");
    answer.insert(1, ".");
    return answer;
}

double InverseKuk::doubleOf(const std::string &binaryValue) {
    double result = 0;
    std::string integralPart = binaryValue.substr(0, binaryValue.find('.'));
    std::string fractionalPart = binaryValue.substr(binaryValue.find('.') + 1);
    for (int i = 0; i < integralPart.length(); i++) {
        result += (integralPart[i] - '0') * pow(2, i);
    }
    for (int j = 0; j < fractionalPart.length(); j++) {
        result += (fractionalPart[j] - '0') * pow(2, (-1) * (j + 1));
    }
    return result;
}

std::vector<int> InverseKuk::getV(std::string binary) {
    std::vector<int> out;
    int index = binary.find('1');
    for (int i = 0; i < 3; i++) {
        if (index + i <= binary.length() - 1) {
            out.push_back(binary[index + i] - '0');
        } else {
            out.push_back(0);
        }
    }
    return out;
}
