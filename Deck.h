//---------------------------------------------------------------------------

#ifndef DeckH
#define DeckH
#include <vector>
using namespace std;

class Deck
{

	public:
	vector<int> cards;
	Deck(vector<pair<int,int>>);
	void Aranjeaza(vector<pair<int,int>> );
	vector<int> imparteCartile(int);

};
//---------------------------------------------------------------------------
#endif
