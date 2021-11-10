// --------------------------------------------------------------------
// Kevin Trinh, kevatrin
// 2019 Summer CMPS101 PA2
// Matrix.h
// Contains the function prototypes for Matrx ADT
// --------------------------------------------------------------------
#ifndef _MATRIX_H_INCLUDE_
#define _MATRIX_H_INCLUDE_
#include "List.h"

static const int TRUE = 1;
static const int FALSE = 0;
typedef struct MatrixObj* Matrix;
typedef struct EntryObj* Entry;

// newEntry()
// Returns a reference to a new Entry object
Entry newEntry(int column, double value);

// equals()
// Compares the val data fields of each Entry objects and 
// returns 1 if true, 0 otherwise
int equalsEntry(Entry E, Entry x);

// printEntry()
// Prints the Entry object in (col,val) format
void printEntry(FILE* out, Entry E);

// newMatrix()
// Returns a reference to a new Matrix object in the zero state
Matrix newMatrix();

// freeMatrix
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM);

// Access Functions

// size()
// Return the size of square Matrix M.
int size(Matrix M);

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M);

// equals
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals (Matrix A, Matrix B);

// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M);

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1 <=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic Operations

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy (Matrix A);

// transpose()
// Returns a reference to a new Mtraix object representing the transpose of A.
Matrix transpose(Matrix A);

// scalarMult()
// Returns a reference to a new Matrix object representing xA
Matrix scalarMult(double x, Matrix A);

// sum()
// Returns a reference to a new Matrix object representing A+B
// Pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);

// diff()
// Returns a reference to a new Matrix object representing A-B
// Pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);

// product()
// Returns a reference to a new Matrix object representing AB
// Pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows are not printed.
// Each non-zero is represented as one line consisting of the row number, followed by a colon,
// a space, then a space separated list of pairs "(col, val)" giving the column numbers
// and non-zero values in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);

// dot
// Helper Function
// Computes product of two matrices
double dot(List P, List Q);

// listAdd
// Helper Function
// Computes the sum of two matrices
List listAdd(List P, List Q);

// listSub
// Helper Function
// Computes the difference of two matrices
List listSub(List P, List Q);
#endif

