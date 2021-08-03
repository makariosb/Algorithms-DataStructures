#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRSIZE 1000 //Το μεγεθος των πινακων τυχαιων αριθμων.
#define ARR_SEED 1234567 //Random Array Seed

//Γεμιζει πινακα μεγεθους ARRSIZE στην θεση του δεικτη array με τυχαιους αριθμους στο διαστημα [-9,9]
void randarray(int *array) {
    srand(ARR_SEED);
    int temp = 0;

    for (int i = 0; i < ARRSIZE; i++) {
        *(array + i) = rand() % 10;
    }

    for (int i = 0; i < ARRSIZE; i++) {
        temp = rand() % 10;
        if (temp < 5) {
            *(array + i) *= -1;
        }
    }
}

//Εκτυπωνει τα στοιχεια πινακα (στο δεικτη array) μεγεθους ARRSIZE στο command line (Για testing σκοπους)
void printarr(int *array) {
    for (int i = 0; i < ARRSIZE; i++) {
        printf("Vector Element #%d is %d\n", i, *(array + i));
    }
}

//Αλγοριθμος ταξης N^3. Η αρχη μετρησης του χρονου ξεκινα αφου δημιουργηθουν μεταβλητες της συναρτησης.
void ordern3(int *array) {
    double xronos = 0;
    int s = 0, m = 0;
    
	clock_t t = clock();
    //Αρχη Χρονομετρησης
    for (int j = 0; j < ARRSIZE; j++) {
        for (int k = j; k < ARRSIZE; k++) {
            s = 0;
            for (int i = j; i < k; i++) {
                s += *(array + i);
            }
            if (s > m) {
                m = s;
            }
        }
    }
    //Τελος Χρονομετρησης
    t = clock() - t;
    xronos = ((double)t) / CLOCKS_PER_SEC; // σε seconds
    printf("O(N^3) found %d in %0.2f msec.\n", m, xronos * 1000);
}

//Αλγοριθμος ταξης N^2. Η αρχη μετρησης του χρονου ξεκινα αφου δημιουργηθουν μεταβλητες της συναρτησης.
void ordern2(int *array) {
    double xronos = 0;
    int s = 0, m = 0;
    int S[ARRSIZE];

    clock_t t = clock();
    //Αρχη Χρονομετρησης
    for (int i = 0; i < ARRSIZE; i++) {
        if (i == 0) {
            S[i] = *(array + i);
        }
        else {
            S[i] = S[i - 1] + *(array + i);
        }
    }

    for (int j = 0; j < ARRSIZE; j++) {
        for (int k = j; k < ARRSIZE; k++) {
            if (j == 0) {
                s = S[k];
            }
            else {
                s = S[k] - S[j - 1];
            }

            if (s > m) {
                m = s;
            }
        }
    }

    //Τελος Χρονομετρησης
    t = clock() - t;
    xronos = ((double)t) / CLOCKS_PER_SEC; // σε seconds
    printf("O(N^2) found %d in %0.2f msec.\n", m, xronos * 1000);
}

//Αλγοριθμος ταξης N. Η αρχη μετρησης του χρονου ξεκινα αφου δημιουργηθουν μεταβλητες της συναρτησης.
void ordern(int *array) {
    double xronos = 0;
    int m = 0;
    int M[ARRSIZE];

    clock_t t = clock();

    //Αρχη Χρονομετρησης
    for (int T = 0; T < ARRSIZE; T++) {
        if (T == 0) {
            M[T] = fmax(0, *(array + T));
        }
        else {
            M[T] = fmax(0, M[T - 1] + *(array + T));
        }
    }

    for (int T = 0; T < ARRSIZE; T++) {
        m = fmax(m, M[T]);
    }
    //Τελος Χρονομετρησης
    t = clock() - t;
    xronos = ((double)t) / CLOCKS_PER_SEC; // σε seconds
    printf("O(N) found %d in %0.2f msec.\n", m, xronos * 1e3);
}

int main() {
    int arr[ARRSIZE];
    randarray(arr);
    //printarr(arr);// (Για επαληθευση ορθης δημιουργιας του πινακα)
    printf("Arraysize is: %d\n", ARRSIZE);
    ordern3(arr);
    ordern2(arr);
    ordern(arr);
    printf("Done!\n");
    return 0;
}
