//---------------------------------------------------------------------------

#ifndef UnitCardH
#define UnitCardH
#include "Card.h"
//#include "Unit1.h"

class UnitCard:public Card
{   public:
	int power,rowRestriction;
	UnitCard();
	UnitCard(int,TCaption,UnicodeString ,UnicodeString ,int ,Target*,Ability*,int,int);
	void virtual buildCardUI(TPoint,TWinControl*);
	void virtual Copiaza(Card*&,int);
	void virtual placeOnBattlefield(Battlefield*,TPoint);
	void virtual modificaPower(int);
};

class Special_Card:public Card
{
public:
   Special_Card(int,TCaption,UnicodeString ,UnicodeString ,int,Target*,Ability*);
   void virtual placeOnBattlefield(Battlefield*,TPoint);
   void virtual Copiaza(Card*&,int);
   void virtual triggerAbility(Card*,vector < pair<int,int> > [3],Battlefield*,Battlefield*);
//   void virtual buildCardUI(TPoint,TForm*);
};
//---------------------------------------------------------------------------
#endif
