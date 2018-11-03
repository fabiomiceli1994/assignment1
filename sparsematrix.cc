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
#include <stdexcept>

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

//destructor
SparseMatrix::~SparseMatrix()
{}



std::vector<double> SparseMatrix::operator*( const std::vector<double>& input ) const
{
  if( colSize_ != input.size())
  {
    std::cout << "Error. Multiplication of matrix and vector cannot be defined." << std::endl;
    exit(EXIT_FAILURE);
  }
  double sums;
  std::vector<double> tmp ( rowSize_ ); // output vector. size = rows of matrix
  for( unsigned int i = 0; i<rowSize_; ++i)
  {
    sums = 0;
    for( unsigned j : *colsInd_->at(i) )
    {
      sums += getValue(i, j)*input.at(j);
    }
    tmp.at(i) = sums;
  }
  return tmp;
}

unsigned int SparseMatrix::getRowSize () const //returns the number of rows
{
  return rowSize_;
}

unsigned int SparseMatrix::getColSize () const //returns the number of columns
{
  return colSize_;
}

void SparseMatrix::addEntry ( unsigned int rowNumb, unsigned int colNumb, double newValue ) //adds an entry to the matrix in the location [rowNumb][colNumb]
{

  if( (rowNumb<=rowSize_) && (colNumb<=colSize_) && (rowNumb>=0) && (colNumb>=0) ) //checking consistency of the request
  {

    std::vector<int>* current_line_Indices   = colsInd_->at(rowNumb); //assigning the reference of rowNumb of colsInd to a vector of pointers representing the line of the indices matrix I am currently looking at
    std::vector<double>* current_line_Values = rows_->at(rowNumb); //assigning the reference of rowNumb of rows to a vector of pointers representing the line of the entries matrix I am currently looking at

    if(newValue != 0)
    {
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
    }
  }
  else
  {
    std::cout << "Error. Trying to add an entry at a non existing location." << std::endl;
    exit(EXIT_FAILURE);
  }
}


double SparseMatrix::getValue (int x, int y) const //Get the value (x, y) in the real matrix. x is right even inthe actual ones
{
  if ( (*colsInd_).at(x) == 0 )
  {
    return 0.0;
  }

  std::vector<int> curr_row = (*(*colsInd_).at(x)); // copying the x-th vector of colsInd in curr_row

  // find y in row
  //std::vector<int>::iterator it;
  //std::find finds y in the given vector. y is the column index of the big matrix. But I have to find the column index of colsInd_ containing y
  //to find the position I use std::distance
  ptrdiff_t position = std::distance(curr_row.begin(),  std::find (curr_row.begin(), curr_row.end(), y));
  unsigned int pos = position;

  if( pos >= curr_row.size() ) { //no y value present. Then returns 0.
    return 0.0;
  } else
  {

  }

  // Using x and pos into rows_ to access the entry value
  double found_value = (*(*rows_).at(x)).at(pos);

  return found_value;

}



void SparseMatrix::printMatrix () //prints the matrix
{

  for( unsigned int i=0; i< rowSize_; ++i)
  {
    for( unsigned int j=0; j< colSize_; ++j)
    {
      std::cout.width(10);
      std::cout << std::left << getValue(i, j);
    }
    std::cout << std::endl;
  }
}

//Gauss Seidel algorithm
void SparseMatrix::Gauss_Seidel( std::vector<double>& x_0, const std::vector<double>& b, const double tol, const int itCheck, std::string fileName, const int MaxIter )
{
  //checks consistency of the matrix and vector sizes
  if( ( rowSize_ != colSize_ ) || ( rowSize_ != x_0.size() ) || ( x_0.size() != b.size() ) )
  {
    std::cout << "Error. Size of matrix and vectors are not correct. Method cannot be implemented." << std::endl;
    exit(EXIT_FAILURE);
  }

  // in every other case
  double sigma; //stores the partial sums I need to implent the algorithm
  int iterations = 0; //counts the iterations which are necessary to converge
  std::vector<double> residual (b.size()); // declaring the residual
  //residual = vectorSub(b, multiplication(x_0)); //computing it
  residual = vectorSub(b, (*this)*x_0); //computing it

  // std::cout << LinfNorm(residual) << std::endl;

  double resMaxNorm = LinfNorm(residual); // maximum norm of the residual
  double resMaxNorm_check = resMaxNorm ; // I will use it to check the algorithm doesnt get stuck

  std::string Filename = fileName + std::to_string (getRowSize());
  //std::cout << Filename << std::endl;

  std::ofstream myOutFile (Filename + ".txt");
  if ( !myOutFile.good() )
  {
    std::cout << "Failed to open the file." <<std::endl;
  }

  myOutFile << "#Details of solution of linear sistem Ax = b through Gauss-Seidel algorithm. A is " << getRowSize() << "x" << getColSize() << " matrix. x and b are " << b.size() << "vectors." << std::endl;
  myOutFile.width(15);
  myOutFile << std::left << "# 1-iterations" ;
  myOutFile.width(25);
  myOutFile << std::left << "2-residual (LinfNorm)" << std::endl;
  myOutFile.flush();

  while( (resMaxNorm > tol) && (iterations<=MaxIter) )
  {

      for( unsigned int i=0; i<x_0.size(); ++i)
      {
        sigma = 0;
        for(unsigned j : *colsInd_->at(i))
        {
          if( j != i)
          {
            sigma += getValue(i, j)*x_0.at(j);
          }
        }
        if(getValue(i, i)!=0)
        {
          x_0.at(i) = (b.at(i)-sigma)/(getValue(i, i));
        }else
        {
          std::cout << "One of the elements on the diagonal of A is zero. Cannot use the algorithm. Exiting the program." << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      residual = vectorSub(b, (*this)*x_0); //computing it
      resMaxNorm = LinfNorm(residual); //updating the maxNorm
      iterations++; //counting the iterations
      myOutFile.width(15);
      myOutFile << std::left << iterations;
      myOutFile.width(25);
      myOutFile << std::left << resMaxNorm << std::endl;
      myOutFile.flush();
      if( (iterations % itCheck) == 0 ) //every itCheck iterations, checks that the algorithm hasn't got stuck
      {
        if( resMaxNorm >= resMaxNorm_check ) //if the error stays the same of gets bigger the algorithm has to be stopped, since this a necessary condition for convergence
        {
          std::cout << "Gauss-Seidel algorithm has been stopped. Convergence cannot be reached." << std::endl;
          exit(EXIT_FAILURE);
        }else
        {
          resMaxNorm_check = resMaxNorm;
        }
      }
  }
  myOutFile.close();
}




std::vector<double> vectorSum ( std::vector<double> v1, std::vector<double> v2 ) //sums two vectors
{
  //checks consistency
  if( v1.size() != v2.size() )
  {
    std::cout << "Error. Summing two vectors having different sizes." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector <double> tmp (v1.size());
  for(unsigned int i=0; i<v1.size(); ++i)
  {
    tmp.at(i) = v1.at(i) + v2.at(i);
  }
  return tmp;
}

std::vector<double> vectorSub ( std::vector<double> v1, std::vector<double> v2 ) //subtracts two vectors
{
  //checks consistency
  if( v1.size() != v2.size() )
  {
    std::cout << "Error. Subtracting two vectors having different sizes." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector <double> tmp (v1.size());
  for(unsigned int i=0; i<v1.size(); ++i)
  {
    tmp.at(i) = v1.at(i) - v2.at(i);
  }
  return tmp;
}

double LinfNorm ( std::vector<double> v ) //LinfNorm of a vector
{
  double max = fabs(v.at(0));
  for(unsigned int i=1; i<v.size(); ++i)
  {
    if(max<fabs(v.at(i)))
    {
      max = fabs(v.at(i));
    }
  }
  return max;
}

//Gauss Seidel algorithm testing function
void Gauss_Seidel_test( unsigned int N, double lambda, double delta, SparseMatrix& A, const double tol, const int itCheck, const int MaxIter)
{
  std::vector<double> x_0(N, 0);
  std::vector<double> w (N); //vector w required by the assignment
  std::vector<double> D(N+1); //vector D required by the assignment
  std::vector<double> b(N);
  //checks consistency of the matrix and vector sizes
  if( ( A.getRowSize() != A.getColSize() ) || ( A.getRowSize() != x_0.size() ) || ( x_0.size() != b.size() ) )
  {
    std::cout << "Error. Size of matrix and vectors are not correct. Method cannot be implemented." << std::endl;
    exit(EXIT_FAILURE);
  }


  double a = 4*(1-delta);

  for(unsigned int i=0; i<N; ++i)
  {
    w.at(i) = (i+1.)/(N+1);
    b.at(i) = -2*a*(w.at(i)-0.5)*w.at(0)*w.at(0);
  }
  b.at(N-1) += 1;


  for(unsigned int i=1; i<N+1; ++i)
  {
    D.at(i) = a*(w.at(i-1)-0.5)*(w.at(i-1)-0.5)+delta;
  }

    D.at(0) = D.at(1);

  for( unsigned int i=0; i<N; ++i) //initialising w[i], D[i] and A
  {

    for( unsigned int j=0; j<N; ++j)
    {
      if( (i-1) == j )
      {
        A.addEntry( i, j, -D.at(i) );
      }else if( i == j )
      {
        A.addEntry( i, j, D.at(i+1) + D.at(i) + lambda );
      }else if( (i+1) == j )
      {
        A.addEntry( i, j, -D.at(i+1) );
      }else
      {
        continue;
      }
    }
  }

  std::string FilenameS = "d_" + std::to_string (delta) + "_l_" + std::to_string (lambda) + "_GSResidual_";

  A.Gauss_Seidel(x_0, b, tol, itCheck, FilenameS, MaxIter);

  std::cout << "Error (lambda=" << lambda << ", delta="<< delta << ")=" << LinfNorm(vectorSub(w, x_0)) <<std::endl;

}
