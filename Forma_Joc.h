//---------------------------------------------------------------------------

#ifndef Forma_JocH
#define Forma_JocH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "JocGwent.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *exitBtn;
	TButton *btnUnu;
	TTimer *turnTimer;
	TMemo *Memo1;
	TLabel *Label1;
	TButton *passBtn;
	TImage *boardImg;
    void __fastcall btnUnuClick(TObject *Sender);
	void __fastcall exitBtnClick(TObject *Sender);
	void __fastcall turnTimerTimer(TObject *Sender);
	void __fastcall passBtnClick(TObject *Sender);
	void __fastcall boardImgClick(TObject *Sender);
	void __fastcall boardImgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
private:	// User declarations
	JocGwent* joc;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	vector<Card*>prototypes;
	vector<pair<int,int>>deckArray;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
