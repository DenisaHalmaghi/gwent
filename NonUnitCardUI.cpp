//---------------------------------------------------------------------------

#pragma hdrstop

#include "NonUnitCardUI.h"


NonUnitCardUI::NonUnitCardUI():CardUI(){

	symbol=nullptr;
}

NonUnitCardUI::~NonUnitCardUI(){
//if(cardImg)
//{
//	delete cardImg;
//}

}

NonUnitCardUI::NonUnitCardUI(TPoint pos,TForm* parent,UnicodeString image,UnicodeString fact,
TCaption pc, Ability* ab,UnicodeString cardType,int nrInst)
:CardUI(pos,parent,image,fact,pc,ab,nrInst)
{

		symbol=new TImage(cardImg);
		symbol->Parent = parent;
		TPngImage* img = new TPngImage();
		img->LoadFromFile("symbols/"+ cardType+ ".png");

		symbol->Picture->Assign(img);
		symbol->Stretch=true;
		symbol->Height= factionTop->Height-15;
		symbol->Width= symbol->Height*0.89473;
		symbol->BringToFront();
		Aranjeaza();
}

void NonUnitCardUI::Aranjeaza(){
	CardUI::Aranjeaza();
	symbol->Left=factionTop ->Left+factionTop ->Width/2-symbol->Width/2;
	symbol->Top=factionTop ->Top +factionTop ->Height/2- symbol->Height/2;
}

void NonUnitCardUI::Muta(int x,int y){
	 CardUI::Muta(x,y);
	 Aranjeaza();
}

bool NonUnitCardUI::hasLock()
{
	return false;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
