#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Função que verifica o fim das expressões (do, while)
int check_end(char next){
    char end[] = {' ', '{', '}', '(', ')', ';', '[', ']'};
    for(int i = 0; i < 8; i++){
        if(next == end[i]){
            return 1;
        }
    }
    return 0;
}

//Função que verifica se os identificadores são escirtos corretamente seguindo as normas da linguagem C
int check_id(string s){

    if(s[0] != '_' && (s[0] < 'a' || s[0] > 'z') && (s[0] < 'A' || s[0] > 'Z')){
        cout << "[ERRO] Erro lexico! O caractere inicial nao e permitido para o identificador. -> " + s + "\n";
        return 0;
    }

    for(int i = 1; i < s.length(); i++){
        if((s[i] < 'a' || s[i] > 'z') && (s[i] < '0' || s[i] > '9') && (s[i] < 'A' || s[i] > 'Z') && s[i] != '_'){
            cout << "[ERRO] Erro lexico! Tipo nao reconhecido -> " + s + "\n";
            return 0;    
        }
    }
    return 1;
}

//Função que identifica um operador relacional
int check_op(char c){
    if(c >= '<' && c <= '>'){
        return 1;
    }
    return 0;
}

int main(){


    // Contador para armazenar valores em vetor de lexemas (-1 para o contador aumenta e preencher o vetor no indice 0)
    int cont = -1;

    // Buffer_C responsável por pegar a letra atual
    // Buffer_Next responsável por pegar a próxima letra
    // Buffer_S responsável pelo resultado das letras juntas do buffer_c (string)
    char buffer_c, buffer_next;
    std::string buffer_s;

    // Ordem de tokens esperado pelo analisador sintático
    string token_syntax[] = {"Res_do", "Ch_open", "Ch_close", "Res_while", "P_open", "identificador", "Op_rel", "identificador", "P_close", "end"};

    std::vector<std::string> lexemas;
    std::vector<std::string> tokens;

    ifstream myFile("codigo.txt");
    string myLine;

    // Percorrendo o arquivo
    while(getline (myFile, myLine)) {
        for(int i = 0; i < myLine.length(); i++){

            //Verificando se o caractere atual é um espaço em branco
            if(myLine[i] != ' '){
                buffer_c = myLine[i];
                buffer_next = myLine[i+1];
                buffer_s += buffer_c;


                // Verificação de palavras reservadas e identificadores com base em suas características.

                //Verificação do 'do'
                if(buffer_s == "do" && check_end(buffer_next)){
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[0]);
                    cont++;
                    buffer_s = "";
                }
                //Verificação do '{'
                else if(buffer_s == "{"){
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[1]);
                    cont++;
                    buffer_s = "";
                }
                //Verificação do '}'
                else if(buffer_s == "}"){
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[2]);
                    cont++;
                    buffer_s = "";
                }
                //Verificação do 'while'
                else if(buffer_s == "while" && check_end(buffer_next)){
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[3]);
                    cont++;
                    buffer_s = "";
                }
                //Verificação do '('
                else if(buffer_s == "("){
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[4]);
                    cont++;
                    buffer_s = "";
                }

                //Verificação do ')'
                else if(buffer_s == ")"){
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[8]);
                    cont++;
                    buffer_s = "";
                }

                //Verificação do ';'
                else if(buffer_s == ";"){
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[9]);
                    cont++;
                    buffer_s = "";
                }

                //Verificação dos operadores '<, =, >'
                else if(check_op(buffer_c) && ((buffer_next >= 'a' && buffer_next <= 'z') || buffer_next == ' ')){
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[6]);
                    cont++;
                    buffer_s = "";
                }

                //Verificação do 'identificador'
                else if(check_end(buffer_next)){
                    if(!check_id(buffer_s)){
                        return 1;
                    }
                    lexemas.push_back(buffer_s);
                    tokens.push_back(token_syntax[5]);
                    cont++;
                    buffer_s = "";
                }
                
            }
            //Removendo o caractere atual se for um espaço em branco
            else{
                myLine.erase(i, 0);
            }
        }
    }


    // Analisador Sintático

    //Verifica se o código recebido foi digitado na ordem correta. Se não, exibe msg de erro e aponta onde está o erro
    for(int i = 0; i < 10; i++){
        if(token_syntax[i] != tokens[i]){
            cout << "Erro sintático (expressão fora de ordem ou incompleta) -> " + lexemas[i] + " " + lexemas[i + 1] + "\n";
            cout << "Você quis dizer 'do {} while();' ?\n";
            return 1;
        }
    }
    cout << "[Compilado]";
}