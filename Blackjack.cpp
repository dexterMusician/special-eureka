// code is too long, needs to be optimised.
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class CARDS //Treating every single card as a single object. Abstract class, not used in main().
{
	 char name[4][12]={"Spade","Club","Hearts","Diamond"};
	 char cardName[12];
	 int valueOfCard;
public:
	void getCard()// Function to get card informations while drawing from the deck
	{	valueOfCard=0;
		time_t seed;
		time(&seed);
		srand((unsigned int) seed);
			valueOfCard=(rand()%12)+1;
			int j=(rand()%4)+1;
			strcpy(cardName,name[j]);	
	}
	void showCard()
	{
	
		cout<<"\n"<<valueOfCard<<" of ";
		puts(cardName);
		
	}
	int retvalue()//accessor function
	{
		return valueOfCard;
	}
	char retname()
	{
		return cardName[0];
	}
};




class PLAYER // class with properties of every player in the game of blackjack.
{	
protected:
	CARDS playerCards[8];
	int playerScore=200;
	int numberOfcards=1;
	
public:
	int CardsValue()// returns the total value of cards in the player's hand.
	{
		int cardNumber;
		int value=0;
		for(cardNumber=0;cardNumber<=numberOfcards;cardNumber++)
		{
			value=value+playerCards[cardNumber].retvalue();
		}
		return value;
	}

	void dealCards() // deals the first two cards of the player. Non repeating cards.
	{	
		do
		{	playerCards[0].getCard();
			playerCards[1].getCard();
		}
		while(playerCards[0].retvalue()==playerCards[1].retvalue()&& playerCards[0].retname()==playerCards[1].retname());
	}

	

	void showCards()
	{	
		cout<<"\n\t\t\t\tYour cards..."<<endl;
		for(int i=0;i<=numberOfcards;i++)
		{	cout<<"********\n ";
			cout<<"Your "<<i+1<<"th  card is  ";
			playerCards[i].showCard();
			cout<<"********"<<endl;
		}
	}

	bool busted() // condition to check if the player got busted.
	{
		if(CardsValue()>21)
			return true;
		else 
			return false;
	}

	void callCard() // function to draw from deck.
	{	
		playerCards[numberOfcards+1].getCard();
		numberOfcards++;
	}

	void resetCard() // an important function. To reset the cards after the round.
	{
		numberOfcards=1;
	}

	int orginalScore()
	{
		return playerScore;
	}
	
	
	
	int getModifiedScore(int difference) // to modify the score of the player
	{
		playerScore=playerScore+difference;
		return playerScore;
	}

	
};	

class AI : public PLAYER // subclass of PLAYER since the dealer is also a player.
{	
public:
	void whenToCall() // logic based function for drawing from deck
	{	
		dealCards(); // instead of calling along user's deal card.
		if(playerScore>=150)
			while(CardsValue()<15)
			{
				callCard();
			}
		else
			while(CardsValue()<16)
				callCard();
	}		
	void showCards()// function overided. Otherwise some kind of logical error.
	{
		cout<<"\n\t\t\t\tDealer's cards..."<<endl;
		for(int i=0;i<=numberOfcards;i++)
		{	cout<<"********\n ";
			cout<<"Dealer's"<<i+1<<"th  card is  ";
			playerCards[i].showCard();
			cout<<"********"<<endl;
		}
	}		
	


};


class GAMEPLAY // This class is the class used in MAIN().
{	int round=1;
	PLAYER player;
	AI dealer;
	
	void playerLost()
	{
		cout<<"\n\t You,yes ''YOU'' lost!"<<endl;
		player.getModifiedScore(-20);
		dealer.getModifiedScore(20);
	}
	void playerWon()
	{
		cout<<"\n\t You win this round chump!"<<endl;
		player.getModifiedScore(20);
		dealer.getModifiedScore(-20);
	}

	void roundDraw()
	{	
		cout<<"\n\t the round is tie. You somehow managed to match wits with the computer...Bravo!"<<endl;
	}
	void deal()
	{
		player.dealCards();
		dealer.dealCards();
	}	
public:
	bool matchAndPlayerResult()// code for the match and returns true if player won and false if dealer won.
	{	int round=1;
		while(true)
		{	
			cout<<"\n\n\t\t***********************ROUND"<<round<<"**************************"<<endl;;
			cout<<"\n\t\t\tYour Score "<<player.orginalScore()<<endl;
			cout<<"\t\t\t\t Dealer score "<<dealer.orginalScore()<<endl;
			char ans='y';
			deal();	
			while(ans=='y')
			{	
				player.showCards();		
				cout<<"\n\n\n\tDo you wish to call card ? (type 'y' to draw)"<<endl;;
				cin>>ans;
				if(ans!='y')
				{
					break;
				}
				player.callCard();	
				if(player.busted())
				{	player.showCards();
					playerLost();
					break;
				}
			}	
				if(player.busted())
					goto reset;
				dealer.whenToCall();
				dealer.showCards();
				if(dealer.busted())
					playerWon();
				else if(player.CardsValue()>dealer.CardsValue())
					playerWon();
				else if(dealer.CardsValue()>player.CardsValue())
					playerLost();
		  reset:player.resetCard();
				dealer.resetCard();
				round++;
				if(player.orginalScore()==0||dealer.orginalScore()==0)
					break;
		} 
		
		if(player.orginalScore()==0)
			return false;
		else if(dealer.orginalScore()==0)
			return true;
	}
};						

int main()
{
	GAMEPLAY gameplay;
	if(gameplay.matchAndPlayerResult())
		cout<<"\n\t********Congratulations. You have won against the WORST EVER AI....***********";
	else
		cout<<"\n\t********YOU are a NOOOOOOOOBBB. HAHAHA";
	return 0;

}				
