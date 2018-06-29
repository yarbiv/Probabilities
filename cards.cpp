#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

class Hand {
  public:

    int aceCount() { //this is dumb but also very important b/c an ace can be a one or an eleven
      int count = 0;
      for (int i = 0; i < handSize; i++) {
        if (cards[i] == 1) count++;
      }
      return count;
    }

    void clearHand() {
      for (int i = 0; i < 10; i++) {
        cards[i] = 0;
      }
      handSize = 0;
    }

    int handSum() { //this will be used ie. if (p1.handSum() + 10*aceCount < 21 .... you get the idea)
      int count = 0;
      for (int i = 0; i < handSize; i++) {
        count += cards[i];
      }
      return count;
    }

    void addCard(int cardVal) { //this should be protected I think but its fine to have it public for now
      cards[handSize++] = cardVal;
    }

    void printHand() { //honestly? just for bug checking
      for (int i = 0; i < handSize; i++) {
        cout << cards[i];
        if (i != handSize-1) cout << ", ";
      }
      cout << endl;
    }

    int* showHand() {
      return cards;
    }

    int size() {
      return handSize;
    }

    Hand() {
      handSize = 0;
      for (int i = 0; i < 10; i++) {
        cards[i] = 0;
      }
    }

  private:
    int cards[10];
    int handSize;
};

class Deck {
  public:
    int remainingCards() {
      return cardsLeft;
    }

    int deal(Hand& hand, int cardsToDeal) {
      int index = cardsLeft - 1;
      for (int i = 0; i < cardsToDeal; i++) {
        hand.addCard(deck[index--]);
        cardsLeft--;
      }
      return deck[index+1];
    }

    void shuffle() {
      cardsLeft = 52;
      int count = 0; //keeps track of numbers :)
      for (int i = 0; i < cardsLeft; i++) {
        if (i % 4 == 0 && count < 10) count++; //every four, increments by 1
        deck[i] = count;
      }
      for (int i = 0; i < cardsLeft-1; i++) {
        int j = i + rand() / (RAND_MAX / (cardsLeft-1 - i + 1) + 1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
      }
      return;
    }

    // void shuffle(int* arr, int size) { //whole thing is fucking jank
    //   int count = 0;
    //   int repeats[] = {4,4,4,4,4,4,4,4,4,16}; //how many times each shows up
    //   cardsLeft = 52;
    //   for (int i = 0; i < size; i++) {
    //     int curr = arr[i]-1; //subtracts frequency of other cards
    //     repeats[curr]--;
    //     cardsLeft--;
    //   }
    //
    //   for (int i = 0; i < 10; i++) {//converts frequency table to deck type array
    //     for (int j = 0; j < repeats[i]; j++) {
    //       deck[count++] = i+1;
    //     }
    //   }
    //
    //   srand((unsigned int)time(NULL));
    //
    //
    //   for (int i = 0; i < cardsLeft-1; i++) {
    //     int j = i + rand() / (RAND_MAX / (cardsLeft-1 - i + 1) + 1);
    //     int temp = deck[i];
    //     deck[i] = deck[j];
    //     deck[j] = temp;
    //   }
    // }

    void printDeck() {
      for (int i = 0; i < cardsLeft; i++) {
        cout << deck[i];
        if (i != cardsLeft - 1) cout << ", ";
      }
      cout << endl;
    }

    Deck() {
      cardsLeft = 52;
      int count = 0; //keeps track of numbers :)
      for (int i = 0; i < cardsLeft; i++) {
        if (i % 4 == 0 && count < 10) count++; //every four, increments by 1
        deck[i] = count;
      }
    }

  private:
    int cardsLeft;
    int deck[52];

};



int main() {
  srand((unsigned int)time(NULL));
  Deck q4;
  Hand player;

  cout << endl << "Question 4: Checking Thresholds" << endl;

  for (int threshold = 10; threshold <= 20; threshold++) {
    float count = 0;
    q4.shuffle();
      for (int i = 0; i < 10000; i++) {

        int sum11 = player.handSum() + 10*player.aceCount();
        int sum1 = player.handSum();

        //while (sum1 <= 21 && sum11 < threshold) {
        while (true) {

          if (q4.remainingCards() == 0) {
            i--; //restart hand if the deck is empty.
            q4.shuffle();
            player.clearHand();
            //cout << "Shuffling..." << endl;
            break;
          }
          q4.deal(player, 1); //deal until we get to something interesting.
          sum11 = player.handSum() + 10*player.aceCount();
          sum1 = player.handSum();
          if ( (sum11 >= threshold && sum11 <= 21) || (sum1 >= threshold && sum1 <= 21) || sum1 > 21 ) break;
        }
        if (sum11 >= threshold && sum11 <= 21) {
          count++;
          //player.printHand();
          player.clearHand();
        }
        else if (sum1 >= threshold && sum1 <= 21) {
          count++;
          //player.printHand();
          player.clearHand();
        }
        else {
          // cout << "BUST" << endl;
          // player.printHand();
          player.clearHand();
        }
    }
    cout << "When threshold is " << threshold << ", frequency of busts is " << 1 - count/10000 << endl;
  }
//END OF QuESTION 4
//START OF Q5

  cout << endl << "Question 5: Card-counting" << endl;

  int threshold = 17;
  Deck q5;
  Hand p1, p2, p3, dealer, player1;
  int cardCount = 0;
  float winCount = 0;

  for (int i = 0; i < 10000; i++) {
    int pSum11 = 0;
    int pSum1 = 0;
    int dSum11 = 0;
    int dSum1 = 0;
    int bet = 0;
    int playerHandSum = 0;
    int dealerHandSum = 0;

    if (cardCount > 0) bet = 1; //bet high
    else if (cardCount < 0) bet = -1; //bet low

    q5.deal(dealer, 1);
    if (q5.remainingCards() == 0) {
      i--;
      q5.shuffle();
      dealer.clearHand();
      cardCount = 0;
      continue;
    }
    for (int j = 0; j < 6; j++) {
      int card;
      if (j < 2) card = q5.deal(p1, 1);
      if (j < 4 && j >= 2) card = q5.deal(p2, 1);
      if (j >= 4 && j < 6) card = q5.deal(p3, 1);

      if (card >= 2 && card < 7) cardCount++;
      else if (card == 10 || card == 1) cardCount--;

      if (q5.remainingCards() == 0) break;
    }


    while (true) {
      if (q5.remainingCards() == 0) break;

      int card = q5.deal(player1, 1);
      if (card >= 2 && card < 7) cardCount++;
      else if (card == 10 || card == 1) cardCount--;

      pSum11 = player1.handSum() + 10*player1.aceCount();
      pSum1 = player1.handSum();

      if ( (pSum11 >= threshold && pSum11 <= 21) || (pSum1 >= threshold && pSum1 <= 21) || pSum1 > 21 ) break;
    }
    if (pSum11 >= threshold && pSum11 <= 21) {
      playerHandSum = pSum11;
    }
    else if (pSum1 >= threshold && pSum1 <= 21) {
      playerHandSum = pSum1;
    }
    else if (q5.remainingCards() > 0){
      //cout << "player bust, bet/wincount: " << bet << ", "<< winCount << endl;
      if (bet == -1) winCount++;
      //cout << winCount << endl;
      playerHandSum = -1;
    }

    while (true) {
      if (q5.remainingCards() == 0) break;

      int card = q5.deal(dealer, 1);
      if (card >= 2 && card < 7) cardCount++;
      else if (card == 10 || card == 1) cardCount--;

      dSum11 = dealer.handSum() + 10*dealer.handSum();
      dSum1 = dealer.handSum();

      if ( (dSum11 >= 17 && dSum11 <= 21) || (dSum1 >= 17 && dSum1 <= 21) || dSum1 > 21 ) break;
    }

    if (dSum11 >= 17 && dSum11 <= 21) {
      dealerHandSum = dSum11;
    }
    else if (dSum1 >= 17 && dSum1 <= 21) {
      dealerHandSum = dSum1;
    }
    else if (q5.remainingCards() > 0){
      //cout << "dealer bust, bet/wincount: " << bet << ", "<< winCount << endl;
      if (bet != -1) winCount++;
      //cout << winCount << endl;
      dealerHandSum = -1;
    }

    if (dealerHandSum > 0 && playerHandSum > 0 && q5.remainingCards() > 0) {
      //cout << dealerHandSum << ", " << playerHandSum << ", " << bet << ", " << winCount << endl;
      if (dealerHandSum >= playerHandSum && bet == -1) winCount++;
      else if (dealerHandSum < playerHandSum && bet != -1) winCount++;
      //cout << winCount << endl;
    }


    if (q5.remainingCards() == 0) {
      i--;
      q5.shuffle();
      player1.clearHand();
      p1.clearHand();
      p2.clearHand();
      p3.clearHand();
      dealer.clearHand();
      cardCount = 0;
      continue;
    }

  }
  cout << "This card-counting algorithm won with a frequency of " << winCount / 10000;





  return 0;
}
