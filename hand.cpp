#include "hand.h"

Hand::Hand(){
	curValue.count=0;
	curValue.soft=false;
}

void Hand::discardAll(){
	curValue.count=0;
	curValue.soft=false;
}

void Hand::addCard(Card c){
	switch (c.spot){
		case 0:curValue.count+=2;break;
		case 1:curValue.count+=3;break;
		case 2:curValue.count+=4;break;
		case 3:curValue.count+=5;break;
		case 4:curValue.count+=6;break;
		case 5:curValue.count+=7;break;
		case 6:curValue.count+=8;break;
		case 7:curValue.count+=9;break;
		case 8:curValue.count+=10;break;
		case 9:curValue.count+=10;break;
		case 10:curValue.count+=10;break;
		case 11:curValue.count+=10;break;
		case 12:
			if (curValue.count+11<=21){
				curValue.count+=11;
				curValue.soft=true;
			}
			else{
				curValue.count+=1;
			};
			break;
		default: break; //Maybe error message here.
	}
	if (curValue.count>21 && curValue.soft==true){
		curValue.soft=false;
		curValue.count-=10;
	}
		
}

HandValue Hand::handValue() const{
	return curValue;
}
