#include "Pollard.h"
#include "math.h"
#include "IntUtils.h"
//Floyd version
int Pollard::getFactor(int n) {
    if (n <= 3) {
        return n;
    } else if(n == 4){
        return 2;
    }
    int x = IntUtils::getRandom(1, n - 2);
    int y = 1;
    int i = 0;
    int stage = 2;
    while (IntUtils::gcd(n, abs(x - y)) == 1) {
        if (i == stage) {
            y = x;
            stage = stage * 2;
        }
        x = (x * x + 1) % n;
        i++;
    }
    return IntUtils::gcd(n, abs(x - y));
}
