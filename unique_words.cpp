//Mason Sciotti
//CSC225 - Dr. Wilkens

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long ulong;
struct wordPair{
	string word;
	int frequency;
	wordPair(){	word = ""; frequency = 0; }
};
bool readFile(string fname, wordPair *words, int &nl);
ulong ELFHash(const string str, ulong M);
void alphabetize(wordPair *unsorted, vector<wordPair>& sorted);
bool compareWord(wordPair A, wordPair B){
	return A.word.compare(B.word) < 0;
}
int main(void){
	wordPair words[10993];
	vector<wordPair> sorted;
	int numberOfLines;

	if (readFile("sonnets.txt", words, numberOfLines)){	
		alphabetize(words,sorted);
		for (unsigned int i = 0; i < sorted.size(); i++)
			cout << setw(10) << sorted[i].word << setw(8) << sorted[i].frequency << endl;
		cout << "\nNumber of unique words: " << sorted.size() << endl;
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
bool readFile(string fname, wordPair *words, int & nl){
	string line, input;
	int tablesize = 10993;
	bool found = false;

	ifstream fin(fname);
	nl = 0;
	while (!fin.eof()){
		getline(fin, line);
		if (line.size()){
			nl++;
			istringstream iss(line);
			vector<string>vec{ istream_iterator<string>(iss), istream_iterator<string>() };
			for (int i = 0; i < int(vec.size()); i++){
				input = strip(vec[i]);
				ulong str_hash = ELFHash(input, tablesize);

				while (found == false){
					if (words[str_hash].word == "" && words[str_hash].frequency == 0){
						words[str_hash].word = input;
						words[str_hash].frequency++;
						found = true;
					}
					else if (words[str_hash].word == input){
						words[str_hash].frequency++;
						found = true;
					}
					else{
						str_hash++;
						if (str_hash == tablesize)
							str_hash = 0;
					}
				}
				found = false;
			/*		if (words[str_hash].word == "" && words[str_hash].frequency == 0){
						words[str_hash].word = input;
						words[str_hash].frequency++;
					}
					else if (words[str_hash].word == input && words[str_hash].frequency != 0)
						words[str_hash].frequency++;

					else if (words[str_hash].word != input){
						while (found = false){
							for (int j = 0; j < tablesize; j++){
								if (words[j].frequency == 0 && words[str_hash].word == ""){
									words[j].word = input;
									words[j].frequency++;
									found = true;
								}
								else if (words[j].word == input){
									words[j].frequency++;
									found = true;
								}
							}
						}
					}*/

				}
			}
		}

		fin.close();
		return true;
	}
ulong ELFHash(const string str, ulong M){
	ulong h = 0;
	const char *key = str.c_str();
	while (*key != '\0') {
		h = (h << 4) + *key++;
		unsigned long g = h & 0xF0000000L;
		if (g) h ^= g >> 24;
		h &= ~g;
	}
	return h % M;
}
void alphabetize(wordPair *unsorted, vector<wordPair>& sorted){
	
	for (int i = 0; i < 10993; i++)
		if (unsorted[i].word != "")
			sorted.push_back(unsorted[i]);

	sort(sorted.begin(), sorted.end(), compareWord);

}
