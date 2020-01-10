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
		btnUnu->Visible=false;
		UnicodeString deckString=IntToStr(C_Deck)+"#";
		deckString+=Util::join( deckArray,"#");
		sClient->Socket->SendText(deckString);

		Memo1->Lines->Add("sent"+deckString);


}
//---------------------------------------------------------------------------
void __fastcall TForm1::exitBtnClick(TObject *Sender)
{

	   btnUnu->Visible=1;
	   //a inceput jocul dar nu s-a terminat inca
	   if(joc&&!gameIsOver)
	{
		ShowMessage("Ai pierdut!");
		sClient->Socket->SendText(IntToStr(C_Forfeit)+"#");

	}
	sClient->Active=false;
	  delete joc;
	   Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::turnTimerTimer(TObject *Sender)
{

	   //!!!check if any or both players passed and behave accordingly
	   //!!restrictioneaza in functie de turn
		turnTimer->Enabled=false;
	   bool turn;
	   try
	   {
         turn=joc->switchTurn();
	   }
	   catch(Util u)
	   {
			 handleEnd(u.winner);

	   }

	   Memo1->Lines->Add(turn);
	   if(!turn)
	   {
		  sClient->Socket->SendText(IntToStr(C_Turn)+"#");
	   }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::passBtnClick(TObject *Sender)
{
	//daca am pus jos o carte imi pot termina tura
		try
		   {
			joc->endTurn();

		   }
		   catch(Util u)
		   {
			 turnTimer->Enabled=false;
			sClient->Socket->SendText(IntToStr(C_Turn)+"#");

				try
			   {
					joc->switchTurn();
			   }
			   catch(Util u)
			   {

                        turnTimer->Enabled=false;
						 handleEnd(u.winner);

			   }

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
	joc=nullptr;
	sClient->Active=true;
	gameIsOver=0;
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


		   UnicodeString deckCards=Util::join(deckArray,"#");
			UnicodeString merged=Util::join(mergedDecks,"#");
			Memo1->Lines->Add(merged);
			Memo1->Lines->Add(myDeckStartIndex);
			Memo1->Lines->Add(deckCards);
		   joc->creeazaCartile(mergedDecks,deckArray,myDeckStartIndex);
		   joc->afiseazaCartile(this);
            if(message[1])
		   {
				Memo1->Lines->Add(joc->switchTurn());
				turnTimer->Enabled=true;

		   }
		  // UnicodeString merged=Util::join(mergedDecks,"#");

		   break;
		}

		case C_Turn:
		{


		//merge in gol

			try
		   {
			Memo1->Lines->Add(joc->switchTurn());
		   }
		   catch(Util u)
		   {
				handleEnd(u.winner);
			  return;
		   }
			if(joc->didIPass())
			{

				 try
			   {

				joc->switchTurn();
			   }
			   catch(Util u)
			   {
				  handleEnd(u.winner);
				  return;
			   }

				Memo1->Lines->Add("am dat pass");
				sClient->Socket->SendText(IntToStr(C_Turn)+"#");
                Memo1->Lines->Add("am trimis passul");
				return;
			}




			turnTimer->Enabled=true;

			break;
		}

			case C_Muta:
		{
			joc->mutaCarteInamic(message[1],Point(message[2],message[3]));
			joc->stergeDinHandInamic(message[4]);

			break;
		}

		case C_TriggerAbility:
		{

			int first=message[1];
			int second= message[2];
			joc->triggerEnemyAbility(message[1],message[2]);

			break;
		}

			case C_Forfeit:
		{
			//e gata jocul
//			sClient->Active=false;
			ShowMessage("Oponentul tau a renuntat.Ai castigat!");
			gameIsOver=1;
			break;
		}

		case C_StergeHandInamic:
		{
            joc->stergeDinHandInamic(message[1]);

			break;
		}


    }

}



void TForm1::handleEnd(int winner)
{
    if(winner>2)
	{
		return;
	}

	UnicodeString mesaj;
	mesaj="Ai pierdut!";
	if(!winner)
	{
		mesaj="Egalitate";
	}
	if(winner==1)
	{
		mesaj="Ai castigat!";
	}
	ShowMessage(mesaj);
	gameIsOver=1;
}
//---------------------------------------------------------------------------

