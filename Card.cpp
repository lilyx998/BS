#include <iostream>
#include <string>
using namespace std; 

class Card{
  private: 
    string rank, suit; 
    
  public: 
    Card() {}

    int getValue(){
      int res = 0; 
      for(const string& rank : ranks){
        for(const string& suit : suits){
          res++; 
          if(this->rank == rank && this->suit == suit)
            return res; 
        }
      }
      return -1; 
    }

    Card(const string& rank, const string& suit) : rank(rank), suit(suit) {}

    string get_rank() const {
      return rank; 
    }

    string get_suit() const {
      return suit; 
    }

    bool is_ace_spades() const {
      return rank == "Ace" && suit == "Spades"; 
    }  

    string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"};
    string ranks[13] = {"Ace," "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
};

ostream & operator<<(ostream &os, const Card &card) {
  os << card.get_rank() + " of " + card.get_suit(); 
  return os; 
}

bool operator==(const Card &lhs, const Card &rhs) {
  return lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit(); 
}