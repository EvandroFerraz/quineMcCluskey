#ifndef IMPLICANTS_H
#define IMPLICANTS_H

#include<string>

using namespace std;

class Implicants{
    public:
    //Cabeçalho da função de construção
    Implicants(string, string, bool, int);

    //Funções de Leitura
    string getBinaryCode() const;

    string getTruthTable() const;

    bool getMark() const;

    int getBox() const;

    //Funções de Update
    void setBinaryCode(string);

    void setTruthTable(string);

    void setMark(bool);

    void setBox(int);

private: //Variables can only be assigned by the get/set functions;
    string binaryCode;
    string truthTable;
    bool mark;
    int box;
};

#endif // IMPLICANTS_H
