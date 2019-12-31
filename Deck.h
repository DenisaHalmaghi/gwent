//---------------------------------------------------------------------------

#ifndef DeckH
#define DeckH
#include <vector>
using namespace std;

class Deck
{
	friend class JocGwent;

	public:
    vector<int> cards;
	Deck(vector<int>);

	vector<int> imparteCartile(int);

};
//---------------------------------------------------------------------------
#endif
