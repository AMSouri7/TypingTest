#include <fstream>
#include <regex>
#include <string>

int main() {
    std::ifstream sqlFile("words.sql");
    std::ofstream txtFile("words.txt");
    std::string line;
    std::regex wordRegex(R"(\('([^']+)'\))");
    std::smatch match;

    while (std::getline(sqlFile, line)) {
        if (line.find("INSERT INTO") != std::string::npos) {
            auto begin = line.cbegin();
            auto end = line.cend();
            while (std::regex_search(begin, end, match, wordRegex)) {
                txtFile << match[1] << "\n";
                begin = match.suffix().first;
            }
        }
    }

    return 0;
}
