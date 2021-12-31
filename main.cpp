#include <bits/stdc++.h>
using namespace std; 
#include "Card.cpp"
#include "Pack.cpp"

// driver function 

int main(){
  // create card pack
  Pack p; 
  p.shuffle(); 

  // create players
  vector<Player*> players; 
  for(int i = 0; i<4; i++){
    cout << "Create player #" << i << endl; 
    cout << "Enter player name: " << endl; 
    string name; 
    cin >> name; 

    string playerType; 
    cout << "Human or NPC?" << endl; 
    cin >> playerType; 
    while(playerType != "Human" && playerType != "NPC"){
      cout << "ERROR: must enter \"Human\" or \"NPC\"" << endl; 
      cout << "Human or NPC?" << endl; 
      cin >> playerType; 
    }
    if(playerType == "Human")
      players.push_back(new HumanPlayer(name)); 
    else
      players.push_back(new NPCPlayer(name)); 
    cout << endl; 
  }

  // distribute cards
  for(int i = 0; i<4; i++){
    p.distributeCards(players[i]);
  }
  
  // first turn 
  int playerTurn = -1; 
  for(int i = 0; i<4; i++){
    if(players[i]->hasAceOfSpades()){
      playerTurn = (i+1) % 4; 
      players[i]->playAceOfSpades();
      break;
    }
  }
  cout << endl; 
  
  // turns
  int cardNum = 3; 
  vector<Card> cardsInMiddle; 
  cardsInMiddle.push_back(Card("Ace", "Spades"));
  while(true){
    cout << "Player " << playerTurn << "'s turn" << endl; 
    vector<Card> played = players[playerTurn]->playTurn(cardNum); 
    for(Card& c : played)
      cardsInMiddle.push_back(c); 
    cout << endl;

    cout << "Call BS?" << endl; 
    for(int i = (playerTurn+1) % 4; i != playerTurn; i = (i+1) % 4){
      if(players[i]->callBS(played, cardNum, cardsInMiddle, players[playerTurn]))
        break; 
    }
    cout << endl; 

    if(players[playerTurn]->noCardsLeft())
      break; 
    
    cardNum = (cardNum + 1) % 13; 
    playerTurn = (playerTurn + 1) % 4;  
  }

  cout << "Congrats Player " << playerTurn << "! You win :]" << endl; 
  return 0; 
}