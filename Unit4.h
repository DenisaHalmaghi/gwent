//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "JocGwent.h"
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TImage *boardImg;
	TTimer *turnTimer;
	TButton *btnUnu;
	TButton *exitBtn;
	TButton *passBtn;
	TMemo *Memo1;
	TLabel *Label1;
	void __fastcall btnUnuClick(TObject *Sender);
	void __fastcall exitBtnClick(TObject *Sender);
	void __fastcall turnTimerTimer(TObject *Sender);
	void __fastcall passBtnClick(TObject *Sender);
	void __fastcall boardImgClick(TObject *Sender);
	void __fastcall boardImgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
JocGwent* joc;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
