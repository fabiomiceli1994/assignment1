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
  SparseMatrix operator*(const std::vector<double> v);
  SparseMatrix operator-( SparseMatrix& A);
  SparseMatrix& operator=(const SparseMatrix& source);



  int getRowSize () const; //gets the number of rows
  int getColSize () const; //gets the number of columns
  void addEntry ( int rowNumb, int colNumb, double newValue); //adds an entry to the matrix in the location [rowNumb][colNumb]
  double getValue (int x, int y) const; //return the element (x, y) of the real matrix
  void printMatrix (); //prints the matrix
  void printEntries (); //prints the entries in the order they are pushed in
  std::vector<double> multiplication( const std::vector<double> v ) const; //matrix vector multiplication
  void Gauss_Seidel ( std::vector<double>& x_0, const std::vector<double>& b, const double tol, const int itCheck, std::string fileName, const int MaxIter ); //Gauss_Seidel

  //void inversion ( double a, double delta, double tol);


private:
  int rowSize_; //number of rows of the matrix
  int colSize_; //number of columns of the matrix
  std::vector<std::vector<double>*>* rows_; //vector of vector: first vector is matrix, its slots are the rows, whose slots are the entries
  std::vector<std::vector<int>*>* colsInd_; //vector of vector: first vector is matrix, its slots are rows, whose entries are the column indexes

};


//multiplication by scalar. opposite order
SparseMatrix operator*(double a, SparseMatrix A);
std::vector<double> vectorSum ( std::vector<double> v1, std::vector<double> v2 ); //sums two vectors
std::vector<double> vectorSub ( std::vector<double> v1, std::vector<double> v2 ); //subtracts two vectors
double LinfNorm ( std::vector<double> v ); //returns the maximum of a vector. In this case I use it to construct the LinfNorm
void Gauss_Seidel_test( double delta, SparseMatrix& A, std::vector<double>& x_0, std::vector<double>& b, const double tol, const int itCheck, std::string fileName, const int MaxIter); //function for testing Gauss_Seidel



#endif
