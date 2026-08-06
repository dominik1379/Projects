#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include <ctype.h>

char* reverse(const char* text);
char* vigenere_encrypt(const char* key, const char* text);
char* vigenere_decrypt(const char* key, const char* text);
unsigned char* bit_encrypt(const char* text);
char* bit_decrypt(const unsigned char* text);
unsigned char* bmp_encrypt(const char* key, const char* text);
char* bmp_decrypt(const char* key, const unsigned char* text);

//2
char* reverse(const char* text){
if (text == NULL) 
    {
    return NULL;
    }
    char* reversed = (char*) calloc(strlen(text) + 1,sizeof(char));
    int j = 0;
    for (int i = strlen(text) - 1; i >= 0; i--, j++) {
        reversed[j] = text[i];
    reversed[j + 1] = '\0';
}
    for(int i=0;i<strlen(reversed);i++){
        reversed[i] = toupper(reversed[i]);
    }

return reversed;
}

//3
char* vigenere_encrypt(const char* key, const char* text)
{   
    if(text == NULL || key == NULL || key[0] == 0)
        return NULL;
        
    int tlen = strlen(text);
	char* cipher = (char*)calloc(tlen+1,sizeof(char));   
    int len = strlen(key);
    char* txt = (char*) calloc(tlen+1,sizeof(char));
    char* kluc = (char*) calloc(len+1,sizeof(char));

    for(int i = 0; i < strlen(text); i++){
        txt[i] = toupper(text[i]);
    }
    for(int j = 0;j < strlen(key);j++){
        kluc[j] = toupper(key[j]);

        if(kluc[j] < 'A'|| kluc[j] > 'Z')            
        {
            free(kluc);
            free(cipher);
            free(txt);
            return NULL;
        }
    }
    for (int k = 0, p = 0; k < strlen(text); k++) {
            if (txt[k] >= 'A' && txt[k] <= 'Z') {
                cipher[k] = (txt[k] - 'A' + (kluc[p % len]) - 'A') % 26 + 'A';
                p++;
            }
            else
            {
                cipher[k] = txt[k];
            }
    }
    free(txt);
    free(kluc);     

return cipher;
}
//3.2
char* vigenere_decrypt(const char* key, const char* text){

if (text == NULL || key == NULL || key[0] == 0)
        return NULL;

    int tlen = strlen(text);
    char* cipher = (char*)calloc(tlen + 1, sizeof(char));
    char* txt = (char*)calloc(tlen + 1, sizeof(char));
    int len = strlen(key);
    char* kluc = (char*)calloc(len + 1, sizeof(char));

    for (int i = 0; i < strlen(text); i++) {
        txt[i] = toupper(text[i]);
    }

    for (int j = 0; j < strlen(key); j++) {
        kluc[j] = toupper(key[j]);
        if(kluc[j] < 'A' || kluc[j] > 'Z'){
            free(txt);
            free(cipher);
            free(kluc);
            return NULL;
        }
    }
    for (int k = 0, p = 0; k < strlen(text); k++) {
        if (txt[k] >= 'A' && txt[k] <= 'Z') {
            cipher[k] = (26 + (txt[k] - 'A') - (kluc[p % len] - 'A')) % 26 + 'A';
            p++;
        }
        else {
            cipher[k] = txt[k];
        }
    }

    free(txt);
    free(kluc);

    return cipher;
}

//4
unsigned char* bit_encrypt(const char* text)
{
    if(text == NULL)
    {
        return NULL;
    }
	int newSize = strlen(text);
	unsigned char* newText = (unsigned char*)calloc(newSize + 1, sizeof(unsigned char));
	newText[newSize] = 0; // koniec retazca

	for (int i = 0; i < newSize; i++)
	{
		// H = 72 = 0100 1000

		// potrebujem: 0100 1000 -> 0100
		// vypocet:    (0100 1000 >> 4) = 0000 0100
		unsigned char left4 = text[i] >> 4;
		// potrebujem: 0100 1000 -> 1000
		// vypocet:    (0100 1000 & 0000 1111) = 0000 1000
		unsigned char right4 = text[i] & 0b00001111;

		// potrebujem: 0100 -> 01
		// vypocet:    (0000 0100 >> 2) = 0000 0001
		unsigned char left2_of_left4 = left4 >> 2; // (0000 0100 >> 2) = 0000 0001

		// potrebujem: 0100 -> 00
		// vypocet:    (0000 0100 & 0000 0011) = 0000 0000
		unsigned char right2_of_left4 = left4 & 0b00000011; // (0000 0100 & 0000 0011) = 0000 0000
        // potrebujem: 01 -> 10
		// vypocet:    ((0000 0001 >> 1) + ((0000 0001 & 0b00000001) << 1)) = 0000 0010
		unsigned char left2_of_left4Switched = (left2_of_left4 >> 1) + ((left2_of_left4 & 0b00000001) << 1); // navzajom vymenim bity

		// potrebujem: 00 -> 00
		// vypocet:    ((0000 0000 >> 1) + ((0000 0000 & 0b00000001) << 1)) = 0000 0000
		unsigned char right2_of_left4Switched = (right2_of_left4 >> 1) + ((right2_of_left4 & 0b00000001) << 1); // navzajom vymenim bity
        		// potrebujem: 10 (+) 00 -> 1000
		// vypocet:    ((0000 0010 << 2) + 0000 0000) = 0000 1000
		unsigned char left4Switched = (left2_of_left4Switched << 2) + right2_of_left4Switched;

		// potrebujem: 1000 ^ 1000 -> 0000
		// vypocet:    (0000 1000 ^ 0000 1000) = 0000 0000
		unsigned char right4Xored = left4Switched ^ right4;

		// potrebujem: 1000 (+) 1000 -> 1000 1000
		// vypocet:    (0000 1000 << 4) + 0000 1000 = 1000 1000
		newText[i] = (left4Switched << 4) + right4Xored;
        newText[i] = (left4Switched << 4) + right4Xored;
	}

	return newText;
}

//4.2
char* bit_decrypt(const unsigned char* text){

    if(text == NULL)
        return NULL;

    int newSize = strlen((char *)text);
	char* newText = (char*)calloc(newSize + 1, sizeof(char));
	newText[newSize] = 0; // koniec retazca

	for (int i = 0; i < newSize; i++)
	{
		unsigned char left4Switched = text[i] >> 4;
		unsigned char right4Xored = text[i] & 0b00001111;

		unsigned char left2_of_left4Switched = left4Switched >> 2;
        unsigned char right2_of_left4Switched = left4Switched & 0b00000011;

		unsigned char left2_of_left4 = (left2_of_left4Switched >> 1) + ((left2_of_left4Switched & 0b00000001) << 1); // navzajom vymenim bity
		unsigned char right2_of_left4 = (right2_of_left4Switched >> 1) + ((right2_of_left4Switched & 0b00000001) << 1); // navzajom vymenim bity

		unsigned char left4 = (left2_of_left4 << 2) + right2_of_left4;
		unsigned char right4 = left4Switched ^ right4Xored;
        newText[i] = (left4 << 4) + right4;
	}

	return newText;
}

//5
unsigned char* bmp_encrypt(const char* key, const char* text)
{
    if(text == NULL || key == NULL)
        return NULL;
    
    char* encrypted1 = reverse(text);
    char* encrypted2 = vigenere_encrypt(key,encrypted1);
    unsigned char* encrypted3 = bit_encrypt(encrypted2);

    free(encrypted1);
    free(encrypted2);

return encrypted3;
}
//5.2
char* bmp_decrypt(const char* key, const unsigned char* text)
{
    if(text == NULL || key == NULL)
        return NULL;
    
    char* decrypted1 = bit_decrypt(text);
    char* decrypted2 = vigenere_decrypt(key,decrypted1);
    char* decrypted3 = reverse(decrypted2);
    
    free(decrypted1);
    free(decrypted2);

return decrypted3;
}
