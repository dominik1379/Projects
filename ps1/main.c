#include <stdio.h>
#include "playfair.h"
#include "bmp.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(){
    char *encrypted, *decrypted;
    unsigned char *bitEncrypted;
    char *bitDecrypted;


    encrypted = playfair_encrypt("weaver", "ixxalids");
    printf("\n");
    printf("%s", encrypted);
    //free(encrypted);

    decrypted = playfair_decrypt("weaver",encrypted);
    printf("\n%s", decrypted);
    free(decrypted);
    free(encrypted);


    printf("\n\n");
    encrypted = vigenere_encrypt("CoMPuTeR","Hello world!");
    printf("%s", encrypted);
    free(encrypted);
    
    decrypted = vigenere_decrypt("computer", "JSXAI PSINR!");
    printf("\n");
    printf("%s", decrypted);
    free(decrypted);

    printf("\n\n");
    encrypted = reverse ("Hello world!");
    printf("%s", encrypted);
    free(encrypted);
    printf("\n\n");

    bitEncrypted = bit_encrypt("Hello world!");
    for(int x = 0; x < 12; x++){
        printf("%x",bitEncrypted[x]);
    }
    bitDecrypted = bit_decrypt(bitEncrypted);
    printf("\n");
    printf("%s", bitDecrypted);
    free(bitEncrypted);
    free(bitDecrypted);


    char* key = "Computer";
    char* text = "Hello";
    bitEncrypted = bmp_encrypt(key, text);
    for(int x = 0; x < 5; x++){
        printf("%x", bitEncrypted[x]);
    }

    bitDecrypted = bmp_decrypt(key,bitEncrypted);
    free(bitEncrypted);
    printf("%s", bitDecrypted);
    free(bitDecrypted);
    printf("\n");


return 0;
}
