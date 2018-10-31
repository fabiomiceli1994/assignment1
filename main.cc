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

#include "sparsematrix.hh"

int main()

{

  // SparseMatrix matrix = SparseMatrix (1);
  // SparseMatrix mat1 = SparseMatrix (101, 101);
  //
  // mat1.addEntry(1, 5, 3.0);
  // mat1.addEntry(100, 100, 9.0);
  //
  // mat1.addEntry(4, 3, 11.0);

  // mat1.printMatrix();


  // SparseMatrix mat_c = mat1;
  //
  // std::cout << "\n\n" << std::endl;
  //
  // mat_c.printMatrix();

  SparseMatrix mat = SparseMatrix (3, 3);
  mat.addEntry(0, 0, 2);
  mat.addEntry(0, 1, -1);
  mat.addEntry(0, 2, 0);
  mat.addEntry(1, 0, -1);
  mat.addEntry(1, 1, 2);
  mat.addEntry(1, 2, -1);
  mat.addEntry(2, 0, 0);
  mat.addEntry(2, 1, -1);
  mat.addEntry(2, 2, 2);
  std::vector<double> b = {0, 0, 1};
  std::vector<double> x_0 = {0, 0, 0};
  std::vector<double> check = vectorSub(b, mat.multiplication(x_0));

  for( unsigned int i=0; i<check.size(); ++i)
  {
    std::cout << "check[" << i << "] = " << check.at(i) << std::endl;
  }

  // for(unsigned int i = 0; i<check.size(); ++i)
  // {
  //   std::cout << "check " << " " << check.at(i) << std::endl;
  // }

  mat.Gauss_Seidel ( x_0, b, 0.00000001, 10, "GS_");








 // Commento prova per git

  return 0;
}
