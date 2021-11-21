#include <iostream>
#include <vector>

/* Puedes escribir otras funciones auxiliares aquí */

int getNumberOfGroups(int nRows, int nColumns, int aisleSeat,
    std::vector<std::pair<int, int> > positions, int groupSize) {
  /*
   * Escribe tu código para la función principal aquí
   */
}

/* NO EDITAR MAIN */

int main() {
  std::vector<int> problems;
  std::vector<int> solutions;
  std::vector<std::string> titles;

  /*
    1.1 Von Neumann
    ===============

    0 X || 0 0 0 0
    0 0 || 0 0 0 0
    0 0 || 0 0 X 0
    0 0 || 0 0 X 0
  */
  titles.push_back("1.1 Von Neumann");
  problems.push_back(getNumberOfGroups(4, 6, 2,
      {{1, 2}, {3, 5}, {4, 5}}, 3));
  solutions.push_back(2);

  /*
    1.2 Turing
    ==========

    0 X || 0 0 0 0
    0 0 || 0 0 0 0
    0 0 || 0 0 X 0
    0 0 || 0 X 0 0
  */
  titles.push_back("1.2 Turing");
  problems.push_back(getNumberOfGroups(4, 6, 2,
      {{1, 2}, {3, 5}, {4, 4}}, 4));
  solutions.push_back(3);

  /*
    1.3 Boole
    =========

    0 X 0 0 || 0 0
    0 0 X 0 || 0 X
    0 0 0 0 || 0 X
    0 0 X 0 || 0 0
  */
  titles.push_back("1.3 Boole");
  problems.push_back(getNumberOfGroups(4, 6, 4,
      {{1, 2}, {2, 3}, {2, 6}, {3, 6}, {4, 3}}, 2));
  solutions.push_back(7);

  /*
    2.1 Ada Byron
    =============

    0 0 0 X || 0 0 0 0
    X X 0 0 || 0 0 X 0
    0 0 0 0 || 0 0 0 0
    0 0 0 0 || 0 0 0 X
  */
  titles.push_back("2.1. Ada Byron");
  problems.push_back(getNumberOfGroups(4, 8, 4,
      {{1, 4}, {2, 1}, {2, 2}, {2, 7}, {4, 8}}, 4));
  solutions.push_back(5);

  /*
    2.4 Donald Knuth
    ================

    X 0 0 0 || 0 0 X 0
    0 0 0 X || 0 0 0 0
    0 X 0 0 || 0 0 0 0
    0 0 0 0 || 0 0 0 X
  */
  titles.push_back("2.4 Donald Knuth");
  problems.push_back(getNumberOfGroups(4, 8, 4,
      {{1, 1}, {1, 7}, {2, 4}, {3, 2}, {4, 8}}, 5));
  solutions.push_back(3);

  /*
    Carrel 1
    ========

    0 0 0 ||
  */
  titles.push_back("Carrel 1");
  problems.push_back(getNumberOfGroups(1, 3, 3, {}, 3));
  solutions.push_back(1);

  /*
    Carrel 2
    ========

    0 0 || 0
  */
  titles.push_back("Carrel 2");
  problems.push_back(getNumberOfGroups(1, 3, 2, {}, 3));
  solutions.push_back(0);

  /*
    Carrel 3
    ========

    || 0 0 0
  */
  titles.push_back("Carrel 3");
  problems.push_back(getNumberOfGroups(1, 3, 0, {}, 3));
  solutions.push_back(1);

  std::cout << "\n";
  for (size_t i = 0; i < problems.size(); i++) {
    bool right = problems[i] == solutions[i];
    std::cout << (right ? "✅" : "❌") << " Test " << i + 1 << " - " 
              << titles[i] << ": " << (right ? "" : "NOT ") << "passed\n";
    if (!right) {
      std::cout << "The solution was " << solutions[i]
          << " and the output was " << problems[i] << "\n";
    }
    std::cout << "\n";
  }
  return 0;
}
