/*
 * encry.c
 *
 *  Created on: Apr 23, 2018
 *      Author: ragab
 */


#include "encry.h"




unsigned char display_enc_dec(){
	unsigned int which_en_de=0;
	do{
		printf("You want to do:"
			   "1- encryption, or "
			   "2- decryptioon\n");
		printf("====== ");
		scanf("%d",&which_en_de);


	}while(((which_en_de<0) || (which_en_de>2)) && printf("you have enter wrong number.\n"));
	return which_en_de;

}
unsigned char input_key(ENCRY_INFO * p , int en_or_de){
	if(en_or_de ==1){
		KeyGeneration(&p->rsakey);
		printf("------------------------------------------------------------------------------------\n");
		printf("p=%d , q=%d , n=%d ,phi_n=%d ,  e=%d ,  d=%d " , p->rsakey.p , p->rsakey.q ,p->rsakey.n , p->rsakey.phi_n ,p->rsakey.e,  p->rsakey.d );
		printf("====== ");
		FILE *tmp=fopen("key.txt" , "w");
		if(!tmp){
			printf("there an error in Writing in key.txt!!\n");
			exit(1);
		}else{
			printf("the RMA Algorithm key write to key.txt :\n");
			fprintf(tmp ,"p=%d , q=%d , n=%d ,phi_n=%d ,  e=%d ,  d=%d\n" , p->rsakey.p , p->rsakey.q ,p->rsakey.n , p->rsakey.phi_n ,p->rsakey.e,  p->rsakey.d );
			printf("the RMA Algorithm key written in key.txt  :\n");
			rewind(tmp);
			fclose(tmp);
		}

	}else{
		FILE *tmp=fopen("key.txt" , "r");
		if(!tmp){
			printf("there an error in Reading in key.txt");
			exit(1);
		}else{
			printf("the RMA Algorithm key Reading from key.txt :\n");
			fscanf(tmp ,"p=%d , q=%d , n=%d ,phi_n=%d ,  e=%d ,  d=%d\n" , &p->rsakey.p , &p->rsakey.q , &p->rsakey.n , &p->rsakey.phi_n , &p->rsakey.e,  &p->rsakey.d);
			printf("the RMA Algorithm key Read from key.txt  :\n");
			printf("p=%d , q=%d , n=%d ,phi_n=%d ,  e=%d ,  d=%d\n" , p->rsakey.p , p->rsakey.q ,p->rsakey.n , p->rsakey.phi_n ,p->rsakey.e,  p->rsakey.d );
			rewind(tmp);
			fclose(tmp);
		}

	}
	return 1;

}

unsigned char display_plain_test(){
	unsigned int which_of_input=0;
	do{
	printf("Your plain text is\n"
			"1- to be entered by the keyboard and the encrypted text will be displayed in the output screen\n"
			"2- to be entered by the keyboard and the encrypted text will be in encrypted.txt\n"
			"3- in a text file called plain.txt and the encrypted text will be in encrypted.txt\n"
			"4- in a text file called plain.txt and the encrypted text will be displayed in the output screen\n");
	printf("====== ");
	scanf("%d",&which_of_input);

	}while(((which_of_input<0) || (which_of_input>4)) && printf("you have enter wrong number.\n"));
	return which_of_input;

}

unsigned char display_encry_text(){
	unsigned int which_of_output=0;
	do{
	printf("Your encrypted text is\n"
			"1- to be entered by the keyboard and the plain text will be displayed in the output screen\n"
			"2- to be entered by the keyboard and the plain text will be in plain.txt\n"
			"3- in a text file called encrypted.txt   and the plain text will be in plain.txt\n"
			"4- in a text file called encrypted.txt   and the plain text will be displayed in the output screen\n");
	printf("====== ");
	scanf("%d",&which_of_output);

	}while(((which_of_output<0) || (which_of_output>4)) && printf("you have enter wrong number.\n"));
	return which_of_output;

}
void get_string(ENCRY_INFO *p){
	 unsigned int input;
	if(!(p->input)){
		printf("there an error in input tmpfile!!\n");
		exit(1);
	}else{
		printf("type the String and when you end type # then enter\n");
		while((input=getchar()) != '#'){
			fputc(input,p->input);
		}
		printf("the string is got it \n");
		//fputc(EOF,p->input);
		rewind(p->input);
	}
}
void encrypt_string(ENCRY_INFO *p, int en_or_de ){
	unsigned char output_from_tmpfile;
	if(en_or_de == 1){

		if(!(p->output)){
			printf("there an error in ouput tmpfile!!\n");
			exit(1);
		}else{
			printf("now we encrypet/decrypet the string \n");
			while((output_from_tmpfile =fgetc(p->input)) && (feof(p->input) == 0)){
			    unsigned char cipher ;//, value =toascii(output_from_tmpfile);
			    cipher = FindT(output_from_tmpfile, p->rsakey.e, (p->rsakey).n);
			//    printf("output_from_tmpfile=%d\tcipher=%d\n"  , output_from_tmpfile ,cipher);
				fputc((cipher),p->output);
			}
			printf("the encryption on string  done  \n");
			rewind(p->input);
			rewind(p->output);
		}
	}else{
		if(!(p->output)){
			printf("there an error in ouput tmpfile!!\n");
			exit(1);
		}else{
			printf("now we decrypet the string \n");
			while((output_from_tmpfile =fgetc(p->input)) && (feof(p->input) == 0)){
			    unsigned char decipher;//,value =toascii(output_from_tmpfile);
			    decipher = FindT(output_from_tmpfile, p->rsakey.d, p->rsakey.n);
			    //printf("output_from_tmpfile=%d\tdcipher=%d\n"  , output_from_tmpfile ,decipher);
				fputc((decipher),p->output);
			}
			printf("the decryption on string  done  \n");
			rewind(p->input);
			rewind(p->output);
		}
	}

}
void display_string(ENCRY_INFO *p, char *str){
	unsigned char display_char;
	printf("the %s string :\n" ,str);
	while((display_char =fgetc(p->output)) && (feof(p->output) == 0)){
		putchar(display_char);
	}
	printf("\n");
	rewind(p->output);
}
void write_string_infile(ENCRY_INFO *p , char *str){
	unsigned char write_char;
	FILE *tmp=fopen(str , "w");
	if(!tmp){
		printf("there an error in writefile!!\n");
		exit(1);
	}else{
		printf("the encryption string write to file now :\n");
		while((write_char =fgetc(p->output)) && (feof(p->output) == 0)){
			fputc(write_char,tmp);
		}
		printf("the encryption string written in file  :\n");
		rewind(p->output);
		rewind(tmp);
		fclose(tmp);
	}
}
void read_string_fromfile(ENCRY_INFO *p , char *str){
	unsigned char read_char;
	FILE *tmp=fopen(str , "r");
	if(!tmp){
		printf("there an error in readfile!!\n");
		exit(1);
	}else{
		printf("the  string is read from file now :\n");
		while((read_char =fgetc(tmp)) && (feof(tmp) == 0)){
			fputc(read_char,p->input);
		}
		printf("the  string read from file  done :\n");
		rewind(p->input);
		rewind(tmp);
		fclose(tmp);
	}
}

void get_information(ENCRY_INFO *p){
	p->input=tmpfile();
	p->output =tmpfile();
	/*********************************************/
	p->en_or_de   =display_enc_dec();
	input_key(p ,p->en_or_de );
	if((p->en_or_de)  == 1){
		p->plain_test =display_plain_test();
		switch ((p->plain_test)) {
			case 1:get_string(p);encrypt_string(p ,p->en_or_de);display_string(p,"encrypted");break;
			case 2:get_string(p);encrypt_string(p ,p->en_or_de);
					write_string_infile(p , "encrypted.txt");break;
			case 3:read_string_fromfile(p,"plain.txt");encrypt_string(p ,p->en_or_de);
					write_string_infile(p , "encrypted.txt");break;
			case 4:read_string_fromfile(p,"plain.txt");encrypt_string(p ,p->en_or_de);display_string(p,"encrypted");break;
		}
	}else{
		p->en_text    =display_encry_text();
		switch ((p->en_text)) {
			case 1:get_string(p);encrypt_string(p ,p->en_or_de);display_string(p,"decrypted");break;
			case 2:get_string(p);encrypt_string(p ,p->en_or_de);
					write_string_infile(p , "plain.txt");break;
			case 3:read_string_fromfile(p,"encrypted.txt");encrypt_string(p ,p->en_or_de);
					write_string_infile(p , "plain.txt");break;
			case 4:read_string_fromfile(p,"encrypted.txt");encrypt_string(p ,p->en_or_de);display_string(p,"decrypted");break;
		}
	}
	fclose(p->input);
	fclose(p->output);


}


