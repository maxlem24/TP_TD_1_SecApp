#include <stdio.h>

int main(void)
{
  // Utilisation du type "char"
  char c, c1;

  puts("Débordement du type \"[signed] char\" par valeur positive > 127 (via c1 = c+1) :");
  c = 127;
  c1 = c+1;
  printf("variable  c  | %lu octet(s) : char [%c]==[%hhd]\n", sizeof(c), c, c);
  printf("variable  c1 | %lu octet(s) : char [%c]==[%hhd] ", sizeof(c1), c1, c1);
  // Si c1 (= c + 1) < c -> Débordement -> est-ce suffisant pour détecter tous les débordements en char > 127 ? 
  if (c1 < c)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");

  puts("Débordement du type \"[signed] char\" par valeur négative < -128 (via c1 = c-1) :");
  c = -128;
  c1 = c-1;
  printf("variable  c  | %lu octet(s) : char [%c]==[%hhd]\n", sizeof(c), c, c);
  printf("variable  c1 | %lu octet(s) : char [%c]==[%hhd] ", sizeof(c1), c1, c1);
  // Si c1 (= c - 1) > c -> Débordement -> est-ce suffisant pour détecter tous les débordements en char > 127 ? 
  if (c1 > c)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");

  puts("Exemple à méditer (c1 = c - 256) :");
  c = 64;
  c1 = c - 256;
  printf("variable  c  | %lu octet(s) : char [%c]==[%hhd]\n", sizeof(c), c, c);
  printf("variable  c1 | %lu octet(s) : char [%c]==[%hhd] ", sizeof(c1), c1, c1);
  if (c1 == c)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement!\n");

  puts("Limite de l'exemple précédent (c1 = 0) :");
  c = 48;
  c1 = 0;
  printf("variable c  | %lu octet(s) : char [%c]==[%hhd]\n", sizeof(c), c, c);
  printf("variable c1 | %lu octet(s) : char [%c]==[%hhd] ", sizeof(c1), c1, c1);
  if (c1 == c)
    puts("-> débordement!\n");
  else
    puts("-> pas de débordement! (Erreur) \n");

  printf("Correction des erreurs \n");
  short result;

  printf("\nAddition: \n");
  char add;
  printf("Valeur initiale [-128;127] :\n");
  scanf("%hhd",&c);
  printf("Valeur à ajouter :\n");
  scanf("%hhd",&add);

  result = (short)c + (short)add;
  printf("Resultat : %d\n",result);

  printf("variable c      | %lu octet(s) : [%hhd]\n", sizeof(c),  c);
  printf("variable add    | %lu octet(s) : [%hhd]\n", sizeof(add), add);
  printf("variable result | %lu octet(s) : [%hd]\n", sizeof(result), result);


  printf("\nSoustraction: \n");
  char sub;
  printf("Valeur initiale [-128;127] :\n");
  scanf("%hhd",&c);
  printf("Valeur à soustraire :\n");
  scanf("%hhd",&sub);

  result = (short)c - (short)sub;
  printf("Resultat : %d\n",result);

  printf("variable c      | %lu octet(s) : [%hhd]\n", sizeof(c),  c);
  printf("variable sub    | %lu octet(s) : [%hhd]\n", sizeof(sub), sub);
  printf("variable result | %lu octet(s) : [%hd]\n", sizeof(result), result);

  printf("\nMultiplication: \n");
  char mul;
  printf("Valeur initiale [-128;127] :\n");
  scanf("%hhd",&c);
  printf("Valeur à multiplier :\n");
  scanf("%hhd",&mul);

  result = (short)c * (short)mul;
  printf("Resultat : %d\n",result);

  printf("variable c      | %lu octet(s) : [%hhd]\n", sizeof(c),  c);
  printf("variable mul    | %lu octet(s) : [%hhd]\n", sizeof(mul), mul);
  printf("variable result | %lu octet(s) : [%hd]\n", sizeof(result), result);

   return 0;
}

