/*
 * rsa_algorithm.c
 *
 *  Created on: Sep 5, 2021
 *      Author: ragab
 */

#include "rsa_algorithm.h"



int gcd(int a, int b)
{
    int q, r1, r2, r;

    if (a > b)
    {
        r1 = a;
        r2 = b;
    }
    else {
        r1 = b;
        r2 = a;
    }

    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
    }

    return r1;
}

int PrimarityTest(int a, int i)
{
    int n = i - 1;
    int k = 0;
    int j, m, T;

    while (n % 2 == 0)
    {
        k++;
        n = n / 2;
    }

    m = n;
    T = FindT(a, m, i);

    if (T == 1 || T == i - 1) {
        return 1;
    }

    for (j = 0; j < k; j++)
    {
        T = FindT(T, 2, i);
        if (T == 1) {
            return 0;
        }
        if (T == i - 1) {
            return 1;
        }
    }
    return 0;
}

int FindT(int a, int m, int n)
{
    int r;
    int y = 1;

    while (m > 0)
    {
        r = m % 2;
        FastExponention(r, n, &y, &a);
        m = m / 2;
    }
    return y;
}

int FastExponention(int bit, int n, int* y, int* a)
{
    if (bit == 1) {
        *y = (*y * (*a)) % n;
    }

    *a = (*a) * (*a) % n;
    return 0;
}

int inverse(int a, int b)
{
    int inv;
    int q, r, r1 = a, r2 = b, t, t1 = 0, t2 = 1;

    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    if (r1 == 1) {
        inv = t1;
    }

    if (inv < 0) {
        inv = inv + a;
    }

    return inv;
}

int KeyGeneration(RSA *pRas)
{
	//q>7 , p>11
#define NPIMESIZE 5
	int prime[NPIMESIZE]={11, 13, 17, 19, 23};//{2, 3, 5, 7, 11};//, 13, 17, 19};
    do {
        do
        	pRas->p = prime[rand()%NPIMESIZE];
        while ((pRas->p % 2) == 0);

    } while (!PrimarityTest(2, pRas->p));

    do {
        do
        	pRas->q =prime[rand()%NPIMESIZE];
        while (pRas->q % 2 == 0);
    } while (!PrimarityTest(2, pRas->q));

    pRas->n = pRas->p * pRas->q;
    pRas->phi_n = (pRas->p - 1) * (pRas->q - 1);

    do
    	pRas->e = prime[rand()%NPIMESIZE]%(pRas->phi_n - 2) + 2; // 1 < e < phi_n
    while (gcd(pRas->e, pRas->phi_n) != 1);

    pRas->d = inverse(pRas->phi_n, pRas->e);
    return 1;

}

//
//int Encryption(int value, FILE* out)
//{
//    int cipher;
//    cipher = FindT(value, e, n);
//    fprintf(out, "%d ", cipher);
//}
//
//int Decryption(int value, FILE* out)
//{
//    int decipher;
//    decipher = FindT(value, d, n);
//    fprintf(out, "%c", decipher);
//}
//
