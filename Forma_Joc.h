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
#include <System.Win.ScktComp.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *exitBtn;
	TButton *btnUnu;
	TTimer *turnTimer;
	TLabel *Label1;
	TButton *passBtn;
	TImage *boardImg;
	TClientSocket *sClient;

    void __fastcall btnUnuClick(TObject *Sender);
	void __fastcall exitBtnClick(TObject *Sender);
	void __fastcall turnTimerTimer(TObject *Sender);
	void __fastcall passBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sClientRead(TObject *Sender, TCustomWinSocket *Socket);
private:	// User declarations
	JocGwent* joc;
    bool gameIsOver;
	void handleEnd(int);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	vector<Card*>prototypes;
	vector<int>deckArray;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
