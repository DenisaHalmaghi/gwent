//---------------------------------------------------------------------------

#pragma hdrstop

#include "BattlefieldDerivat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Battlefield_Deriv::Battlefield_Deriv(TForm * parent,int inamic):Battlefield(parent,inamic)
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
			  CardUI* test =  Cards[index]->cardInterface;
			  totalScore+=test->getPower();
			}



		  }
	  }
	  score->Caption=totalScore;
	  return totalScore;
}

bool  Battlefield_Deriv::highlightValidTargets(vector<Card*> Cards,Card* targetingCard)
{
	bool anyMatch=false;
	Target* target=targetingCard->getTargetObject();
	int side=target->getSide();
	  for(int i=0;i<2;i++)
	  {
		  for(int j=0;j<positions[i].size();j++)
		  {
			int index= positions[i][j].second;
			if(index>=0)
			{
				Card* current=Cards[index];
				if(current!=targetingCard &&current->checkTargetMatch(target))
				{
				   current->cardInterface->showHighlight();
				   validTargets.push_back(current);
				   anyMatch=true;
				}

			}



		  }
	  }
	  return anyMatch;
}


void  Battlefield_Deriv::clearHighlightedTargets()
{

	  for(int j=0;j<validTargets.size();j++)
	  {
		CardUI * current =  validTargets[j]->cardInterface;
		if(current)
		{
			current->deleteHighlight();
        }


	  }
	  validTargets.clear();
}

bool  Battlefield_Deriv::isTargetValid(Card* target)
{

	  for(int j=0;j<validTargets.size();j++)
	  {
		if(target== validTargets[j])
		{
			return true;
		}

	  }

	  return false;
}
