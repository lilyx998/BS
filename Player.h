#include <bits/stdc++.h>
using namespace std; 
#include "Card.cpp"

class Player{
  public: 
    virtual void takeCard(Card card) = 0; 

    virtual void takeCards(vector<Card>& cards) = 0; 

    virtual string getName() = 0; 

    virtual bool hasAceOfSpades() = 0; 

    virtual void playAceOfSpades() = 0; 

    virtual vector<Card> playTurn(int cardNum) = 0;

    virtual bool noCardsLeft() = 0; 

    virtual bool callBS(vector<Card>& played, int& cardNum, vector<Card>& cardsInMiddle, Player* other) = 0; 

    virtual void remove(const Card& card) = 0; 
};