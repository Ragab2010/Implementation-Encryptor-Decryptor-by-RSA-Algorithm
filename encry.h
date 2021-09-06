/*
 * encry.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ragab
 */

#ifndef ENCRY_H_
#define ENCRY_H_

#include "stdio.h"
#include "rsa_algorithm.h"

typedef struct rules{
	unsigned char en_or_de;
	unsigned char plain_test;
	unsigned char en_text;
	RSA rsakey;
	FILE *input;//from textfile or keypord
	FILE *output;//display or textfile
}ENCRY_INFO;



void display();
unsigned char input_key(ENCRY_INFO * p , int en_or_de);
unsigned char display_plain_test();
unsigned char display_encry_text();
void get_information(ENCRY_INFO *p);
void get_string(ENCRY_INFO *p);
void encrypt_string(ENCRY_INFO *p, int en_or_de );
void write_string_infile(ENCRY_INFO *p , char *str);
void read_string_fromfile(ENCRY_INFO *p , char *str);
void display_string(ENCRY_INFO *p, char *str);



#endif /* ENCRY_H_ */
