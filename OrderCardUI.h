//---------------------------------------------------------------------------

#ifndef OrderCardUIH
#define OrderCardUIH
#include "UnitCardUI.h"

class OrderCardUI:public UnitCardUI
{
	TShape * orderBack;
	TLabel * orderFront;
    void Aranjeaza();
	public:
	OrderCardUI(TPoint,TWinControl*,UnicodeString,UnicodeString ,TCaption , Ability* ,TCaption ,int );

	void Muta(int,int);
	void modifyOrderUI(int);
};
//---------------------------------------------------------------------------
#endif
