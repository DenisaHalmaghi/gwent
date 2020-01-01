//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Forma_Joc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
  //  Button1->Caption="hi";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnUnuClick(TObject *Sender)
{

		UnicodeString deckString=IntToStr(C_Deck)+"#";
		deckString+=Util::join( deckArray,"#");
		sClient->Socket->SendText(deckString);
		//sClient->Socket->SendText("testt");
		Memo1->Lines->Add("sent"+deckString);

	//testShape->Canvas->TextOut(2,3"a");

//	auto fn1 =  bind(myMouseDown, _1, _2, _3,_4,_5,myUICard);
//	myUICard->cardImg->OnMouseDown = myMouseDown;
//	Ability* ab2=new Ability(C_Boost,2,0);
//	Card* card2=new UnitCard("Aglais","monsters","adda_striga",10,1,ab2,6,0);
//	Cards.push_back(card2);
//	CardUI* myUICard2=new UnitCardUI(card2,300+myUICard->getWidth()+20,400,this);
//	UICards.push_back(myUICard2);
//	myUICard2->cardImg->OnMouseDown =imgTestMouseDown;
//	myUICard2->cardImg->OnClick =cardClicked;
//	units.push_back(myUICard2);
//	//delete myUICard;
//
//	Ability* ab3=new Ability(C_Damage,3,0);
//	Card* card3=new Card("Aglais","scoia","milaen",9,"artefact",1,ab3);
//	Cards.push_back(card3);
//	CardUI* myUICard3=new NonUnitCardUI(card3,500+myUICard->getWidth()+20,400,this);
//	UICards.push_back(myUICard3);
//	myUICard3->cardImg->OnMouseDown =imgTestMouseDown;
   //	myUICard3->cardImg->OnClick =cardClicked;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::exitBtnClick(TObject *Sender)
{
		sClient->Active=false;
	  //	delete sClient;
		delete joc;
		exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::turnTimerTimer(TObject *Sender)
{
		//To do:
	   //!!!check if any or both players passed and behave accordingly
	   //!!restrictioneaza in functie de turn
		turnTimer->Enabled=false;
	   bool turn=joc->switchTurn();
	   Memo1->Lines->Add(turn);
	   if(!turn)
	   {
		  sClient->Socket->SendText(IntToStr(C_Turn)+"#");
       }
	   //introducem un delay

		//turnTimer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::passBtnClick(TObject *Sender)
{
        	 //daca am pus jos o carte imi pot termina tura
		 if(joc->endTurn())
		 {
			  turnTimer->Enabled=false;
			  turnTimer->Enabled=true;
		 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::boardImgClick(TObject *Sender)
{
	Label1->Caption=Mouse->CursorPos.y;
	 Memo1->Lines->Add("click");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::boardImgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
		   Memo1->Lines->Add("up");

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
   	sClient->Active=true;
	int nrOfCards= deckArray.size();

   // sClient->Socket->SendText(Memo->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sClientConnect(TObject *Sender, TCustomWinSocket *Socket)

{
   // sClient->Socket->SendText("testt2");
	//int nrOfCards= deckArray.size();
   //	UnicodeString deckString=Util::join( deckArray,"#");
   //	sClient->Socket->SendText(deckString);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
	UnicodeString text= Socket->ReceiveText();
	vector<int> message=Util::split(text,"#");
	int size=  message.size();
	Memo1->Lines->Add(text);
	size+=0;
	int firstPart=message[0];
	if(message[0]==C_TriggerAbility)
	{
		int size=0;
		size+=0;
    }
	switch(message[0])
	{
		case C_GameStart:
		{
			int myDeckStartIndex=0;
			vector<int>mergedDecks;
		   if(message[1])
		   {
			  mergedDecks=deckArray;
			  mergedDecks.insert(mergedDecks.end(),message.begin()+3,message.end());
		   }
		   else
		   {
			  mergedDecks.insert(mergedDecks.begin(),deckArray.begin(),deckArray.end());
			  mergedDecks.insert(mergedDecks.begin(),message.begin()+3,message.end());
			  myDeckStartIndex=  mergedDecks.size()- deckArray.size();
		   }
		   joc=new JocGwent(this,boardImg,sClient,prototypes,myDeckStartIndex);
		   if(message[1])
		   {
				Memo1->Lines->Add(joc->switchTurn());
				turnTimer->Enabled=true;

           }

		   UnicodeString deckCards=Util::join(deckArray,"#");
			UnicodeString merged=Util::join(mergedDecks,"#");
			Memo1->Lines->Add(merged);
			Memo1->Lines->Add(myDeckStartIndex);
			Memo1->Lines->Add(deckCards);
		   joc->creeazaCartile(mergedDecks,deckArray,myDeckStartIndex);
		   joc->afiseazaCartile(this);
		  // UnicodeString merged=Util::join(mergedDecks,"#");

		   break;
		}

		case C_Turn:
		{
			Memo1->Lines->Add(joc->switchTurn());
			turnTimer->Enabled=true;

			break;
		}

			case C_Muta:
		{
			joc->mutaCarteInamic(message[1],Point(message[2],message[3]));

			break;
		}

		case C_TriggerAbility:
		{
			UnicodeString joinedMessage=Util::join(message,"__");
			Memo1->Lines->Add(joinedMessage);
			int first=message[1];
			int second= message[2];
			joc->triggerEnemyAbility(message[1],message[2]);

			break;
		}


    }

}
//---------------------------------------------------------------------------

