#include "player.h"

//Implement a simple player
class SimplePlayer : public Player{
public:
	virtual int bet(unsigned int bankroll, unsigned int minimum){
		return minimum;
	}
	
	bool draw(Card dealer, const Hand &player){
		if (!player.handValue().soft){
			if (player.handValue().count<=11)
				return true;
			else if (player.handValue().count==12){
				if (dealer.spot==2 ||dealer.spot==3 ||dealer.spot==4 )
					return false;
				else
					return true;
			}
			else if (player.handValue().count>=13 && player.handValue().count<=16){
				if (dealer.spot<=4)
					return false;
				else
					return true;
			}
			else
				return false;
		}
		else{
			if (player.handValue().count<=17)
				return true;
			else if (player.handValue().count==18){
				if (dealer.spot==0||dealer.spot==5||dealer.spot==6)
					return false;
				else
					return true;
			}
			else
				return false;
		}		
	}
	
	virtual void expose(Card c){}
	
	virtual void shuffled(){}
};

class CountPlayer : public SimplePlayer{
	int ct=0;
public:	
	int bet(unsigned int bankroll, unsigned int minimum){
		if (ct>=2 && bankroll>=2*minimum)
			return 2*minimum;
		else
			return minimum;
	}
	
	void expose(Card c){
		if (c.spot>=8 && c.spot<=12)
			ct--;
		else if (c.spot<=4)
			ct++;
	}
	
	void shuffled(){
		ct=0;
	}
};

static SimplePlayer simpleP;

extern Player *get_Simple(){
	return &simpleP;
}

static CountPlayer countP;

extern Player *get_Counting(){
	return &countP;
}
