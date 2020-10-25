#include <string>
#include <bitset>
#include <iostream>
#include "InverseKuk.h"
#include "math.h"
#include "BigIntegerUtils.h"


double InverseKuk::getInverse(int number) {
    int multiplyer = 1;
    double v = double(number);
    while (v > 1.0) {
        multiplyer *= 10;
        v /= 10;
    }
    std::string binary = getBinaryValueOfFractionalPart(v);
    BigIntegerUtils::removeZerosInStart(binary);
    std::cout<<"binary = "<<binary<<std::endl;
    int v1 = binary[0] - '0';
    int v2 = binary[1] - '0';
    int v3 = binary[2] - '0';
    double z = 0;
    std::cout<<"v = "<<v<<std::endl;
//    for (int k = 0; k < 3; k++) {
//        std::cout<<"v1 = "<< v1 <<std::endl;
//        std::cout<<"v2 = "<< v2 <<std::endl;
//        std::cout<<"v3 = "<< v3 <<std::endl;
//        z = ((double) ((int) (32 / ( 4 * v1 + 2 * v2 + v3))))/ 4;
//        std::cout<<"z = "<< z <<std::endl;
//        double zSquare = pow(z, 2);
//        std::cout<<"z square = "<< zSquare <<std::endl;
//        double vk_zSquare = v * zSquare;
//        std::cout<<"vk*z square = "<< vk_zSquare <<std::endl;
//        z = (2 * z) - vk_zSquare;
//        std::cout<< z <<std::endl;
//        double checkExpression = z / pow(2,  (-1) *(pow(2, k+1) +1)); // must be int
//        if(checkExpression != (int) checkExpression){
//            z = ((int)checkExpression + 1) * pow(2,  (-1) *(pow(2, k+1) +1));
//        }
//        std::cout<< z <<std::endl;
//    }
    return z / multiplyer;
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
    if(answer == ""){
        answer.append("0");
    }else if(answer.length() < 64){
        do{
            answer.append("0");
        }while (answer.length() < 64);
    }
    return answer;
}
