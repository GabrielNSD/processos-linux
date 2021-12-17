#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

struct extractDataMA
{
    unsigned short tag;
    unsigned short conjunto;
};

/**
 * @brief Funcao que recebe um endereco e retorna a TAG e a linha a qual fazem referencia
 *
 * @param address
 * @return struct extractDataMA
 */
struct extractDataMA returnDataMA(unsigned short address)
{
    unsigned short temp = address & 65528; // remove o offset - 65528 = 1111111111111000
    unsigned short tag = temp & 65280;     // zera os 8 dígitos menos significativos - 65024 = 1111111000000000
    tag = tag >> 8;                        // remove os 8 zeros menos significativos
    unsigned short conjunto = temp & 248;  // retorna os 8 dígitos menos significativos, zerando os 3 menos significativos - 504 = 111111000
    conjunto = conjunto >> 3;
    return {tag, conjunto};
}

/* struct extractDataMA returnDataMA(unsigned short address)
{
    unsigned short temp = address & 65528; // remove o offset - 65528 = 1111111111111000
    unsigned short tag = temp & 65024;     // zera os 8 dígitos menos significativos - 65024 = 1111111000000000
    tag = tag >> 9;                        // remove os 8 zeros menos significativos
    unsigned short conjunto = temp & 504;  // retorna os 8 dígitos menos significativos, zerando os 3 menos significativos - 504 = 111111000
    conjunto = conjunto >> 3;
    return {tag, conjunto};
} */

void mapeamentoAssociativo(struct cacheBlock *cache, int tamanhoCache, vector<unsigned short> memory)
{
    int acertos = 0;
    int falhas = 0;

    for (int i = 0; i < memory.size(); i++)
    {
        struct extractDataMA convertido = returnDataMA(memory[i]);
        unsigned short tag = convertido.tag;
        unsigned short conjunto = convertido.conjunto;

        if ((cache[conjunto].linha[0].validade && cache[conjunto].linha[0].tag == tag) || (cache[conjunto].linha[1].validade && cache[conjunto].linha[1].tag == tag))
        {
            acertos++;
        }
        else
        {
            falhas++;
            if (cache[conjunto].linha[0].permissao)
            {
                if (cache[conjunto].linha[0].validade == false)
                {
                    cache[conjunto].linha[0].validade = true;
                }

                cache[conjunto].linha[0].tag = tag;
                cache[conjunto].linha[0].permissao = false;
                cache[conjunto].linha[1].permissao = true;
            }
            else if (cache[conjunto].linha[1].permissao)
            {
                if (cache[conjunto].linha[1].validade == false)
                {
                    cache[conjunto].linha[1].validade = true;
                }
                cache[conjunto].linha[1].tag = tag;
                cache[conjunto].linha[1].permissao = false;
                cache[conjunto].linha[0].permissao = true;
            }
        }
    }

    cout << "acerto Associativo: " << acertos << endl;
    cout << "erros Associativo: " << falhas << endl;
}