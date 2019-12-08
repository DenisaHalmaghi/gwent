//---------------------------------------------------------------------------

#ifndef CardUIH
#define CardUIH
#include "Ability.h"
#include <Vcl.Imaging.pngimage.hpp>

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
