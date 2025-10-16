// Enseignement : 5A ICY 2022..2025 : Cyber-Sécurité Applicative
// Fichier      : 1_BufferOverflow.c
// Auteur       : D. Duvivier (c) 2022..2025 INSA HdF / UPHF / LAMIH
// Licence      : Code exclusivement utilisable dans le cadre des
//              : enseignements à l'INSA HdF avec l'accord de l'auteur
// Disclaimer   : (avis de non responsabilité) ce code est exclusivement
//              : utilisable dans le cadre des enseignements en Cyber-Sécurité
//              : Applicative dans le but d'illustrer quelques notions,
//              : pratiques/démarches de développement et outils utilisables
//              : pour protéger des applications logicielles
// Date         : 18/09/2024
// Objectif     : Exemples de débordement de buffer
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <strings.h>
#include <alloca.h>
#include <stdlib.h>  


// GROUPE 1 : variables globales/statiques
static char buffer1[10]; 
static char chaine1[] = "Ceci est la chaine  1"; 
static const char chaine2[] = "Ceci est la chaine  2"; 
static char chaine3[] = "Ceci est la chaine  3"; 
static char *pointeur1 = &(chaine2[0]); 

///////////////////////////////////////////////////////////////////////////////

void procedure_avec_alloca_et_calloc(void) {

// GROUPE 4 & 5 : alloca & calloc
char buffer4[10]; // Buffer de 10 caractères (dont '\0')
char *buffer5 = NULL; // Buffer 1 pour alloca
char *buffer6 = NULL; // Buffer 2 pour alloca
char *buffer7 = NULL; // Buffer 1 pour calloc
char *buffer8 = NULL; // Buffer 2 pour calloc
char chaine10[] = "Ceci_est_la_chaine_10";
const char chaine11[] = "Ceci_est_la_chaine_11";
char chaine12[] = "Ceci_est_la_chaine_12";

puts("Affichage des 3 chaines déclarées dans procedure_avec_alloca_et_calloc :");
printf("&chaine10  = %p | chaine10   = %s\n", &chaine10, chaine10);
printf("&chaine11  = %p | chaine11   = %s\n", &chaine11, chaine11);
printf("&chaine12  = %p | chaine12   = %s\n", &chaine12, chaine12);
printf("&buffer4   = %p | buffer4    = %s\n", &buffer4, buffer4);

buffer5 = alloca(200);
buffer6 = alloca(300);
buffer7 = calloc(1, 400);
buffer8 = calloc(1, 500);
printf("&buffer5   = %p | buffer5    = %p | *buffer5    = %s\n", &buffer5, buffer5, buffer5);
printf("&buffer6   = %p | buffer6    = %p | *buffer6    = %s\n", &buffer6, buffer6, buffer6);
printf("&buffer7   = %p | buffer7    = %p | *buffer7    = %s\n", &buffer7, buffer7, buffer7);
printf("&buffer8   = %p | buffer8    = %p | *buffer8    = %s\n", &buffer8, buffer8, buffer8);
}

void procedure_inutile(void)
{
  // GROUPE 3 : variables locales sur le stack (procedure_inutile)
  char buffer3[10]; // Buffer de 10 caractères
  char chaine7[] = "Ceci est la chaine  7";
  char chaine8[] = "Ceci est la chaine  8";
  char chaine9[] = "Ceci est la chaine  9";
  char *pointeur3 = &(chaine8[0]);

  puts("Affichage des 3 chaines déclarées dans procedure_inutile :"); 
  printf("&chaine7  = %p | chaine7   = %s\n", &chaine7, chaine7);
  printf("&chaine8  = %p | chaine8   = %s\n", &chaine8, chaine8);
  printf("&chaine9  = %p | chaine9   = %s\n", &chaine9, chaine9);
  printf("&pointeur3 = %p | pointeur3 = %s\n", &pointeur3, pointeur3);

  //A On essaye de faire un débordement de buffer3 dans buffer2
  // buffer3[0]='\0';
  for (int i=0; i<=5; i++)
    buffer3[i] = 65+(i&63);
  printf("&buffer3  = %p | buffer3   = %s\n", &buffer3, buffer3);

}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
  // GROUPE 2 : variables locales sur le stack (main)
  char buffer2[10]; // Buffer de 10 caractères
  char chaine4[] = "Ceci est la chaine  4";
  char chaine5[] = "Ceci est la chaine  5";
  char chaine6[] = "Ceci est la chaine  6";
  char *pointeur2 = &(chaine5[0]);

  // Ci-dessous "&" est utilisé pour représenter l'adresse lors des affichages
  
  puts("Affichage des 3 chaines déclarées en variables globales/statiques :"); 
  printf("&chaine1  = %p | chaine1   = %s\n", &chaine1, chaine1);
  printf("&chaine2  = %p | chaine2   = %s\n", &chaine2, chaine2);
  printf("&chaine3  = %p | chaine3   = %s\n", &chaine3, chaine3);
  printf("&pointer1 = %p | pointeur1 = %s\n", &pointeur1, pointeur1);
  printf("&buffer1  = %p | buffer1   = %s\n", &buffer1, buffer1);

  puts("\nAffichage des 3 chaines déclarées en \"locale au main()\" :");
  printf("&chaine4  = %p | chaine4   = %s\n", &chaine4, chaine4);
  printf("&chaine5  = %p | chaine5   = %s\n", &chaine5, chaine5);
  printf("&chaine6  = %p | chaine6   = %s\n", &chaine6, chaine6);
  printf("&pointeur2 = %p | pointeur2 = %s\n", &pointeur2, pointeur2);
  printf("&buffer2  = %p | buffer2   = %s\n", &buffer2, buffer2);

  procedure_inutile();
  procedure_avec_alloca_et_calloc();

 printf("\n==========================\n\n");

  for (int i=-19; i<=10; i++)
    buffer1[i] = 65+(i&63);

  printf("&buffer1  = %p | buffer1   = %s\n", &buffer1, buffer1);
  procedure_inutile();
  printf("&buffer2  = %p | buffer2   = %s\n", &buffer2, buffer2);
  procedure_avec_alloca_et_calloc();

  // // Affichage de la zone "écrasée" par le remplissage du buffer,
  // // y-compris la/les zone(s) où ça a "débordé"...
  printf("&deadzone = %p | deadzone  = %s\n\n", &(buffer1[-55]), &(buffer1[-55]));

  return 0;
}