// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "ED.hpp"

#include <memory>
#include <string>
#include <vector>

ED::ED(std::string A, std::string B) : A(A), B(B) {
  A += "-";
  B += "-";

  // Allocate the matrix
  M = std::make_unique<std::unique_ptr<cell[]>[]>(A.size() + 1);
  for (unsigned i = 0; i <= A.size(); i++)
    M[i] = std::make_unique<cell[]>(B.size() + 1);
}

int ED::OptDistance() {
  unsigned val = 0;
  for (int i = B.size(), val = -GAP; i >= 0; i--)  // Fill last row
    M[A.size()][i] = (val += GAP);

  for (int i = A.size(), val = -GAP; i >= 0; i--)  // Fill last column
    M[i][B.size()] = (val += GAP);

  for (int i = A.size() - 1; i >= 0; i--) {
    for (int j = B.size() - 1; j >= 0; j--) {
      M[i][j] = min3(M[i + 1][j + 1] + penalty(A[i], B[j]), M[i + 1][j] + GAP,
                     M[i][j + 1] + GAP);
    }
  }
  return M[0][0];
}

std::string ED::Alignment() {
  unsigned i = 0, j = 0;
  std::string finalA;
  std::string finalB;
  std::vector<int> costs;
  while (i < A.size() && j < B.size()) {
    char thisA = A[i];
    char thisB = B[j];
    int oldVal = M[i][j];
    if (M[i][j] == M[i + 1][j + 1] + penalty(A[i], B[j])) {
      ++i;
      ++j;
    } else if (M[i][j] == M[i + 1][j] + GAP) {
      thisB = '-';
      ++i;
    } else if (M[i][j] == M[i][j + 1] + GAP) {
      thisA = '-';
      ++j;
    }
    costs.push_back(oldVal - M[i][j]);
    finalA.push_back(thisA);
    finalB.push_back(thisB);
  }

  // By now, at least one of the strings is fully parsed.
  // We only need to parse the remainder of the longer string and match them
  // with gaps for the other.

  while (i < A.size()) {  // In case string A is longer
    finalA.push_back(A[i]);
    finalB.push_back('-');
    costs.push_back(GAP);
    ++i;
  }

  while (j < B.size()) {  // In case string B is longer
    finalA.push_back('-');
    finalB.push_back(B[j]);
    costs.push_back(GAP);
    ++j;
  }

  // Create the final vertical representation of the alignment
  std::string Alignment;
  for (unsigned i = 0; i < finalA.size(); i++) {
    Alignment.push_back(finalA[i]);
    Alignment.push_back(' ');
    Alignment.push_back(finalB[i]);
    Alignment.push_back(' ');
    Alignment.push_back(costs[i] + '0');
    Alignment.push_back('\n');
  }
  return Alignment;
}
