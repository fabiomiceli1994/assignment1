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
  unsigned int N = 10000; //size of matrix

  //delta is a vector containing the different values I want to test on
  std::vector<double> delta = {1., 10., 50., 100., 500., 1000., 5000., 10000., 50000., 100000.}; //delta
  std::vector<double> lambda = {1., 10., 50., 100., 500., 1000., 5000., 10000., 50000., 100000.}; //lambda

  //testing. The case 10000 is not gonna be tested due to the large time required

  Gauss_Seidel_test (N, 0, 1, 1e-6, 10000, 1e6);


  //varying delta. fixed lambda
  // for(unsigned int i=0; i<delta.size(); ++i)
  // {
  //   Gauss_Seidel_test (N, 0, delta[i], 1e-6, 10000 ,1e6);
  // }
  //
  // //varying lambda. fixed delta
  // for(unsigned int i=0; i<lambda.size(); ++i)
  // {
  //   Gauss_Seidel_test (N, lambda[i], delta[0], 1e-6, 10000, 1e6);
  // }


  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout<< "Elapsed time: " << elapsed.count() << "s\n";

  return 0;
}
