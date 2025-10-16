#include <string.h>
#include <stdio.h>

int main(void) {

  printf("Test de 'strcpy' et 'strncpy'\n\n");

  char src[12] = "ABCDEFGHIJK";
  char dest1[6],dest2[6],dest3[6];

  printf("Copie de même taille\n");
  src[5] = '\0';
  strcpy(dest1,src);
  printf("Source : \t %s \n",src);
  printf("Destination : \t %s \n", dest1);

  printf("\nOverflow avec strcpy\n");
  src[5] = 'F';
  strcpy(dest2,src);
  printf("Source : \t %s \n",src);
  printf("Destination : \t %s", dest2);
  if (strlen(dest2) >= 6)
    puts("\x1B[31m => Buffer Overflow ! \x1B[0m \n");
  else
    puts("\x1B[32m => Pas de dépassement \x1B[0m \n");

  printf("\nOverflow avec strncpy\n");
  strncpy(dest3,src,9);
  printf("Source : \t %s \n",src);
  printf("Destination : \t %s", dest3);
  if (strlen(dest3) >= 6)
    puts("\x1B[31m => Buffer Overflow ! \x1B[0m \n");
  else
    puts("\x1B[32m => Pas de dépassement \x1B[0m \n");

  printf("\nTest de 'strcat' et 'strncat'\n\n");

  char src2[12] = "ABCDEFGHIJK";
  char dest4[12] = "ABCDEF";
  char dest5[12] = "ABCDEF";
  char dest6[12] = "ABCDEF";

  printf("Concatenation avec bonne taille de buffer\n");
  src[5] = '\0';
  strcat(dest4,src);
  printf("Source : \t %s \n",src);
  printf("Destination : \t %s \n", dest4);

  printf("\nOverflow avec strcat\n");
  src[5] = 'F';
  strcat(dest5,src);
  printf("Source : \t %s \n",src);
  printf("Destination : \t %s", dest5);
  if (strlen(dest5) >= 12)
    puts("\x1B[31m => Buffer Overflow ! \x1B[0m \n");
  else
    puts("\x1B[32m => Pas de dépassement \x1B[0m \n");

  printf("\nOverflow avec strncat\n");
  strncat(dest6,src,9);
  printf("Source : \t %s \n",src);
  printf("Destination : \t %s", dest6);
  if (strlen(dest6) >= 12)
    puts("\x1B[31m => Buffer Overflow ! \x1B[0m \n");
  else
    puts("\x1B[32m => Pas de dépassement \x1B[0m \n");



  return 0;
}
