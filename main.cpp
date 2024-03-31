// Project 1

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

void storeToken(string theToken, bool& keywordFound, vector<string>& keywords, vector<string>& identifiers, vector<string>& operators, vector<string>& delimiters, vector<string>& literals);
void tokenize(string str);
void outputVector(vector<string> vec);

int removeComments(string fileName, string& data);
bool isDigit(string str);
bool isWord_Digit_Bool(string str);
bool isSymbol(string str);
bool isKeyword(string str);
bool isBool(string str);
bool isComment(string str);
bool isBracket(string str);
bool isWord(string str);
bool isIdentifier(string str);
bool isSpace(string str);

int main()
{
	string fileName = "unknown";
    string data = "";
    
	cout << "\nEnter the name of the file: ";
	cin >> fileName;

    if (removeComments(fileName, data))
    {
        cout << data << "\n\nOutput2:\n\n";
        tokenize(data);
    }

	return 0;
}

bool isDigit(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
            return false;
    }

    return true;
}

bool isSpace(string str)
{
	return str == " " || str == "\n" || str == "\t";
}

// Checks for valid symbols, majority of which being operators
bool isSymbol(string str)
{
	vector<string> tokens = {"/", "\x5C", "=","'", "''", "+", "-", "<", ">", "*", "#", "%", "!", "\x22", "\x22\x22", "|", "&", ".",
							    "<<", ">>" , "<=", ">=", ">>=", "<<=", "-=", "+=", "*=", "/=",
							       "++", "--", "==", "!=", "&&", "||", ":"};

	for (int i = 0; i < tokens.size(); i++)
		if (tokens[i] == str)
			return true;

	return false;
}

bool isWord_Digit_Bool(string str)
{
	return isBool(str) || isWord(str) || isDigit(str);
}

bool isWord(string str)
{
    return ((str[0] == '"' && str[str.size() - 1] == '"') || (str[0] == '\x27' && str[str.size() - 1] == '\x27'));
}


bool isBool(string str)
{
	return str == "true" || str == "false";
}

bool isComment(string str)
{
	return str == "/*" || str == "//";
}

// removed: using, namespace, std, include
bool isKeyword(string str)
{
	vector<string>keywords = {"string", "double","float", "int", "const", "void", "bool", "char", "main",  "short","signed", "unsigned", "sizeof","static"
							    "node", "typedef", "size_t", "enum", "union", "long","register", "auto",
							    "vector", "struct", "class", "return", "for", "do", "while", "if", "else", 
                                "extern", "switch", "case", "continue", "default", "goto" };
	
	for (int i = 0; i < keywords.size(); i++)
		if (keywords[i] == str)
			return true;

	return false;
}

// Checks for brackets (delimiters)
bool isBracket(string str)
{
	vector<string> brackets = { "{", "}", "(", ")", "," , ";" , "[" , "]", ":"};

	for (int i = 0; i < brackets.size(); i++)
		if (brackets[i] == str)
			return true;

	return false;
}

// Checks if str is from A-z or 0-9, or both
bool isIdentifier(string str)
{
	if (isdigit(str[0]))
		return false;

	int counter = 0;

	if (str[0] == '-')
		counter++;

	for (; counter < str.size(); counter++)
	{
        if (!(isalnum(str[counter])))
        {   
            if (str[counter] == '_')
                continue;
            else
                return false;
        }
	}

	return true;
}

void outputVector(vector<string> vec)
{
  
    for (int i = 0; i < vec.size(); i++)
    { 
        if (i == vec.size() - 1)
            cout << vec.at(i);
        else
            cout << vec.at(i) << ", ";
    }

}

int removeComments(string fileName, string& data)
{
    string str = "";
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "\nERROR: Could not open the file.";
        return 0;
    }
    else
        cout << "\nFile was opened successfully.\n\nOutput1:\n\n";

    string line = "";
    char character = '0';

    bool multiLineComment = false, singleLineComment = false;

    while (file >> noskipws >> character)
    {
        // checks if there are comments
        if (singleLineComment || multiLineComment)
        {
            // check single comment lines -> //
            if (singleLineComment && character == '\n')
                singleLineComment = false;

            // check for multiple line comments -> /* */
            if (multiLineComment && character == '*')
            {
                file >> character;

                if (character == EOF)
                    break;

                if (character == '/')
                    multiLineComment = false;
            }
            continue;
        }

        if (character == '/')
        {
            // turn comment size to 1
            string comment(1, character);

            file >> character;

            if (character == EOF)
                break;

            if (character == '*')
            {
                multiLineComment = true;
                comment += character;
            }
            else if (character == '/')
            {
                singleLineComment = true;
                comment += character;
            }

            if (multiLineComment || singleLineComment)
                continue;
        }

        // might not need one of these
        line += character;
        str += character;
    }

    file.close();

    string clean = "";

    // removes excess spaces, new lines, and any tabs (\t)
    for (int i = 0, j = 1; i < str.size(); i++, j++)
    {
        if (str[i] == '\t')
            continue;

        if (str[i] == '\n' && (str[j] == ' ' || str[j] == '\n'))
        {
            clean += str[i];

            if (str[j] == ' ' || str [j] == '\n')
            {
                while ((str[j] == ' ' || str[j] == '\n') && j < str.size())
                {
                    j++;
                    i++;
                }
            }
        }
        else if (str[i] == ' ')
        {
            clean += str[i];

            if (str[j] == ' ')
            {
                while (str[j] == ' ' && j < str.size())
                {
                    j++;
                    i++;
                }
            }
            
        }
        else
            clean += str[i];
    }

    clean += "\n";
    data = clean;

    return 1;
}

void tokenize(string str)
{
    string line = "";
    char character = '0';

    vector<string> keywords, identifiers, operators, delimiters, literals;

    // a flag that will help in skipping #include <iostream>
    bool keywordFound = false;

    for (int i = 0; i < str.size(); i++)
    {
        character = str[i];

        if (isSpace(string(1, character)))
        {
            if (!line.empty())
            {
                storeToken(line, keywordFound, keywords, identifiers, operators, delimiters, literals);
                line = "";
            }
            continue;
        }

        if (isSymbol(string(1, character)) && !isSymbol(line))
        {
            if (!line.empty())
            {
                storeToken(line, keywordFound, keywords, identifiers, operators, delimiters, literals);
                line = "";
            }

            if ((string(1, character) == "\x22") || ((string(1, character) == "\x27")))
            {
                line += character;
                
                // skip until another quotation is found
                while (i < str.size())
                {
                    i++;
                    character = str[i];
                    
                    if (character == '\n')
                    {
                        line += line[0];
                        break;
                    }
                    else if (character == '\x22' || character == '\x27')
                        break;
                }
            }
        }
        
        if (!isSymbol(string(1, character)) && isSymbol(line))
        {
            storeToken(line, keywordFound, keywords, identifiers, operators, delimiters, literals);
            line = "";
        }

        if (isBracket(string(1, character)))
        {
            if (!line.empty())
            {
                storeToken(line, keywordFound, keywords, identifiers, operators, delimiters, literals);
                line = "";
            }

            if (isBracket(string(1, character)))
            {
                storeToken(string(1, character), keywordFound, keywords, identifiers, operators, delimiters, literals);
                continue;
            }
        }

        line += character;
    }

    cout << "Keywords: "; outputVector(keywords);
    cout << "\n\nIdentifiers: "; outputVector(identifiers);
    cout << "\n\nOperators: "; outputVector(operators);
    cout << "\n\nDelimiters: "; outputVector(delimiters);
    cout << "\n\nLiterals: "; outputVector(literals); cout << "\n\n";
}

void storeToken(string theToken, bool& keywordFound, vector<string>& keywords, vector<string>& identifiers, vector<string>& operators, vector<string>& delimiters, vector<string>& literals)
{
    if (isKeyword(theToken))
    {
        keywordFound = true; // change our flag so we can start adding valid tokens into our vectors
        keywords.push_back(theToken);
    }

    if (keywordFound)
    {
        if (isWord_Digit_Bool(theToken))
        {
            literals.push_back(theToken);
        }
        else if (isSymbol(theToken))
        {
            operators.push_back(theToken);
        }
        else if (isBracket(theToken))
        {
            delimiters.push_back(theToken);
        }
        else if (isKeyword(theToken))
        {
            keywords.push_back(theToken);
        }
        else if (isIdentifier(theToken))
        {
            identifiers.push_back(theToken);
        }
        else
            cout << "Unrecognized token: " << theToken << "\n"; //not rlly needed but will help identify errors
    }
}


