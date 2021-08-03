//OPTIONAL function wich checks if a point (xtemp,ytemp) doesn't have any other
//points in a circle of radius 100 around it AFTER the vectors x,y are fully
//created (it skips the point (xtemp,ytemp) while iterating on vectors x,y).
int checkdistances2(long int *x, long int *y, long int xtemp, long int ytemp, int vectorsize) {
    for (int i = 0; i < vectorsize; i++) {
        if (x[i] == -1) {
            break;
        }
        if (calcdistance(xtemp, x[i], ytemp, y[i]) > 100 || (x[i] == xtemp && y[i] == ytemp)) {
            continue;
        }
        else {
            return 0;
        }
    }
    return 1;
}

//prints the coordinates stored in the same line of two vectors x,y with the
//same length 'size' to the command prompt (for testing purposes)
void printcoords(long int *x, long int *y, int size) {
    for (int i = 0; i < size; i++) {
        printf("Coords of point %d are (%li,%li)\n", i, x[i], y[i]);
    }
}

//Prints all the connections of airport with x,y vector index 'airportindex'
//For testing purposes
void printconnections(long int *start, long int *destinations, long int *distance, long int *next, long int airportindex) {
    long int index = start[airportindex];
    do {
        printf("Airport #%li connects with airport #%li and their distance is %li\n", airportindex, destinations[index], distance[index]);
        index = next[index];
    } while (index != -1);
}

//prints a vector with length size to the command prompt (for testing purposes)
void printvector(long int *vector, int size) {
    printf("Printing Vector of size %d...\n", size);
    for (int i = 0; i < size; i++) {
        printf("%li\n", vector[i]);
    }
}
