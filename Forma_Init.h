//---------------------------------------------------------------------------

#ifndef Forma_InitH
#define Forma_InitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "Forma_Joc.h"
#include <Vcl.Imaging.jpeg.hpp>

//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TShape *Shape1;
	TButton *exitBtn;
	TButton *playBtn;
	TButton *deckCrBtn;
	TImage *Image1;
	TPanel *cardDisplayContainer;
	TScrollBox *ScrollBox1;
	TLabel *noOfCards;
	TMemo *myMemo;

	void __fastcall playBtnClick(TObject *Sender);
	void __fastcall deckCrBtnClick(TObject *Sender);
	void __fastcall exitBtnClick(TObject *Sender);
	void __fastcall ChooseFaction(TObject *Sender);
	void __fastcall ScrollBar1Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
	void __fastcall PutCardInDeck(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall showCardDescription(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);

private:	// User declarations
   UnicodeString selectedFaction;
	vector<UnicodeString> factions;
	vector<TImage*> cardbacks;
	vector<Card*> displayedCards;
	int cardNr;
	int provCost;


public:		// User declarations
	__fastcall TForm4(TComponent* Owner);

//JocGwent* joc;
 vector<Card*>prototypes;

vector<pair<int,int>> currentDeck;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
