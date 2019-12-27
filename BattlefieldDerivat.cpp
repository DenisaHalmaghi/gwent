//---------------------------------------------------------------------------

#pragma hdrstop

#include "BattlefieldDerivat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Battlefield_Deriv::Battlefield_Deriv(TForm * parent):Battlefield(parent)
{

}

void Battlefield_Deriv::ActivateOrders(vector<Card*> Cards)
{
	 for(int i=0;i<onHold.size();i++)
	{
		Card* card=Cards[onHold[i]];
		OrderCardUI* orderUI= (OrderCardUI*)card->cardInterface;
		orderUI->modifyOrderUI(card->getAbility()->getNoOfCharges());
	}
	clearOnHold();
}

void Battlefield_Deriv::IncresePeriodicCounter(vector<Card*> Cards)
{
   for(int i=0;i<periodic.size();i++)
	{

		Card* currCard= Cards[periodic[i]];
		OrderCardUI* currentCardUI=(OrderCardUI* ) (currCard->cardInterface);

		Periodic* current= static_cast<Periodic*>(currCard->getAbility());
		++(*current);
		currentCardUI->modifyOrderUI(current->getNoOfCharges());

	}
}

int  Battlefield_Deriv::CalculateScore(vector<Card*> Cards)
{
	  int totalScore=0;
	  for(int i=0;i<2;i++)
	  {
		  for(int j=0;j<positions[i].size();j++)
		  {
			int index= positions[i][j].second;
			if(index>=0)
			{
			  totalScore+=Cards[index]->cardInterface->getPower();
            }



		  }
	  }
	  score->Caption=totalScore;
	  return totalScore;
}
