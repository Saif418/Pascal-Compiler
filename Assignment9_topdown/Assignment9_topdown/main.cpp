#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<stack>

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
    const int row = 128;
    const int col = 11;
    vector<vector<int>> DFA;
    CToken token;

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
            else if (currentState == 55 && character != 32)
            {
                lexfile.unget();
            }
            if (currentState == 55 || currentState == 10 || currentState == 4)
            {
                if (prevState == 1)
                {
                    token.tokenType[0] = 'w';
                    token.tokenType[1] = 'o';
                    token.tokenType[2] = 'r';
                    token.tokenType[3] = 'd';
                    token.tokenType[4] = '\0';
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
                else if (prevState == 9 || prevState == 3)
                {
                    token.tokenType[0] = 'r';
                    token.tokenType[1] = 'e';
                    token.tokenType[2] = 'a';
                    token.tokenType[3] = 'l';
                    token.tokenType[4] = '\0';
                }
                else if (prevState == 10 || prevState == 0)
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
        if (prevState == 1 || prevState == 2 || prevState == 4 || prevState == 9 || prevState == 10 || prevState == 55 || prevState == 99)
        {
            if (prevState == 1)
            {
                token.tokenType[0] = 'w';
                token.tokenType[1] = 'o';
                token.tokenType[2] = 'r';
                token.tokenType[3] = 'd';
                token.tokenType[4] = '\0';
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
            else if (prevState == 10 || prevState == 55)
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
                token.tokenType[i] = '@';
                token.tokenType[i + 1] = '\0';
                return false;

            }


            cout << "Lex error" << endl;
            return false;


        }

        token.tokenValue[i] = '\0';
        return true;

    }


};

class TopDown
{
private:
    CLex lex;
    CToken token;

public:
    TopDown(string fileName): lex(fileName)
    {
        
    }
    void E()
    {
        T();
    }

    void TPrime()
    {
        if (strcmp(token.tokenValue, "+")==0)
        {
            lex.GetToken(token); // move
            
                TR();
                TPrime();

            
             
        }
        else if (strcmp(token.tokenValue, "-")==0)
        {
            lex.GetToken(token); // move
           
                TR();
                TPrime();

            
           
        }
        else
        {
            // Epselon
        }
       
    }

    void FPrime()
    {
        if (strcmp(token.tokenValue, "*") == 0)
        {
            lex.GetToken(token); // move
            FR();
            FPrime();
        }
        else if (strcmp(token.tokenValue, "/") == 0)
        {
            lex.GetToken(token); // move
            FR();
            FPrime();
        }
        else
        {
            //epselon
        }

    }

    void FR()
    {
        if (strcmp(token.tokenValue, "(") == 0)
        {
            lex.GetToken(token); // move
            E();
            if (strcmp(token.tokenValue, ")") == 0)
            {
                lex.GetToken(token); // move

            }
            else
            {
                cout << "Error" << endl;
                //system("pause");
                exit(0);
            }
        }
        else if (strcmp(token.tokenType, "real") == 0)
        {
            lex.GetToken(token); // move
        }
        else if (strcmp(token.tokenType, "integer") == 0)
        {
            lex.GetToken(token); // move
        }
        else if (strcmp(token.tokenValue ,"+") == 0) //fixed
        {
            lex.GetToken(token); // move
            TR();
           
        }
        else if (strcmp(token.tokenValue, "-") == 0) //fixed
        {
            lex.GetToken(token); // move
            TR();
            
        }
        else
        {
            cout << "Error" << endl;
            //system("pause");
            exit(0);
        }

    }

    void F()
    {
        FR();
        FPrime();
    }

    void TR()
    {
        
            F();
        
        
    }

    void T()
    {
        TR();
        TPrime();
    }

    void parse()
    {
        if (lex.GetToken(token))
        {
            
            E();
            cout << "Good code!" << endl;
            
        }
        else
        {
            cout << "Empty File" << endl;
        }
    }

};



int main()
{
    TopDown td("code.txt");
    td.parse();


    return 0;
}