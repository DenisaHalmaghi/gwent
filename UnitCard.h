//---------------------------------------------------------------------------

#ifndef UnitCardH
#define UnitCardH
#include "Card.h"
//#include "Unit1.h"
class UnitCard:public Card
{   public:
	int power,rowRestriction;
	UnitCard();
	UnitCard(int,TCaption,UnicodeString ,UnicodeString ,int ,bool,Ability*,int,int);
	void virtual buildCardUI(TPoint,TForm*);
};
//---------------------------------------------------------------------------
#endif
