//---------------------------------------------------------------------------

#ifndef CardUIH
#define CardUIH
#include "OrderTypes.h"
#include <Vcl.Imaging.pngimage.hpp>
#define C_CardHeight 180
#define C_Ratio 0.696629
class CardUI
{
protected:

	TImage* factionTop;
	TImage* factionBottom;
	TLabel* provisionCost;
	TLabel* description;


public:
	TImage* cardImg;
	TImage * frame;
	CardUI();
	~CardUI();
	int getWidth();
	int virtual getPower();
	bool virtual hasLock(){return false;}
	CardUI(TPoint ,TWinControl* ,UnicodeString ,UnicodeString ,TCaption , Ability* ,int);
	void Aranjeaza();
	void showDescription(bool);
	void toggleDescription(UnicodeString ,UnicodeString );
	void toggleDescription();
	void virtual Muta(int,int);
	void deleteHighlight();
	void showHighlight();
};

//---------------------------------------------------------------------------
#endif
