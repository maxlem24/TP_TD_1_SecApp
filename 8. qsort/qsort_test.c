#include <stdio.h>          
#include <stdlib.h>

#define INT_ARRAY_COUNT 6
#define DOUBLE_ARRAY_COUNT 7

int intComparator ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}

int doubleComparator ( const void * first, const void * second ) {
    int firstDouble = * (const double *) first;
    int secondDouble = * (const double *) second;
    return (int) (firstDouble - secondDouble);
}

// Fonction qui affiche "yahouu"
int printYahouu() {
    printf("yahouu\n");
    return 0;
}

int main() {
    
    int intArray[] = { 10, 50, 30, 20, 40, 60 };
    double doubleArray[] = { 1.2, 6.4, 7.4, 2.9, 4.3, 5.6, 8.1 };

    qsort( intArray, INT_ARRAY_COUNT, sizeof(int), intComparator );
    qsort( doubleArray, DOUBLE_ARRAY_COUNT, sizeof(double), doubleComparator );

    for( int i=0; i<INT_ARRAY_COUNT; i++ ) {
        printf( "%u - ", intArray[i] );
    }
    printf( "\n" );

    for( int i=0; i<DOUBLE_ARRAY_COUNT; i++ ) {
        printf( "%5.2lf - ", doubleArray[i] );
    }
    printf( "\n" );

    qsort( intArray, INT_ARRAY_COUNT, sizeof(int), printYahouu );

    return 0;
}