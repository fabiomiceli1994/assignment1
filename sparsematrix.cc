#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>

#include "sparsematrix.hh"

//default constructor
SparseMatrix::SparseMatrix ( int const N )
{
  rowSize_ = N;
  colSize_ = N;
  rows_ = new std::vector<std::vector<double>*> (N);
  // rows_ = &rows;
  std::cout << "N: " << N << std::endl;
  colsInd_ =  new std::vector<std::vector<int>*> (N);
  // colsInd_ = &colsInd;
  //rows_ = &(  )
  //rows_ =  {{0.0}};
  //colsInd_ = {{0}};
  //rows_.resize()
}

// set the values of the pivate data
// SparseMatrix::SparseMatrix ( int rowSize, int colSize )
// {
//   if ( (rowSize>0) && (colSize>0) )
//   {
//     rowSize_ = rowSize;
//     colSize_ = colSize;
//     rows_  = std::vector<std::vector<double>>(rowSize, std::vector<double>(colSize, 0));
//     colsInd_ = std::vector<std::vector<int>>(rowSize, std::vector<int>(colSize, 0));
//     for( int i=0; i<rowSize; i++)
//     {
//       for( int j=0; j<colSize; j++)
//       {
//         colsInd_[i][j] = j;
//       }
//     }
//   }else
//   {
//     std::cout << "Error. The row and/or column provided are not positive integers." << std::endl;
//     exit(EXIT_FAILURE);
//   }

// }


// Copy constructor
// SparseMatrix::SparseMatrix(const SparseMatrix& source )
// {
//   rowSize_ = source.rowSize_;
//   colSize_ = source.colSize_;
//   rows_ = source.rows_;
//   colsInd_ = source.colsInd_;
// }
//
// //descructor
SparseMatrix::~SparseMatrix()
{}
//
// bool SparseMatrix::operator==( const SparseMatrix& source )
// {
//   return ( rowSize_ == source.rowSize_ && colSize_ == source.colSize_  && rows_ == source.rows_ && colsInd_ == source.colsInd_ );
// }
//
// bool SparseMatrix::operator!=(const SparseMatrix& source) {
//   return !operator==(source);
// }
//
// SparseMatrix SparseMatrix::operator+(const SparseMatrix& A) //sum of two matrices
// {
//   SparseMatrix temp = SparseMatrix( rowSize_, colSize_ );
//   if( ( rowSize_ == A.rowSize_ ) && ( colSize_ == A.colSize_ ) )
//   {
//     for( int i=0; i<rowSize_; i++)
//     {
//       for( int j=0; j<colSize_; j++)
//       {
//         temp.rows_[i][j] = rows_[i][j] + A.rows_[i][j];
//       }
//     }
//   return temp;
//   }else
//   {
//     std::cout << "Error. Trying to sum matrices of different sizes. Program aborted." << std::endl;
//     exit(EXIT_FAILURE);
//   }
// }
//
//
// SparseMatrix SparseMatrix::operator*(const double a) //scalar multiplication
// {
//   SparseMatrix temp = SparseMatrix( rowSize_, colSize_ );
//     for( int i=0; i<rowSize_; i++)
//     {
//       for( int j=0; j<colSize_; j++)
//       {
//         temp.rows_[i][j] = rows_[i][j]*a;
//       }
//     }
//   return temp;
// }
//
//
// SparseMatrix SparseMatrix::operator-( SparseMatrix& A) //subtraction of two matrices
// {
//   SparseMatrix temp = SparseMatrix( rowSize_, colSize_ );
//   if( ( rowSize_ == A.rowSize_ ) && ( colSize_ == A.colSize_ ) )
//   {
//     return ( (*this) + A*(-1) );
//   }else
//   {
//     std::cout << "Error. Trying to subtract matrices of different sizes. Program aborted." << std::endl;
//     exit(EXIT_FAILURE);
//   }
// }
//
// SparseMatrix& SparseMatrix::operator=(const SparseMatrix& source) //defining equality between matrixes
// {
//   if (this == &source) {
//     std::cout << "Ignoring self-assignment" << std::endl;
//     return *this;
//   }
//   rowSize_ = source.rowSize_;
//   colSize_ = source.colSize_;
//   return *this;
// }

int SparseMatrix::getRowSize () //returns the number of rows
{
  return rowSize_;
}

int SparseMatrix::getColSize () //returns the number of columns
{
  return colSize_;
}

// double SparseMatrix::getEntry ( int rowNumb, int colNumb ) //returns the element [rowNumb][colNumb]
// {
//   return rows_[rowNumb][colNumb];
// }

void SparseMatrix::addEntry ( int rowNumb, int colNumb, double newValue ) //adds an entry to the matrix in the location [rowNumb][colNumb]
{

  if( (rowNumb<=rowSize_) && (colNumb<=colSize_) && (rowNumb>=0) && (colNumb>=0) )
  {
    std::vector<int>* current_line_Indexes   = colsInd_->at(rowNumb);
    std::vector<double>* current_line_Values = rows_->at(rowNumb);


    if(current_line_Indexes == 0) //if 0 I have not acessed the line before
    {

      (*colsInd_)[rowNumb] = new std::vector<int>(1, colNumb);
      (*rows_)[rowNumb] = new std::vector<double>(1, newValue);

    }
    else // Every other time
    {
      current_line_Indexes->push_back(colNumb);
      current_line_Values->push_back(newValue);
    }

   //  std::vector<int>* current_line_STAMPA = colsInd_->at(rowNumb);
   //  std::cout << "->Indexes " << std::endl;
   //  for(auto const& value: (*current_line_STAMPA))
   //   std::cout << "I: " << value << std::endl;
   //
   // std::vector<double>* current_line_STAMPA_V = rows_->at(rowNumb);
   // std::cout << "->Values " << std::endl;
   // for(auto const& value: (*current_line_STAMPA_V)){
   //  std::cout << "V: " << value << std::endl;
   //  }
  }
  else
  {
    std::cout << "Error. Trying to update an entry which does not exists." << std::endl;
    exit(EXIT_FAILURE);
  }
}

// std::vector<double> inversion ( double a, double delta, doubel tol)
// {
//   std::vector<double> w (rowSize_, 0); //vector w required by the assignment
//   std::vector<double> D(rowSize_, 0); //vector D required by the assignment
//   double delta = 1; //delta. Da rivedere per renderlo migliore. Funzione di controllo sulla positivita di delta: aggiungere.
//   double a = 4*(1-delta); //a. Da rivedere per renderlo migliore
//
//   for( int i=0; i<rowSize_; i++) //initialising w[i] and D[i]
//   {
//     for( int j=0; j<colSize_; j++)
//     {
//       w[i] = (i+1)/(rowSize_+1);
//       D[i] = a*(w[i]-0.5)*(w[i]-0.5)+delta;
//       if( (i-1) == j )
//       {
//         (*this).addEntry( i, j, -D[i-1] );
//       }else if( i == j )
//       {
//         (*this).addEntry( i, j, D[i] + D[i-1] );
//       }else if( (i+1) == j )
//       {
//         (*this).addEntry( i, j, -D[i] );
//       }else
//       {
//         (*this).addEntry( i, j, 0 );
//       }
//     }
//   }
// }


// void SparseMatrix::printMatrix () //prints the matrix
// {
//   for( int i=0; i< rowSize_; i++)
//   {
//     for( int j=0; j< colSize_; j++)
//     {
//       std::cout.width(6);
//       std::cout << rows_[i][j];
//     }
//     std::cout << std::endl;
//   }
// }
//
// //multiplication by a scalar, opposite order
// SparseMatrix operator*(double a, SparseMatrix A)
// {
//   return A*a;
// }










// std::vector<int>* current_line_Indexes   = colsInd_->at(rowNumb);
// std::vector<double>* current_line_Values = rows_->at(rowNumb);
//
//
// if(current_line_Indexes == 0) //if 0 I have not acessed the line before
// {
//
//   (*colsInd_)[rowNumb] = new std::vector<int>(1, colNumb);
//   (*rows_)[rowNumb] = new std::vector<double>(1, newValue);
//
// }
// else // Every other time
// {
//   current_line_Indexes->push_back(colNumb);
//   current_line_Values->push_back(newValue);
// }
//
// //  std::vector<int>* current_line_STAMPA = colsInd_->at(rowNumb);
// //  std::cout << "->Indexes " << std::endl;
// //  for(auto const& value: (*current_line_STAMPA))
// //   std::cout << "I: " << value << std::endl;
// //
// // std::vector<double>* current_line_STAMPA_V = rows_->at(rowNumb);
// // std::cout << "->Values " << std::endl;
// // for(auto const& value: (*current_line_STAMPA_V)){
// //  std::cout << "V: " << value << std::endl;
// //  }
