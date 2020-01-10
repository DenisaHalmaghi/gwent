//---------------------------------------------------------------------------

#pragma hdrstop

#include "OrderCardUI.h"
#define C_OrderHeight 30
//---------------------------------------------------------------------------
#pragma package(smart_init)



OrderCardUI::OrderCardUI(TPoint pos,TWinControl* parent,UnicodeString image,UnicodeString faction,TCaption pc,
 Ability* ab,TCaption pw,int nrInst)
 :UnitCardUI(pos,parent, image, faction, pc,ab, pw,nrInst)
 {
		Order* order=static_cast<Order*>(ab);

		orderBack=new TShape(cardImg);
		orderBack->Parent=parent;

		orderBack->Shape=stCircle;
		orderBack->Pen->Color=clWhite;
		orderBack->Brush->Style=bsClear;
		orderBack->Height=C_OrderHeight;
		orderBack->Width=C_OrderHeight;

		orderFront=new TLabel(cardImg);
		orderFront->Parent=parent;
		orderFront->Caption="zzz";

		TFont* font= new TFont();
		font->Color=clWhite;
		font->Size = 12;
		font->Style = TFontStyles() << fsBold;

		if(order->getZeal())
		{
			orderFront->Caption=order->getNoOfCharges();
		   	orderBack->Pen->Color=clGreen;

		}
		orderFront->Font=font;
		delete font;

		Aranjeaza();
 }

void OrderCardUI::Aranjeaza()
{
	UnitCardUI::Aranjeaza();

	orderBack->Left=cardImg ->Left+cardImg ->Width/2-orderBack->Width/2;
	orderBack->Top=cardImg ->Top+cardImg ->Height-orderBack->Height;

	orderFront->Left=orderBack ->Left+orderBack ->Width/2-orderFront->Width/2;
	orderFront->Top=orderBack ->Top+orderBack ->Height/2-orderFront->Height/2;

}

 void OrderCardUI::Muta(int x,int y)
{
	UnitCardUI::Muta(x,y);
	Aranjeaza();

}

 void OrderCardUI::modifyOrderUI(int number)
{
	TColor cl=clRed;
	if(number>0)
	{
	   cl=clGreen;
    }
	orderBack->Pen->Color=cl;
	orderFront->Caption=number;
	orderFront->Left=orderBack ->Left+orderBack ->Width/2-orderFront->Width/2;
}
