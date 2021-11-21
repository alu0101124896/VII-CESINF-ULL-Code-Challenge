/**
 * File: main.cc
 * Author: Sergio Tabares Hernández <alu0101124896@ull.edu.es>
 * Since: Autumn 2021
 * Description: This is my solution to the VII CESINF ULL Code Challenge.
 */

#include <iostream>
#include <utility>
#include <vector>

// Class to store a continuous group of seats
class seatsGroup {
 private:
  int beginColumn, endColumn;

 public:
  seatsGroup(int, int);
  ~seatsGroup();

  int getBeginColumn();
  int getEndColumn();

  int size();
  void remove(int);
};

seatsGroup::seatsGroup(int beginColumn, int endColumn) {
  this->beginColumn = beginColumn;
  this->endColumn = endColumn;
}

seatsGroup::~seatsGroup() {}

int seatsGroup::getBeginColumn() { return this->beginColumn; }
int seatsGroup::getEndColumn() { return this->endColumn; }

// Method to calculate the number of seats on the group
int seatsGroup::size() { return this->endColumn - this->beginColumn; }

// Method to remove a given number of seats from the begining towards the end
void seatsGroup::remove(int numOfSeats) { this->beginColumn += numOfSeats; }

// Method to obtain all the available seat groups from a given room
std::vector<seatsGroup *> getAvailableSeatsGroups(
    int nRows, int nColumns, std::vector<std::pair<int, int>> positions) {
  // Store occupied seats by room row
  std::vector<int> emptyVector;
  std::vector<std::vector<int>> occupiedSeats(nRows, emptyVector);
  for (int i = 0; i < positions.size(); i++) {
    occupiedSeats[std::get<0>(positions[i]) - 1].push_back(
        std::get<1>(positions[i]) - 1);
  }

  // Divide each row into groups of available seats
  std::vector<seatsGroup *> availableSeatsGroups;
  for (int i = 0; i < nRows; i++) {
    int beginColumn = 0;
    for (int j = 0; j < occupiedSeats[i].size(); j++) {
      int endColumn = occupiedSeats[i][j];
      if (beginColumn < endColumn) {  // at least one seat
        availableSeatsGroups.push_back(new seatsGroup(beginColumn, endColumn));
      }
      beginColumn = endColumn + 1;
    }
    if (beginColumn < nColumns) {  // at least one seat
      availableSeatsGroups.push_back(new seatsGroup(beginColumn, nColumns));
    }
  }
  return availableSeatsGroups;
}

// Method to obtain the maximum number of groups that can enter on a given room
int getNumberOfGroups(int nRows, int nColumns, int aisleSeat,
                      std::vector<std::pair<int, int>> positions,
                      int groupSize) {
  int solution = 0;
  std::vector<seatsGroup *> availableSeatsGroups =
      getAvailableSeatsGroups(nRows, nColumns, positions);

  for (int i = 0; i < availableSeatsGroups.size(); i++) {
    seatsGroup *currentAviableSeatsGroup = availableSeatsGroups[i];
    while (groupSize <= currentAviableSeatsGroup->size()) {
      if ((currentAviableSeatsGroup->getEndColumn() < aisleSeat) ||
          (aisleSeat <= currentAviableSeatsGroup->getBeginColumn())) {
        // all group together
        solution++;
        currentAviableSeatsGroup->remove(groupSize);
      } else {  // aisleSeat divides the group in two
        if (((aisleSeat - currentAviableSeatsGroup->getBeginColumn()) != 1) &&
            (((currentAviableSeatsGroup->getBeginColumn() + groupSize) -
              aisleSeat) != 1)) {
          // no subgroups made of one person
          solution++;
          currentAviableSeatsGroup->remove(groupSize);
        } else {  // ignore first seat and try again
          currentAviableSeatsGroup->remove(1);
        }
      }
    }
  }
  return solution;
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
  problems.push_back(getNumberOfGroups(4, 6, 2, {{1, 2}, {3, 5}, {4, 5}}, 3));
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
  problems.push_back(getNumberOfGroups(4, 6, 2, {{1, 2}, {3, 5}, {4, 4}}, 4));
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
  problems.push_back(
      getNumberOfGroups(4, 6, 4, {{1, 2}, {2, 3}, {2, 6}, {3, 6}, {4, 3}}, 2));
  solutions.push_back(7);

  /*
    2.1 Ada Byron
    =============

    0 0 0 X || 0 0 0 0
    X X 0 0 || 0 0 X 0
    0 0 0 0 || 0 0 0 0
    0 0 0 0 || 0 0 0 X
  */
  titles.push_back("2.1 Ada Byron");
  problems.push_back(
      getNumberOfGroups(4, 8, 4, {{1, 4}, {2, 1}, {2, 2}, {2, 7}, {4, 8}}, 4));
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
  problems.push_back(
      getNumberOfGroups(4, 8, 4, {{1, 1}, {1, 7}, {2, 4}, {3, 2}, {4, 8}}, 5));
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
    std::cout << (right ? "✅" : "❌") << " Test " << i + 1 << " - " << titles[i]
              << ": " << (right ? "" : "NOT ") << "passed\n";
    if (!right) {
      std::cout << "The solution was " << solutions[i] << " and the output was "
                << problems[i] << "\n";
    }
    std::cout << "\n";
  }
  return 0;
}
