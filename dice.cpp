#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

void printRollsQ1(int min, int max, int numRepeats) {
  double tally[max]; //each element of tally[] contains the frequency of our dice roll for a given num
  for (int i = 0; i < max; i++) tally[i] = 0;
  for (int i = 0; i < numRepeats; i++) {
    int rollResult = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    if (rollResult > max || rollResult < min) {
      std:cerr << "roll result not within min or max: terminating";
      exit;
    }
    tally[rollResult-1]++;
  }
  for (int i = 0; i < max; i++) {
    if (tally[i] == 0) {
      std::cout << i+1 << ": " << 0 << endl;
    }
    else {
      std::cout << i+1 << ": " << tally[i]/numRepeats << endl;
    }
  }
}

void printRollsQ3(int min, int max, int numRepeats) {
  double tally[max*2]; //2x tally bc two dice
  for (int i = 0; i < max*2; i++) tally[i] = 0;
  for (int i = 0; i < numRepeats; i++) {
    int firstRollResult = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    int secondRollResult = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    tally[firstRollResult+secondRollResult-2]++;
  }
  for (int i = 0; i < max*2-1; i++) {
    if (tally[i] == 0) {
      std::cout << i+2 << ": " << 0 << endl;
    }
    else {
      std::cout << i+2 << ": " << tally[i]/numRepeats << endl;
    }
  }
}



int main() {
  srand((unsigned int)time(NULL));

  cout << "Question 1: 10 rolls" << endl;
  printRollsQ1(1, 6, 10);
  cout << endl << "Question 1: 1000 rolls" << endl;
  printRollsQ1(1, 6, 1000);
  cout << endl << "Question 1: 100000 rolls" << endl;
  printRollsQ1(1, 6, 100000);

  //the below block is the answer to question 2:

  cout << endl << "Question 2: Equality over 100 rolls" << endl;
  int rollResult;
  double equalityTally = 0;

  for (int i = 0; i < 100000; i++) {
    int lowCount = 0;
    int highCount = 0;
    for (int j = 0; j < 100; j++) {
      rollResult = 1 + rand() / (RAND_MAX / (6 - 1 + 1) + 1);
      if (rollResult <= 3) lowCount++;
      if (rollResult > 3) highCount++;
    }
    if (lowCount == highCount && lowCount != 0) equalityTally++;
  }
  double result = equalityTally / 100000;

  std::cout << "The frequency of low roll=high roll is: " << result << endl;

  cout << endl << "Question 3: Distribution of 3 dice" << endl;

  printRollsQ3(1,6,100000);

  return 0;
}
