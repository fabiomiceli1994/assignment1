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

int main()

{

  // SparseMatrix matrix = SparseMatrix (1);
  SparseMatrix mat1 = SparseMatrix (10, 10);

  mat1.addEntry(1, 5, 3.0);
  mat1.addEntry(1, 10, 9.0);

  mat1.addEntry(4, 3, 11.0);

 // Commento prova per git
  
  return 0;
}
