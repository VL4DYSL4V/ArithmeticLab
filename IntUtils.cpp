#include <random>
#include "math.h"
#include "IntUtils.h"
#include "limits.h"

bool IntUtils::isSquare(int xx) {
    double x = sqrt(xx);
    return x == (int) x;
}

int IntUtils::gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int IntUtils::getRandom() {
    // Truly random seed.
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, std::numeric_limits<int>::max());
    return dist(rng);
}

int IntUtils::getRandom(int lowerBound, int upperBound) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(lowerBound, upperBound - 1);
    return dist(rng);
}

int IntUtils::getFactorial(int n) {
    if(n == 0){
        return 1;
    }
    return n * getFactorial(n - 1);
}
