#include<iostream>
#include"deck.h"

Deck::Deck() {
	for (int iter = 0; iter < 52; ++iter) {
		deck[iter].spot = (Spot)(iter % 13);
		deck[iter].suit = (Suit)(iter / 13);
	}
	next = 0;
}

void Deck::reset() {
	for (int iter = 0; iter < 52; ++iter) {
		deck[iter].spot = (Spot)(iter % 13);
		deck[iter].suit = (Suit)(iter / 13);
	}
	next = 0;
}

void Deck::shuffle(int n) {
	const int leftNum = n;
	const int rightNum = DeckSize - n;
	Card leftDeck[leftNum];
	Card rightDeck[rightNum];
	for (int iter=0; iter<leftNum; ++iter)
		leftDeck[iter]=deck[iter];
	for (int iter=0; iter<rightNum; ++iter)
		rightDeck[iter]=deck[iter+leftNum];
	if (leftNum < rightNum) {
		for (int iter=0; iter<leftNum; ++iter){
			deck[2*iter]=rightDeck[iter];
			deck[2*iter+1]=leftDeck[iter];
		}
		for (int iter=leftNum; iter<rightNum; ++iter)
			deck[leftNum+iter]=rightDeck[iter];
	}
	else{
		for (int iter=0; iter<rightNum; ++iter){
			deck[2*iter]=rightDeck[iter];
			deck[2*iter+1]=leftDeck[iter];
		}
		for (int iter=rightNum; iter<leftNum; ++iter)
			deck[rightNum+iter]=leftDeck[iter];
	}
	next=0;
}


Card Deck::deal(){
	DeckEmpty deckEmpty;
	if (next<DeckSize)
		return deck[next++];
	else
		throw deckEmpty;//Problem: if this is a correct return type
}

int Deck::cardsLeft(){
	return DeckSize-next;
}
