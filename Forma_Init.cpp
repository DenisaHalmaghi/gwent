//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Forma_Init.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define C_CardbackRatio 1.498046875
#define C_PCThreshold 100
#define C_MinCards 14

TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{

	factions.push_back("monsters");
	factions.push_back("scoia");
	 cardNr=0;
	 provCost=0;

	Target * target1=new Target(C_Enemy,"unit");
	Target * target2=new Target(C_Ally,"unit");
	Target * target3=new Target(C_Self,"unit");


	int i=0;


	prototypes.push_back(new Card(i++,"Adda Striga","monsters","adda_striga",6,target1,new Ability(C_Destroy,2)));

	prototypes.push_back(new UnitCard(i++,"Aglais","monsters","katakan",8,target1,new Periodic(C_Damage,10,1),10));

	prototypes.push_back(new UnitCard(i++,"Nekurat","monsters","Nekurat",5,target1,new Periodic(C_Bleed,2,2),3));

	prototypes.push_back(new Special_Card(i++,"Crimson Curse","monsters","Crimson_Curse",9,target1,new Ability(C_Bleed,8)));

	prototypes.push_back(new UnitCard(i++,"Queen of The Night","monsters","Night_Queen",9,target2,new Ability(C_Purify,4),4));

	prototypes.push_back(new UnitCard(i++,"Wild Hunt Navigator","monsters","Wild_Hunt_Navigator",5,target2,new Ability(C_Boost,2),3));

	prototypes.push_back(new UnitCard(i++,"Wild Hunt Warrior","monsters","Wild_Hunt_Warrior",5,target1,new Ability(C_Damage,2),3));

	prototypes.push_back(new UnitCard(i++,"Protofleder","monsters","Protofleder",10,target1,new Charges(C_Damage,1,3,1),3));

	prototypes.push_back(new UnitCard(i++,"Weavess","monsters","Weavess",8,target1,new Ability(C_Damage,4),3));

	prototypes.push_back(new UnitCard(i++,"Whispess","monsters","Whispess",8,target2,new Ability(C_Boost,4),3));

	prototypes.push_back(new UnitCard(i++,"Alp","monsters","Alp",5,target1,new Ability(C_Bleed,4),2));

	prototypes.push_back(new UnitCard(i++,"Gael","monsters","Gael",7,target1,new NonRep(C_Damage,2),3));

	prototypes.push_back(new UnitCard(i++,"Nithral","monsters","Nithral",9,target1,new Ability(C_Lock,2),5));

	prototypes.push_back(new UnitCard(i++,"Speartip Asleep","monsters","Speartip_Asleep",9,target3,new Ability(C_Damage,0),9));

	prototypes.push_back(new UnitCard(i++,"Speartip Awake","monsters","Speartip_Awake",14,target3,new Ability(C_Damage,0),12));

	prototypes.push_back(new UnitCard(i++,"Dettlaff","monsters","Dettlaff",12,target1,new Periodic(C_Bleed,1,1),5));

	prototypes.push_back(new Special_Card(i++,"Parasite","monsters","Parasite",7,target1,new Ability(C_Damage,6)));

	prototypes.push_back(new UnitCard(i++,"Caretaker","monsters","Caretaker",11,target1,new Ability(C_Destroy,2),6));



	prototypes.push_back(new UnitCard(i++,"Ronvid The Annoying","scoia","Ronvid",6,target3,new Ability(C_Boost,5),1));

	prototypes.push_back(new Special_Card(i++,"Runeword","scoia","Runeword",4,target2,new Ability(C_Vitality,4)));

	prototypes.push_back(new Special_Card(i++,"Moon Dust","scoia","Moon_Dust",4,target1,new Ability(C_Damage,4)));

	prototypes.push_back(new UnitCard(i++,"Priscilla","scoia","Priscilla",12,target2,new Periodic(C_Vitality,1,1),5));

	prototypes.push_back(new UnitCard(i++,"Dandelion","scoia","Dandelion",12,target2,new Periodic(C_Boost,1,1),5));

	prototypes.push_back(new UnitCard(i++,"Keira Metz","scoia","Keira_Metz",10,target2,new Charges(C_Vitality,3,2,1),5));

	prototypes.push_back(new UnitCard(i++,"Nenneke","scoia","Nenneke",8,target2,new Charges(C_Boost,1,4,1),4));

	prototypes.push_back(new UnitCard(i++,"Kaedweni Sergeant","scoia","Kaedweni_Sergeant",5,target2,new Charges(C_Boost,1,2),4));

	prototypes.push_back(new UnitCard(i++,"Margarita","scoia","Margarita",9,target1,new Ability(C_Lock,2),5));

	prototypes.push_back(new UnitCard(i++,"Hubert Rejk","scoia","Hubert_Rejk",9,target1,new NonRep(C_Poison,2),5));

	prototypes.push_back(new UnitCard(i++,"Anna Strenger","scoia","Anna_Strenger",9,target2,new Ability(C_Purify,2),4));

	prototypes.push_back(new UnitCard(i++,"Prince Stennis","scoia","Prince_Stennis",9,target1,new Ability(C_Destroy,2),4));

	prototypes.push_back(new UnitCard(i++,"Ballista","scoia","Ballista",5,target1,new NonRep(C_Damage,2),3));

	prototypes.push_back(new UnitCard(i++,"Cintrian Spellweaver","scoia","Cintrian_Spellweaver",5,target1,new Periodic(C_Damage,1,2),5));

	prototypes.push_back(new UnitCard(i++,"Dryad Ranger","scoia","Dryad_Ranger",5,target1,new Ability(C_Poison,2),3));

	prototypes.push_back(new UnitCard(i++,"Ivo","scoia","Ivo",11,target1,new Ability(C_Destroy,2),6));

	prototypes.push_back(new UnitCard(i++,"Milaen","scoia","milaen",9,target1,new Ability(C_Damage,4),9));

	prototypes.push_back(new UnitCard(i++,"Aglais","scoia","aglais",9,target2,new Charges(C_Vitality,2,3,1),2));

}

//---------------------------------------------------------------------------



void __fastcall TForm4::playBtnClick(TObject *Sender)
{
	 if(cardNr<C_MinCards)
	 {
		 ShowMessage("Prea putine carti");
		 return;
	 }

	 if(provCost>C_PCThreshold)
	 {
		 ShowMessage("Provision Cost prea mare");
		 return;
	 }

		UnicodeString deckString="deck#"+IntToStr(cardNr)+"#";
		deckString+=Util::join( currentDeck,"#");

		myMemo->Lines->Add(deckString);


		//pass variables
		Form1->prototypes=prototypes;
		Form1->deckArray=Util::desfaPairs(currentDeck);
		cleanUp();
		Form1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::deckCrBtnClick(TObject *Sender)
{


		cleanUp();

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
		  noOfCards->Caption="Carti:0 /"+IntToStr(C_MinCards);
		  cardNr=0;
			currentDeck.clear();
		  selectedFaction=  factions[img->Tag];

		  //delete faction cardbacks
		  for(int i=0;i<cardbacks.size();i++)
		  {
			   delete cardbacks[i];
		  }
		  cardbacks.clear();

		  noOfCards->Visible=true;
		  playBtn ->Visible=true;

		  int top=5;
		  int side_left=15;
		  int side_right=side_left+cardDisplayContainer->Width;
		  int left=side_left;
		  int cardWidth= C_CardHeight*C_Ratio;
		  for(int j=0;j<1;j++){
			  for(int i=0;i<prototypes.size();i++)
			  {
				  Card* card=prototypes[i];
				  if(card->getFaction()==selectedFaction)
				  {

					//reached right side
					//begin new row
					if(left+cardWidth>=side_right)
					{
					   left=side_left;
					   top+= C_CardHeight+15;
					}


					  card->buildCardUI(Point(left,top),ScrollBox1);
					  card->cardInterface->frame->OnClick=PutCardInDeck;
					  card->cardInterface->frame->OnMouseUp=showCardDescription;
					  displayedCards.push_back(card);
					  left+=cardWidth+15;
				  }
			  }
		  }


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
			noOfCards->Caption="Carti:"+ IntToStr(cardNr)+" /"+IntToStr(C_MinCards)+"\nProvision Cost:"+IntToStr(provCost)+"/"+IntToStr(C_PCThreshold);
		}



}
//---------------------------------------------------------------------------


void __fastcall TForm4::showCardDescription(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbRight)
	{

		TImage* img=(TImage*)Sender;
		int tag=img->Tag;
		prototypes[tag]->toggleDescription();

	}
}
//---------------------------------------------------------------------------
void TForm4::cleanUp()
{
        //remove all previously displayed cards
		for(int i=0;i<displayedCards.size();i++)
		{
			displayedCards[i]->destroyUI();
		}
		displayedCards.clear();
		noOfCards->Caption="";
		cardNr=0;
		currentDeck.clear();
}
