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
		delete sClient;
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
	   Memo1->Lines->Add(joc->switchTurn());
	   //introducem un delay

		turnTimer->Enabled=true;
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
	//int nrOfCards= deckArray.size();
	UnicodeString deckString=Util::join( deckArray,"#");
	sClient->Socket->SendText(deckString);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
	UnicodeString text= Socket->ReceiveText();
	vector<int> message=Util::split(text,"#");
	int size=  message.size();
    size+=0;
	switch(message[0])
	{
		case C_GameStart:
		{
			vector<int>mergedDecks;
		   if(message[1])
		   {
			  mergedDecks=deckArray;
			  mergedDecks.insert(mergedDecks.begin(),message.begin()+2,message.end());
		   }
		   else
		   {
			  mergedDecks.insert(mergedDecks.begin(),message.begin()+2,message.end());
			  mergedDecks.insert(mergedDecks.begin(),deckArray.begin(),deckArray.end());
		   }
           joc=new JocGwent(this,boardImg,sClient,prototypes,deckArray);
			turnTimer->Enabled=true;
		   joc->creeazaCartile(mergedDecks);
		   joc->afiseazaCartile(this);

		   break;
		}

		case C_SendDecks:
		{
				UnicodeString deckString="deck#";
				deckString+=Util::join( deckArray,"#");
				sClient->Socket->SendText(deckString);
			break;
        }
    }

}
//---------------------------------------------------------------------------

