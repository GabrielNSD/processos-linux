#include <stdlib.h>

struct CacheLine
{
    bool validade;
    unsigned int tag;
};

struct CacheLine *inicializar(int tamanho)
{
    struct CacheLine *cache = (struct CacheLine *)malloc(sizeof(struct CacheLine));
    for (int i = 0; i < tamanho; i++)
    {
        cache[i].validade = false;
        cache[i].tag = 0;
    }
    return cache;
}