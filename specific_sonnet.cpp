// Mason Sciotti
// CSC 225 - Dr. Wilkens
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

struct node{
	string word;
	node*left, *right;
	node(){ left = NULL; right = NULL; word = ""; }
	node(string www) { left = NULL; right = NULL; word = www; }
};
struct sonnetInfo{
	int sonnetNumber;
	vector<string> lines;
	node *somewords;
	sonnetInfo() :sonnetNumber(0){}
	sonnetInfo(int sn, vector<string> lns, node *w){
		sonnetNumber = sn;
		lines = lns;
		somewords = w;
	}

	string wordList(){}
	friend
		ostream& operator<<(ostream & o, sonnetInfo& si);
};
ostream& operator<<(ostream & o, sonnetInfo& si){
	cout << "Sonnet number " << si.sonnetNumber << endl;
	int i, n = si.lines.size();
	for (i = 0; i < n; i++)
		cout << si.lines[i] << endl;
	return o;
}
bool insert(string word, node *root){
	assert(root != NULL);
	if (word == root->word)// duplicate
		return false;  // or whatever the application calls for!
	if (word < root->word){
		if (root->left == NULL)
			root->left = new node(word);
		else
			insert(word, root->left);
	}

	else {
		if (root->right == NULL)
			root->right = new node(word);
		else
			insert(word, root->right);
	}
	return true;
}//closing braket for insert function
bool totalWords(string &total, node *root){
	if (root == NULL)
		return false;
	totalWords(total, root->left);
	total += ", ";
	total += root->word;
	totalWords(total, root->right);

	return true;
}
bool readFile2(string fname, vector<sonnetInfo> &sinfo, int &nsonnets);

int main(void){
	vector<sonnetInfo> sonnets;
	string sonnetWords = "";
	int k, swlen, numberOfSonnets = 0;

	if (readFile2("sonnets.txt", sonnets, numberOfSonnets)){
		int i, n = sonnets.size();
		bool done = false;
		cout << "We have information about " << n << " sonnets\n";
		while (!done){
			cout << "\nEnter a sonnet to see: (1.." << n << ") or 0 to quit ";
			cin >> i;
			if (i == 0)
				done = true;
			else if (i >= 1 && i <= n){
				i--;
				cout << endl;
				cout << sonnets[i];

				cout << "\nThe set of words:\n";
				sonnetWords = "{";
				totalWords(sonnetWords, sonnets[i].somewords);
				sonnetWords += "}";
				swlen = sonnetWords.length();

				while (swlen > 50){
					k = sonnetWords.find_first_of(",}", 50);
					cout << sonnetWords.substr(0, k + 1) << endl;
					sonnetWords = sonnetWords.substr(k + 1);
					swlen -= (k + 1);
				}
				cout << sonnetWords << endl;
			}
		}
	}
	return 0;
}
string strip(string s){
	static string wletters = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned int pos1 = s.find_first_of(wletters), pos2 = s.find_last_of(wletters);
	if (pos1 != -1 && pos2 != -1)
		return s.substr(pos1, pos2 - pos1 + 1);
	else return string("");
}
bool readFile2(string fname, vector<sonnetInfo> &sinfo, int & nsonnets){
		string line, sline, word;
		int lineNumber = 1, snum, sonnetNumber;
		const int LIMBO = 0, STARTSONNET = 1, MIDSONNET = 2, ENDSONNET = 3;
		int state = LIMBO;
		vector<string> sonnetLines;
		node *sonnetwords;
		sonnetInfo currInfo;

		try{
			ifstream fin(fname);
			nsonnets = 0;
			while (!fin.eof()){
				getline(fin, line);
				sline = strip(line);
				if (sline.length() == 0){
					if (state == MIDSONNET)
						state = ENDSONNET;
				}

				else if ((state == LIMBO) && (sline.length() > 0) && isdigit(sline[0])){
					try{
						snum = stoi(sline);
						sonnetNumber = snum;
						state = STARTSONNET;
					}

					catch (exception stoiex){
						;
					}
				}
				istringstream iss(line);
				vector<string>vec{ istream_iterator<string>(iss), istream_iterator<string>() };
				switch (state){
				case LIMBO: break;
				case STARTSONNET:
					sonnetLines.clear();
					sonnetwords = NULL;
					state = MIDSONNET;
					break;

				case MIDSONNET:
					sonnetLines.push_back(line);
					for (int i = 0; i < int(vec.size()); i++){
						word = strip(vec[i]);
						if (word.size()){
							if (sonnetwords == NULL)
								sonnetwords = new node(word);

							else
								insert(word, sonnetwords);
						}
					}
					break;

				case ENDSONNET:
					nsonnets++;
					sinfo.push_back(sonnetInfo(sonnetNumber, sonnetLines, sonnetwords));
					state = LIMBO;
					break;
				}
			}
			fin.close();
		}
		catch (exception ex){
			cout << "Problem in readFile2 (" << fname << "), " << ex.what() << endl;
			return false;
		}
		return true;
	}
