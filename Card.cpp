//---------------------------------------------------------------------------

#pragma hdrstop

#include "Card.h"

//int Card::nrInst=0;  //fa-l nul de fiecare data cand se deschide o "fereastra" noua

Card::Card(int index,TCaption name,UnicodeString faction,UnicodeString image,int pc,
Target* target,Ability* ab,UnicodeString cardType)
{
	nrInst=index;
	this->name=name;
	this->image=image;
	this->faction=faction;

	this->target=target;
	this->cardType=cardType;
	provisionCost=pc;
	ability=ab;

	cardInterface=nullptr;

}
Card::Card(){
	name="default";
	image="default";
	faction="monsters";

	target=0;
	provisionCost=10;
	cardType="special_card";
	ability=nullptr;
	cardInterface=nullptr;
}

Card::~Card(){
	delete ability;
	delete cardInterface;
	delete target;
}

Ability* Card::getAbility(){
 return ability;
}

UnicodeString Card::getFaction(){
 return faction;
}

void Card::copiazaEsentiale(Ability*& ab_copy,Target*& tg_copy){	 ability->CopiazaAbility(ab_copy);
	 tg_copy=new Target(target->side,target->type);

}
void  Card::Copiaza(Card*& copie,int index)
{
	 Ability* ab;
	 Target* tg;
	 copiazaEsentiale(ab,tg);
	 copie=new Card(index,name,faction,image,provisionCost,tg,ab,cardType);
}
void Card::buildCardUI(TPoint pos,TWinControl* parent)
{

	cardInterface=new NonUnitCardUI(pos,parent,image,faction, provisionCost,ability,cardType,nrInst);
}

void Card::modificaPower(int dp)
{
	return;
}

int Card::getProvisionCost()
{
	return provisionCost;
}

void Card::triggerAbility(Card* tg, vector<pair<int, int>>effects[3],Battlefield* btl,Battlefield* btlInamic){

	UnitCardUI* target= (UnitCardUI*)(tg->cardInterface);
	if(((UnitCardUI*)cardInterface)->hasLock())
	{
		return;
	}

	switch(ability->getName())
	{
		case C_Boost:
		{
			//+ cat trebuie boostata
			tg->modificaPower(ability->getQuantum());
			break;
		 }
		case C_Damage:
		{
			//power+= - damage
			tg->modificaPower(-ability->getQuantum());
			break;
		}
		case C_Bleed:
		{

			Bleed_Vitality(C_Bleed,tg->getIndex(),target,effects);
			break;

		}

		case C_Vitality:
		{

			Bleed_Vitality(C_Vitality,tg->getIndex(),target,effects);
			break;

		}
		case C_Purify:
		{
		//cauta si scoate toate efectele de pe ea
		   for(int i=0;i<2;i++)
			{
				for(int j=0;j<effects[i].size();j++)
				{
					if(effects[i][j].first==tg->getIndex())
					{
						effects[i].erase( effects[i].begin()+j);
						target->removeEffect();
						break;
					}
				}
			}


			   target->removePoison_Lock(C_Poison);
			   target->removePoison_Lock(C_Lock);
			   break;
		}

		case C_Poison:

		{
		   if(target->hasPoison())
		   {
				target->setPower(0);
		   }
		   else
		   {
			   target->appendPoison_Lock(C_Poison,30);
		   }
		   break;
		}

		case C_Lock:

		{
		   if(!target->hasLock())
		   {
			   target->appendPoison_Lock(C_Lock,25);
		   }
		   else
		   {
			   return;
           }

		   break;
		}

		case C_Destroy:
		{
			target->setPower(0);
			 break;
		}

	}
		if(target->getPower()<1)
		{
			//nu mai exista
			tg->clearFromEffects(effects);
			tg->destroyUI();
			btl->freePosition(tg->getIndex());
			btlInamic->freePosition(tg->getIndex());
			return;
		}

		//cartea mai exista

		target->AranjeazaPower();

}

int Card::getIndex()
{
	return nrInst;
}

void Card::destroyUI()
{
    if(cardInterface)
	{
	   delete cardInterface;
	   cardInterface=nullptr;
	}

}

void  Card::clearFromEffects(vector < pair<int,int> >  effects[3])
{
	 for(int i=0;i<2;i++)
	 {
		for(int j=0;j<effects[i].size();j++)
		{
			if(effects[i][j].first==nrInst)
			{
				effects[i].erase( effects[i].begin()+j);
			}

        }
     }
}

void Card::Bleed_Vitality(int effect,int index,UnitCardUI* target, vector<pair<int, int>>effects[3])
{
			int quantum= ability->getQuantum();
			//cauta cartea in matrice
			for(int i=0;i<2;i++)
			{
				for(int j=0;j<effects[i].size();j++)
				{
					pair current=effects[i][j];
					if(current.first==index)
					{

						//modifica durata corespunzator
						int semn=(i==effect)?1:-1;
						quantum+=semn*current.second; //daca e pe bleed stack effect altfel vezi diferenta

						if(quantum>0)//ramane efectul nou
						{
							effects[i].erase( effects[i].begin()+j);
							effects[effect].push_back(make_pair(index,quantum));
							target->appendEffect(effect,quantum);
						}
						else if(quantum==0)//se anuleaza
						{
							effects[i][j].second= quantum;
							target->appendEffect(effect,effects[i][j].second);
						   effects[i].erase( effects[i].begin()+j);
						   target->removeEffect();
						}
						else //ramane care era
						{
							effect=i;
							quantum*=(-1);
							//stergem cel vechi
							effects[i].erase( effects[i].begin()+j);
							//introducem cel nou
							effects[effect].push_back(make_pair(index,quantum));
							target->appendEffect(effect,quantum);
						}

						return ; //grija ca daca facem return si avem mai multe tinte(viitor)-> buba
					}


				}
			}


		 //push it into the effects matrix (indexul din vectorul de carti,ca sa putem gasi cartea)
		 effects[effect].push_back(make_pair(index,quantum));
		 //add something to signal this for the user
		 target->appendEffect(effect,quantum);

}

void Card::placeOnBattlefield(Battlefield* btl,TPoint pos)
{


	TPoint newPos =btl->place(pos,nrInst);

	cardInterface->Muta(newPos.X,newPos.Y);

}

void  Card::takeCareOfOrder()
{
	if(ability->getAbilityType()=="order")
	{
		Order* ord=dynamic_cast<Order*>(ability);
		ord->signalUsed();
		((OrderCardUI*)cardInterface)->modifyOrderUI(ord->getNoOfCharges());
	}
}

void  Card::toggleDescription()
{
	 cardInterface->toggleDescription(name, ability->getAbilityDescription());
}

Target* Card::getTargetObject()
{
	 return target;
}

bool Card::checkTargetMatch(Target* target)
{
	return target->getType()==cardType;
}
//---------------------------------------------------------------------------


#pragma package(smart_init)
