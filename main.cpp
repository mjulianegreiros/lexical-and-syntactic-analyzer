#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    /*string reservados[6] = {"do", "while", "{", "}", "(", ")"};
    string *codigo = new string;

    ifstream myFile("codigo.txt");
    string myLine;
    
    while(getline (myFile, myLine)) {
        for(int i = 0; i < myLine.length(); i++){
            if(myLine[i] == ' '){
            myLine.erase(i, 1);
            }
        }
        cout << myLine;
    } 
    */

    char buffer_c, buffer_next;
    std::string buffer_s;
    string token[] = {"Res_do", "Ch_open", "Ch_close", "Res_while", "P_open", "Numero", "Op_rel", "P_close", "end"};
    std::vector<std::string> lexemas;

    ifstream myFile("codigo.txt");
    string myLine;


    //Removendo espaços em branco do .txt
    while(getline (myFile, myLine)) {
        for(int i = 0; i < myLine.length(); i++){
            if(myLine[i] != ' '){
                buffer_c = myLine[i];
                buffer_next = myLine[i+1];
                buffer_s += buffer_c;

                cout << buffer_c;
                cout << "\n";
                cout << buffer_s;
                cout << "\n";

                if(buffer_s == "do" && (buffer_next == ' ' || buffer_next == '{')){
                    lexemas.push_back(buffer_s);
                    cout << "Vetor de lexemas: " + lexemas[0] + "\n";
                    buffer_s = "";
                }
                else if(buffer_s == "{"){
                    lexemas.push_back(buffer_s);
                    cout << "Vetor de lexemas: " + lexemas[1] + "\n";
                    buffer_s = "";
                }
                else if(buffer_s == "}"){
                    lexemas.push_back(buffer_s);
                    cout << "Vetor de lexemas: " + lexemas[2] + "\n";
                    buffer_s = "";
                }
                else if(buffer_s == "while" && (buffer_next == ' ' || buffer_next == '(')){
                    lexemas.push_back(buffer_s);
                    cout << "Vetor de lexemas: " + lexemas[3] + "\n";
                    buffer_s = "";
                }
                else if(buffer_s == "("){
                    lexemas.push_back(buffer_s);
                    cout << "Vetor de lexemas: " + lexemas[4] + "\n";
                    buffer_s = "";
                }
                else if(buffer_s == ")"){
                    lexemas.push_back(buffer_s);
                    cout << "Vetor de lexemas: " + lexemas[5] + "\n";
                    buffer_s = "";
                }
                else if(buffer_s == ";"){
                    lexemas.push_back(buffer_s);
                    cout << "Vetor de lexemas: " + lexemas[6] + "\n";
                    buffer_s = "";
                }
            }
            else{
                myLine.erase(i, 0);
            }
        }
    }

    for(int i = 0; i < lexemas.size(); i++){
        cout << lexemas[i];
    }
}