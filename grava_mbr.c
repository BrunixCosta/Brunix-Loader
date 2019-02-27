//Esse é o gravador de MBR que eu fiz.Ele grava e carrega o loader.


#include <stdio.h>
#include <stdlib.h>
//#include <io.h>
#include <windows.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

FILE *arqAsm = NULL;
FILE *mbr = NULL;

unsigned char buf[512]; //A MBR tem tamanho 512


void Carrega_Bootloader() {


  

  arqAsm = fopen( "loader.bin", "r" );

  if(!arqAsm) {

  printf("Erro ao ler arquivo binario!");

  }

  fseek( arqAsm, 0, 0 );

  fread( (void*)buf, 1, 510, arqAsm ); //lemos o conteúdo do arquivo para nosso buffer

  buf[510] = 0x55; //colocamos o 0x55aa no final da MBR, pois
  buf[511] = 0xaa; //algumas BIOS precisam disso


  fclose( arqAsm );

  printf("Arquivo binario lido com sucesso!\n\n");
  printf("Tentando leitura da MBR...\n\n");

}








void Escreve_MBR() {


  mbr = fopen("\\\\.\\PhysicalDrive1", "rb+"); 

  if (!mbr) {

    printf("Problema ao tentar abrir MBR!\n\n");
    

  } else {

  printf("MBR aberta com sucesso!\n\n Fazendo leitura...\n\n");

}

  fseek( mbr, 0, SEEK_SET);


  if ( !fwrite(buf, sizeof(buf), 1, mbr) ) {

    printf("Problema ao gravar na MBR\n\n" );

  } else {

  printf("MBR gravada com sucesso!\n\n");

}

  fclose( mbr );


}



int main() {


Carrega_Bootloader();
Escreve_MBR();


return(0);

}
