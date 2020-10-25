#include "FactorDicson.h"
#include "math.h"
#include "IntUtils.h"

int FactorDicson::getFactor(int n) {
    int x, xx, y, d, q, rt;
    rt = sqrt(double(n));
    if (IntUtils::isSquare(n))
        return rt;
    x = rt;
    while (x < n) {
        d = IntUtils::gcd(x, n);
        if (1 < d && d < n)
            return d;
        xx = (x * x) % n;
        if (IntUtils::isSquare(xx)) {
            y = sqrt(double(xx));
            q = (x - y) % n;
            d = IntUtils::gcd(q, n);
            if (1 < d && d < n)
                return d;
        }
        x++;
    }
    return x;
}

