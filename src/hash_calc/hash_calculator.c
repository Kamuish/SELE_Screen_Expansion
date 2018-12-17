/*
 * main.c
 *
 *  Created on: 6 Dec 2017
 *      Author: Luis Abreu
 */
 
#include <stdio.h>
#include <stdlib.h>
 
int getVal(char c) // transforma ASCII EM HEX
{
    int rtVal = 0;
    if(c >= '0' && c <= '9'){
       rtVal = c - '0';
       }
   else{
       rtVal = c - 'A' + 10;
       }
    return rtVal;
}
 
int main(void)
{
    int counter=1;
    int byte=0;
    int byte2=0;
    int word=0;
    int hash = 0;
    int i = 0;      //auxilar for
    int tamanho=0;  //tamanho de cada data ( apenas para testar se estava direito)
    int nbytes=0;   //conta o numero de bytes analisados
    int nwords=0;
 
    char c;
    char useless;   // "useless"
    unsigned char high = 0x0;
    unsigned char low;
 
    FILE *file;
    file = fopen("/home/andre/eclipse-workspace/project_ICARUS/src/flash_tests/Debug/flash_tests.hex", "r");
    if (file) {
        while ( (c = getc(file)) != EOF) {
            //putchar(c);
            if(c == ':'){
                printf("\nHex row number:%d ", counter);
                counter++;
                //tamanho = (int)getc(file) ;
                high = getc(file);
                low  = getc(file);
                tamanho = (getVal(high) << 4) | getVal(low) ;
                //printf("Tamanho:%d ", tamanho);
                //depois de obter o tamanho , descarto 4 bits do endereço e + 2 do record type para chegar a data
                for(i=0 ; i < 6 ; i++){
                    useless = getc(file);
                }
                //printf("Data: ");
                for(i=0; i < (tamanho/2) ; i++){ //pega em 2 bytes , junta-os e faz um xor com a HASH;
                    high = getc(file);
                    low = getc(file);
                    //printf("Word Hex:%c%c", high , low);
                    byte = (getVal(high) << 4) | getVal(low)  ;
                    high = getc(file);
                    low = getc(file);
                    //printf("%c%c", high , low);
                    byte2 = (getVal(high) << 4) | getVal(low)  ;
                    word = (byte2 << 8) | byte ;
                    nwords++;
                    printf(" Word %d Dec:%d ",nwords,word);
                    hash = word ^ hash ;
                    nbytes=nbytes+2;
                    printf(" Hash atual: %d\n",hash);
                }
                //printf("  CheckSum: ");
                for(i=0 ; i < 1 ; i++){
                    high = getc(file);
                    low = getc(file);
                    //printf("%c%c ", high , low);
                }
                printf("Hash atual: %d\n",hash);
                printf("\n");
            }
        }
    }
    fclose(file);
    printf("Numero de bytes corridos:%d ", nbytes);
    printf("Numero de words corridos:%d ", nwords);
    printf("Hash gerada: %d",hash);
}
