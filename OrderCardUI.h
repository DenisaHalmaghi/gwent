//---------------------------------------------------------------------------

#ifndef OrderCardUIH
#define OrderCardUIH
#include "UnitCardUI.h"

class OrderCardUI:public UnitCardUI
{
	TShape * orderBack;
	TLabel * orderFront;
	public:
	OrderCardUI(TPoint,TWinControl*,UnicodeString,UnicodeString ,TCaption , Ability* ,TCaption ,int );
	void Aranjeaza();
	void Muta(int,int);
	void modifyOrderUI(int);
};
//---------------------------------------------------------------------------
#endif
