//---------------------------------------------------------------------------

#ifndef NonUnitCardUIH
#define NonUnitCardUIH

#include "CardUI.h"


class NonUnitCardUI:public CardUI{
	protected:
	TImage* symbol;
    void Aranjeaza();
	public:
	NonUnitCardUI();
	NonUnitCardUI(TPoint,TWinControl*,UnicodeString,UnicodeString,TCaption, Ability*,UnicodeString,int);
	~NonUnitCardUI();

	void Muta(int,int);
	bool hasLock();
	void virtual hideUI();
};
//---------------------------------------------------------------------------
#endif
