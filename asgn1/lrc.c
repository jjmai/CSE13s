#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int diceplay();
uint32_t left();
uint32_t right();

typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};

const char *names[] = {"Dude",  "Walter", "Maude",   "Big Lebowski", "Brandt",
                       "Bunny", "Karl",   "Kieffer", "Franz",        "Smokey"};
int money[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
int pot;

int main() {
  int rollamount, i, k, entered, index = 0;
  int d = 0;
  int dice = 0;
  int dead = 0;
  int players, seed;
  bool t = true;
  bool f = false;
  printf("Random seed: ");
  scanf("%d", &seed); // ask user input for seed
  srand(seed);
  printf("How many players? ");
  scanf("%d", &players); // ask user input for #players
  if (players < 1 || players > 10) {
    printf("Cannot enter player number less than 2 or above 10\n");
    exit(t);
  }

  while (dead <    // while more than 1 player with
         players - // more than 0 dollars, continue
             1) {
    entered = f; // entered =false
    dead = 0;
    if (index >= players) { // if index goes beyond list of players
      index = 0;            // go back to beginning
    }
    if (money[index] != 0) {
      printf("%s rolls... ", names[index]); // print if player still alive
    }
    rollamount = money[index];
    for (i = 0; i < rollamount; i++) { // for loop for dice rolling
      entered = t;                     // roll dice=money(max3)
      if (i == 3) {
        break;
      }
      dice = rand() % 6;
      d = diceplay(dice, index, players); // returns the pot amount
    }
    if (entered) { // print new line only if player rolls
      printf("\n");
    }
    for (k = 0; k < players; k++) { // checks to see how many people with $0
      if (money[k] <= 0) {
        ++dead;
      }
    }
    ++index;
  }
  for (i = 0; i < players; i++) { // wins!
    if (money[i] != 0) {
      printf("%s wins the $%d pot with $%d left in the bank!\n", names[i], d,
             money[i]);
    }
  }
}

int diceplay(int d, int index, int players) {
  int position; // becomes position of player
  int face = 0;
  face = die[d];

  if (face == LEFT) {
    money[index] = money[index] - 1;
    position = left(index, players);
    money[position] = money[position] + 1;
    printf("gives $1 to %s ", names[position]);
  } else if (face == RIGHT) {
    money[index] = money[index] - 1;
    position = right(index, players);
    money[position] = money[position] + 1;
    printf("gives $1 to %s ", names[position]);
  } else if (face == CENTER) {
    ++pot;
    money[index] = money[index] - 1;
    printf("puts 1$ in the pot ");
  } else {
    printf("gets a pass ");
  }
  return pot;
}

uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}
uint32_t right(uint32_t pos, uint32_t players) { return ((pos + 1) % players); }
