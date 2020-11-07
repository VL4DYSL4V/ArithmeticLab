#include "DivisionKuk.h"
#include "InverseKuk.h"

double DivisionKuk::divide(int x, double divisor) {
    InverseKuk inverseKuk;
    return ((double) x) * inverseKuk.getInverse(divisor);
}
