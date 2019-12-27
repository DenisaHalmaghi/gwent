//---------------------------------------------------------------------------

#pragma hdrstop

#include "CardUI.h"


CardUI::CardUI(){

	cardImg= nullptr;
	factionTop= nullptr;
	factionBottom=nullptr;
	provisionCost=nullptr;
	frame=nullptr;
  //	card=nullptr;
}

int CardUI::getWidth(){

	return cardImg->Width;
}
CardUI::~CardUI(){

	delete cardImg;

}



CardUI::CardUI(TPoint pos,TForm* parent,UnicodeString image,UnicodeString faction,
TCaption pc, Ability* ab,int nrInst){
		// card=c;

		 //luam cartea corespunzatoare din vectorul de carti
		  description=nullptr;
		  frame=nullptr;
		 //initializam imaginile corespunzator
		 cardImg=new TImage(parent);
		 cardImg->Parent = parent;
		 TPngImage* img = new TPngImage();
		 img->LoadFromFile("symbols/"+image+".png");


		 cardImg->Picture->Assign(img);
		 cardImg->Stretch=true;
		 //cardImg->Proportional=true;
		 cardImg->Height=C_CardHeight;
		 cardImg->Width=C_CardHeight*C_Ratio;
		 cardImg->Left =pos.x;
		 cardImg->Top =pos.y;
		 cardImg->Tag=nrInst;


		  //initializam faction bannerul de sus(dreapta)
		 factionTop=new TImage(cardImg);
		 factionTop->Parent = parent;
		 img->LoadFromFile("symbols/"+faction+"_top.png");
		 factionTop->Picture->Assign(img);
		 factionTop->AutoSize =true;


		 //initializam faction bannerul de jos(stnga)
		 factionBottom=new TImage(cardImg);
		 factionBottom->Parent = parent;
		 img->LoadFromFile("symbols/"+faction+"_bottom.png");
		 factionBottom->Picture->Assign(img);
		 factionBottom->AutoSize =true;

		//initializam labelul care arata provision costul
		provisionCost=new TLabel(cardImg);
		provisionCost->Parent=parent;
		provisionCost->AutoSize=true;
		provisionCost->Caption=pc;
		provisionCost->BringToFront();


        frame=new TImage(cardImg);
		frame->Parent= cardImg->Parent;
		img->LoadFromFile("symbols/golden_frame.png");
		frame->Picture->Assign(img);
		frame->Stretch=true;
		frame->Tag=cardImg->Tag;
		//cardImg->Proportional=true;
		frame->Height=C_CardHeight+2;
		frame->Width=C_CardHeight*C_Ratio+2;
		//frame->SendToBack();


		//SET UP FONT
		TFont *font = new TFont;
		font->Size = 18;
		font->Color = clWhite;
		font->Style = TFontStyles() << fsBold;
		provisionCost->Font=font;
		font->Size = 11;
		font->Style = TFontStyles();
		//set up description label
//		description=new TLabel(cardImg);
//		description->Parent=parent;
//		description->Height=C_CardHeight*1.2;
//		description->Color=cl3DDkShadow;
//		description->Transparent=false;
//		description->AutoSize=false;
//		description->Width=cardImg->Width*1.3;
//		description->Font=font;
//		description->WordWrap=true;


		//delete temps
		delete font;
		delete img;

		//set up text
//		UnicodeString text[]=
//		{"Give bleeding for","Give vitality for","Boost a unit by","Damage a unit by",
//		"Poison a unit","Purify a unit","Lock a unit","Destroy a unit if it has at least 8 power"};
//
//		UnicodeString abilityDescription[]=
//		{"Bleeding:Damages a unit by 1 on turn end","Vitality:Boosts a unit by 1 on turn end",
//		"Boost:Increase a Unit's current Power.","Damage:Decrease a Unit's current Power."
//		,"Poison:If a unit has two Poison statuses, destroy it.","Purify:Remove all statuses.",
//		"Lock:Status that disables a card's abilities.","Destroy:Remove a card from the battlefied"
//
//		};
//
//		UnicodeString desc;
//		UnicodeString descBody;
//		UnicodeString type=ab->getAbilityType();
//		int qt= ab->getQuantum();
//
//		int name=ab->getName();
//		descBody=(type=="order"?"\nOrder:":"\nDeploy:")+text[name]+" "+qt+ (name<2?" rounds":"")
//		+"\n\n"+abilityDescription[name];
//		if(type=="order")
//		{
//			Order* order=(Order*)ab;
//			descBody+="\nOrder:Lets the player manually trigger the ability";
//			if(order->getZeal())
//			{
//			   desc+="\nZeal";
//			   descBody+="\nZeal:Order can be used immediately";
//			}
//			int charges=order->getNoOfCharges();
//			if(charges>1)
//			{
//			   desc+="\nCharges:"+IntToStr(charges);
//			   descBody+="\nCharges:Number of times order can be activated";
//			}
//		}
//		else
//		{
//			descBody+="\nDeploy:Trigger this ability when played.";
//		}
//		desc+=descBody;
//
//
//		description->Caption= desc;
		Aranjeaza();
}

void CardUI::Aranjeaza() //pozitioneaza toate elementele relativ la cardImg
{
	int left=cardImg->Left;
	int top= cardImg->Top;

	//faction bannerul de jos(stnga)
	factionBottom->Left=left + cardImg->Width - factionBottom->Width;
	factionBottom ->Top=top + cardImg->Height - factionBottom->Height;

	//faction bannerul de sus(dreapta)
	factionTop->Left =left;
	factionTop->Top =top;

	//provision cost label
	provisionCost->Top=factionBottom ->Top+factionBottom ->Height-provisionCost->Height-5;
	provisionCost->Left=factionBottom ->Left+factionBottom ->Width/2-provisionCost->Width/2;

	//frame-ul
    frame->Left=cardImg->Left;
	frame->Top=cardImg->Top;
	//card description
	if(description)
	{
		description->Top=top;
		description->Left=left+cardImg->Width;
    }

}

void CardUI::Muta(int x,int y){
	   this->cardImg->Left =x;     //aici da eroare
	   this->cardImg->Top =y;
	   Aranjeaza();
}

void CardUI::showDescription(bool yes)
{
	if(yes)
	{
	   description->Transparent=false;
	   return;
	}

	description->Transparent=true;

}

void CardUI::toggleDescription(UnicodeString name,UnicodeString abilityDesc)
{
	if(!description)
	{
		description=new TLabel(cardImg);
		description->Parent=cardImg->Parent;
		description->Height=C_CardHeight*1.2;
		description->Color=cl3DDkShadow;
		description->Transparent=false;
		description->AutoSize=false;
		description->Width=cardImg->Width*1.3;
		description->Font->Size = 11;
		description->Font->Color = clWhite;
		description->WordWrap=true;
		description->Caption=name+"\n"+abilityDesc;
		Aranjeaza();
		return;
    }
	if(description->Visible)
	{
	   description->Visible=false;
	   return;
	}

	description->Visible=true;

}

int CardUI::getPower()
{
	return 0;
}

void CardUI::showHighlight()
{
	TPngImage* img = new TPngImage();
	img->LoadFromFile("symbols/blue_frame.png");
	frame->Picture->Assign(img);
	delete img;
}

void CardUI::deleteHighlight()
{
	TPngImage* img = new TPngImage();
	img->LoadFromFile("symbols/golden_frame.png");
	frame->Picture->Assign(img);
	delete img;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
