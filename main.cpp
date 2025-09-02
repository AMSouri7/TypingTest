#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

int main() {
    set<string> words;
    string line;

    ifstream f1("word_list.sql");
    while (getline(f1, line)) {
        size_t start = line.find("('");
        while (start != string::npos) {
            size_t end = line.find("')", start);
            if (end != string::npos) {
                string word = line.substr(start + 2, end - start - 2);
                words.insert(word);
                start = line.find("('", end);
            } else break;
        }
    }
    f1.close();

    ifstream f2("word_list_high.sql");
    while (getline(f2, line)) {
        size_t start = line.find("('");
        while (start != string::npos) {
            size_t end = line.find("')", start);
            if (end != string::npos) {
                string word = line.substr(start + 2, end - start - 2);
                words.insert(word);
                start = line.find("('", end);
            } else break;
        }
    }
    f2.close();

    ifstream f3("word_list_medium.sql");
    while (getline(f3, line)) {
        size_t start = line.find("('");
        while (start != string::npos) {
            size_t end = line.find("')", start);
            if (end != string::npos) {
                string word = line.substr(start + 2, end - start - 2);
                words.insert(word);
                start = line.find("('", end);
            } else break;
        }
    }
    f3.close();

    ofstream all("ALLWORDS.txt");
    for (const auto& w : words) {
        all << w << endl;
    }
    all.close();

    cout << "Enter your English text:\n";
    auto start = steady_clock::now();
    string input;
    getline(cin, input);
    auto end = steady_clock::now();
    int time = duration_cast<seconds>(end - start).count();

    istringstream stream(input);
    string word;
    int total = 0, wrong = 0;
    set<string> wrongWords;

    while (stream >> word) {
        for (char& c : word) {
            if (ispunct(c)) c = ' ';
        }
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        total++;
        if (words.find(word) == words.end()) {
            wrongWords.insert(word);
            wrong++;
        }
    }

    ofstream result("result.txt");
    result << "Typing time: " << time << " seconds\n";
    result << "Total words: " << total << "\n";
    result << "Wrong words: " << wrong << "\n";
    result << "Accuracy: " << (total > 0 ? 100 * (total - wrong) / total : 0) << "%\n\n";
    result << "Wrong word list:\n";
    for (const auto& w : wrongWords) {
        result << w << "\n";
    }
    result << "\nOriginal text:\n" << input << "\n";
    result.close();

    cout << "Done. Check result.txt\n";
    return 0;
}

