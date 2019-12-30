//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitCardUI.h"

UnitCardUI::UnitCardUI():CardUI(){

	power=nullptr;
}

UnitCardUI::~UnitCardUI(){
//if( cardImg)
//{
//	 delete cardImg;
//}

//	if(effectLabel)
//	{
//		delete effectLabel;
//	}
}

UnitCardUI::UnitCardUI(TPoint pos,TWinControl* parent,UnicodeString image,UnicodeString faction,
TCaption pc, Ability* ab,TCaption pw,int nrInst)
:CardUI(pos,parent,image,faction,pc,ab,nrInst)
{
	   //	UnitCard* card=(UnitCard*)c ;
		effectLabel=nullptr;
		poison=nullptr;
		lock=nullptr;
		power=new TLabel(cardImg);
		power->Parent=parent;
		power->AutoSize=true;
		power->Caption=pw;
		power->Font=provisionCost->Font;
		power->BringToFront();
		Aranjeaza();
}

void UnitCardUI::Aranjeaza(){
	CardUI::Aranjeaza();
	AranjeazaPower();

	if(effectLabel){
		effectLabel->Left=cardImg->Left;
		effectLabel->Top=cardImg->Top+cardImg->Height-effectLabel->Height;
	}

	if(poison)
	{
		poison->Left=cardImg ->Left+cardImg ->Width/2-2*poison->Width;
		poison->Top=cardImg ->Top+cardImg ->Height-poison->Height;
	}

		if(lock)
	{
		lock->Left=cardImg ->Left+cardImg ->Width/2-lock->Width/2;
		lock->Top=cardImg ->Top+cardImg ->Height-lock->Height;
	}

}

void  UnitCardUI::AranjeazaPower(){
	power->Left=factionTop ->Left+factionTop ->Width/2-power->Width/2;
	power->Top=factionTop ->Top +factionTop ->Height/2- power->Height/2;
}

void UnitCardUI::Muta(int x,int y){
	 CardUI::Muta(x,y);
	 Aranjeaza();
}

void  UnitCardUI::setPower(int pw)
{
		power->Caption=pw;
}

int UnitCardUI::getPower()
{
	return StrToInt(power->Caption);
}

void UnitCardUI::setColor(TColor cl)
{
	power->Font->Color=cl;
}

//
//void UnitCardUI::triggerAbility(CardUI* tg){
//	UnitCardUI* target= dynamic_cast<UnitCardUI*>(tg);
//	Ability* ab=card->getAbility();
//	string abName=ab->getName();
//
//	if(abName=="boost"){
//	   int oldPower= target->getPower();
//	   target->setPower(oldPower+ab->getQuantum());
//	}
//	else if(abName=="damage"){
//		int oldPower= target->getPower();
//	   target->setPower(oldPower-ab->getQuantum());
//	}
//    target->AranjeazaPower();
//}

void UnitCardUI::highlightSelf()
{

}

void UnitCardUI::appendEffect(int effect,int qt)
{
	delete effectLabel;
	effectLabel=nullptr;
	 effectLabel=new TLabel(cardImg);
	 effectLabel->Parent=cardImg->Parent;
	 effectLabel->Caption=qt;
	 effectLabel->AutoSize=true;
	 effectLabel->Left=cardImg->Left+6;
	 effectLabel->Top=cardImg->Top+cardImg->Height-2*effectLabel->Height-1;
	 TFont* font= new TFont();
	 switch(effect)
	 {
		 case C_Bleed:font->Color=clRed;break;
		 case C_Vitality:font->Color=clLime;break;
	 }
	 font->Size = 14;
	 font->Style = TFontStyles() << fsBold;
	 effectLabel->Font=font;
	 delete font;


}

void UnitCardUI::removeEffect()
{
   delete effectLabel;
   effectLabel=nullptr;
}

void UnitCardUI::modifyEffect(int newCapt)
{
	   effectLabel->Caption=newCapt;
}

void UnitCardUI::appendPoison_Lock(int effect,int size)
{
	TImage* temp;
	UnicodeString image;
	int left=  cardImg ->Left+cardImg ->Width/2;
	if(effect==C_Lock)
	{
		temp=lock;
		image="lock";
		left-=size/2;
		delete lock;
		lock=nullptr;
	}
	else
	{
		delete poison;
		poison=nullptr;
		temp=poison;
		image="poison";
		left-=2*size;
	}

	temp= new TImage(cardImg);
	temp->Parent=cardImg->Parent;
	temp->Width=size;
	temp->Height=size;
	temp->Stretch=true;

	TPngImage* img = new TPngImage();
	img->LoadFromFile("symbols/"+image+".png");
	temp->Picture->Assign(img);
	delete img;



	temp->Left=left;
	temp->Top=cardImg ->Top+cardImg ->Height-temp->Height;

	if(effect==C_Lock)
	{
		lock=temp;
	}
	else
	{
		poison=temp;
	}

}

void UnitCardUI::removePoison_Lock(int effect)
{
    if(effect==C_Lock)
	{
		if(lock)
		{
			delete lock;
			lock=nullptr;
		}

	}
	else
	{
		if(poison)
		{
			delete poison;
			poison=nullptr;
        }

	}

}

bool UnitCardUI::hasPoison()
{
   if(poison)
   {
	   return true;
   }
   return false;
}

bool UnitCardUI::hasLock()
{
   if(lock)
   {
	   return true;
   }
   return false;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
