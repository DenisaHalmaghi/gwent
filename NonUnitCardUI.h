//---------------------------------------------------------------------------

#ifndef NonUnitCardUIH
#define NonUnitCardUIH

#include "CardUI.h"


class NonUnitCardUI:public CardUI{
	protected:
	TImage* symbol;
	public:
	NonUnitCardUI();
	NonUnitCardUI(TPoint,TWinControl*,UnicodeString,UnicodeString,TCaption, Ability*,UnicodeString,int);
	~NonUnitCardUI();
	void Aranjeaza();
	void Muta(int,int);
	bool hasLock();
};
//---------------------------------------------------------------------------
#endif
