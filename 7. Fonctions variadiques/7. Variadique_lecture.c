#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SENTINEL -1

// Additionner tous les éléments en entrées, jusqu'au SENTINEL
// Problème : pour les fonctions variadiques, les vérifications de max_arguments sont toujours faites dans le code, donc si c'est mal fait on peut avoir des comportements indéfinis
// Autre problème : le type de tous les arguments est défini par le premier argument, si on en met un autre erreur
int maximum( int first, ... ) {
    int max = first;
    va_list parametersInfos;
    va_start( parametersInfos, first );

    while( true ) {
        printf("&var_list =\t%p | var_list = %s\n", &parametersInfos, *parametersInfos);
        int current = (int) va_arg( parametersInfos, int );
        printf("&current =\t%p | current = %d\n", &current, current);
        if ( current ==  SENTINEL) break; 
        if ( current > max )
            max = current;
    }
    va_end( parametersInfos );
    return max;
}

int main() {

    // Problème : si on oublie le sentinel ?
    // On affiche tout jusqu'à atteindre un segfault, ce qui fait lire toute la pile
    printf( "%d\n", maximum( 4, 6, 5 ));
    return EXIT_SUCCESS;
}