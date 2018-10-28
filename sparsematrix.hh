#ifndef CLASS_SPARSEMATRIX
#define SPARSEMATRIX

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>    // std::find

class SparseMatrix
{
public:
  SparseMatrix(); //default construct
  SparseMatrix( int rowSize, int colSize ); //sets value of private data
  SparseMatrix( const SparseMatrix& source ); //copy constructor
  ~SparseMatrix(); //destructor

  //bool operators for matrixes
  bool operator==(const SparseMatrix& source);
  bool operator!=(const SparseMatrix& source);

  //useful operators for the class
  SparseMatrix operator+(const SparseMatrix& A);
  SparseMatrix operator*(const double a);
  SparseMatrix operator-( SparseMatrix& A);
  SparseMatrix& operator=(const SparseMatrix& source);


  int getRowSize (); //gets the number of rows
  int getColSize (); //gets the number of columns
  void addEntry ( int rowNumb, int colNumb, double newValue); //adds an entry to the matrix in the location [rowNumb][colNumb]
  double getValue (int x, int y); //return the element (x, y) of the real matrix
  void printMatrix (); //prints the matrix
  void printEntries (); //prints the entries in the order they are pushed in
  //std::vector<double> inversion ( double a, double delta, double tol);

private:
  int rowSize_; //number of rows of the matrix
  int colSize_; //number of columns of the matrix
  std::vector<std::vector<double>*>* rows_; //vector of vector: first vector is matrix, its slots are the rows, whose slots are the entries
  std::vector<std::vector<int>*>* colsInd_; //vector of vector: first vector is matrix, its slots are rows, whose entries are the column indexes

};

//multiplication by scalar. opposite order
SparseMatrix operator*(double a, SparseMatrix A);

#endif
