#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>

#include "sparsematrix.hh"

int main()

{
  auto start = std::chrono::high_resolution_clock::now();
  int N = 100; //size of matrix

  //delta is a vector containing the different values I want to test on
  std::vector<double> delta = {1., 10., 50., 100., 500., 1000}; //delta
  std::vector<double> lambda = {0., 1., 10., 50., 100., 500., 1000}; //lambda

  SparseMatrix mat = SparseMatrix (N, N);
  std::vector<double> x_0 (mat.getRowSize());
  std::vector<double> b (mat.getRowSize());
  Gauss_Seidel_test (lambda.at(0), delta.at(0), mat, x_0, b, 1e-6, 10000 ,1e6);

     // for(unsigned int i = 0; i<x_0.size();  ++i)
     // {
     //   std::cout << x_0.at(i) << std::endl;
     // }

  //testing. The case 10000 is not gonna be tested due to the large time required

  // for(unsigned int i=0; i<delta.size(); ++i)
  // {
  //   SparseMatrix mat = SparseMatrix (N, N);
  //   std::vector<double> x_0 (mat.getRowSize());
  //   std::vector<double> b (mat.getRowSize());
  //   Gauss_Seidel_test (lambda.at(0), delta.at(i), mat, x_0, b, 1e-6, 10000 ,1e6);
  // }
  //
  // for(unsigned int i=0; i<lambda.size(); ++i)
  // {
  //   SparseMatrix mat = SparseMatrix (N, N);
  //   std::vector<double> x_0 (mat.getRowSize());
  //   std::vector<double> b (mat.getRowSize());
  //   Gauss_Seidel_test (lambda.at(i), delta.at(0), mat, x_0, b, 1e-6, 10000, 1e6);
  // }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout<< "Elapsed time: " << elapsed.count() << "s\n";



  // //varying delta.
  // int M=100;
  // for(unsigned int i=0; i<delta.size(); ++i)
  // {
  //   SparseMatrix mat = SparseMatrix (M, M);
  //   std::vector<double> x_0 (mat.getRowSize());
  //   std::vector<double> b (mat.getRowSize());
  //   Gauss_Seidel_delta (delta.at(i), mat, x_0, b, 1e-6, 10000, "delta_", 1e6);
  // }
  //
  // //testing with lambda
  // for(unsigned int i=0; i<lambda.size(); ++i)
  // {
  //   SparseMatrix mat = SparseMatrix (M, M);
  //   std::vector<double> x_0 (mat.getRowSize());
  //   std::vector<double> b (mat.getRowSize());
  //   Gauss_Seidel_lambda (lambda.at(i), delta.at(0), mat, x_0, b, 1e-6, 10000, "lambda_", 1e6);
  // }


  //mat.Gauss_Seidel ( x_0, b, 0.00000001, 10, "GS_");








 // Commento prova per git

  return 0;
}
