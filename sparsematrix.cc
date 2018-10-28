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

#include "sparsematrix.hh"

//default constructor
SparseMatrix::SparseMatrix ()
{
  rowSize_ = 1;
  colSize_ = 1;
  rows_ = new std::vector<std::vector<double>*> (1);
  colsInd_ = new std::vector<std::vector<int>*> (1);
}

//sets the value of the private data
SparseMatrix::SparseMatrix ( int const M, int const N )
{
  if( M>0 && N>0 )
  {
    rowSize_ = M;
    colSize_ = N;
    rows_ = new std::vector<std::vector<double>*> (M);
    colsInd_ = new std::vector<std::vector<int>*> (M);
  }else
  {
    std::cout << "Error. Either (Both) the column or (and) row size provided are not positive integers." << std::endl;
    exit(EXIT_FAILURE);
  }

}

// Copy constructor
SparseMatrix::SparseMatrix(const SparseMatrix& source )
{
  rowSize_ = source.rowSize_;
  colSize_ = source.colSize_;

  this->rows_ = new std::vector<std::vector<double>*> (rowSize_);
  this->colsInd_ = new std::vector<std::vector<int>*> (rowSize_);

  int rows_size = (*source.rows_).size();
  for(int i=0; i<rows_size; ++i)
  {

    std::vector<double>* addr_of_values = (*source.rows_).at(i);

    if(addr_of_values == 0)
    {
      continue;
    }

    std::vector<double>* copy_of_values = new std::vector<double>(*addr_of_values);

    (*this->rows_)[i] = copy_of_values;

    std::vector<int>* addr_of_values_colsInd = (*source.colsInd_).at(i);
    std::vector<int>* copy_of_values_colsInd = new std::vector<int>(*addr_of_values_colsInd);
    (*this->colsInd_)[i] = copy_of_values_colsInd;

    i++;
  }
}

//descructor
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

void SparseMatrix::addEntry ( int rowNumb, int colNumb, double newValue ) //adds an entry to the matrix in the location [rowNumb][colNumb]
{

  if( (rowNumb<=rowSize_) && (colNumb<=colSize_) && (rowNumb>=0) && (colNumb>=0) ) //checking consistency of the request
  {

    std::vector<int>* current_line_Indices   = colsInd_->at(rowNumb); //assigning the reference of rowNumb of colsInd to a vector of pointers representing the line of the indices matrix I am currently looking at
    std::vector<double>* current_line_Values = rows_->at(rowNumb); //assigning the reference of rowNumb of rows to a vector of pointers representing the line of the entries matrix I am currently looking at

    if( current_line_Indices == 0 ) //if 0 I have not accessed the line before
    {

      (*colsInd_)[rowNumb] = new std::vector<int>(1, colNumb); //dynamically puts a vector of size 1 and value colNumb in the row rowNumb of the indices matrix
      (*rows_)[rowNumb] = new std::vector<double>(1, newValue); //dynamically puts a vector of size 1 and value newValue in the row rowNumb of the enties matrix

    }
    else // Every other time, i.e. if I have accessed the line before
    {
      current_line_Indices->push_back(colNumb); //adds the index through a pushback
      current_line_Values->push_back(newValue); //adds the entry through a pushback
    }

    // std::vector<int>* current_line_STAMPA = colsInd_->at(rowNumb);
    // std::cout << "->Indices " << std::endl;
    // for(auto const& value: (*current_line_STAMPA))
    //  std::cout << "I: " << value << std::endl;
    //
    // std::vector<double>* current_line_STAMPA_V = rows_->at(rowNumb);
    // std::cout << "->Values " << std::endl;
    // for(auto const& value: (*current_line_STAMPA_V)){
    //  std::cout << "V: " << value << std::endl;
    // }
  }
  else
  {
    std::cout << "Error. Trying to add an entry at a non existing location." << std::endl;
    exit(EXIT_FAILURE);
  }
}


double SparseMatrix::getValue (int x, int y) //Get the value (x, y) in the real matrix. x is right even inthe actual ones
{
  if ( (*colsInd_).at(x) == 0 )
  {
    return 0.0;
  }

  std::vector<int> curr_row = (*(*colsInd_).at(x)); // copying the x-th vector of colsInd in curr_row

  // find y in row
  std::vector<int>::iterator it;
  //std::find finds y in the given vector. y is the column index of the big matrix. But I have to find the column index of colsInd_ containing y
  //to find the position I use std::distance
  ptrdiff_t pos = std::distance(curr_row.begin(),       std::find (curr_row.begin(), curr_row.end(), y));

  if(pos >= curr_row.size()) { //no y value present. Then returns 0.
    return 0.0;
  } else {
    //std::cout << "Pos: " << pos << std::endl;
  }

  // Using x and pos into rows_ to access the entry value
  double found_value = (*(*rows_).at(x)).at(pos);

  //std::cout << "Value in " << x << ","<< y<< " is " << found_value << std::endl;

  return found_value;

}



void SparseMatrix::printMatrix () //prints the matrix
{

  for( int i=0; i< rowSize_; ++i)
  {
    for( unsigned int j=0; j< colSize_; ++j)
    {
      std::cout << getValue(i, j);
    }
    std::cout << std::endl;
  }
}


void SparseMatrix::printEntries () //prints the entries in the order they are pushed in
{

  for( int i=0; i< rowSize_; ++i)
  {
    for( unsigned int j=0; j< colSize_; ++j)
    {
      if( (*rows_).at(i) == 0 )
      {
        std::cout << 0 << "\t";
      }else
      {
        if(j < (*(*rows_).at(i)).size())
        {
          std::cout << (*(*rows_).at(i)).at(j) << "\t";
        }else
        {
          std::cout << 0 << "\t";
        }
      }
    }
    std::cout << std::endl;
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



//
// //multiplication by a scalar, opposite order
// SparseMatrix operator*(double a, SparseMatrix A)
// {
//   return A*a;
// }










// std::vector<int>* current_line_Indices   = colsInd_->at(rowNumb);
// std::vector<double>* current_line_Values = rows_->at(rowNumb);
//
//
// if(current_line_Indices == 0) //if 0 I have not acessed the line before
// {
//
//   (*colsInd_)[rowNumb] = new std::vector<int>(1, colNumb);
//   (*rows_)[rowNumb] = new std::vector<double>(1, newValue);
//
// }
// else // Every other time
// {
//   current_line_Indices->push_back(colNumb);
//   current_line_Values->push_back(newValue);
// }
//
// //  std::vector<int>* current_line_STAMPA = colsInd_->at(rowNumb);
// //  std::cout << "->Indices " << std::endl;
// //  for(auto const& value: (*current_line_STAMPA))
// //   std::cout << "I: " << value << std::endl;
// //
// // std::vector<double>* current_line_STAMPA_V = rows_->at(rowNumb);
// // std::cout << "->Values " << std::endl;
// // for(auto const& value: (*current_line_STAMPA_V)){
// //  std::cout << "V: " << value << std::endl;
// //  }
