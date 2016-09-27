#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<cassert>
#include "player.h"
#include "card.h"
#include "hand.h"
#include "deck.h"
#include "rand.h"

using namespace std;

int main(int argc, char* argv[]) {
	static unsigned int minimum=5;
	//initialize arguements
	unsigned int bankroll, hand, thishand=0;
	string mod;
	bankroll=(unsigned int)atoi(argv[1]);
	hand=(unsigned int)atoi(argv[2]);
	mod=argv[3];
	//initialize the player
	Player* player=NULL;
	if (mod=="simple")
		player=get_Simple();
	else if (mod=="counting")
		player=get_Counting();
	//initialize the deck
	Deck deck;
	cout << "Shuffling the deck\n";
	for (int iter=0; iter<7; ++iter){
		int cut=get_cut();
		deck.shuffle(cut);
		cout << "cut at " << cut << endl;
		player->shuffled();
	}
	//start simulation
	if (bankroll>=minimum){
	for (thishand=1; thishand<=hand; ++thishand){
		//define hand and deal
		Hand newHand;
		Card newDeal,dealer,holeCard;
		int betNum;
		bool bustPlayer=false, bustDealer=false;
		//initial state
		cout << "Hand " << thishand << " bankroll " << bankroll << endl;
		//check if need shuffle
		if (deck.cardsLeft()<20){
			cout << "Shuffling the deck\n";
			for (int iter=0; iter<7; ++iter){
				int cut=get_cut();
				deck.shuffle(cut);
				cout << "cut at " << cut << endl;
				player->shuffled();
			}
		}
		//begin hand
		betNum=player->bet(bankroll,minimum);
		cout << "Player bets " << betNum << endl;
		//first draw by player
		newDeal=deck.deal();
		cout << "Player dealt "<< SpotNames[newDeal.spot]<<" of "<<SuitNames[newDeal.suit]<<endl;
		player->expose(newDeal);
		newHand.addCard(newDeal);
		//second draw by dealer
		dealer=deck.deal();
		cout << "Dealer dealt "<< SpotNames[dealer.spot]<<" of "<<SuitNames[dealer.suit]<<endl;
		player->expose(dealer);
		//third draw by player
		newDeal=deck.deal();
		cout << "Player dealt "<< SpotNames[newDeal.spot]<<" of "<<SuitNames[newDeal.suit]<<endl;
		player->expose(newDeal);
		newHand.addCard(newDeal);
		//forth draw by dealer
		holeCard=deck.deal();
		if (newHand.handValue().count==21){
			cout << "Player dealt natural 21\n";
			bankroll+=(betNum*3/2);
		}
		else{
		while ( player->draw(dealer, newHand) ){
			newDeal=deck.deal();
			cout << "Player dealt "<< SpotNames[newDeal.spot]<<" of "<<SuitNames[newDeal.suit]<<endl;
			player->expose(newDeal);
			newHand.addCard(newDeal);
			if (newHand.handValue().count>=22){
				bustPlayer=true;
				cout << "Player's total is " << newHand.handValue().count << endl;
				cout << "Player busts\n";
				bankroll-=betNum;
				break;
			}
		}

		if (!bustPlayer){
			cout << "Player's total is " << newHand.handValue().count << endl;
			Hand dealerHand;
			dealerHand.addCard(dealer);
			dealerHand.addCard(holeCard);
			player->expose(holeCard);
			cout<<"Dealer's hole card is "<<SpotNames[holeCard.spot]<<" of "<<SuitNames[holeCard.suit]<<endl;
			while (dealerHand.handValue().count<17){
				newDeal=deck.deal();
				cout << "Dealer dealt "<< SpotNames[newDeal.spot]<<" of "<<SuitNames[newDeal.suit]<<endl;
				player->expose(newDeal);
				dealerHand.addCard(newDeal);
				if (dealerHand.handValue().count>=22){
					bustDealer=true;
					break;
				}
			}
			cout << "Dealer's total is " << dealerHand.handValue().count << endl;
			if (bustDealer){
				cout << "Dealer busts\n";
				bankroll+=betNum;
			}
			else {
				if (dealerHand.handValue().count>newHand.handValue().count){
					cout << "Dealer wins\n";
					bankroll-=betNum;
				}	
				else if (dealerHand.handValue().count<newHand.handValue().count){
					cout << "Player wins\n";
					bankroll+=betNum;
				}
				else
					cout << "Push\n";
			}
		}
		}
		if (bankroll<minimum)
			break;
		if (thishand==hand)
			break;
	}
	}
	cout << "Player has " << bankroll << " after " << thishand<< " hands\n";
	
	return 0;
}
