#include <iostream>

class GameEntry{							// a game score entry
public:		
	GameEntry(const std::string& n="", int s=0); // constructor
	std::string getName() const;			// get player name
	int getScore() const;					// get score

private:
	std::string name;						//player's name
	int score;								// player's score
    
};


GameEntry::GameEntry(const std::string& n, int s) // constructor
: name(n),score(s){}


// accessors
std::string GameEntry::getName() const {return name;}
int GameEntry::getScore() const { return score;}

class Scores {				// stores game high scores
public:
	Scores(int maxEnt = 10); // constructor
	~Scores();
	void add(const GameEntry& e); // add a game entry
	GameEntry remove(int i) throw(IndexOutOfBounds);

private:
	int maxEntries;			// maximum number of entries
	int numEntries;			// actual number of entries
	GameEntry* entries;		// array of game entries
};

Scores::Scores(int maxEnt){
	maxEntries=maxEnt;		// save the max size
	entries = new GameEntry[maxEntries];  // allocate array storage
	numEntries = 0;			// initially no elements
}

Scores::~Scores(){
	delete[] entries;		// destructor
}

void Scores::add(const GameEntry& e){		// add a game entry
	int newScore=e.getScore();				// score to add
	if (numEntries==maxEntries){			// the array is full
		if(newScore<= entries[maxEntries-1].getScore())
			return;							// not high enough
	}
	else numEntries++;						// if not full one more entry

	int i=numEntries-2;						// start with next to the last 
	while(i >=0 && newScore > entries[i].getScore()){
		entries[i+1]=entries[i];
		i--;
	}
	entries[i+1]=e;							// put e in the empty spot
}

GameEntry Scores::remove(int i) throw (IndexOutOfBounds){
	if((i<0) || (i>=numEntries))		// invalid index
		throw IndexOutOfBounds("Invalid index");

	GameEntry e = entries[i];			// save the removed object

	for(int j=i+1;j<numEntries;j++)
		entries[j-1] = entries[j];		// shift entries left
	numEntries--;						// one fewer entry
	return e;							// return the removed object
}