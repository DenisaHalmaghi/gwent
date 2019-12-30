//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Forma_Init.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define C_CardbackRatio 1.498046875
#define C_PCThreshold 160
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	//Button1->Caption="henlo";
	factions.push_back("monsters");
	factions.push_back("scoia");
	 cardNr=0;
	 provCost=0;
	//cardDisplayContainer->AutoScroll =true;
	Target * target1=new Target(C_Ally,"unit");

	Ability* ab1=new Charges(C_Destroy,3,3);
	Card* card1=new UnitCard(0,"Aglais","scoia","aglais",9,target1,ab1,2,0);
	prototypes.push_back(card1);

	Ability* ab2=new Ability(C_Purify,2);
	Card* card2=new Card(1,"Aglais","monsters","adda_striga",10,target1,ab2);
	prototypes.push_back(card2);


	Ability* ab3=new Ability(C_Lock,2);
	Card* card3=new UnitCard(2,"Aglais","scoia","milaen",8,target1,ab3,10,0);
	prototypes.push_back(card3);


	Ability* ab4=new Periodic(C_Damage,2,1);
	Card* card4=new UnitCard(3,"Aglais","monsters","katakan",8,target1,ab4,10,0);
	prototypes.push_back(card4);

}
//---------------------------------------------------------------------------



void __fastcall TForm4::playBtnClick(TObject *Sender)
{
//	 if(cardNr<25)
//	 {
//		 return;
//	 }
//
//	 if(provCost>C_PCThreshold)
//	 {
//		 return;
//	 }
		Form1->prototypes=prototypes;
//		vector<int>deckArray;
//		for(int i=0;i<currentDeck.size();i++)
//		{
//			pair<int,int> current= currentDeck[i];
//			for(int j=0;j<current.second;j++)
//			{
//				deckArray.push_back(current.first);
//            }
//        }

		Form1->deckArray=currentDeck;

		Form1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::deckCrBtnClick(TObject *Sender)
{

	  //remove all previously displayed cards
		for(int i=0;i<displayedCards.size();i++)
		{
			displayedCards[i]->destroyUI();
		}
		displayedCards.clear();

		//show faction cardbacks
	   for(int i=0;i<factions.size();i++)
	   {
		 TImage* cardback=new TImage(this);
		 cardback->Parent = this;
		 TPngImage* img = new TPngImage();
		 img->LoadFromFile("symbols/"+factions[i]+"_cardback.png");
		 cardback->Picture->Assign(img);
		 cardback->Width=180;
		 cardback->Height= C_CardbackRatio* cardback->Width;
		 cardback->Stretch=true;
		 cardback->Left=500+i*cardback->Width+i*20;
		 cardback->Top=500;
		 cardback->Tag=i;
		 cardbacks.push_back(cardback);
		 cardback->OnClick=ChooseFaction;
	   }
}
//---------------------------------------------------------------------------

void __fastcall TForm4::exitBtnClick(TObject *Sender)
{
     for(int i=0;i<prototypes.size();i++)
	  {
		  delete prototypes[i];

	  }
    exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::ChooseFaction(TObject *Sender)
{
		  TImage* img=  (TImage*) Sender;
		  //set faction
		  selectedFaction=  factions[img->Tag];
		 // Button1->Caption=selectedFaction;
		  //delete faction cardbacks
		  for(int i=0;i<cardbacks.size();i++)
		  {
			   delete cardbacks[i];
		  }
		  cardbacks.clear();

		  noOfCards->Visible=true;
		  playBtn ->Visible=true;

		  int top=5;//cardDisplayContainer->Top;//24
		  int side_left=15;//cardDisplayContainer->Left; //533
		  int side_right=side_left+cardDisplayContainer->Width;
		  int left=side_left;
		  int cardWidth= C_CardHeight*C_Ratio;
		  for(int j=0;j<1;j++){
		  for(int i=0;i<prototypes.size();i++)
		  {
			  Card* card=prototypes[i];
			  //if(card->getFaction()/*==selectedFaction*/)
			  //{

				//reached right side
				//begin new row
				if(left+cardWidth>=side_right)
				{
				   left=side_left;
				   top+= C_CardHeight+15;
				}


				  card->buildCardUI(Point(left,top),ScrollBox1);
				  card->cardInterface->frame->OnClick=PutCardInDeck;
				  displayedCards.push_back(card);
				  left+=cardWidth+15;
			  //}
		  }
		  }


}
//---------------------------------------------------------------------------

void __fastcall TForm4::ScrollBar1Scroll(TObject *Sender, TScrollCode ScrollCode,
		  int &ScrollPos)
{
   //	cardDisplayContainer->ScrollBy(0,-ScrollPos);
   // cardDisplayContainer->Top+=5;
}
//---------------------------------------------------------------------------




void __fastcall TForm4::PutCardInDeck(TObject *Sender)
{
		TImage* img=(TImage*)Sender;
		int tag=img->Tag;
		bool existent=false;
		bool adaugat=false;
		for(int i=0;i<currentDeck.size();i++)
		{
			pair<int,int> current=currentDeck[i];
			if(current.first==tag)
			{
				existent=true;
				if(current.second==1)
				{
					adaugat=true;
				   currentDeck[i].second++;
				}
				break;
            }
		}

		if(!existent)
		{
			currentDeck.emplace_back( tag,1);
			adaugat=true;
		}

		if(adaugat)
		{
			cardNr++;
			provCost+= prototypes[tag]->getProvisionCost();
			noOfCards->Caption="Carti:"+ IntToStr(cardNr)+" /25"+"\nProvision Cost:"+IntToStr(provCost)+"/160";
		}


   //	TForm* forma=new TForm(this);
	//forma->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{
	//currentDeck=standard deck
	playBtn->Click();
}
//---------------------------------------------------------------------------

