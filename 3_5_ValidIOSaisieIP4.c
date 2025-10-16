// Enseignement : 5A ICY 2022..2025 : Cyber-Sécurité Applicative
// Fichier      : 3_5_ValidIOSaisieIP4.c
// Auteur       : D. Duvivier (c) 2022..2025 INSA HdF / UPHF / LAMIH
// Licence      : Code exclusivement utilisable dans le cadre des
//              : enseignements à l'INSA HdF avec l'accord de l'auteur
// Disclaimer   : (avis de non responsabilité) ce code est exclusivement
//              : utilisable dans le cadre des enseignements en Cyber-Sécurité
//              : Applicative dans le but d'illustrer quelques notions,
//              : pratiques/démarches de développement et outils utilisables
//              : pour protéger des applications logicielles
// Date         : 24/09/2024
// Objectif     : Exemples de validation des entrées/sorties
// Projet       : Saisie d'une adresse IP v4
// version      : 1.2
// Limitations  : À vous de voir !
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// Procédure pour vider le buffer clavier (tentative naïve, non sécurisée)
//
// -> Utilise scanf en mode "glouton"
void viderbuffer(void)
{
  scanf("%*s"); // Tout ce qui est en entrée est ignoré
                // (par paquet de taille XXX caractères où XXX est la taille
                // du tampon clavier) !
                // Associé au "%s" de scanf(),
                // "*" signifie << ignorer autant de caractères que possible >>.
                // En détails : %s lit autant de caractères que possible
                // et "*" demande à scanf d'ignorer ce qui vient d'être lu
                // et de ne pas le placer dans une variable dont le pointeur
                // serait passé en argument de scanf().
                // Il est possible d'utiliser %*[^\n] pour stopper sur les
                // "retours à la ligne"
}

//////////////////////////////////////////////////////////////////////////////
// Saisie d'une adresse IP v4
//
// Passe en paramètre les 4 champs par adresse et renvoie leurs valeurs
//
void saisirIP4(int *d1, int *d2, int *d3, int *d4)
{
  int coderetour;     // Code de retour du scanf

  do
  {
    puts("Veuillez saisir une adresse IP v4");
    puts("Exemple: 192.168.0.12");
    *d1 = *d2 = *d3 = *d4 = -1;
    coderetour = scanf("%3d.%3d.%3d.%3d", d1, d2, d3, d4);
    // Ci-dessous il est possible de durcir la saisie
    // en fonction des "classes réseaux" & "masques réseaux"
    if ((coderetour != 4) ||
	(*d1 < 0) || (*d2 < 0) || (*d3 < 0) || (*d4 < 0) ||
	(*d1 > 255) || (*d2 > 255) || (*d3 > 255) || (*d4 > 255)) {
      puts("Adresse IP incorrecte");
      viderbuffer();
    }
  } while (coderetour != 4);
}



//////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROGRAMME PRINCIPAL ///////////////////////////
//////////////////////////////////////////////////////////////////////////////
int main (void)
{
  int d1, d2, d3, d4; // 4 champs de l'adresse IPv4

  saisirIP4(&d1, &d2, &d3, &d4);

  printf("Adresse IP v4 saisie = %d.%d.%d.%d\n", d1, d2, d3, d4);

  /////////////////////////////////////////////////////////////////////////////
  // Question : est-ce possible de "faire planter" ce code ? Comment ?
  // Y-a-t'il un risque "d'attente active" ?
  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
