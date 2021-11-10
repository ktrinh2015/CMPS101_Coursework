// -------------------------------------------------------------------------------------------
// Sparse.c
// Client for Matrix ADT

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

 int main (int argc, char* argv[]){
 FILE* in, *out;
 int n = 0, nnzA = 0, nnzB = 0;
 int i =0, j = 0, k = 0;
 double value = 0;
 Matrix A = NULL;
 Matrix B = NULL;

    if(argc != 3){
       fprintf(stderr,"Usage: %s <infile> <outfile>\n", argv[0]);
       exit(1);
    } 
 in = fopen(argv[1],"r");
 out = fopen(argv[2],"w");

    if(in == NULL){
       fprintf(stderr,"Unable to open file %s for reading\n", argv[1]);
       exit(1);
    }
    if(out == NULL){
       fprintf(stderr,"Unable to open file %s for writing\n", argv[2]);
       exit(1);
    }
 fscanf(in, "%d %d %d", &n, &nnzA, &nnzB);
    while(fscanf(in, "%d %d %lf", &i, &j, &value) != EOF){
       if(A == NULL && B == NULL){
          A = newMatrix(n);
          B = newMatrix(n);
       }
       else{
          if(k < nnzA){
              changeEntry(A, i, j, value);
              k++;
          }
          else{
             changeEntry(B, i, j, value);
          }
       }
    }
          
 fprintf(out,"A has %d non-zero entries:", NNZ(A));
 printMatrix(out,A);

 fprintf(out,"B has %d non-zero entries:", NNZ(B));
 printMatrix(out,B);

 Matrix C = scalarMult(1.5,A);
 fprintf(out,"(1.5)*A =\n");
 printMatrix(out,C);
 
 Matrix D = sum(A,B);
 fprintf(out,"A+B =\n");
 printMatrix(out,D);

 Matrix E = sum(A,A);
 fprintf(out,"A+A =\n");
 printMatrix(out,E);

 Matrix F = diff(B,A); 
 fprintf(out,"B-A =\n");
 printMatrix(out,F);

 Matrix G = transpose(A);
 fprintf(out,"Transpose(A) =\n");
 printMatrix(out,G);

 Matrix H = diff(A,A);
 fprintf(out,"A-A =\n");
 printMatrix(out,H);
 
 Matrix I = product(A,B);
 fprintf(out,"A*B =\n");
 printMatrix(out,I);

 Matrix J = product(B,B);
 fprintf(out,"B*B =\n");
 printMatrix(out,J);

 freeMatrix(&A);
 freeMatrix(&B);
 freeMatrix(&C);
 freeMatrix(&D);
 freeMatrix(&E);
 freeMatrix(&F);
 freeMatrix(&G);
 freeMatrix(&H);
 freeMatrix(&I);
 freeMatrix(&J);
 
 fclose(in);
 fclose(out);
 return 0;
 }









