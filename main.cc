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
  SparseMatrix mat1 = SparseMatrix (101, 101);

  mat1.addEntry(1, 5, 3.0);
  mat1.addEntry(100, 100, 9.0);

  mat1.addEntry(4, 3, 11.0);

  mat1.printMatrix();


  SparseMatrix mat_c = mat1;

  std::cout << "\n\n" << std::endl;

  mat_c.printMatrix();







 // Commento prova per git

  return 0;
}
