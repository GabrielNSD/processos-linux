#include <stdlib.h>

struct CacheLine
{
    bool validade;
    unsigned int tag;
};

struct CacheLine *inicializar(int tamanho)
{
    struct CacheLine *cache = (struct CacheLine *)malloc(tamanho * sizeof(struct CacheLine));
    for (int i = 0; i < tamanho; i++)
    {
        cache[i].validade = false;
        cache[i].tag = 0;
    }
    return cache;
}

struct cacheBlock
{
    bool permissao;
    bool validade;
    unsigned int conjunto[2];
};

struct cacheBlock *inicializarBloco(int tamanho)
{
    struct cacheBlock *cache = (struct cacheBlock *)malloc(tamanho * sizeof(struct cacheBlock));
    for (int i = 0; i < tamanho; i++)
    {
        cache[i].permissao = false;
        cache[i].validade = false;
        cache[i].conjunto[0] = 0;
        cache[i].conjunto[1] = 0;
    }
    return cache;
}