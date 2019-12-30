//---------------------------------------------------------------------------

#pragma hdrstop

#include "Deck.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)

Deck::Deck(vector<pair<int,int>>cardsInDeck)
{

	 Aranjeaza(cardsInDeck);
	 random_shuffle(cards.begin(), cards.end());

}

vector<int> Deck::imparteCartile(int number)
{
	vector<int> returnedCards;
	int size;
	for(int i=0;i<number &&( size=cards.size() );i++)
	{
		 returnedCards.push_back(cards[size-1]);
		 cards.pop_back();
	}

	size=cards.size();
	return returnedCards;
}

void Deck::Aranjeaza(vector<pair<int,int>>perechi )
{
	for(int i=0;i<perechi.size();i++)
	{
		pair<int,int> current= perechi[i];
		for(int j=0;j<current.second;j++)
		{
			cards.push_back(current.first);
		}
	}
}
