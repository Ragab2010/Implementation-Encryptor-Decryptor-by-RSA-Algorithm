/*
 * rsa_algorithm.h
 *
 *  Created on: Sep 5, 2021
 *      Author: ragab
 */

#ifndef RSA_ALGORITHM_H_
#define RSA_ALGORITHM_H_
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
typedef struct ras{
	int p ,  q , n,  phi_n ,  e ,  d;
}RSA;


int KeyGeneration(RSA *pRas);
int gcd(int a, int b);
int inverse(int a, int b);
int PrimarityTest(int a, int i);
int FindT(int a, int m, int n);
int FastExponention(int bit, int n, int* y, int* a);



#endif /* RSA_ALGORITHM_H_ */
