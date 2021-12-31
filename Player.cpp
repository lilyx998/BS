#include <bits/stdc++.h>
#include "Player.h"
using namespace std; 

string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"};
string ranks[13] = {"Ace," "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

class HumanPlayer : public Player{
  private: 
    vector<Card> cards; 
    string name; 

    struct compare{
      bool operator()(Card& a, Card& b){
        return a.getValue() < b.getValue(); 
      }
    };

  public: 
    HumanPlayer(string name) : name(name) {}

    virtual void takeCard(Card card){
      cards.push_back(card); 
      sort(cards.begin(), cards.end(), compare());
    }

    virtual void takeCards(vector<Card>& cards){
      for(Card& card : cards)
        takeCard(card); 
    }

    virtual string getName(){
      return name; 
    }

    virtual bool hasAceOfSpades() {
      for(Card& c : cards){
        if(c.is_ace_spades())
          return true;
      }
      return false; 
    }

    virtual void playAceOfSpades(){
      cout << name << "plays Ace of Spades" << endl; 
      remove(Card("Ace", "Spades"));
    }

    virtual vector<Card> playTurn(int cardNum){ 
      printCards();
      cout << name << ", please play " << ranks[cardNum] << "s." << endl;  
      cout << "How many cards would you like to play?" << endl; 
      int quant; 
      cin >> quant; 

      vector<Card> played; 
      for(int i = 0; i<quant; i++){
        string rank, suit; 
        cout << "What is the rank and suit of a card would you like to play? (ie \"Three Spades\")" << endl; 
        cin >> rank >> suit >> suit;
        played.push_back(Card(rank, suit)); 
        remove(Card(rank, suit));
      }
      cout << name << " plays " << quant << " " << ranks[cardNum]; 
      if(quant > 1)
        cout << "'s";
      cout << endl; 
      return played; 
    }

    virtual bool noCardsLeft(){
      return cards.size() == 0; 
    }

    virtual bool callBS(vector<Card>& played, int& cardNum, vector<Card>& cardsInMiddle, Player* other){
      cout << name << ", do you call BS? [Y/N]" << endl;
      string ans; 
      cin >> ans; 
      if(ans == "N"){
        cout << name << " passes." << endl; 
        return false;
      } 
      cout << name << " calls BS." << endl; 
      for(Card& c : played){
        if(c.get_rank() != ranks[cardNum]){
          cout << other->getName() << " lied and takes cards in middle." << endl; 
          other->takeCards(cardsInMiddle); 
          cardsInMiddle.clear(); 
          return true; 
        }
      }
      cout << other->getName() << " did not lie. " << name << " takes cards in middle" << endl; 
      takeCards(cardsInMiddle); 
      cardsInMiddle.clear(); 
      return true; 
    }

    void printCards(){
      cout << name << "'s cards: " << endl; 
      for(int i = 0; i<cards.size()-1; i++){
        cout << cards[i] << ", ";
      }
      cout << cards[cards.size()-1] << endl; 
    }

    virtual void remove(const Card& c){
      for(int i = 0; i<cards.size(); i++){
        if(cards[i] == c){
          cards.erase(cards.begin() + i);
          return; 
        }
      }
    }
};

class NPCPlayer : public Player{
  private: 
    vector<Card> cards; 
    string name; 

    struct compare{
      bool operator()(Card& a, Card& b){
        return a.getValue() < b.getValue(); 
      }
    };

  public: 
    NPCPlayer(const string& name) : name(name) {}

    virtual void takeCard(Card card){
      cards.push_back(card); 
      sort(cards.begin(), cards.end(), compare());
    }

    virtual void takeCards(vector<Card>& cards){
      for(Card& card : cards)
        takeCard(card); 
    }

    virtual string getName(){
      return name; 
    }

    virtual bool hasAceOfSpades() {
      for(Card& c : cards){
        if(c.is_ace_spades())
          return true;
      }
      return false; 
    }

    virtual void playAceOfSpades(){
      cout << name << "plays Ace of Spades" << endl; 
      remove(Card("Ace", "Spades"));
    }

    virtual vector<Card> playTurn(int cardNum){
      vector<Card> played; 
      for(Card& c : cards){
        if(c.get_rank() == ranks[cardNum]){
          played.push_back(c); 
          remove(c); 
        }
      }
      if(played.size() == 0){
        for(int i = 1; i<cards.size(); i++){
          if(cards[i].get_rank() == cards[i-1].get_rank()){
            played.push_back(cards[i]); 
            cards.erase(cards.begin() + i); 
            break; 
          }
        }
      }
      cout << name << " plays " << played.size() << " " << ranks[cardNum]; 
      if(played.size() > 1)
        cout << "'s";
      cout << endl; 
      return played; 
    }

    virtual bool noCardsLeft(){
      return cards.size() == 0; 
    }

    virtual bool callBS(vector<Card>& played, int& cardNum, vector<Card>& cardsInMiddle, Player* other){
      int count = 0; 
      for(Card& c : cards){
        if(c.get_rank() == ranks[cardNum])
          count++; 
      }

      if(count + played.size() > 4){
        other->takeCards(cardsInMiddle); 
        cardsInMiddle.clear(); 
        cout << name << " calls BS." << endl; 
        cout << other->getName() << " lied and takes cards in middle." << endl;
        return true; 
      } 

      if(count == 3){
        cout << name << " calls BS." << endl; 
        for(Card& c : played){
          if(c.get_rank() != ranks[cardNum]){
            cout << other->getName() << " lied and takes cards in middle." << endl; 
            other->takeCards(cardsInMiddle); 
            cardsInMiddle.clear(); 
            return true; 
          }
        }
        cout << other->getName() << " did not lie. " << name << " takes cards in middle" << endl; 
        takeCards(cardsInMiddle); 
        cardsInMiddle.clear(); 
        return true; 
      }

      return false; 
    }

    virtual void remove(const Card& c){
      for(int i = 0; i<cards.size(); i++){
        if(cards[i] == c){
          cards.erase(cards.begin() + i);
          return; 
        }
      }
    }
};