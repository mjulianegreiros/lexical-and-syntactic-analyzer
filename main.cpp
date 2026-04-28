#include <iostream>
#include <fstream>

using namespace std;

int main(){
    string reservados[6] = {"do", "while", "{", "}", "(", ")"};
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

    return 0;

}