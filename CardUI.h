//---------------------------------------------------------------------------

#ifndef CardUIH
#define CardUIH
#include "OrderTypes.h"
#include <Vcl.Imaging.pngimage.hpp>
#define C_CardHeight 190
#define C_Ratio 0.696629
class CardUI
{
protected:

	TImage* factionTop;
	TImage* factionBottom;
	TLabel* provisionCost;

public:
	TImage* cardImg;
	CardUI();
	~CardUI();
	int getWidth();
	bool virtual hasLock(){return false;}
	CardUI(TPoint ,TForm* ,UnicodeString ,UnicodeString ,TCaption , Ability* ,int);
	void Aranjeaza();
	void virtual Muta(int,int);
};

//---------------------------------------------------------------------------
#endif
