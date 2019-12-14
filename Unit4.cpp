//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::btnUnuClick(TObject *Sender)
{
    joc=new JocGwent(this,boardImg);
	turnTimer->Enabled=true;
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
void __fastcall TForm4::exitBtnClick(TObject *Sender)
{
     	delete joc;
		exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::turnTimerTimer(TObject *Sender)
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
void __fastcall TForm4::passBtnClick(TObject *Sender)
{
        	 //daca am pus jos o carte imi pot termina tura
		 if(joc->endTurn())
		 {
			  turnTimer->Enabled=false;
			  turnTimer->Enabled=true;
		 }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::boardImgClick(TObject *Sender)
{
	Label1->Caption=Mouse->CursorPos.y;
	 Memo1->Lines->Add("click");
}
//---------------------------------------------------------------------------
void __fastcall TForm4::boardImgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
		   Memo1->Lines->Add("up");

}
//---------------------------------------------------------------------------

