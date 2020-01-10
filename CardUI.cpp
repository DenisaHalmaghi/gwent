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



CardUI::CardUI(TPoint pos,TWinControl* parent,UnicodeString image,UnicodeString faction,
TCaption pc, Ability* ab,int nrInst)
{

		  description=nullptr;
		  frame=nullptr;
		 //initializam imaginile corespunzator
		 cardImg=new TImage(parent);
		 cardImg->Parent = parent;
		 TPngImage* img = new TPngImage();
		 img->LoadFromFile("symbols/"+image+".png");


		 cardImg->Picture->Assign(img);
		 cardImg->Stretch=true;
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

		img->LoadFromFile("symbols/golden_frame.png");

        frame=new TImage(cardImg);
		frame->Parent= cardImg->Parent;
		frame->Picture->Assign(img);
		frame->Stretch=true;
		frame->Tag=cardImg->Tag;
		frame->Height=C_CardHeight+2;
		frame->Width=C_CardHeight*C_Ratio+2;



		//SET UP FONT
		TFont *font = new TFont;
		font->Size = 18;
		font->Color = clWhite;
		font->Style = TFontStyles() << fsBold;
		provisionCost->Font=font;
		font->Size = 11;
		font->Style = TFontStyles();


		//delete temps
		delete font;
		delete img;


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
	   this->cardImg->Left =x;
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

void CardUI::hideUI()
{
	frame->Visible=false;
	cardImg->Visible=false;
	factionTop->Visible=false;
	factionBottom->Visible=false;
	provisionCost->Visible=false;
	if(description)
	{
	   description->Visible=false;
    }

}

//---------------------------------------------------------------------------
#pragma package(smart_init)
