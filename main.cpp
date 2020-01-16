#include <iostream> //biblioteca b�sica do c++
#include <stdlib.h> //permite a utiliza��o do comando system()
#include <math.h> //permite a utiliza��o do comando log2()
#include <vector> //permite a utiliza��o da classe vector
#include <algorithm> //permite a utiliza��o do comando sort()

#include "Implicants.h"

//Printa as informa��es de todos os implicantes atualmente na lista
void printImplicantList(vector<Implicants>& implicantList){
    for(int i=0;i<implicantList.size();i++){
        cout << implicantList[i].getBinaryCode() << " " << implicantList[i].getTruthTable() << " " << implicantList[i].getMark() << " " << implicantList[i].getBox() << endl;
    }
}

//Cria o grupo inicial de implicantes
void fillImplicantList(vector<Implicants>& newImplicantsList, string TT, int n){

    for(int i=0;i<TT.size();i++){
        if(TT[i] == 'x' || TT[i] == '1'){

            //Gera o c�digo bin�rio de um n�mero inteiro, referente ao mintermo i de TT
            int minterm = i;
            string binaryCode;

            //O n�mero inteiro � dividido por 2 enquanto > 0 e o resta de cada divis�o � adicionado como c�digo bin�rio
            while(minterm > 0) {
                if(minterm % 2 == 0)
                    binaryCode = '0' + binaryCode;
                else
                    binaryCode = '1' + binaryCode;

                minterm = minterm / 2;
            }

            //Adiciona (n - binaryCode.size()) zeros ao lado esquerdo, formando um c�digo bin�rio de n elementos
            int numZeros = n - binaryCode.size(); // a fun��o .size() retorna um valor inteiro, por isso pode ser usada em c�lculos entre n�meros inteiros
            for(int j=0;j<numZeros;j++){
                binaryCode = '0' + binaryCode;
            }

            //Gera a tabela verdade de um mintermo i
            //No grupo inicial cada implicante cobre apenas o mintermo que representa
            string truthTable;
            for(int j=0;j<TT.size();j++){
                if(j==i)
                    truthTable = truthTable + '1';
                else
                    truthTable = truthTable + '0';
            }

            //Calcula a quantidade de 1's no c�digo bin�rio de cada implicante para definir sua caixa
            int box = 0;
            for(int j=0;j<binaryCode.size();j++){
                if(binaryCode[j] == '1'){
                    box++;
                }
            }

            //Adiciona o novo implicante na lista din�mica
            Implicants newImplicant(binaryCode,truthTable,false,box); //mark = false inicialmente para todos os implicants
            newImplicantsList.push_back(newImplicant); //O comando push_back adiciona um novo elemento a uma lista din�mica
        }
    }
}

struct sortByBox{ //Fun��o para ordena��o por caixa, que incrementa a l�gica do comando sort()
    bool operator()(Implicants const &a, Implicants const &b) const{ //Utiliza-se como base uma struct do tipo bool operator (operador booleano)
        if(a.getBox() < b.getBox()){
            return true;
        }else{
          return false;
        }
    }
};

struct sortByX{//Fun��o para ordena��o pelo n�mero de 'x' no c�digo bin�rio seguido pela quantidade de mintermos cobertos pelo implicante.

    string TT;

    bool operator()(Implicants const &a, Implicants const &b) const{
        int xa = 0, xb = 0, mintermosA = 0, mintermosB = 0;

        //Identifica o n�mero de 'x' no c�digo bin�rio dos implicante a e b
        for(int i=0;i<a.getBinaryCode().size();i++){
            if(a.getBinaryCode()[i] == 'x')
                xa++;
            if(b.getBinaryCode()[i] == 'x')
                xb++;
        }

        //Identifica o n�mero de mintermos cobertos pelos implicante a e b
        for(int i=0;i<TT.size();i++){
            if(TT[i] == '1'){
                if(a.getTruthTable()[i] == '1')
                    mintermosA++;
                if(b.getTruthTable()[i] == '1')
                    mintermosB++;
            }
        }

        //Um implicante a sobe ao topo da lista se xa > xb ou se xa == xb e mintermosA > mintermosB
        if(xa > xb){
            return true;
        }else{
            if(xa == xb && mintermosA > mintermosB){
                return true;
            }else{
                return false;
            }
        }
    }
};

void quinePart1(vector<Implicants>& implicantList, int n){

    bool keepLoop = true; //Vari�vel que controla quando o loop de combina��o entre os implicants ter� fim

    while(keepLoop == true){
        //Ordena��o pelo valor da caixa
        sort(implicantList.begin(), implicantList.end(), sortByBox()); //Passe-se como par�metro o ponto inicial e final da lista, definindo o range de elementos que ser� ordenado. Como terceiro par�metro, tem-se tamb�m a fun��o para guiar a l�gica de ordena��o
        vector<Implicants> auxImplicantList = implicantList; //Define uma lista auxiliar para que seja poss�vel alterar os valores da lista original sem alterar a l�gica dos loops de compara��o
        bool existeCombinacao = false; //Flag pra saber se em cada grupo de itera��es existiu pelo menos uma combina��o entre as caixas

        for(int i = 0; i<auxImplicantList.size(); i++){ //Percorre os elementos da lista auxiliar de implicantes
            for(int j=i+1; j<auxImplicantList.size();j++){ //Itera��o para comparar um implicante da lista com o implicante seguinte, que devido � ordena��o por caixas ser�o sempre da mesma ou da pr�xima caixa (i ou i+1 (i+1 = j neste c�digo))
                if(auxImplicantList[j].getBox() == (auxImplicantList[i].getBox()+1)){ //Verifica se existe a diferen�a de 1 entre os indicies das caixas mesmo, se estou comparando i com i+1

                    int dif = 0, pos; //Vari�vel para guardar a quantidade de varia��es ocorridas e a posi��o em que ocorreu a �ltima dessas varia��es
                    for(int k = 0; k < n; k++){
                        if(auxImplicantList[i].getBinaryCode()[k] != auxImplicantList[j].getBinaryCode()[k]){
                            dif++;
                            pos = k;
                        }
                    }

                    if(dif == 1){ //Se ocorreu apenas uma varia��o entre os elementos do c�digo bin�rio dos implicantes comparados
                        implicantList[i].setMark(true); //Marco os implicantes combinados
                        implicantList[j].setMark(true);
                        //Os novos valores recebem inicialmente os valores de do implicante na posi��o i
                        string newTruthTable = implicantList[i].getTruthTable(), newBinaryCode = implicantList[i].getBinaryCode();
                        newBinaryCode[pos] = 'x'; //para atualizar o c�digo bin�rio simplesmente adiciona-se 'x' � posi��o onde ocorreu a diferen�a

                        //Atualiza-se a tabela verdade adicionando os mintermos cobertos pelo implicante na posi��o j � tabela verdade do implicante na posi��o i
                        for(int k=0;k<implicantList[i].getTruthTable().size();k++){
                            if(implicantList[j].getTruthTable()[k] == '1'){
                                newTruthTable[k] = '1';
                            }
                        }

                        //Adicionando um novo implicante a lista, gerado pela combina��o dos implicantes nas posi��es i e j
                        //Tem-se mark = false, tendo em vista que o implicante gerado � novo, ainda sem combina��o.
                        //O valor da caixa do novo implicante gerado vai ser sempre igual ao valor da caixa do implicante na posi��o i
                        Implicants newImplicant(newBinaryCode, newTruthTable, false, implicantList[i].getBox());
                        implicantList.push_back(newImplicant);
                        existeCombinacao = true; //Adiciona-se um valor verdadeiro na flag, indicando que uma combina��o foi realizada

                    }
                }else if(auxImplicantList[j].getBox() >= (auxImplicantList[i].getBox()+2)){ //....
                    break;
                }
            }
        }

        //Condi��o para o pr�ximo grupo de combina��es
        if(existeCombinacao == true){ //Se pelo menos uma combina��o foi realizada neste grupo exclui-se as fun��es com marca = true e as repetidas
            int a = 0;
            while(a<implicantList.size()){
                if(implicantList[a].getMark() == true){
                    implicantList.erase(implicantList.begin()+a); //Sempre que acontece o .erase() o �ndice dos itens na lista se atualiza automaticamente (indice++), de forma que a atualiza��o deve ser realizada apenas se o erase n�o foi
                }else{ //se o implicante n�o estiver marcado exclui os iguais a ele
                    int b = a+1;
                    while(b<implicantList.size()){
                        if(implicantList[a].getBinaryCode() == implicantList[b].getBinaryCode()){
                            implicantList.erase(implicantList.begin()+b);
                        }else{
                            b++; //Atualiza o �ndice b apenas se n�o foi feito erase() na lista
                        }
                    }
                    a++; //Atualiza o �ndice a apenas se n�o foi feito erase() na lista
                }
            }
            keepLoop = true;
        }else{
            //Se n�o ocorreu nenhuma combina��o quer dizer que todas as poss�veis combina��es entre mintermos j� foram realizadas e o loop pode ser parado, o que conclui a fase 1 do quine
            keepLoop = false;
        }
    }
}

void quinePart2(vector<Implicants>& implicantList, string TT){

    //O objetivo da fase de cobertura � selecionar primeiramente os implicantes primos seguidos dos implicantes de menor custo que cubram os mintermos restantes de TT
    //Sempre que um implicante novo � selecionado, zera-se a posi��o correspondente aos mintermos cobertos por ele em TT

    //Desconsidera os don't care states para a fase de cobertura
    for(int i=0;i<TT.size();i++){
        if(TT[i] == 'x')
            TT[i] = '0';
    }

    vector<string> implicantSaida;

    //Encontra os mintermos cobertos apenas por 1 implicante
    for(int i=0;i<TT.size();i++){
        if(TT[i] == '1'){
            vector<int> coveredBy;
            for(int j=0;j<implicantList.size();j++){
                if(implicantList[j].getTruthTable()[i] == '1'){
                    coveredBy.push_back(j);
                }
            }
            if(coveredBy.size() == 1){ //Se o implicante salvo � essencial
                //Adiciona o implicante no vetor de sa�da
                implicantSaida.push_back(implicantList[coveredBy[0]].getBinaryCode());

                //Zera as posi��es referentes aos mintermos cobertos pelo implicante salvo
                for(int j=0;j<TT.size();j++){
                    if(implicantList[coveredBy[0]].getTruthTable()[j] == '1'){
                        TT[j] = '0';
                    }
                }

                //Apaga o implicante selecionado para solu��o da lista de implicantes
                implicantList.erase(implicantList.begin()+coveredBy[0]);
            }
        }
    }

    //Cria-se um ponteiro de mem�ria
    size_t found;
    //O ponteiro found recebe a posi��o que existe um valor 1 em TT
    found = TT.find('1');

    //Seleciona os implicantes primos restantes, o loop continua at� que n�o exista mais nenhum valor 1 em TT
    while(found != string::npos){
        //Ordena por Custo > Quantidade de Mintermos Cobertos
        //Maior n�mero de 'x' = menor custo
        sortByX sort1;
        sort1.TT = TT; //Cria-se uma vari�vel da struct sortByX que recebe TT como par�metro

        sort(implicantList.begin(), implicantList.end(), sort1); //Ordena implicantList usando sort1 como guia de ordena��o

        //Se um implicante no topo da lista cobre um dos mintermos de TT, tem-se que este implicante � a melhor escolha na cobertura
        //Assim como na sele��o de implicantes essenciais, todo implicante selecionado tem seus mintermos zerados em TT e � exclu�do da lista de implicantes
        for(int i=0;i<implicantList.size();i++){
            if(implicantList[i].getTruthTable()[found] == '1' && TT[found] == '1'){
                implicantSaida.push_back(implicantList[i].getBinaryCode());

                for(int j=0;j<TT.size();j++){
                    if(implicantList[i].getTruthTable()[j] == '1')
                        TT[j] = '0';
                }

                implicantList.erase(implicantList.begin()+i);

                found = TT.find('1'); //Busca mintermos n�o cobertos em TT novamente, resetando o loop se um mintermo n�o coberto foi encontrado
            }
        }
    }

    //Imprime os implicantes selecionados para cobertura de TT
    string funcBoolean;
    for(int i=0;i<implicantSaida.size();i++){
        cout << implicantSaida[i] << endl;

        //Imprime os implicantes no formato de uma fun��o booleana
        string aux = implicantSaida[i];
        string aux2;
        for(int j=0;j<aux.size();j++){
            if(aux[j] == '1'){
                aux2 = j+65;
                funcBoolean = funcBoolean + aux2;
            }
            if(aux[j] == '0'){
                aux2 = j+65;
                funcBoolean = funcBoolean + aux2 + "'";
            }
        }
        if(i != implicantSaida.size()-1)
            funcBoolean = funcBoolean + " + ";
    }
    cout << funcBoolean << endl;
}


int main(){
    string TT; //Vari�vel para a tabela verdade de entrada
    bool validTT = false; //Vari�vel para validar a tabela verdade de entrada

    //A tabela verdade de entrada deve ser uma string composta apenas pelos caracteres 1, 0 e x.
    //O while vai continuar at� que o usu�rio digite uma tabela verdade v�lida (validTT = true)
    while(validTT == false){

        cout << "Digite a tabela verdade de entrada: " << endl;
        cin >> TT;

        system("cls");

        //Verifica se TT possui um tamanho v�lido (deve ser 8 para 3 vari�veis de entrada, 16 para 4, 32 para 5 e etc)
        //TT.size() = a quantidade de elementos na string TT, representando a quantidade de termos na tabela de entrada
        //O tamanho � v�lido se o logaritmo na base 2 de TT.size() � > 1 e � um n�mero inteiro
        if(log2(TT.size()) > 1 && log2(TT.size()) == (int)log2(TT.size())){
            //Verifica se os caracteres de TT est�o no formato correto (0 = maxtermo, 1 = mintermo ou x = don't care state)
            bool isBinary = true;
            for(int i=0;i<TT.size();i++){
                if(TT[i] != '1' && TT[i] != '0' && TT[i] != 'x'){ //Caso um dos elementos em TT n�o respeite o padr�o predefinido atribui-se falso para isBinary
                    isBinary = false;
                    break;
                }
            }
            if(isBinary == true) //Se isBinary = true tem-se uma tabela de entrada v�lida
                validTT = true;
        }
    }

    //Define-se um vetor de vari�veis do tipo Implicants
    //Um vetor definido pela classe vector n�o possui uma quantidade fixa de elementos, de forma que esta classe pode ser utilizada na cria��o
    //de uma estrutura de lista din�mica
    vector<Implicants> implicantList;

    int n = log2(TT.size()); //n = quantidade de vari�veis de entrada

    //Fun��o para preencher os a lista de implicantes inicial
    fillImplicantList(implicantList, TT, n);

    quinePart1(implicantList, n); //Combina��o de Implicantes - Fase para gera��o dos implicantes primos

    quinePart2(implicantList, TT); //Cobertura de Mintermos - Fase para gera��o dos implicantes primos essenciais

    //printImplicantList(implicantList);
}
