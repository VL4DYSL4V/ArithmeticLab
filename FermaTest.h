/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FermaTest.h
 * Author: владислав
 *
 * Created on 16 октября 2020 г., 17:06
 */

#ifndef FERMATEST_H
#define FERMATEST_H

class FermaTest {
public:
    FermaTest();
    FermaTest(const FermaTest& orig);
    virtual ~FermaTest();
    bool isPrime(int number, int iterationAmount);
private:
    int getRandom(int upperBound);
};

#endif /* FERMATEST_H */

