#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Roughly Europe's size is is 5300km * 4000 km
#define WX (int)5300
#define WY (int)4000
#define NUM_AIRPORTS 1000     //Number of airports (points) to generate
#define NUM_CONNECTIONS 10000 //Number of connections to generate

//initializes vector of size n with -1
void initializevector(long int *vector, int n) {
    for (int i = 0; i < n; i++) {
        vector[i] = -1;
    }
}

//returns a random 32 bit long int random number in range [0,max]
long int getrandomnumber(long int max) {
    long int p = (rand() << 15) | rand();
    p = p % (max + 1);
    return p;
}

//Returns the Eucledian distance between the points (x1,y1)
//and (x2,y2) in integer form.
long int calcdistance(long int x1, long int x2, long int y1, long int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

//Returns 1 if the distances from point (xtemp,ytemp) to every other point
//stored in vectors x,y are greater than 100.
int checkdistances(long int *x, long int *y, long int xtemp, long int ytemp, int vectorsize) {
    for (int i = 0; i < vectorsize; i++) {
        if (x[i] == -1) {
            break;
        }
        if (calcdistance(xtemp, x[i], ytemp, y[i]) > 100) {
            continue;
        }
        else {
            return 0;
        }
    }
    return 1;
}

//Creates 2 vectors (x,y) of size numberofairports which represents the
//coordinates of airports in a WX * WY grid.
void makeairports(long int **x, long int **y, int numberofairports) {
    //allocate space
    *x = malloc(numberofairports * sizeof(long int));
    *y = malloc(numberofairports * sizeof(long int));
    //for readability
    long int *xvector = *x;
    long int *yvector = *y;
    long int temp = 0, xtemp = 0, ytemp = 0; //for iterating random numbers in the grid
    initializevector(xvector, numberofairports);
    initializevector(yvector, numberofairports);

    for (int i = 0; i < numberofairports; i++) {
        temp = getrandomnumber(WX * WY - 1);
        xtemp = temp % WX;
        ytemp = temp / WY;
        while (checkdistances(xvector, yvector, xtemp, ytemp, numberofairports) != 1) {
            temp = getrandomnumber(WX * WY - 1);
            xtemp = temp % WX;
            ytemp = temp / WY;
        }
        xvector[i] = xtemp;
        yvector[i] = ytemp;
    }
}

//Makes specified number of connections between the airports in vectors x,y and
//encodes them in sparse matrix representation with vectors start,destinations,
//distance and next
void makeconnections(long int **start, long int **destinations, long int **distance, long int **next, long int *x, long int *y, int numberofconnections, int numberofairports) {
    long int p = 0;
    long int a1 = 0, a2 = 0;
    long int destindex = 0, index = 0;

    // Memory Allocation
    *start = malloc(numberofairports * sizeof(long int));
    *destinations = malloc(numberofconnections * sizeof(long int));
    *distance = malloc(numberofconnections * sizeof(long int));
    *next = malloc(numberofconnections * sizeof(long int));
    //For readability
    long int *startvector = *start;
    long int *destinationsvector = *destinations;
    long int *distancevector = *distance;
    long int *nextvector = *next;
    //Initialization of vectors with -1
    initializevector(startvector, numberofairports);
    initializevector(destinationsvector, numberofconnections);
    initializevector(distancevector, numberofconnections);
    initializevector(nextvector, numberofconnections);

    for (destindex = 0; destindex < numberofconnections; destindex++) {
        //find a random connection between 2 different airports
        do {
            p = getrandomnumber(numberofairports * numberofairports - 1);
            a1 = p % numberofairports; //start airport index
            a2 = p / numberofairports; //destination airport index
        } while (a1 == a2);            //not an element of the main diagonal (that would mean destination == start of journey)

        if (startvector[a1] == -1) {
            startvector[a1] = destindex;
        }
        else {
            index = startvector[a1];
            //Find the last used destination index position for this start airport
            while (nextvector[index] != -1) {
                index = nextvector[index];
            }
            //Append the next unused position index to the next vector
            nextvector[index] = destindex;
        }
        destinationsvector[destindex] = a2;
        distancevector[destindex] = calcdistance(x[a1], x[a2], y[a1], y[a2]);
    }
}

//For every airport that has connections this function sums the shortest
//distance among all its connections.
long int sumdistances(long int *start, long int *distance, long int *next, int numberofairports) {
    int index = 0;
    long int minimumdist = 0;
    long int total = 0;

    for (int i = 0; i < numberofairports; i++) {
        if (start[i] == -1) {
            continue;
        }

        else {
            index = start[i];
            minimumdist = distance[index];
            while (next[index] != -1) {
                index = next[index];
                if (distance[index] < minimumdist) {
                    minimumdist = distance[index];
                }
            }
        }
        total += minimumdist;
    }
    return total;
}

int main() {
    long int *x = NULL;
    long int *y = NULL;
    long int *start = NULL;
    long int *destinations = NULL;
    long int *distance = NULL;
    long int *next = NULL;
    long int total = 0;

    srand(1234567);
    makeairports(&x, &y, NUM_AIRPORTS);
    makeconnections(&start, &destinations, &distance, &next, x, y, NUM_CONNECTIONS, NUM_AIRPORTS);

    total = sumdistances(start, distance, next, NUM_AIRPORTS);
    printf("The sum of all the shortest connections for every airport is: %li km\n\n", total);
    printf("Grid size: WX = %d , WY = %d\nParameters: airports = %d , connections = %d\n", WX, WY, NUM_AIRPORTS, NUM_CONNECTIONS);
    
	free(x);
    free(y);
    free(start);
    free(destinations);
    free(distance);
    free(next);
    return 0;
}
