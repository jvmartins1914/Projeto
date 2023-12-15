#ifndef TABELAS_H
#define TABELAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define DIRETORIO_TABELAS "tabelas"

typedef struct {
    char nome[50];
    char tipo[10];
} Coluna;

typedef struct {
    unsigned int chavePrimaria;
    char **dados;  
} Registro;

typedef struct {
    char nomeTabela[50];
    Coluna *colunas;
    unsigned int numColunas;
    Registro *registros;
    unsigned int numRegistros;
} Tabela;

void criarDiretorio();

void limparBuffer();

void salvarDadosArquivo(Tabela *tabela);

void carregarDadosArquivo(Tabela *tabela);

void liberarMemoriaRegistros(Tabela *tabela);

void criarTabela(Tabela *tabela);

void listarTabelas();

void listarDadosTabela(Tabela *tabelas, unsigned int numTabelas);

void inserirRegistro(Tabela *tabelas, unsigned int numTabelas);

void liberarMemoria(Tabela *tabelas, unsigned int numTabelas);

void apagarTupla(Tabela *tabelas, unsigned int numTabelas);

void apagarTabela(Tabela **tabelas, unsigned int *numTabelas);

#endif  // TABELAS_H
