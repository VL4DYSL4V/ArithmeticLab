#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "FermaTest.h"

FermaTest::FermaTest() {
}

FermaTest::FermaTest(const FermaTest& orig) {
}

FermaTest::~FermaTest() {
}

int FermaTest::getRandom(int upperBound) {
    int out = rand() % upperBound;
    if(out == 0){
        out++;
    }
    return out;
}

bool FermaTest::isPrime(int number, int iterationAmount) {
    for (int i = 0; i < iterationAmount; i++) {
        int a = getRandom(number);
        

    }
    return true;
}


