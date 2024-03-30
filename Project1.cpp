#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>

std::string readFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string removeComments(const std::string &str)
{
    std::string result;
    bool inBlockComment = false;
    bool inLineComment = false;

    for (int i = 0; i < str.size(); i++)
    {
        if (!inBlockComment && !inLineComment && i < str.size() - 1 && str[i] == '/' && str[i + 1] == '*')
        {
            inBlockComment = true;
            i++;
        }
        else if (!inBlockComment && !inLineComment && i < str.size() - 1 && str[i] == '/' && str[i + 1] == '/')
        {
            inLineComment = true;
            i++;
        }
        else if (inBlockComment && i < str.size() - 1 && str[i] == '*' && str[i + 1] == '/')
        {
            inBlockComment = false;
            i++;
        }
        else if (inLineComment && str[i] == '\n')
        {
            inLineComment = false;
        }
        else if (!inBlockComment && !inLineComment)
        {
            result += str[i];
        }
    }

    return result;
}

std::map<std::string, std::vector<std::string>> tokenize(const std::string &str)
{
    std::map<std::string, std::vector<std::string>> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, ' '))
    {
        if (token == "def" || token == "return" || token == "print")
        {
            tokens["Keywords"].push_back(token);
        }
        else if (token == "=" || token == "+")
        {
            tokens["Operators"].push_back(token);
        }
        else if (token == "(" || token == ")" || token == ":" || token == ",")
        {
            tokens["Delimiters"].push_back(token);
        }
        else if (std::isdigit(token[0]))
        {
            tokens["Literals"].push_back(token);
        }
        else
        {
            tokens["Identifiers"].push_back(token);
        }
    }

    return tokens;
}

void printTokens(const std::map<std::string, std::vector<std::string>> &tokens)
{
    std::cout << "Tokenized Code in Tabular Form:\n";
    for (const auto &category : tokens)
    {
        std::cout << category.first << "\t";
        for (const auto &token : category.second)
        {
            std::cout << token << ' ';
        }
        std::cout << '\n';
    }
}

int main()
{
    std::string filename = "filename.txt"; // replace with your file name
    std::string data = readFile(filename);
    std::string cleanedData = removeComments(data);
    std::map<std::string, std::vector<std::string>> tokens = tokenize(cleanedData);

    std::cout << "Cleaned Code:\n"
              << cleanedData << '\n';
    printTokens(tokens);

    return 0;
}
