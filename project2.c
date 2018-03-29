#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WX (int) 1e5
#define WY (int) 1e4
#define MAXDISTANCE 1e3

//prints a vector with length size to the command prompt (for testing purposes)
void printvector(long int *vector, int size) {
    printf("Printing Vector of size %d...\n", size );
    for (int i = 0; i < size; i++) {
        printf("%li\n", vector[i] );
    }
}

//prints the coordinates stored in the same line of two vectors x,y with the
//same length 'size' to the command prompt (for testing purposes)
void printcoords(long int *x, long int *y, int size) {
    for (int i = 0; i < size; i++) {
        printf("Coords of point %d are (%li,%li)\n",i,x[i],y[i]);
    }
}

//initializes vector of size n with -1
void initializevector(long int *vector, int n) {
    for (int i = 0; i < n; i++) {
        vector[i] = -1;
    }
}

//returns a random 32 bit long int random number in range [0,max]
long int getrandomnumber(long int max) {
    long int p = (rand() << 15) | rand();
    p =p%(max+1);
    return p;
}

// PROSOXI! Mporei na mhn epistrefei swsto long int na to koitaksw
long int calcdistance(long int x1,long int x2,long int y1,long int y2) {
    return sqrt( pow(x1-x2,2) + pow(y1-y2,2) );
}

//Returns 1 if the distances from point (xtemp,ytemp) to every other point
//stored in vectors x,y are greater than 100.
int checkdistances(long int *x,long int *y,long int xtemp,long int ytemp, int vectorsize) {
    for (int i = 0; i<vectorsize; i++) {
        if (x[i]==-1){
            break;
        }
        if(calcdistance(xtemp,x[i],ytemp,y[i]) > 100 ){
            continue;
        }
        else{
            return 0;
        }
    }
    return 1;
}

//Creates 2 vectors (x,y) of size numberofairports which represents the
//coordinates of airports in a WX * WY grid.
void makeairports(long int **x, long int **y, int numberofairports) {
    //allocate space
    *x = malloc(numberofairports * sizeof(long int) );
    *y = malloc(numberofairports * sizeof(long int) );
    //for readability/comfort
    long int *xvector = *x;
    long int *yvector = *y;
    long int temp=0, xtemp=0, ytemp=0; //for iterating random numbers in the grid
    initializevector(xvector, numberofairports);
    initializevector(yvector, numberofairports);

    for (int i = 0; i < numberofairports; i++) {
        temp = getrandomnumber(WX*WY-1);
        xtemp = temp % WX;
        ytemp = temp / WY;
        while (checkdistances(xvector,yvector,xtemp,ytemp,numberofairports) != 1) {
            temp = getrandomnumber(WX*WY-1);
            xtemp = temp % WX;
            ytemp = temp / WY;
        }
        xvector[i] = xtemp;
        yvector[i] = ytemp;
    }
}


int main() {
    long int *x = NULL;
    long int *y = NULL;
    int airports = 1000;

    srand(1046895);
    makeairports(&x,&y,airports);

    printcoords(x,y,airports);

    free(x); free(y);


    printf("wx = %d , wy = %d\n",WX,WY );

    return 0;
}
