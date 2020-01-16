#include "Implicants.h" //A conexão entre os arquivos .h e .cpp de uma classe é feita com este include

//Construtor da classe Implicants, serve pra declarar uma nova variável do tipo Implicants
Implicants::Implicants(string newBinaryCode, string newTruthTable, bool newMark, int newBox){
    binaryCode = newBinaryCode;
    truthTable = newTruthTable;
    mark = newMark;
    box = newBox;
}

//GETTERS
string Implicants::getBinaryCode() const {
    return binaryCode;
}

string Implicants::getTruthTable() const {
    return truthTable;
}

bool Implicants::getMark() const {
    return mark;
}

int Implicants::getBox() const {
    return box;
}

//SETTERS
void Implicants::setBinaryCode(string newBinaryCode){
    binaryCode = newBinaryCode;
}

void Implicants::setTruthTable(string newTruthTable){
    truthTable = newTruthTable;
}

void Implicants::setMark(bool newMark){
    mark = newMark;
}

void Implicants::setBox(int newBox){
    box = newBox;
}
