// Enseignement : 5A ICY 2022..2025 : Cyber-Sécurité Applicative
// Fichier      : 1_ScalarOverflow.c
// Auteur       : D. Duvivier (c) 2022..2025 INSA HdF / UPHF / LAMIH
// Licence      : Code exclusivement utilisable dans le cadre des
//              : enseignements à l'INSA HdF avec l'accord de l'auteur
// Disclaimer   : (avis de non responsabilité) ce code est exclusivement
//              : utilisable dans le cadre des enseignements en Cyber-Sécurité
//              : Applicative dans le but d'illustrer quelques notions,
//              : pratiques/démarches de développement et outils utilisables
//              : pour protéger des applications logicielles
// Date         : 18/09/2024
// Objectif     : Exemples de débordement de l'arithmétique sur les scalaires
//              : "juste" sur les additions et soustractions.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

int main(void)
{
  // Déclarations de quelques scalaires en utilisant différents types
  char c, c1; // Pas de long (cf. wchar.h & wint_t) ni short pour char
  unsigned char uc = 255, uc1 = uc+1; // Pas de long ni short pour char
  short int i1, i = 16384; // Juste pour illustrer les problèmes de transtypage
  float f = 1.0/10.0; // Juste pour illustrer les problèmes de précision
  float g = 1000000000000.0; // Juste pour illustrer les problèmes de précision

  // Ci-dessous "[valeur]_10" signifie que la valeur est affichée en base 10
  
  puts("Débordement du type \"[signed] char\" par valeur positive > 127 (via c1 = c+1) :");
  c = 127;
  c1 = c+1;
  printf("variable  c  | %lu octet(s) : char [%c]==[%hhd]_10\n", sizeof(c), c, c);
  printf("variable  c1 | %lu octet(s) : char [%c]==[%hhd]_10 ", sizeof(c1), c1, c1);
  // Si c1 (= c + 1) < c -> Débordement -> est-ce suffisant pour détecter tous les débordements en char > 127 ? 
  if (c1 < c)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");

  puts("Débordement du type \"[signed] char\" par valeur négative < -128 (via c1 = c-1) :");
  c = -128;
  c1 = c-1;
  printf("variable  c  | %lu octet(s) : char [%c]==[%hhd]_10\n", sizeof(c), c, c);
  printf("variable  c1 | %lu octet(s) : char [%c]==[%hhd]_10 ", sizeof(c1), c1, c1);
  // Si c1 (= c - 1) > c -> Débordement -> est-ce suffisant pour détecter tous les débordements en char > 127 ? 
  if (c1 > c)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");

  puts("Exemple à méditer (c1 = c - 256) :");
  c = 64;
  c1 = c - 256;
  printf("variable  c  | %lu octet(s) : char [%c]==[%hhd]_10\n", sizeof(c), c, c);
  printf("variable  c1 | %lu octet(s) : char [%c]==[%hhd]_10 ", sizeof(c1), c1, c1);
  if (c1 == c)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");
  
  puts("Débordement du type unsigned char par valeur positive > 255 (uc1 = uc+1) :");
  uc = 255;
  uc1 = uc+1;
  printf("variable uc  | %lu octet(s) : char [%c]==[%hhd]_10\n", sizeof(uc), uc, uc);
  printf("variable uc1 | %lu octet(s) : char [%c]==[%hhd]_10 ", sizeof(uc1), uc1, uc1);
  // Si uc1 (= uc + 1) < uc -> Débordement -> est-ce suffisant pour détecter tous les débordements en char > 255 ? 
  if (uc1 < uc)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");

  puts("Débordement du type unsigned char par valeur négative (< 0) (uc1 = uc-1)");
  uc = 0;
  uc1 = uc-1;
  printf("variable uc  | %lu octet(s) : char [%c]==[%hhu]_10\n", sizeof(uc), uc, uc);
  printf("variable uc1 | %lu octet(s) : char [%c]==[%hhu]_10 ", sizeof(uc1), uc1, uc1);
  // Si uc1 (= uc - 1) > uc -> Débordement -> est-ce suffisant pour détecter tous les débordements en char > 127 ? 
  if (uc1 > uc)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");

  puts("Exemple à méditer (uc1 = uc + 256) :");
  uc = 64;
  uc1 = uc + 256;
  printf("variable uc  | %lu octet(s) : char [%c]==[%hhu]_10\n", sizeof(uc), uc, uc);
  printf("variable uc1 | %lu octet(s) : char [%c]==[%hhu]_10 ", sizeof(uc1), uc1, uc1);
  if (uc1 == uc)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");

  // Indice : Je teste des différences de "1" (i.e. c1 = c +/- 1), mais puis-je détecter
  // - des différences comprises entre 1 et 63
  // - des différences comprises entre 64 et 127
  // - des différences comprises entre 128 et 255
  // - des différences comprises entre 256 et 511... ?
  
  puts("Perte de précision par transtypage incorrect (stockage impossible de 16384 dans uc) :");
  uc = (unsigned char)i;
  // i contient 16384, que vaut uc ? Pourquoi cette valeur ?
  printf("variable uc  | %lu octet(s) : char [%c]==[%hhu]_10\n\n", sizeof(uc), uc, uc);

  puts("Débordement du type \"[signed] short intt\" par valeur positive > 32767 (via i1 = i+1) :");
  i = 32767;
  i1 = i+1;
  printf("variable  i  | %lu octet(s) : short int [%hd]_10\n", sizeof(i), i);
  printf("variable  i1 | %lu octet(s) : short int [%hd]_10 ", sizeof(i1), i1);
  // Si i1 (= i + 1) < i -> Débordement -> est-ce suffisant pour détecter tous les débordements en short int > 32767 ? 
  if (i1 < i)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");
  
  puts("Perte de précision dans les calculs en float (g = 1000000000000.0; f = 1/10 * g) :");
  // Que vaut 1/10 * g ?
  f *= g;
  printf("variable  g  | %lu octet(s) : float %.2f\n", sizeof(g), g);
  printf("variable  f  | %lu octet(s) : float %.2f\n", sizeof(f), f);

  // Il existe des problèmes similaires de dépassements dans tous les types scalaires...

  // En vous répartissant le travail dans le groupe (i.e. chacun
  // choisit un ou deux types à tester de manière à "couvrir" tous les
  // exemples), testez avec ces types, s'ils existent :
  // short short int, short int, int, long int, long long int
  // short short unsigned int, short unsigned int, unsigned int, long unsigned int, long long unsigned int
  // short short float, short float, float, long float, long long float
  // short short unsigned float, short unsigned float, unsigned float, long unsigned float, long long unsigned float
  // short short double, short double, double, long double, long long double
  // short short unsigned double, short unsigned double, unsigned double, long unsigned double, long long unsigned double
  
  return 0;
}
