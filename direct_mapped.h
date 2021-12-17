#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
numeroDoBlocoNaMemPrincipal/TotalDeLinhasNaCache = NumeroDaLinhaASerOcupada (resto da divisao de inteiros)

*/

struct extractData
{
    unsigned short tag;
    unsigned short line;
};

/**
 * @brief Funcao que recebe um endereco e retorna a TAG e a linha a qual fazem referencia
 *
 * @param address
 * @return struct extractData
 */
struct extractData returnData(unsigned short address)
{
    unsigned short temp = address & 65528; // remove o offset - 65528 = 1111111111111000
    unsigned short tag = temp & 65024;     // zera os 9 dígitos menos significativos - 65024 = 1111111000000000
    tag = tag >> 9;                        // remove os 9 zeros menos significativos
    unsigned short line = temp & 504;      // retorna os 9 dígitos menos significativos, zerando os 3 menos significativos - 504 = 111111000
    line = line >> 3;
    return {tag, line};
}

void directMapped(struct CacheLine *cache, int tamanhoCache, vector<unsigned short> memory)
{

    int acertos = 0;
    int erros = 0;

    for (int i = 0; i < memory.size(); i++)
    {
        struct extractData convertido = returnData(memory[i]);
        unsigned short tag = convertido.tag;
        unsigned short line = convertido.line;

        if (cache[line].validade)
        {
            if (cache[line].tag == tag)
            {
                acertos++;
            }
            else
            {
                erros++;
                cache[line].tag = tag;
            }
        }
        else
        {
            erros++;
            cache[line].validade = true;
            cache[line].tag = tag;
        }
    }

    cout << "acertos: " << acertos << endl;
    cout << "erros: " << erros << endl;

    return;
}