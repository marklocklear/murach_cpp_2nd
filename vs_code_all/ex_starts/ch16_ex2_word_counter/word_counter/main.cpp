#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct WordCounts {
	string word;
	int count;
};

vector<string> load_words(string filename);
vector<WordCounts> get_word_count(const vector<string>& words);

int main() {
	cout << "The Word Counter program\n\n";

	string filename = "";
	cout << "Enter a file name: ";
	cin >> filename;

	vector<string> words;

	words = load_words(filename);

	cout << endl;
	cout << words.size() << " WORDS: ";
	for (string word : words) {
		cout << word << ' ';
	}
	cout << endl << endl;

	auto word_count = get_word_count(words);

	cout << word_count.size() << " UNIQUE WORDS: ";
	for (auto pair : word_count) {
		cout << pair.word << ' ';
	}
	cout << endl << endl;

	cout << "COUNT PER WORD: ";
	for (auto pair : word_count) {
		cout << pair.word << '=' << pair.count << ' ';
	}
	cout << endl << endl;
}

vector<string> load_words(string filename) {
	vector<string> words;
	ifstream infile(filename);

	string word;
	while (infile >> word) {

		string new_word = "";
		for (char c : word) {
			if (c == '.' || c == ',') {
				continue;               // remove punctuation
			}
			else if (isupper(c)) {
				new_word += tolower(c); // convert to lowercase
			}
			else {
				new_word += c;
			}
		}
		words.push_back(new_word);      // add word 
	}
	infile.close();

	return words;
}

vector<WordCounts> get_word_count(const vector<string>& words) {
	vector<WordCounts> word_count;
	bool found = false;
	for (string word : words) {
		for (auto& wordObj : word_count) {
			if (wordObj.word == word) {
				wordObj.count = wordObj.count + 1;
				found = true;
				break;
			}
		}
		if (!found) {
			WordCounts wordObj;
			wordObj.word = word;
			wordObj.count = 1;
			word_count.push_back(wordObj);
		}
		found = false;
	}
	return word_count;
}
