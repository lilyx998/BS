#include <bits/stdc++.h>
using namespace std; 
#include "Card.cpp"
#include "Player.cpp"

class Pack{
  private: 
    int idx; 
    Card cards[52]; 

  public: 
    Pack() : idx(0) {
      string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"};
      string ranks[13] = {"Ace," "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
      int i = 0; 
      for(string& suit : suits)
        for(string& rank : ranks)
          cards[i++] = Card(rank, suit); 
    }

    void shuffle(){
      for(int shuffleCount = 0; shuffleCount < 7; shuffleCount++){
        Card temp[52]; 
        for(int idx = 0, i = 0; idx < 52; i++){
          temp[idx++] = cards[26 + i];
          temp[idx++] = cards[i]; 
        }
        
        for(int idx = 0; idx < 52; idx++)
          cards[idx] = temp[idx]; 
      }
    }

    // distributes 13 cards to player
    void distributeCards(Player* player){
      for(int i = 0; i<13; i++)
        player->takeCard(cards[idx++]);
    }
};