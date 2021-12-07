#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
numeroDoBlocoNaMemPrincipal/TotalDeLinhasNaCache = NumeroDaLinhaASerOcupada (resto da divisao de inteiros)

*/

struct extractData {
    unsigned short tag;
    unsigned short line;
};

/**
 * @brief Funcao que recebe um endereco e retorna a TAG e a linha a qual fazem referencia
 * 
 * @param address 
 * @return struct extractData 
 */
struct extractData returnData (unsigned short address) {
    unsigned short temp = address << 10;
    unsigned short tag = address >> 6;
    unsigned short line = temp >> 10;
    return {tag, line};
}

void directMapped(struct CacheLine *cache, int tamanhoCache, vector<unsigned short> memory)
{
    cout << "dentro da funcao directMapped " << endl;

    //cout << "size " << memory.size() << endl;

    int acertos = 0;
    int erros = 0;

    for (int i = 0; i < memory.size(); i++) {
        struct extractData convertido = returnData(memory[i]);
        unsigned short tag = convertido.tag;
        unsigned short line = convertido.line;
        //cout << convertido.tag << " " << convertido.line << endl;

        if(cache[line].validade){
            //cout << "valido " << endl;
            if(cache[line].tag == tag) {
                acertos++;
            } else {
                erros++;
                cache[line].tag = tag;
            }
        } else {
            //cout << "invalido" << endl;
            erros++;
            cache[line].validade = true;
            cache[line].tag = tag;
        }

    }

    cout << "acertos: " << acertos << endl;
    cout << "erros: " << erros << endl;

    return;
}