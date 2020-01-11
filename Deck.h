//---------------------------------------------------------------------------

#ifndef DeckH
#define DeckH
#include <vector>
using namespace std;

class Deck
{
	friend class JocGwent;
	 vector<int> cards;
	public:

	Deck(vector<int>);

	vector<int> imparteCartile(int);

};
//---------------------------------------------------------------------------
#endif
