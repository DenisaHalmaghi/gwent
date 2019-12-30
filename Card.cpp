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
//
//int Card::getTarget()
//{
//	return target->side;
//}void Card::copiazaEsentiale(Ability*& ab_copy,Target*& tg_copy){	 ability->CopiazaAbility(ab_copy);
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

void Card::triggerAbility(Card* tg, vector<pair<int, int>>effects[3],Battlefield* btl){

	UnitCardUI* target= (UnitCardUI*)(tg->cardInterface);
	if(((UnitCardUI*)cardInterface)->hasLock())
	{
		return;
	}

	switch(ability->getName())
	{
		case C_Boost:
		{
		   //	int oldPower= target->getPower();
			tg->modificaPower(ability->getQuantum());
		   //target->setPower(0);
			break;
		 }
		case C_Damage:
		{
			int oldPower= target->getPower();
			tg->modificaPower(-ability->getQuantum());
			break;
		}
		case C_Bleed:
		{
		   //	int quantum= ability->getQuantum();
//			bool gasit=0;
//			int effect=C_Bleed;
//			//cauta cartea in matrice
//			for(int i=0;i<2;i++)
//			{
//				for(int j=0;j<effects[i].size();j++)
//				{
//					pair current=effects[i][j];
//					if(current.first==tg->getIndex())
//					{
//						gasit=1;
//						//modifica durata corespunzator
////
//						int semn=(!i)?1:-1;
//						quantum+=semn*current.second; //daca e pe bleed stack effect altfel vezi diferenta
//
//						if(quantum>0)//ramane bleed
//						{
//						effects[i].erase( effects[i].begin()+j);
//						effects[effect].push_back(make_pair(tg->getIndex(),quantum));
//						target->appendEffect(effect,quantum);
//							//modificam doar durata
////							if(semn>0)  //==1 ,adica l-am gasit pe randul bleed
////							{
////								effects[i][j].second= quantum;
////								target->appendEffect(effect,quantum);
////							}
////							else //e pe randul opus dar nu se se schimba efectul
////							{
////								effects[i].erase( effects[i].begin()+j);
////								effects[C_Bleed].push_back(make_pair(tg->getIndex(),quantum));
////							}
//
//						}
//						else if(quantum==0)//se anuleaza
//						{
//							effects[i][j].second= quantum;
//							target->appendEffect(effect,effects[i][j].second);
//						   effects[i].erase( effects[i].begin()+j);
//						   target->removeEffect();
//						}
//						else //ramane cel vechi  aka vitality in cazul acesta
//						{
//							effect=C_Vitality;
//							quantum*=(-1);
//							//stergem cel vechi
//							effects[i].erase( effects[i].begin()+j);
//							//introducem cel nou
//							effects[C_Vitality].push_back(make_pair(tg->getIndex(),quantum));
//							target->appendEffect(effect,quantum);
//						}
//
//						return;   //grija ca daca facem return si avem mai multe tinte(viitor)-> buba
//					}
//				}
//
////				if(gasit)
////				{
////					break;
////				}
//			}

			Bleed_Vitality(C_Bleed,tg->getIndex(),target,effects);

//			if(!gasit)
//			{
//				 //push it into the effects matrix (indexul din vectorul de carti,ca sa putem gasi cartea)
//				 effects[C_Bleed].push_back(make_pair(tg->getIndex(),quantum));
//				 //add something to signal this for the user
//				 target->appendEffect(C_Bleed,quantum);
//			}


			 break;


		}



		case C_Vitality:
		{

//			int quantum= ability->getQuantum();
//			bool gasit=0;
//			int effect=C_Vitality;
//			//cauta cartea in matrice
//			for(int i=0;i<2;i++)
//			{
//				for(int j=0;j<effects[i].size();j++)
//				{
//					pair current=effects[i][j];
//					if(current.first==tg->getIndex())
//					{
//						gasit=1;
//						//modifica durata corespunzator
////
//						int semn=(i)?1:-1;
//						quantum+=semn*current.second;
//
//						if(quantum>0)//ramane efectul nou
//						{
//							//modificam doar durata
//							effects[i].erase( effects[i].begin()+j);
//							effects[effect].push_back(make_pair(tg->getIndex(),quantum));
//							target->appendEffect(effect,quantum);
//						}
//						else if(quantum==0)//se anuleaza
//						{
//							effects[i][j].second= quantum;
//							target->appendEffect(effect,effects[i][j].second);
//						   effects[i].erase( effects[i].begin()+j);
//						   target->removeEffect();
//						}
//						else //ramane cel vechi  aka vitality in cazul acesta
//						{
//							effect=C_Bleed;
//							quantum*=(-1);
//							//stergem cel vechi
//							effects[i].erase( effects[i].begin()+j);
//							//introducem cel nou
//							effects[effect].push_back(make_pair(tg->getIndex(),quantum));
//							target->appendEffect(effect,quantum);
//						}
//
//						return;
//					}
//				}
//
////				if(gasit)
////				{
////					break;
////				}
//			}
//
//			if(!gasit)
//			{
//			//push it into the effects matrix (indexul din vectorul de carti,ca sa putem gasi cartea)
//			 effects[C_Vitality].emplace_back(tg->getIndex(),quantum);
//			 //add something to signal this for the user
//			 target->appendEffect(C_Vitality,quantum);
//			 break;
//		   }

			Bleed_Vitality(C_Vitality,tg->getIndex(),target,effects);
			break;

		}
		case C_Purify:
		{
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
			   tg->destroyUI();
			   return;
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
			tg->destroyUI();
			btl->freePosition(tg->getIndex());
			return;
		//target->getPower();
//		   if(target->getPower()>8)
//		   {
//				target->setPower(0);
//			   //	return;
//			  // target->appendPoison_Lock(C_Lock,25);
//		   }
//
//		   break;
		}

	}
		if(target->getPower()<1)
		{
			//nu mai exista
			tg->destroyUI();
			btl->freePosition(tg->getIndex());
			return;
		}

		//cartea mai exista
		//takeCareOfOrder();
		target->AranjeazaPower();

}

int Card::getIndex()
{
	return nrInst;
}

void Card::destroyUI()
{
	delete cardInterface;
	cardInterface=nullptr;
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
	TPoint newPos=btl->place(pos,nrInst);
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
