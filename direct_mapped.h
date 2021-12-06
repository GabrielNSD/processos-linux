#include <iostream>
#include <stdlib.h>
//#include "./cache_interface.h"

using namespace std;

/* void directMapped(struct Cache *cache)
{
    cout << "dentro da funcao " << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << cache[i] << endl;
    }
    cache[2] = cache[2] + 4;
    return;
} */

void directMapped(struct CacheLine *cache, int tamanhoCache)
{
    cout << "dentro da funcao directMapped " << endl;

    // mostrar conteudo do cache na tela
    /*
    for (int i = 0; i < tamanhoCache; i++)
    {
        cout << "validade " << cache[i].validade << endl;
        cout << "conteudo " << cache[i].tag << endl;
    }*/

    return;
}