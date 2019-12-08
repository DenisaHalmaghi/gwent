//---------------------------------------------------------------------------

#pragma hdrstop

#include "CardUI.h"


CardUI::CardUI(){

	cardImg= nullptr;
	factionTop= nullptr;
	factionBottom=nullptr;
	provisionCost=nullptr;
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


		//SET UP FONT
		TFont *font = new TFont;
		font->Size = 18;
		font->Color = clWhite;
		font->Style = TFontStyles() << fsBold;
		provisionCost->Font=font;
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
}

void CardUI::Muta(int x,int y){
	   this->cardImg->Left =x;     //aici da eroare
	   this->cardImg->Top =y;
	   Aranjeaza();
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
