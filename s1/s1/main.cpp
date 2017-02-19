#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

struct Statistics {
	int count;
	std::string word;
};

std::string prepare(const std::string& s) {
	std::string data;
	data.resize(s.size());
	std::transform(s.begin(), s.end(), data.begin(), ::tolower);
	while (ispunct(*(data.begin()))) {
		data.erase(data.begin());
	}
	while (ispunct(*(data.end() - 1))) {
		data.pop_back();
	}
	return data;
}

bool compare(Statistics a, Statistics b) {
	return (a.count > b.count);
}

int main() {
	std::map<std::string, int> vocabulary;
	std::map<std::string, int>::iterator it;
	std::ifstream file("file.txt");
	const int WORDS_COUNT = 50;			// N words
	std::vector<Statistics> s;
	
	if (file.is_open()) {
		std::string word;
		while (!file.eof()) {
			file >> word;
			word = prepare(word);
			it = vocabulary.find(word);
			if (it != vocabulary.end()) {
				vocabulary[word]++;
			}
			else {
				vocabulary[word] = 1;
			}
		}
		for (auto it = vocabulary.begin(); it != vocabulary.end(); it++) {
			Statistics temp;
			temp.word = it->first;
			temp.count = it->second;
			s.push_back(temp);
		}
		std::sort(s.begin(), s.end(), compare);
		file.close();
	}
	for (int i = 0; i < s.size(); i++) {
		std::cout << s[i].word << " " << s[i].count << "\n";
	}
}