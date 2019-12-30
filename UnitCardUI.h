//---------------------------------------------------------------------------

#ifndef UnitCardUIH
#define UnitCardUIH
#include "CardUI.h"

class UnitCardUI:public CardUI{
	protected:
	TLabel* power;
	TLabel* effectLabel;
	TImage* poison;
	TImage* lock;
	public:
	UnitCardUI();
	~UnitCardUI();
	UnitCardUI(TPoint,TWinControl*,UnicodeString,UnicodeString,TCaption, Ability*,TCaption,int);
    void AranjeazaPower();
	void Aranjeaza();
	void Muta(int,int);
	void setPower(int);
	int getPower();
	void appendEffect(int,int qt=1);
	void removeEffect();
	void modifyEffect(int);
	void setColor(TColor);
	void appendPoison_Lock(int,int);
	void removePoison_Lock(int);
	bool hasPoison();
	bool hasLock();
   //	void triggerAbility(CardUI*);
	void highlightSelf();


};
//---------------------------------------------------------------------------
#endif
