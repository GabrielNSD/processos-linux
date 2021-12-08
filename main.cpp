#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#include "./cache_interface.h"
#include "./direct_mapped.h"

using namespace std;

/* struct CacheLine
{
    bool validade;
    unsigned int conteudo;
}; */

int main()
{
    std::ifstream file("enderecos.dat");

    std::vector<unsigned short> addresses; // short tem 16 bits, int tem 32

    int pid;

    unsigned short input;
    while (file >> input)
    {
        addresses.push_back(input);
    }

    cout << "processo pai id: " << getpid() << endl;

    pid = fork();

    // Primeiro processo filho, cache diretamente mapeado
    if (pid == -1)
    {
        cout << "impossivel criar um filho" << endl;
        exit(-1);
    }
    else if (pid == 0)
    {
        cout << "codigo do processo filho em execucao: " << getpid() << endl;

        int TAMANHO_CACHE = 64;

        struct CacheLine *cache = inicializar(TAMANHO_CACHE);
        cout << endl;
        directMapped(cache, TAMANHO_CACHE, addresses);

        exit(1);
    }
    else
    {
        wait(NULL);
        cout << "fim da espera pelo fim do processo filho 1 (executado no processo pai)" << endl;
    }

    // Segundo processo filho, mapeamento associativo
    pid = fork();

    if (pid == -1)
    {
        cout << "impossivel criar um filho" << endl;
        exit(-1);
    }
    else if (pid == 0)
    {
        cout << "codigo do processo filho 2 em execucao " << getpid() << endl;

        int TAMANHO_CACHE = 32;

        struct cacheBlock *cache = inicializarBloco(TAMANHO_CACHE);
        exit(1);
    }
    else
    {
        wait(NULL);
        cout << "fim da espera pelo fim do processo filho 2 (executado no processo pai)" << endl;
    }

    exit(0);
}