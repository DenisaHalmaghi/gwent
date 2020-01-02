//---------------------------------------------------------------------------

#ifndef JocGwentH
#define JocGwentH
#include "UnitCard.h"
#include "Deck.h"
#include "BattlefieldDerivat.h"
#include <System.Win.ScktComp.hpp>

#define C_Deck 98
#define C_GameStart 99
#define C_Turn 100
#define C_Muta 101
#define C_TriggerAbility 102
#define C_Pass 103

class JocGwent
{

TImage* board;
TTimer* targetTimer;
TForm* parent;
vector<Card*> prototypes;
vector<Card*> Cards;
vector<int> hand;
vector<pair<int,int>> effects[3];
Battlefield_Deriv* btl;
Battlefield_Deriv* btlInamic;
Deck* deck;
TClientSocket * sClient;
//game logic vars
bool placedCard;    //mai trebuie?
Card* targetedCard;
Card* droppedCard;
bool myTurn;
int roundNumber;
int turn;
int myDeckStartIndex;
Battlefield_Deriv* targetedBattlefield;
bool passed[2];
//vector<pair<int,int>> positions[2];
//int pos_top[2];

public:
 JocGwent(TForm*,TImage*,TClientSocket *,vector<Card*>,int);
 ~JocGwent();
 void Init(TForm*);
 bool endTurn();
 bool switchTurn();
 void creeazaCartile(vector<int>origin,vector<int>,int);
 void afiseazaCartile(TForm* parent);
 void mutaCarteInamic(int,TPoint);
 void triggerEnemyAbility(int,int);
 bool didIPass();
 void opponentPassed();
 void __fastcall cardMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
 void __fastcall boardDragOver(TObject *Sender, TObject *Source, int X,
		  int Y, TDragState State, bool &Accept);
 void __fastcall boardDragDrop(TObject *Sender, TObject *Source, int X,
		  int Y);
 void __fastcall targetTimerTimer(TObject *Sender);
 void __fastcall cardClicked(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);


};
//---------------------------------------------------------------------------
#endif
