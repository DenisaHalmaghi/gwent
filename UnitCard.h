//---------------------------------------------------------------------------

#ifndef UnitCardH
#define UnitCardH
#include "Card.h"


class UnitCard:public Card
{
 protected:
	int power;
 public:

	UnitCard();
	UnitCard(int,TCaption,UnicodeString ,UnicodeString ,int ,Target*,Ability*,int);
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
   void virtual takeCareOfSpecialCard();
   void virtual triggerAbility(Card*,vector < pair<int,int> > [3],Battlefield*,Battlefield*);

};
//---------------------------------------------------------------------------
#endif
