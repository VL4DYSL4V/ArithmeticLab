#include "SquareSieve.h"
#include "math.h"
#include "IntUtils.h"

int SquareSieve::getFactor(int n) {
    if (n % 2 == 0) {
        return 2;
    } else if (n == 1) {
        return 1;
    }
    double sqrtN = sqrt(double(n));
    int sqrtN_Int = (int)sqrtN;
    if(sqrtN == sqrtN_Int){
        return sqrtN_Int;
    }
    int x = sqrtN_Int + 1;
    for (int k = 0; k < x; k++) {
        int x_plus_k = x + k;
        int y_2 = pow(x_plus_k, 2) - n;
        if (IntUtils::isSquare(y_2)) {
            return x_plus_k + (int) sqrt(double(y_2));
        }
    }
    return n;
}

