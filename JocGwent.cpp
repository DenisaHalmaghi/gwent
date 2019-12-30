//---------------------------------------------------------------------------

#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma hdrstop

#include "JocGwent.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)

#define C_HandStart 920
JocGwent::JocGwent(TForm* parent,TImage* boardImg,vector<Card*>prototypes,vector<pair<int,int>>cardsInDeckArray)
{
   //initializam var locale
	droppedCard=nullptr;
	targetedCard=nullptr;
	targetWasSelected=0;
	board=boardImg;
	turn=0;
	roundNumber=0;
	targetTimer=new TTimer(parent);
	targetTimer->Enabled=false;

	//cream battlefield ul
	btl=new Battlefield_Deriv(parent);

	//cream pachetul de carti
	deck=new Deck(cardsInDeckArray);
	hand=deck->imparteCartile(10);
	//preluam variabile de la form
	this-> prototypes=prototypes;
   //	deckArray= cardsInDeckArray;

	Init(parent);
	//board->SendToBack();

//	int width=C_CardHeight*C_Ratio;
//	int left=C_Left_Start;
//	//vector<pair<int,int>> temp;
//	while(left+width+5<C_Left_End)
//	{
//	   pair entry=make_pair(left,-1);
//	   positions[0].push_back(entry);
//	   positions[1].push_back(entry);
//	   left=left+width+5;
//	}
//	int c=0;
//	pos_top[0]=C_MyTop;
//	pos_top[1]=C_MyTop+C_CardHeight+7;



}

void JocGwent::Init(TForm* parent)
{
	//attach listeners for game flow
	board->OnDragOver= boardDragOver;
	board->OnDragDrop= boardDragDrop;
	targetTimer->OnTimer=targetTimerTimer;

//	Target * target1=new Target(C_Ally,"unit");
//	Ability* ab1=new Charges(C_Destroy,3,3);
//	Card* card1=new UnitCard(0,"Aglais","scoia","aglais",9,target1,ab1,2,0);
//	prototypes.push_back(card1);
//	card1->buildCardUI(Point(300,300),parent);
//
//	//CardUI* myUICard=new UnitCardUI(card1,300,300,parent);
//	card1->cardInterface->frame->OnMouseDown =cardMouseDown;
//	//card1->cardInterface->cardImg->OnMouseUp =cardClicked;
//	card1->cardInterface->frame->OnMouseUp =cardClicked;
//	//card1->cardInterface->showHighlight();
//
//	//myUICard->cardImg->OnClick =cardClicked;
//
//   //	UICards.push_back(myUICard);
////
//	Ability* ab2=new Ability(C_Purify,2);
//	Card* card2=new Card(1,"Aglais","monsters","adda_striga",10,target1,ab2);
//
//	prototypes.push_back(card2);
//	card2->buildCardUI(Point(500,500),parent);
//	card2->cardInterface->frame->OnMouseDown =cardMouseDown;
//	card2->cardInterface->frame->OnMouseUp =cardClicked;
//
//	Ability* ab3=new Ability(C_Lock,2);
//	Card* card3=new UnitCard(2,"Aglais","scoia","milaen",8,target1,ab3,10,0);
//	prototypes.push_back(card3);
//	card3->buildCardUI(Point(800,500),parent);
//	card3->cardInterface->frame->OnMouseDown =cardMouseDown;
//  //	card3->cardInterface->cardImg->OnMouseUp =cardClicked;
//	card3->cardInterface->frame->OnMouseUp =cardClicked;
//	//card3->cardInterface->toggleHighlight();
//
//	Ability* ab4=new Periodic(C_Damage,2,1);
//	Card* card4=new UnitCard(3,"Aglais","monsters","katakan",8,target1,ab4,10,0);
//	prototypes.push_back(card4);
//	card4->buildCardUI(Point(950,500),parent);
//	card4->cardInterface->frame->OnMouseDown =cardMouseDown;
//	card4->cardInterface->frame->OnMouseUp =cardClicked;
//	//card4->cardInterface->frame->OnMouseUp =cardClicked;

//	for(int i=0;i<prototypes.size();i++)
//	{
//		Card* test=nullptr;
//		prototypes[i]->Copiaza(test,i);
//		Cards.push_back(test);
//		test->buildCardUI(Point(i*100,i*200),parent);
//		test ->cardInterface->frame->OnMouseDown =cardMouseDown;
//		test ->cardInterface->frame->OnMouseUp =cardClicked;
//
//	}

	 int left=C_Left_Start;

	for(int i=0;i<hand.size();i++)
	{
		Card* test=nullptr;
		prototypes[hand[i]]->Copiaza(test,i);
		Cards.push_back(test);
		test->buildCardUI(Point(left,C_HandStart),parent);
		test ->cardInterface->frame->OnMouseDown =cardMouseDown;
		test ->cardInterface->frame->OnMouseUp =cardClicked;
		left+=C_CardHeight*C_Ratio;

	}







//	card3->Copiaza(test,0);
//   // delete card2;
//	Cards.push_back(test);
//	test-> buildCardUI(Point(950,900),parent);
//	test ->cardInterface->frame->OnMouseDown =cardMouseDown;
//	test ->cardInterface->frame->OnMouseDown =cardMouseDown;
//	CardUI* myUICard2=new UnitCardUI(card2,300+myUICard->getWidth()+20,400,parent);
//	UICards.push_back(myUICard2);
//	myUICard2->cardImg->OnMouseDown =cardMouseDown;
//	myUICard2->cardImg->OnClick =cardClicked;
   //	units.push_back(myUICard2);
//	myUICard->cardImg->OnMouseDown =imgTestMouseDown;
//	myUICard->cardImg->OnClick =cardClicked;
//	units.push_back(myUICard);
}

void __fastcall JocGwent::cardMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{

	TImage *clickedImg = (TImage*)Sender;
	int index=  clickedImg->Tag;
	Card* card= Cards[index];
	//if right button then toggle description
	if(Button == mbRight)
	{
		card->toggleDescription();
		return;
	}
	if(myTurn)
	{
	   clickedImg->BeginDrag(false,-2);
    }

	//if right button show ui for details

}

void __fastcall JocGwent::boardDragOver(TObject *Sender, TObject *Source, int X,
		  int Y, TDragState State, bool &Accept)
{
	if(Y>C_MyTop)
	{
		 Accept = true;
		 TImage *test = (TImage*)Source;
		 Cards[test->Tag]->cardInterface->Muta(Mouse->CursorPos.x, Mouse->CursorPos.y);
	}


//		 test->Left= Mouse->CursorPos.x;
//		 test->Top= Mouse->CursorPos.y;


	  //	 draggedCard->Muta( Mouse->CursorPos.x, Mouse->CursorPos.y);
}

void __fastcall JocGwent::boardDragDrop(TObject *Sender, TObject *Source, int X,
		  int Y)
{
	  TImage* currentImage=  (TImage*)Source;

	  int index=currentImage->Tag;
	  Card* card= Cards[index];

//	  int index=(abs(Y-pos_top[0])> abs(Y-pos_top[1]))?1:0;
//	  int minIndex=0;
//	  int dm=1000;
//	  int temp;
//	  for(int i=0;i<positions[index].size();i++)
//	  {
//		  pair current= positions[index][i];
//		  temp=abs(current.first-X);
//		 if(temp<dm&&current.second==-1)  //if you move cards around second becomes occupied!!!
//
//		 {
//			 minIndex=i;
//			 dm=temp;
//
//		 }
//	  }


		  card->placeOnBattlefield(btl,Point(X,Y));

		  btl->CalculateScore(Cards);

	  //check if position is occupied and if it is move the other cards
	  //check if possible first(won't pass index 0) and get the min of cards to be moved (left or right)
	  //parcurgere cu swap pt first +apeleaza muta pentru fiecare carte pt care se face swap
	  //vezi la drop sa se puna unde trebuie cartea
	 // positions[index][minIndex].second=currentImage->Tag;//cand o carte e distrusa -sterge!!!

//		  TPoint pos=btl->place(Point(X,Y));
//
//		 int x=pos.X;
//	  card->cardInterface-> Muta(pos.X,pos.Y);

	  //FIRST CHECK IF IT S OF TYPE ORDER!! AND IF NOT CONTINUE ELSE WAIT 1 ROUND
	  //BEFORE TRIGGERING ON CLICK!!!

	  //IF ORDER PUSH IT INTO ORDERS ARRAY
	  //IF PLAIN ORDER AND IS ALREADY INSIDE CHECK IF USED
	  //IF ITS CHARGES OR WITH CD ACT ACORDINGLY
	  Ability* ab=card->getAbility();
	  if(!ab->getZeal())
	  {
		btl->adToOnHold(index);

			return;
	  }

	  if(!card->getTargetObject()->getSide()){
		card->triggerAbility(card,effects,btl);
		btl->CalculateScore(Cards);
	   //	droppedCard=card;
	  }
	  else{
		  //hightlightCards() and triggerCard()

		   targetWasSelected=false;
		   if(btl->highlightValidTargets (Cards,card))
		   {
				//there was at least 1 match
			   //ability can be used;
				droppedCard=card;

		   }
//		   targetTimer->Interval=200;
//		   targetTimer->Enabled=true;
		 // pt trigger enable timeout save currentlydropped card in a variable to be used
	  }
	 // Memo1->Text=card->getCard()->getAbility()->getZeal();
	 btl->CalculateScore(Cards);
}

void __fastcall JocGwent::targetTimerTimer(TObject *Sender)
{
//check if a card other than the placed one was clicked and if it was stop counting
//	if(targetWasSelected)
//	{
	  //targetTimer->Enabled=false;
//	  droppedCard->triggerAbility(targetedCard,effects,btl);
//	  droppedCard=nullptr;
//	}
//	else
//	{
//	  droppedCard->cardInterface->cardImg->Left=droppedCard->cardInterface->cardImg->Left+1;
//	}

}//---------------------------------------------------------------------------

void __fastcall JocGwent::cardClicked(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{

		if(myTurn)
		{

			//Memo1->Lines->Add("click");
			TImage* clickedImg=(TImage*) Sender;
			int index=  clickedImg->Tag;
			Card* card= Cards[index];
			//if right button then toggle description
			if(Button == mbRight)
			{
			  //	card->toggleDescription();
				return;
			}

			//handle abilities
			if(!droppedCard)
			{
				if(btl->onBoard(index))
				{

					Ability* ab=card->getAbility();
					if(ab->getAbilityType()=="order")
					{

						Order* ord=dynamic_cast<Order*>(ab);
					   if(ord->canBeUsed()&&!btl->inOnHold(index))
					   {
							if(btl->highlightValidTargets (Cards,card))
						   {
								//there was at least 1 match
							   //ability can be used;
								//droppedCard=card;

						   }
							droppedCard=card;
							//droppedCard=card;

					   }

					}
					else
					{
						return;
					}

				}

			}
			else
			{
				//for targeting
				targetedCard=card;
				//targetedCard->Muta(700,700);
				if(targetedCard!=droppedCard && btl->isTargetValid(targetedCard))
				{
	//				 Ability* ab=droppedCard->getAbility();
	//				if(droppedCard->getAbility()->getAbilityType()=="order")
	//				{
	//
	//					Order* ord=dynamic_cast<Order*>(ab);
	//					ord->signalUsed();
	//					((OrderCardUI*)droppedCard->cardInterface)->modifyOrderUI(ord->getNoOfCharges());
	//				}
	//			   targetWasSelected=true;
					droppedCard->triggerAbility(targetedCard,effects,btl);
					droppedCard->takeCareOfOrder();
					btl->CalculateScore(Cards);
					btl->clearHighlightedTargets();
				  //	btl->CalculateScore(Cards);
					//droppedCard=nullptr;
				}
			}
        }
//

}

JocGwent::~JocGwent()
{
	   for(int i=0;i<Cards.size();i++){
		delete Cards[i];
	  }
	  Cards.clear();

	   for(int i=0;i<prototypes.size();i++){
		delete prototypes[i];
	  }
	  prototypes.clear();

}

bool JocGwent::endTurn()
{
	if( droppedCard)
	{
	   return switchTurn();
	}
	return 0;

}

bool JocGwent::switchTurn()
{

	turn++;
	if(turn==2)
	{
		turn=0;
		//la finalul unui tur pentru ambii playeri
		//parcurgem vectorul de efecte si le declansam
		for(int i=0;i<2;i++)
		{
			int rowSize= effects[i].size();
			for(int j=0;j<effects[i].size();j++)
			{
				pair current=effects[i][j];
				//daca i e zero e bleed, altfel e vitality
				int sign=i?1:-1;
				UnitCard* carte=dynamic_cast < UnitCard* >(Cards[current.first]);
				UnitCardUI* unit=dynamic_cast < UnitCardUI* >(carte->cardInterface);
			   //	int oldpw=unit->getPower();
				carte->modificaPower(sign*1);
				if(unit->getPower()<1)
				{
					carte->destroyUI();
					effects[i].erase( effects[i].begin()+j);
					btl->freePosition(carte->getIndex());
                    //aici stergi pozitia
				}
				else
				{

					if(current.second==1)
					{
					   //s-a dus durata deci scoate-l din sir
	//				  effects[i].clear();
					   effects[i].erase( effects[i].begin()+j);
					   //scoate efectul de pe carte
					   unit->removeEffect();
					   j--;
					}
					else
					{
						effects[i][j].second--;
						unit->modifyEffect(effects[i][j].second);
					}
					unit->AranjeazaPower();

                }

			}
		}
		//semnaleaza ca se pot folosi abilitatile de order
		btl->ActivateOrders(Cards);
		//semnaleaza trecerea unui turn pentru periodice
		btl->IncresePeriodicCounter(Cards);
		btl->CalculateScore(Cards);
		btl->clearHighlightedTargets();
	}

	if(!droppedCard){
		//randomly delete a card from hand
	}
	droppedCard=nullptr;
   //	placedCard=0;
	return myTurn=!myTurn;

}

//void JocGwent::passRound()
//{
//
//}
