//---------------------------------------------------------------------------

#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma hdrstop

#include "JocGwent.h"

#define C_Eu 1
#define C_Inamic 2
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define C_HandStart 920
JocGwent::JocGwent(TForm* parent,TImage* boardImg,TClientSocket * socket,
vector<Card*>prototypes,int myCardsStart)
{
   //initializam var locale
	droppedCard=nullptr;
	myTurn=0;
	targetedCard=nullptr;
	targetedBattlefield=nullptr;
	dragedImage= nullptr;
	endingDrag=0;
	passed[0]=passed[1]=false;
	board=boardImg;
	sClient=socket;
//	turn=0;
//	roundNumber=0;
//	targetTimer=new TTimer(parent);
//	targetTimer->Enabled=false;
	deck=nullptr;
	this->parent= parent;
	myDeckStartIndex=myCardsStart;
	//cream battlefield ul
	btl=new Battlefield_Deriv(parent);
	btlInamic= new Battlefield_Deriv(parent,1);
	//cream pachetul de carti
   //	deck=new Deck(cardsInDeckArray);
	this-> prototypes=prototypes;


	Init(parent);


}

void JocGwent::Init(TForm* parent)
{
	//attach listeners for game flow
	board->OnDragOver= boardDragOver;
	board->OnDragDrop= boardDragDrop;
//	targetTimer->OnTimer=targetTimerTimer;
	arataRand=new TLabel (parent);
	arataRand ->Parent=parent;
	TFont *font = new TFont;
	font->Size = 18;
	font->Color = clWhite;
	font->Style = TFontStyles() << fsBold;
	arataRand->Font=font;
	delete font;
	arataRand->Top=C_MyTop;
	arataRand->Left=0;
	arataRand->Font=font;


}

void __fastcall JocGwent::cardMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{

	TImage *clickedImg = (TImage*)Sender;
	if(!clickedImg)
	{
	return;
	}
	int index=  clickedImg->Tag;
	Card* card= Cards[index];
	//if right button then toggle description
	if(Button == mbRight)
	{
		if(!btl->onBoard(index))
		{
		   ShowMessage(card->ability->description);
		}
		else
		{
			card->toggleDescription();
        }


		return;
	}
	if(myTurn&&!placedCard&&!btl->onBoard(index))
	{


		initialPosition=Point( card ->cardInterface->cardImg->Left,card->cardInterface->cardImg->Top);
	   clickedImg->BeginDrag(false,-2);
	   dragedImage= clickedImg;
	}



}

void __fastcall JocGwent::boardDragOver(TObject *Sender, TObject *Source, int X,
		  int Y, TDragState State, bool &Accept)
{
   //	endingDrag=false;
	TImage *draggedImg = (TImage*)Source;
	 if(!draggedImg)
	{
		return;
	}

	if(!myTurn)
	{
		Cards[draggedImg->Tag]->cardInterface->Muta( initialPosition.x,initialPosition.y);
		return;
	}

	if(Y>C_MyTop)
	{
		 Accept = true;

		 Cards[draggedImg->Tag]->cardInterface->Muta(Mouse->CursorPos.x, Mouse->CursorPos.y);
	}


}

void __fastcall JocGwent::cardEndDrag(TObject *Sender, TObject *Target, int X,
int Y)
{

	TImage *draggedImg = (TImage*)Sender;
	if (!Target)
	{
		Cards[draggedImg->Tag]->cardInterface->Muta( initialPosition.x,initialPosition.y);
	}
}

void __fastcall JocGwent::boardDragDrop(TObject *Sender, TObject *Source, int X,
		  int Y)
{
	  TImage* currentImage=  (TImage*)Source;

	  int index=currentImage->Tag;
	  Card* card= Cards[index];
	  //pune la loc in hand
	  if(!myTurn||endingDrag)
	{
		card->cardInterface->Muta( initialPosition.x,initialPosition.y);
		return;
	}


	  UnicodeString myHand=Util::join(hand,"#");
	  card->placeOnBattlefield(btl,Point(X,Y));
	  placedCard=true;
	  int indexSters=Util::stergeIndex(hand,index);
	   myHand=Util::join(hand,"#");
	  sClient->Socket->SendText(IntToStr(C_Muta)+"#"+IntToStr(index)+"#"+IntToStr(X)+"#"+IntToStr(Y)+"#"+IntToStr(indexSters)+"#");

	  btl->CalculateScore(Cards);


	  Ability* ab=card->getAbility();

	if(ab->type=="order")
	{
		if(!ab->getZeal())
		{
			btl->adToOnHold(index);
		}
		return;
	}

	  int side=card->getTargetObject()->getSide();
	  if(!side){
		card->triggerAbility(card,effects,btl,btlInamic);
		sClient->Socket->SendText(IntToStr(C_TriggerAbility)+"#"+IntToStr(index)+"#"+IntToStr(index)+"#");
		btl->CalculateScore(Cards);

	  }
	  else{

			targetedBattlefield=btlInamic;
			if(side==C_Ally)
			{
				targetedBattlefield=btl;
			}

		   if(targetedBattlefield->highlightValidTargets (Cards,card))
		   {
				//there was at least 1 match
			   //ability can be used;
				droppedCard=card;

		   }
		  else
			{

				card->takeCareOfSpecialCard();
			}

	  }

	 btl->CalculateScore(Cards);
}

//void __fastcall JocGwent::targetTimerTimer(TObject *Sender)
//{
//
//
//}

//---------------------------------------------------------------------------

void __fastcall JocGwent::cardClicked(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{

		if(myTurn)
		{


			TImage* clickedImg=(TImage*) Sender;
			int index=  clickedImg->Tag;
			Card* card= Cards[index];
//			//if right button then toggle description
//			if(Button == mbRight)
//			{
//			  //	card->toggleDescription();
//				return;
//			}

			//handle abilities
			if(!droppedCard)
			{
				if(!card->cardInterface->hasLock()&&btl->onBoard(index))
				{

					Ability* ab=card->getAbility();
					if(ab->getAbilityType()=="order")
					{

						Order* ord=dynamic_cast<Order*>(ab);
					   if(ord->canBeUsed()&&!btl->inOnHold(index))
					   {
							int side= card->getTargetObject()->getSide();
							targetedBattlefield=btlInamic;
							if(side==C_Ally)
							{
								targetedBattlefield=btl;
							}
							if(targetedBattlefield->highlightValidTargets (Cards,card))
						   {
								//there was at least 1 match
							   //ability can be used;
								droppedCard=card;

						   }


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

				if(targetedCard!=droppedCard && targetedBattlefield->isTargetValid(targetedCard))
				{

					int targetIndex =targetedCard->nrInst;
					int droppedIndex =droppedCard->nrInst;
					droppedCard->triggerAbility(targetedCard,effects,btl,btlInamic);
					int size=0;size+=0;
					UnicodeString mesaj=  IntToStr(C_TriggerAbility)+"#"+IntToStr(droppedIndex)+"#"+IntToStr(targetIndex)+"#";
					sClient->Socket->SendText(mesaj);

					droppedCard->takeCareOfOrder();
					btl->CalculateScore(Cards);
					btlInamic->CalculateScore(Cards);
					btl->clearHighlightedTargets();
					btlInamic->clearHighlightedTargets();

					targetedBattlefield=nullptr;

					droppedCard=nullptr;
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

	   for(int i=0;i<enemyCardbacks.size();i++){
		delete enemyCardbacks[i];
	  }
	   enemyCardbacks.clear();

	   delete btl;
	   delete btlInamic;
	   delete deck;
	   delete arataRand;
	   arataRand=nullptr;


}

bool JocGwent::endTurn()
{
	if( placedCard/*&&myTurn*/)
	{

		if(!hand.size())
		{
			passed[0]=true;

		}
		throw Util(100);

	}

   return 0;

}

bool JocGwent::switchTurn()
{

     if(!arataRand||!btl||!btlInamic||!deck)
	{
		throw Util(100);
	}

	if(myTurn&&!placedCard&&hand.size()){
		endingDrag   =1;
		dragedImage->EndDrag(true);
		//randomly delete a card from hand
		int randNumber=Util::randomNumber(hand.size());
		sClient->Socket->SendText(IntToStr(C_StergeHandInamic)+"#"+IntToStr(randNumber)+"#");
		Cards[hand[randNumber]]->destroyUI();
		hand.erase( hand.begin()+randNumber);
		endingDrag=false;

	}

	  arataRand->Caption="";


	placedCard=0;

    if(myTurn)
	{
	   triggerEffects(false);
	  btl->clearHighlightedTargets();
	  btlInamic->clearHighlightedTargets();
	  btlInamic->IncresePeriodicCounter(Cards);
	  btlInamic->ActivateOrders(Cards);
	}
	else
	{
		triggerEffects(true);

			arataRand->Caption="Randul meu";

		btl->IncresePeriodicCounter(Cards);
		btl->ActivateOrders(Cards);
//		endedTurn=0;
	}

    btl->CalculateScore(Cards);
	btlInamic->CalculateScore(Cards);


	droppedCard=nullptr;

	if(!passed[0]&&!hand.size())
	{

		passed[0]=true;

	}
	if(passed[0]&& passed[1])
	{

		 arataRand->Caption="";


		int winner=0;
		int scorInamic = StrToInt(btlInamic->score->Caption);
		int scorulMeu=StrToInt(btl->score->Caption);
		if(scorulMeu >scorInamic)
		{
			winner=C_Eu;
		}
		else if( scorulMeu<scorInamic)
		{
			winner=C_Inamic;
		}
        myTurn=0;
		throw Util(winner);
	}

	return myTurn=!myTurn;

}

 void JocGwent::triggerEffects(bool enemy)
 {
       for(int i=0;i<2;i++)
		{
			int rowSize= effects[i].size();
			for(int j=0;j<effects[i].size();j++)
			{
				pair current=effects[i][j];
                if(btl->onBoard(current.first )==!enemy)
				{
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
		}
 }

void JocGwent::creeazaCartile(vector<int>origin,vector<int> CardsInDeck,int deckStartIndex)
{
	int  size= origin.size();
	size+=0;
	vector<int> deckIndexes;
	   for(int i=0;i<origin.size();i++)
	{
		if(i>=deckStartIndex&&deckIndexes.size()< CardsInDeck.size())
		{
			deckIndexes.push_back(i);
		}
		int index= origin[i];
		Card* test=nullptr;
		Card* prototype=prototypes[index];
		prototype->Copiaza(test,i);
		Cards.push_back(test);

	}
	deck=new Deck(deckIndexes);
    hand=deck->imparteCartile(10);


}

 void JocGwent::afiseazaCartile(TForm* parent)
 {

		int left=C_Left_Start;

		 UnicodeString myHand=Util::join(hand,"#");
		 int enemyStartIndex=0;
		if(!myDeckStartIndex)
		{
			enemyStartIndex=deck->cards.size()+hand.size();
		}
		UnicodeString enemyFaction=Cards[enemyStartIndex+1]->faction;

		TPngImage* img = new TPngImage();
		for(int i=0;i<hand.size();i++)
		{
			int index= hand[i];
			Card* test=Cards[index];

			test->buildCardUI(Point(left,C_HandStart),parent);
			test ->cardInterface->frame->OnMouseDown =cardMouseDown;
			test ->cardInterface->frame->OnMouseUp =cardClicked;
            test ->cardInterface->frame->OnEndDrag =cardEndDrag;

			TImage* cardback=new TImage(parent);
		 cardback->Parent = parent;

		 img->LoadFromFile("symbols/"+enemyFaction+"_cardback.png");
		 cardback->Picture->Assign(img);
		 cardback->Width=C_Ratio*C_CardHeight;
		 cardback->Height= C_CardHeight;
		 cardback->Stretch=true;
		  cardback->Left=left;
		 cardback->Top=-C_CardHeight/2;
		 enemyCardbacks.push_back(cardback);
			left+=C_CardHeight*C_Ratio;

		}
		delete img;
 }

 void JocGwent::mutaCarteInamic(int indexCarte,TPoint pos )
{

	int index= indexCarte;
	Card* enemyCard= Cards[index];
	enemyCard->buildCardUI(pos,parent);
	enemyCard->placeOnBattlefield(btlInamic,pos);
	enemyCard ->cardInterface->frame->OnMouseDown =cardMouseDown;
	enemyCard ->cardInterface->frame->OnMouseUp =cardClicked;
	btlInamic->CalculateScore(Cards);
	if(enemyCard->ability->type=="order")
	{
	  btlInamic->adToOnHold(index);
	}
   	enemyCard->takeCareOfSpecialCard();

}

void JocGwent::stergeDinHandInamic(int indexManaInamic)
{
	delete  enemyCardbacks[indexManaInamic];
	enemyCardbacks.erase( enemyCardbacks.begin()+indexManaInamic);
     if(!enemyCardbacks.size())
	{
		passed[1]=true;
	}

}

 void JocGwent::triggerEnemyAbility(int trigger,int target)
 {
	 Card * trigeringCard=Cards[trigger];
	 Card * targetedCard=Cards[target];
	 trigeringCard->triggerAbility(targetedCard,effects,btl,btlInamic);
	 trigeringCard->takeCareOfOrder();
	 btl->CalculateScore(Cards);
	 btlInamic->CalculateScore(Cards);
 }

 bool JocGwent::didIPass()
 {
	 return passed[0];
 }
 void JocGwent::opponentPassed()
 {

	 passed[1]=true;
 }

//void JocGwent:: faCurat()
//{
//	 throw Util(0);
//}

