#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<stack>
#include<unordered_set>
#include<cctype>
#include <algorithm>

using namespace std;


struct CToken
{
    char tokenType[50];
    char tokenValue[50];

    void clearTokens()
    {
        for (int i = 0; i < 50; i++)
        {
            tokenType[i] = ' ';
            tokenValue[i] = ' ';
        }

    }

};

class CLex
{
private:
    int currentState;
    int prevState;
    char currentChar;
    ifstream lexfile;
    ifstream rWords;
    const int row = 128;
    const int col = 13;
    vector<vector<int>> DFA;
    CToken token;
    unordered_set<string> rwords;

public:

    CLex(string lexFileName)
    {
        // open DFA
        DFA.resize(row, vector<int>(col));
        ifstream DFAfile("2dDFA.txt");
        if (!DFAfile) {
            cerr << "Cannot open DFA file\n";
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                DFAfile >> DFA[i][j];
            }
        }


        DFAfile.close();

        // open lexfile
        lexfile.open(lexFileName);
        if (!lexfile) {
            cerr << "Cannot open lexing file\n";
        }

        //rwords
        rWords.open("Rword.txt");
        if (!rWords) {
            cerr << "Cannot open Rword file\n";
        }
        string word;
        while (rWords >> word) {
            rwords.insert(word);
        }
        rWords.close();

    }

    bool GetToken(CToken& token)
    {
        currentState = 0;
        prevState = 0;
        token.clearTokens();
        int i = 0; // placement into the array of chars

        while (!(lexfile.eof()))
        {
            currentChar = lexfile.get();
            prevState = currentState;
            int character = static_cast<int>(currentChar);
            if (currentChar < 0)
            {
                break;

            }
            currentState = DFA[character][currentState];


            if (currentState != 0 && currentState != 55 && currentState != 99)
            {
                token.tokenValue[i] = currentChar;
                i++;
            }
            else if (currentState == 55 && character != 32 || ((character == 58 || character == 46) && prevState == 1))//
            {
                lexfile.unget();
            }
            if (currentState == 55 || currentState == 10 || currentState == 4 || ((character == 58 || character == 46) && prevState == 1))// 
            {

                if (prevState == 1)
                {
                    token.tokenValue[i] = '\0';
                    if (rwords.find(token.tokenValue) != rwords.end())
                    {

                        token.tokenType[0] = 'r';
                        token.tokenType[1] = 'w';
                        token.tokenType[2] = 'o';
                        token.tokenType[3] = 'r';
                        token.tokenType[4] = 'd';
                        token.tokenType[5] = '\0';

                    }
                    else
                    {
                        token.tokenType[0] = 'v';
                        token.tokenType[1] = 'a';
                        token.tokenType[2] = 'r';
                        token.tokenType[3] = 'i';
                        token.tokenType[4] = 'a';
                        token.tokenType[5] = 'b';
                        token.tokenType[6] = 'l';
                        token.tokenType[7] = 'e';
                        token.tokenType[8] = '\0';

                    }


                }
                else if (prevState == 2)
                {
                    token.tokenType[0] = 'l';
                    token.tokenType[1] = 'i';
                    token.tokenType[2] = 't';
                    token.tokenType[3] = 'i';
                    token.tokenType[4] = 'n';
                    token.tokenType[5] = 't';
                    token.tokenType[6] = 'e';
                    token.tokenType[7] = 'g';
                    token.tokenType[8] = 'e';
                    token.tokenType[9] = 'r';
                    token.tokenType[10] = '\0';
                }
                else if (prevState == 9 || prevState == 3)
                {
                    token.tokenType[0] = 'l';
                    token.tokenType[1] = 'i';
                    token.tokenType[2] = 't';
                    token.tokenType[3] = 'r';
                    token.tokenType[4] = 'e';
                    token.tokenType[5] = 'a';
                    token.tokenType[6] = 'l';
                    token.tokenType[7] = '\0';
                }
                else if (prevState == 10 || prevState == 0 || prevState == 12 || prevState == 11)
                {
                    token.tokenType[0] = 's';
                    token.tokenType[1] = 'p';
                    token.tokenType[2] = 'e';
                    token.tokenType[3] = 'c';
                    token.tokenType[4] = 'i';
                    token.tokenType[5] = 'a';
                    token.tokenType[6] = 'l';
                    token.tokenType[7] = '\0';
                }
                else if (1)
                {

                }


                token.tokenValue[i] = '\0';
                return true;

            }
            else if (currentState == 99)
            {

                cout << "Lex error" << endl;

                return false;
            }


        }
        // at the end of the file
        token.tokenValue[i] = '\0';
        if (prevState == 1 || prevState == 2 || prevState == 4 || prevState == 9 || prevState == 10 || prevState == 55 || prevState == 99 || prevState == 11)
        {
            if (prevState == 1)
            {
                if (rwords.find(token.tokenValue) != rwords.end())
                {

                    token.tokenType[0] = 'r';
                    token.tokenType[1] = 'w';
                    token.tokenType[2] = 'o';
                    token.tokenType[3] = 'r';
                    token.tokenType[4] = 'd';
                    token.tokenType[5] = '\0';

                }
                else
                {
                    token.tokenType[0] = 'w';
                    token.tokenType[1] = 'o';
                    token.tokenType[2] = 'r';
                    token.tokenType[3] = 'd';
                    token.tokenType[4] = '\0';

                }

            }
            else if (prevState == 2)
            {
                token.tokenType[0] = 'i';
                token.tokenType[1] = 'n';
                token.tokenType[2] = 't';
                token.tokenType[3] = 'e';
                token.tokenType[4] = 'g';
                token.tokenType[5] = 'e';
                token.tokenType[6] = 'r';
                token.tokenType[7] = '\0';
            }
            else if (prevState == 4 || prevState == 9)
            {
                token.tokenType[0] = 'r';
                token.tokenType[1] = 'e';
                token.tokenType[2] = 'a';
                token.tokenType[3] = 'l';
                token.tokenType[4] = '\0';
            }
            else if (prevState == 10 || prevState == 55 || prevState == 11 || prevState == 12)
            {
                token.tokenType[0] = 's';
                token.tokenType[1] = 'p';
                token.tokenType[2] = 'e';
                token.tokenType[3] = 'c';
                token.tokenType[4] = 'i';
                token.tokenType[5] = 'a';
                token.tokenType[6] = 'l';
                token.tokenType[7] = '\0';
            }
            else if (prevState == 99)
            {
                token.tokenType[0] = 'E';
                token.tokenType[1] = 'L';
                token.tokenType[2] = 'S';
                token.tokenType[3] = 'E';
                token.tokenType[4] = '\0';
            }
        }
        else
        {
            if (currentChar < 0)
            {
                //token.tokenType[i] = '@';
                token.tokenType[i + 1] = '\0';
                return false;

            }


            cout << "Lex error" << endl;
            return false;


        }


        return true;

    }


};

class CParser
{
private:
    map<string, int> key;
    map<string, int> productions;
    vector<vector<char>> opc;
    ifstream loadKeys;
    ifstream loadProduction;
    ifstream loadOPC;
    CToken token;
    CLex LEX;
    stack<string> stack;
    char action;

public:

    CParser(string filename) : LEX(filename)
    {

        loadKeys.open("key.txt");
        if (!loadKeys) {
            cerr << "Cannot open keys file\n";
        }
        string k;
        int v;
        for (int i = 0; i < 37; ++i) {
            if (loadKeys >> v >> k) {
                key.insert({ k, v });
            }

        }

        loadKeys.close();

        loadProduction.open("productions.txt");
        if (!loadProduction) {
            cerr << "Cannot open production file\n";
        }
        string input;
        string firstTwo;
        int num;
        for (int i = 0; i < 41; i++)
        {
            if (loadProduction >> input)
            {
                firstTwo = input.substr(0, 2);
                input.erase(0, 2);
                num = stoi(firstTwo);
                productions.insert({ input,num });
            }
        }

        loadProduction.close();

        loadOPC.open("Tokenmap.txt");
        if (!loadOPC) {
            cerr << "Cannot open token map file\n";
        }
        opc.resize(key.size(), vector<char>(key.size()));

        for (int i = 0; i < key.size(); i++)
        {
            for (int j = 0; j < key.size(); j++)
            {
                loadOPC >> opc[i][j];
            }
        }

        loadOPC.close();

    }

    void parse()
    {
        CToken drivingToken;
        //LEX.GetToken(drivingToken);
        int column = 0;

       /* if ((strcmp(drivingToken.tokenType, "special") == 0) || (strcmp(drivingToken.tokenType, "rword") == 0))
        {
            column = key[drivingToken.tokenValue];
        }
        else
        {
            if (!(LEX.GetToken(drivingToken)))
            {
                cout << "File is empty" << endl;
                return;
            }
            else
            {
                
                column = key[drivingToken.tokenType];
            }

        }*/
        
        if (!(LEX.GetToken(drivingToken)))
        {
            cout << "File is empty" << endl;
            return;
        }
        else if ((strcmp(drivingToken.tokenType, "special") == 0) || (strcmp(drivingToken.tokenType, "rword") == 0))
        {
            column = key[drivingToken.tokenValue];
            
        }
        else
        {
            column = key[drivingToken.tokenType];
            
        }

        int row = 0;
        string production;
        while (1)
        {
            if (stack.empty())
            {
                row = key.size() -1; //38
            }
            else
            {
                // get right way symbol
                int size = stack.top().size();

                string wayRight = stack.top().substr(size - 2, 2);
                row = stoi(wayRight);

            }

            action = opc[row - 1][column-1]; //col-1?

            if (action == '<')
            {
                string s = to_string(column);
                if (s.size() < 2)
                {
                    s = '0' + s; // pad since column could be 1 digit
                }
                production = s;
                stack.push(production);

                if (!(LEX.GetToken(drivingToken)))
                {
                    column = key.size();
                }
                else if ((strcmp(drivingToken.tokenType, "special") == 0) || (strcmp(drivingToken.tokenType, "rword") == 0))
                {
                    column = key[drivingToken.tokenValue];
                }
                else
                {
                    column = key[drivingToken.tokenType];
                }


            }
            else if (action == '=')
            {
                string s = to_string(column);
                if (s.size() < 2)
                {
                    s = '0' + s;
                }
                stack.top() += s;
                if (!(LEX.GetToken(drivingToken)))
                {
                    column = key.size();
                }
                else if ((strcmp(drivingToken.tokenType, "special") == 0) || (strcmp(drivingToken.tokenType, "rword") == 0))
                {
                    column = key[drivingToken.tokenValue];
                }
                else
                {
                    column = key[drivingToken.tokenType];
                }

            }
            else if (action == '#')
            {
                cout << "Bad Code" << endl;

                break;
            }
            else if (action == 'A')
            {
                if (stack.top() == "01")
                {
                    cout << " GOOD CODE \n";
                    break;
                }
                else
                {
                    cout << " BAD CODE \n";
                    break;
                }
            }
            else if (action == '>')
            {
                string p = stack.top();
                stack.pop();
                while (p.size() < 12)
                {
                    p += "00";
                }
                production = p; // maybe we do not need this
                int reducedCol = productions[p];
                if (stack.empty())
                {
                    row = key.size();
                }
                else
                {
                    int size = stack.top().size();
                    string wayRight = stack.top().substr(size - 2, 2);
                    row = stoi(wayRight);

                }

                action = opc[row - 1][reducedCol - 1];

                if (action == '<')
                {
                    string s = to_string(reducedCol);
                    if (s.size() < 2)
                    {
                        s = '0' + s;
                    }
                    production = s;

                    stack.push(production); //s

                }
                else if (action == '=')
                {
                    string s = to_string(reducedCol);
                    if (s.size() < 2)
                    {
                        s = '0' + s;
                    }

                    stack.top() += s;

                }

            }

        }


    }

};


int main()
{
    CParser cparser("code.txt");
    cparser.parse();

    return 0;
}