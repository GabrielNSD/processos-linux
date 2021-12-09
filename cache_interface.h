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

struct cacheLineAM {
    bool permissao;
    bool validade;
    bool tag;
};

struct cacheBlock
{
    struct cacheLineAM conjunto[2];
};

struct cacheBlock *inicializarBloco(int tamanho)
{
    struct cacheBlock *cache = (struct cacheBlock *)malloc(tamanho * sizeof(struct cacheBlock));
    for (int i = 0; i < tamanho; i++)
    {
        cache[i].conjunto[0].permissao = true;
        cache[i].conjunto[1].permissao = false;
        cache[i].conjunto[0].validade = false;
        cache[i].conjunto[1].validade = false;
        cache[i].conjunto[0].tag = 0;
        cache[i].conjunto[1].tag = 0;
    }
    return cache;
}