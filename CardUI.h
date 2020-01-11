//---------------------------------------------------------------------------

#ifndef CardUIH
#define CardUIH
#include "OrderTypes.h"
#include <Vcl.Imaging.pngimage.hpp>
#define C_CardHeight 180
#define C_Ratio 0.696629
class CardUI
{
friend class JocGwent;
protected:

	TImage* factionTop;
	TImage* factionBottom;
	TLabel* provisionCost;
	TLabel* description;
	TImage* cardImg;
	void Aranjeaza();
public:

	TImage * frame;
	CardUI();
	CardUI(TPoint ,TWinControl* ,UnicodeString ,UnicodeString ,TCaption , Ability* ,int);
	~CardUI();

	int virtual getPower();
	bool virtual hasLock(){return false;}


	void showDescription(bool);
	void toggleDescription(UnicodeString ,UnicodeString );
	void virtual Muta(int,int);
	void deleteHighlight();
	void showHighlight();
	void virtual hideUI();
};

//---------------------------------------------------------------------------
#endif
