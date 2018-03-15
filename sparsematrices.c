#include <stdio.h>
#include <stdlib.h>
//NOTE: Mporw na allaksw se kapoia kommatia to notation *(ptr + i) se ptr[i]

//Makes an array of randomly generated numbers based on a seed. That array has
//dimensions nxn and is approximately 90% filled with zeros.
void makearray(int **arrptr, int n) {
    int temp=0;
    *arrptr = malloc(n*n*sizeof(int));
    srand(1046895);
    for (int i = 0; i < n*n; i++) {
        temp = rand() % 10 ;
        // ~10% probability for nonzero element
        if (temp<1) {
            *(*arrptr + i) = rand()%10;
        }
        else{
            *(*arrptr + i) = 0;
        }
    }
}

//prints nxn array
void printarr(int *array, int n){
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             printf("%d ", *(array + i * n  + j) );
         }
         printf("\n");
     }
}

 //counts nonzero elements of an nxn array
int countnzelements(int *array, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (*(array + i * n  + j) != 0) {
                count++;
            }
        }
    }
    printf("Number of non zero elements is: %d\n", count);
    return count;
}

//scans nxn array for nonzero elements and appends them to the sparse matrix
//vector val as well as encoding them the right way in vectors iloc and j
void extractnzelements(int * array, int *iloc, int *j, int *val, int n ,int jsize) {
    //int temp; // to test if there is at least 1 nz element in each row in loop below
    int k = 0; //to iterate on the j and val vectors

    for (int l = 0; l < n; l++) {
        *(iloc + l) = k; //stores the position of the first nonzero element of each row
        for (int c = 0; c < n; c++) {
            if ( *(array + l * n + c) != 0 ) {
                *(j + k) = c; //appends to column vector
                *(val + k) = *(array + l * n + c);//appends nonzero value to value vector
                k++;
            }
        }
    }

    //Evaluation
    if (k>jsize) {
        printf("There was an error in extraction of nonzero elements...\n" );
    }
}

//allocates the required mem space for the sparse matrix representation Vectors
//and, assuming malloc succeeds, calls the method extractnzelements to fill them
void makesparsematrix(int *array, int **iloc, int **j, int **val, int n, int jsize) {
    *iloc = malloc(n * sizeof(int) );
    *j = malloc(jsize * sizeof(int) );
    *val = malloc(jsize * sizeof(int) );

    if ( (iloc!=NULL) && (j!=NULL) && (val!=NULL) ) {
        //find nonzero elements and append them to the appropriate vector
        extractnzelements(array, *iloc, *j , *val , n , jsize);

    }
    else{
        printf("Malloc failed to allocate enough Memory Space.\n" );
    }

}

//prints a vector to the command prompt
void printvector(int *vector, int size) {
    printf("Printing Vector of size %d...\n", size );
    for (int i = 0; i < size; i++) {
        printf("%d\n", *(vector + i) );
    }
}

//prints the nonzero elements and their original position through the use of
//the sparse matrix vectors
void readsparsematrix(int *iloc, int *j, int *val, int n ) {
    int ival = 0, jval=0, valval= 0;
    int ivalnext = 0;

    for (int k = 0; k < n-1; k++) {
        ival = iloc[k];
        ivalnext = iloc[k+1] ;
        if(ivalnext>ival){
            for(int l = ival;  l < ivalnext; l++ ){
                jval = j[l];
                valval = val[l];
                printf("Non zero element in (%d,%d) is %d\n",k, jval, valval );
            }
        }
    }
}

int main() {
    int *j=NULL , *val=NULL, *iloc=NULL;
    int jsize=0, n = 10;
    int *inputarray = NULL;
    makearray(&inputarray, n);
    printarr(inputarray,n);
    jsize = countnzelements(inputarray,n);
    makesparsematrix(inputarray, &iloc, &j , &val , n, jsize );

    //Print the Sparse Matrix Vectors if possible
    if ( (iloc!=NULL) && (j!=NULL) && (val!=NULL) ) {
        printf("iloc vector is:\n");
        printvector(iloc, n);
        printf("j vector is:\n");
        printvector(j, jsize);
        printf("val vector is:\n");
        printvector(val, jsize);
    }

    readsparsematrix(iloc,j,val,n);

    free(j); free(val); free(iloc);free(inputarray);
    printf("Done!\n" );
    return 0;
}
