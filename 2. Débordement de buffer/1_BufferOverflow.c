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

// Déclarations globales/statiques (l'ordre des déclarations est important ! soit dans cet ordre, soit l'inverse)
// Static pas obligatoire mais ça force à ce que ce soit global sûr sûr
static char buffer1[10]; // Buffer de 10 caractères
static char chaine1[] = "Ceci est la chaine  1"; //A chaine avec flemme d'indiquer le nb de caracrtères, lecture/écriture
static const char chaine2[] = "Ceci est la chaine  2"; //A idem mais const : il va mettre la variable dans un autre segment, pas aligné avec ses copains
static char chaine3[] = "Ceci est la chaine  3"; //A idem
static char *pointeur1 = &(chaine2[0]); //A les chaines sont alignées mais possible que le pointeur soit ailleurs pour des raisons d'alignement, pointé sur 1er caractère de chaine 2

///////////////////////////////////////////////////////////////////////////////
void procedure_inutile(void)
{
  // Déclarations "locale au main()" (l'ordre des déclarations est important !) ets ce que alignés ?
  char buffer3[10]; // Buffer de 10 caractères
  char chaine7[] = "Ceci est la chaine  7";
  char chaine8[] = "Ceci est la chaine  8";
  char chaine9[] = "Ceci est la chaine  9";
  char *pointeur3 = &(chaine8[0]);

  // Ci-dessous "&" est utilisé pour représenter l'adresse lors des affichages
  
  puts("Affichage des 3 chaines déclarées en variables globales/statiques :"); 
  printf("&chaine7  = %p | chaine7   = %s\n", &chaine7, chaine7);
  printf("&chaine8  = %p | chaine8   = %s\n", &chaine8, chaine8);
  printf("&chaine9  = %p | chaine9   = %s\n", &chaine9, chaine9);

  // Affichage indirect de la chaîne 8 via le pointeur "pointeur3"
  printf("pointeur3 = %p | pointeur3 = %s\n", pointeur3, pointeur3);

  // Les deux lignes suivantes permettent d'éviter les hurlements du compilateur
  // concernant le fait de ne pas utiliser la variable "buffer3" :-)
  buffer3[0]='\0';
  printf("&buffer3  = %p | buffer3   = %s\n", &buffer3, buffer3);

}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
  // Déclarations "locale au main()" (l'ordre des déclarations est important !) est ce que alignés & dans le même segment ?
  //A Oui ils sont alignés avec un écart de 0x20 chacun

  //! est ce que à partir de ce groupe là on peut modifier un autre groupe (ex : procédure_inutile ?)
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

  // Affichage indirect de la chaîne 2 via le pointeur "pointeur1"
  printf("pointeur1 = %p | pointeur1 = %s\n", pointeur1, pointeur1);
  
  // Tentative de modification de la chaîne 2 via un pointeur :
  // Essayez la ligne suivante +/- en laissant const devant la déclaration de la chaine2
  // *pointeur1 = 'Z';
  // ==> Est-ce que cela donne une erreur de compilation ou une erreur à l'exécution ? 

  //A ERREUR D'ÉXÉCUTION  Segmentation Fault: Puisque le pointeur n'est pas const le compilateur n'empêche pas, mais comme il pointe vers un const ça bug après
  //A si on enlève le const ça fonctionne sans problème
 
  puts("\nModification de 2 chaines en même temps :");
  chaine1[19] = chaine3[19] = '-';
  // Question : Est-ce encore possible si je déclare les 3 chaines en << static const >> ?

  //A NON car ce sont des consts donc read only, le compilateur refuse la modification


  // Affichage des 3 chaines déclarées en variables globales/statiques
  printf("&chaine1  = %p | chaine1   = %s\n", &chaine1, chaine1);
  printf("&chaine2  = %p | chaine2   = %s\n", &chaine2, chaine2);
  printf("&chaine3  = %p | chaine3   = %s\n", &chaine3, chaine3);

  puts("\nPetit remplissage du tableau \"buffer1\" avec un débordement de buffer :");
  // -> par valeur inférieure (car ici -55 est < 0 qui est la limite inf du buffer)
  // -> et/ou par valeur supérieure (car ici 9 est la valeur supérieure (si \0 non ajouté) et 30 > 9)
  // Question : jusque quelles valeurs (inférieure / supérieure pouvez vous aller sans provoquer d'erreur de segmentation) ?
  // Pourquoi ces valeurs ?

  //A avec les valeurs actuelles, jusqu'à -19 en inférieur : dans l'exemple la variable la plus proche dessous est chaine3, il y a 0x28 de différence, sachant que chaine3 à 22 charactères (21 + le /0) soit 0x16, cela veut dire que on peut aller jusqu'à 0x68 - 0x40 - 0x16 = 0x12 soit en décimal 18 sans écraser. à partir de -19 on écrase le /0 et la chaine affiche alors aussi le contenu de buffer1
  //A en supérieur : 3990 inclus, après ça on a un segmentation fault.

  // Que se passe-t'il si nous enlevons le "const" devant la déclaration de chaine2

  //A L'adresse de chaine2 change, elle devient alignée avec chaine1 et chaine3 (0x20 d'écart) et le pointeur1 aussi change d'adresse (il est plus loin). On peut donc l'écraser aussi

  for (int i=-19; i<=10; i++)
    buffer1[i] = 65+(i&63);

  printf("&buffer1  = %p | buffer1   = %s\n", &buffer1, buffer1);
  
  // Affichage des 3 chaines déclarées en variables globales/statiques
  printf("&chaine1  = %p | chaine1   = %s\n", &chaine1, chaine1);
  printf("&chaine2  = %p | chaine2   = %s\n", &chaine2, chaine2);
  printf("&chaine3  = %p | chaine3   = %s\n", &chaine3, chaine3);

  // Affichage de la zone "écrasée" par le remplissage du buffer,
  // y-compris la/les zone(s) où ça a "débordé"...
  printf("&deadzone = %p | deadzone  = %s\n\n", &(buffer1[-55]), &(buffer1[-55]));
  //A ça affiche le débordement inférieur mais aussi le contenu de buffer1 puisque l'on a aussi écrasé le /0 donc il ne s'arrête pas de lire avant de voir celui du buffer1

  // Etes-vous convaincus de l'utilité de "const" pour les chaines statiques/constantes ?
  //A Pas vraiment : ça évite de les écraser par erreur mais si on a un débordement de buffer ça ne protège pas du tout, on peut très bien écraser une chaine const

  // ATTENTION : l'ordre des déclarations de buffer1, chaine1, chaine2, chaine3 est important
  // --> Vous pouvez vérifier +/- en modifiant l'ordre + regardez les adresses !

  //A Effectivement l'ordre est important, si on inverse l'ordre des déclarations, le buffer1 se retrouve au dessus des chaines et on peut écraser chaine1 aussi

  // Question : est-ce le même comportement pour buffer2, chaine4, chaine5, chaine6 ?
  // [n'oubliez pas de tester +/- avec "const"]

  //A Si je met un const devant chaine4 ou chaine5 cependant, on ne constate pas de différence elles sont toujours alignées avec 0x20 d'écart. 

  // Voici le début du code... à vous d'écrire et tester le reste...

  puts("Affichage des 3 chaines déclarées en \"locale au main()\" :");
  printf("&chaine4  = %p | chaine4   = %s\n", &chaine4, chaine4);
  printf("&chaine5  = %p | chaine5   = %s\n", &chaine5, chaine5);
  printf("&chaine6  = %p | chaine6   = %s\n", &chaine6, chaine6);

  // Affichage indirect de la chaîne 5 via le pointeur "pointeur2"
  printf("pointeur2 = %p | pointeur2 = %s\n", pointeur2, pointeur2);

  // Les deux lignes suivantes permettent d'éviter les hurlements du compilateur
  // concernant le fait de ne pas utiliser la variable "buffer2" :-)
  buffer2[0]='\0';
  printf("&buffer2  = %p | buffer2   = %s\n", &buffer2, buffer2);

  // Question : comment (dans quel ordre, dans quelle(s) zone(s) mémoire sont stockées
  // les variables (ici les chaînes de caractères & buffer) selon qu'elles sont
  // sous forme de déclarations globales/statiques ou dans le main() ?

  //A Dans le cas où elles sont globales/statiques, elles sont dans le segment data qui est situé dans des adresses basses et dans le cas où elles sont locales elles sont dans la pile (stack) comme pour main où elles sont donc placées dans les adresses hautes. 
  //A EN théorie ça devrait faire :

  // ADRESSES HAUTES
  // ------
  // Stack (main) (buffer2, chaine4, chaine5, chaine6, pointeur2)
  // STack (procedure_inutile) (buffer3, chaine7, chaine8, chaine9, pointeur3)
  // ------
  // DU VIDE
  // ------
  // Heap
  // ------
  // BSS (buffer1)
  // ------
  // Data (chaine1, chaine2, chaine3, pointeur1)
  // ------ 
  // Texte
  // ------
  // ADRESSES BASSES

  //A dans data sont les variables initialisées au démmarage, BSS les non initialisées (buffer1), et chaque stack à ses propres variables locales (main & procedure_inutile)

  // Avons-nous le même comportement pour les chaînes 7, 8, 9 dans
  // la "procedure_inutile()" ?

  //A Dans le cas de procedure_inutile elles sont aussi dans la pile (stack) mais dessous main. Après recherche c'est parce que chaque appel de fonction crée un nouveau stack qui est empilé sur le précédent. Donc procedure_inutile a son propre stack en dessous de celui de main.

  procedure_inutile();

  // Que faut-il en déduire de l'ordre de stockage en mémoire des variables ?
  // Quel est l'impact d'utiliser le mot-clef "const" ?

  //A L'ordre de stockage est important car si on a un débordement de buffer on peut écraser des variables proches. 
  //A Pour const sur les variables globales/statiques ça les met dans un segment différent dans les adresses basses, séparées des autres. Mais pour les variables locales ça ne change rien (excepté qu'on ne peut pas les modifier dans le code)

  // Sur *MA* machine, si je remplace la boucle de remplissage du buffer1 par
  // for (int i=-55; i<=3000; i++)
  // cela continue de fonctionner sans "plantage" du code,
  // mais si je passe à celle ci
  // for (int i=-55; i<=4000; i++)
  // alors j'ai une erreur de segmentation... !!!
  // Et sur vos machines ?
  // Pourquoi ai-je ce genre de comportement sur ma machine
  // (et peut être sur les votres) ?

  //A L'erreur de segmentation indique que l'on a tenté d'écrire sur une zone mémoire protégée. 

  // J'espère qu'avec cet exemple de code, vous en saurez plus sur les débordements
  // de buffer et ce qu'il est possible (ou pas) de faire +/- en provoquant
  // une erreur de segmentation :-) ...

  // ------------------------------

  //A essayons de faire un débordement sur chaine4 qui est dessous buffer2, et chaine 5 et 6

  for (int i=-40; i<=10; i++)
    buffer2[i] = 65+(i&63);

  printf("&buffer2  = %p | buffer2   = %s\n", &buffer2, buffer2);
  printf("&deadzone = %p | deadzone  = %s\n\n", &(buffer2[-40]), &(buffer2[-40]));
  printf("&chaine4  = %p | chaine4   = %s\n", &chaine4, chaine4);
  printf("&chaine5  = %p | chaine5   = %s\n", &chaine5, chaine5);
  printf("&chaine6  = %p | chaine6   = %s\n", &chaine6, chaine6);

  //A on réussi ! elles sont toutes à la suite donc c'est simple, même dans main ça marche 
  //A Est ce qu'on peut écraser une variable locale d'une autre fonction ? Essayons de mettre buffer2 dans chaine7

  // for (int i=-200; i<=10; i++)
  //   buffer2[i] = 65+(i&63);

  // printf("&buffer2  = %p | buffer2   = %s\n", &buffer2, buffer2);
  // procedure_inutile();

  //A ça ne marche pas ; les variables de procedure_inutile sont dans un autre stack, créé à chaque appel de la fonction, donc on ne peut pas y accéder depuis main
  //A Testons alloca maintenant voir où ça se place

  char *buffer4 = alloca(200);
  printf("&buffer4  = %p | buffer4   = %s\n", &buffer4, buffer4);

  //A Regardons si on peut écraser chaine6 qui est dessous buffer4
  for (int i=-30; i<=301; i++) {
    buffer4[i] = 65+(i&63);
  }
    

  buffer4[301] = '\0';
  printf("&buffer4  = %p | buffer4   = %s\n", &buffer4, buffer4);
    printf("&chaine6  = %p | chaine6   = %s\n", &chaine6, chaine6);

  //A les résultats sont aléatoires : en effet il arrive un moment où la boucle efface le pointeur buffer4 lui même, et le fait donc écrire ailleurs en mémoire, donc le contenu affiché est aléatoire. Parfois on écrase chaine6, parfois pas.

  return 0;
}