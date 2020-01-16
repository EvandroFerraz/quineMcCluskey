#ifndef IMPLICANTS_H
#define IMPLICANTS_H

#include<string>

using namespace std;

class Implicants{
    public:
    //Cabe�alho da fun��o de constru��o
    Implicants(string, string, bool, int);

    //Fun��es de Leitura
    string getBinaryCode() const;

    string getTruthTable() const;

    bool getMark() const;

    int getBox() const;

    //Fun��es de Update
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
