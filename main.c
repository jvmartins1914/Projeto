#include "tabelas.h"

void criarDiretorio() {
  
#ifdef _WIN32
    mkdir(DIRETORIO_TABELAS);
#else
    mkdir(DIRETORIO_TABELAS, 0700);
#endif
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void salvarDadosArquivo(Tabela *tabela) {
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "%s/%s", DIRETORIO_TABELAS, tabela->nomeTabela);

    FILE *file = fopen(caminhoArquivo, "w");
    if (file == NULL) {
        printf("Erro: Falha ao criar o arquivo da tabela %s.\n", tabela->nomeTabela);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %u\n", tabela->nomeTabela, tabela->numColunas);
    for (unsigned int i = 0; i < tabela->numColunas; ++i) {
        fprintf(file, "%s %s\n", tabela->colunas[i].nome, tabela->colunas[i].tipo);
    }

    for (unsigned int i = 0; i < tabela->numRegistros; ++i) {
        fprintf(file, "%u", tabela->registros[i].chavePrimaria);
        for (unsigned int j = 0; j < tabela->numColunas; ++j) {
            fprintf(file, " %s", tabela->registros[i].dados[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void carregarDadosArquivo(Tabela *tabela) {
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "%s/%s", DIRETORIO_TABELAS, tabela->nomeTabela);

    FILE *file = fopen(caminhoArquivo, "r");
    if (file == NULL) {
        
        return;
    }

    fscanf(file, "%s %u", tabela->nomeTabela, &tabela->numColunas);
    tabela->colunas = (Coluna *)malloc(tabela->numColunas * sizeof(Coluna));
    tabela->registros = NULL;  

    for (unsigned int i = 0; i < tabela->numColunas; ++i) {
        fscanf(file, "%s %s", tabela->colunas[i].nome, tabela->colunas[i].tipo);
    }

    while (!feof(file)) {
        Registro novoRegistro;
        fscanf(file, "%u", &novoRegistro.chavePrimaria);
        novoRegistro.dados = (char **)malloc(tabela->numColunas * sizeof(char *));

        for (unsigned int i = 0; i < tabela->numColunas; ++i) {
            novoRegistro.dados[i] = (char *)malloc(100 * sizeof(char));
            fscanf(file, "%s", novoRegistro.dados[i]);
        }

        tabela->registros = (Registro *)realloc(tabela->registros,
                                                 (tabela->numRegistros + 1) * sizeof(Registro));

        tabela->registros[tabela->numRegistros] = novoRegistro;
        tabela->numRegistros++;
    }

    fclose(file);
}

void liberarMemoriaRegistros(Tabela *tabela) {
    for (unsigned int i = 0; i < tabela->numRegistros; ++i) {
        for (unsigned int j = 0; j < tabela->numColunas; ++j) {
            free(tabela->registros[i].dados[j]);
        }
        free(tabela->registros[i].dados);
    }
    free(tabela->registros);
}

void criarTabela(Tabela *tabela) {
    unsigned int numColunas;
    printf("Digite o número de colunas: ");
    scanf("%u", &numColunas);
    limparBuffer();

    tabela->numColunas = numColunas;
    tabela->colunas = (Coluna *)malloc(numColunas * sizeof(Coluna));
    tabela->registros = NULL;

    printf("Digite o nome da tabela: ");
    fgets(tabela->nomeTabela, sizeof(tabela->nomeTabela), stdin);
    tabela->nomeTabela[strcspn(tabela->nomeTabela, "\n")] = '\0';

    for (unsigned int i = 0; i < numColunas; ++i) {
        printf("Digite o nome da coluna %u: ", i + 1);
        fgets(tabela->colunas[i].nome, sizeof(tabela->colunas[i].nome), stdin);
        tabela->colunas[i].nome[strcspn(tabela->colunas[i].nome, "\n")] = '\0';
        limparBuffer();

        printf("Digite o tipo da coluna %u (char, int, float, double, string): ", i + 1);
        fgets(tabela->colunas[i].tipo, sizeof(tabela->colunas[i].tipo), stdin);
        tabela->colunas[i].tipo[strcspn(tabela->colunas[i].tipo, "\n")] = '\0';
        limparBuffer();
    }

    salvarDadosArquivo(tabela);
}


void listarTabelas() {
    struct dirent *dp;
    DIR *dir = opendir(DIRETORIO_TABELAS);

    if (dir == NULL) {
        printf("Erro: Não foi possível abrir o diretório de tabelas.\n");
        exit(EXIT_FAILURE);
    }

    printf("=== Tabelas ===\n");

    while ((dp = readdir(dir)) != NULL) {
        if (dp->d_type == DT_REG) { 
            printf("%s\n", dp->d_name);
        }
    }

    closedir(dir);
}

void listarDadosTabela(Tabela *tabelas, unsigned int numTabelas) {
    char nomeTabela[50];
    printf("Digite o nome da tabela: ");
    scanf("%s", nomeTabela);

    int indiceTabela = -1;
    for (unsigned int i = 0; i < numTabelas; ++i) {
        if (strcmp(tabelas[i].nomeTabela, nomeTabela) == 0) {
            indiceTabela = i;
            break;
        }
    }

    if (indiceTabela == -1) {
        printf("Erro: Tabela '%s' não encontrada.\n", nomeTabela);
        return;
    }

    printf("=== Dados da Tabela '%s' ===\n", nomeTabela);

    
    for (unsigned int i = 0; i < tabelas[indiceTabela].numColunas; ++i) {
        printf("%s\t", tabelas[indiceTabela].colunas[i].nome);
    }
    printf("\n");

    
    for (unsigned int i = 0; i < tabelas[indiceTabela].numRegistros; ++i) {
        for (unsigned int j = 0; j < tabelas[indiceTabela].numColunas; ++j) {
            printf("%s\t", tabelas[indiceTabela].registros[i].dados[j]);
        }
        printf("\n");
    }
}

void inserirRegistro(Tabela *tabelas, unsigned int numTabelas) {
    char nomeTabela[50];
    printf("Digite o nome da tabela: ");
    scanf("%s", nomeTabela);

    int indiceTabela = -1;
    for (unsigned int i = 0; i < numTabelas; ++i) {
        if (strcmp(tabelas[i].nomeTabela, nomeTabela) == 0) {
            indiceTabela = i;
            break;
        }
    }

    if (indiceTabela == -1) {
        printf("Erro: Tabela '%s' não encontrada.\n", nomeTabela);
        return;
    }

    Registro novoRegistro;
    novoRegistro.dados = (char **)malloc(tabelas[indiceTabela].numColunas * sizeof(char *));

    printf("Digite a chave primária: ");
    scanf("%u", &novoRegistro.chavePrimaria);

    for (unsigned int i = 0; i < tabelas[indiceTabela].numColunas; ++i) {
        novoRegistro.dados[i] = (char *)malloc(100 * sizeof(char));
        printf("Digite o valor para a coluna %s: ", tabelas[indiceTabela].colunas[i].nome);
        scanf("%s", novoRegistro.dados[i]);
    }

    
    for (unsigned int i = 0; i < tabelas[indiceTabela].numRegistros; ++i) {
        if (tabelas[indiceTabela].registros[i].chavePrimaria == novoRegistro.chavePrimaria) {
            printf("Erro: Chave primária já existe na tabela '%s'.\n", nomeTabela);

            
            for (unsigned int j = 0; j < tabelas[indiceTabela].numColunas; ++j) {
                free(novoRegistro.dados[j]);
            }
            free(novoRegistro.dados);

            return;
        }
    }

   
    tabelas[indiceTabela].registros = (Registro *)realloc(
        tabelas[indiceTabela].registros, (tabelas[indiceTabela].numRegistros + 1) * sizeof(Registro)
    );

    tabelas[indiceTabela].registros[tabelas[indiceTabela].numRegistros] = novoRegistro;
    tabelas[indiceTabela].numRegistros++;

    
    salvarDadosArquivo(&tabelas[indiceTabela]);
}

void liberarMemoria(Tabela *tabelas, unsigned int numTabelas) {
    for (unsigned int i = 0; i < numTabelas; ++i) {
        liberarMemoriaRegistros(&tabelas[i]);
        free(tabelas[i].colunas);
    }
    free(tabelas);
}

void apagarTupla(Tabela *tabelas, unsigned int numTabelas) {
    char nomeTabela[50];
    printf("Digite o nome da tabela: ");
    scanf("%s", nomeTabela);

    int indiceTabela = -1;
    for (unsigned int i = 0; i < numTabelas; ++i) {
        if (strcmp(tabelas[i].nomeTabela, nomeTabela) == 0) {
            indiceTabela = i;
            break;
        }
    }

    if (indiceTabela == -1) {
        printf("Erro: Tabela '%s' não encontrada.\n", nomeTabela);
        return;
    }

    unsigned int chavePrimaria;
    printf("Digite a chave primária da tupla a ser apagada: ");
    scanf("%u", &chavePrimaria);

    int indiceTupla = -1;
    for (unsigned int i = 0; i < tabelas[indiceTabela].numRegistros; ++i) {
        if (tabelas[indiceTabela].registros[i].chavePrimaria == chavePrimaria) {
            indiceTupla = i;
            break;
        }
    }

    if (indiceTupla == -1) {
        printf("Erro: Tupla com a chave primária %u não encontrada na tabela '%s'.\n",
               chavePrimaria, nomeTabela);
        return;
    }

    
    for (unsigned int i = indiceTupla; i < tabelas[indiceTabela].numRegistros - 1; ++i) {
        tabelas[indiceTabela].registros[i] = tabelas[indiceTabela].registros[i + 1];
    }

    tabelas[indiceTabela].numRegistros--;

    
    salvarDadosArquivo(&tabelas[indiceTabela]);
}

void apagarTabela(Tabela **tabelas, unsigned int *numTabelas) {
    char nomeTabela[50];
    printf("Digite o nome da tabela a ser apagada: ");
    scanf("%s", nomeTabela);

    int indiceTabela = -1;
    for (unsigned int i = 0; i < *numTabelas; ++i) {
        if (strcmp((*tabelas)[i].nomeTabela, nomeTabela) == 0) {
            indiceTabela = i;
            break;
        }
    }

    if (indiceTabela == -1) {
        printf("Erro: Tabela '%s' não encontrada.\n", nomeTabela);
        return;
    }

    
    for (unsigned int i = indiceTabela; i < *numTabelas - 1; ++i) {
        (*tabelas)[i] = (*tabelas)[i + 1];
    }

    (*numTabelas)--;

    
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "%s/%s", DIRETORIO_TABELAS, nomeTabela);
    remove(caminhoArquivo);
}

int main() {
    criarDiretorio();

    Tabela *tabelas = NULL;
    unsigned int numTabelas = 0;

    
    DIR *dir = opendir(DIRETORIO_TABELAS);
    struct dirent *dp;

    if (dir != NULL) {
        while ((dp = readdir(dir)) != NULL) {
            if (dp->d_type == DT_REG) {  
                Tabela novaTabela;
                strcpy(novaTabela.nomeTabela, dp->d_name);
                carregarDadosArquivo(&novaTabela);

                tabelas = (Tabela *)realloc(tabelas, (numTabelas + 1) * sizeof(Tabela));
                tabelas[numTabelas] = novaTabela;
                numTabelas++;
            }
        }
        closedir(dir);
    } else {
        printf("Erro: Não foi possível abrir o diretório de tabelas.\n");
        exit(EXIT_FAILURE);
    }

    int escolha;
    do {
        printf("\nMenu:\n");
        printf("1. Criar Tabela\n");
        printf("2. Listar Tabelas\n");
        printf("3. Listar Dados de uma Tabela\n");
        printf("4. Inserir Registro\n");
        printf("5. Apagar Registro\n");
        printf("6. Apagar Tabela\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        limparBuffer(); 

        switch (escolha) {
            case 1:
                tabelas = (Tabela *)realloc(tabelas, (numTabelas + 1) * sizeof(Tabela));
                criarTabela(&tabelas[numTabelas]);
                numTabelas++;
                break;
            case 2:
                listarTabelas();
                break;
            case 4:
                inserirRegistro(tabelas, numTabelas);
                break;
            case 3:
                listarDadosTabela(tabelas, numTabelas);
                break;
            case 5:
                apagarTupla(tabelas, numTabelas);
                break;
            case 6:
                apagarTabela(&tabelas, &numTabelas);
                break;
            case 7:
                
                for (unsigned int i = 0; i < numTabelas; ++i) {
                    salvarDadosArquivo(&tabelas[i]);
                }
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 7);


    liberarMemoria(tabelas, numTabelas);

    return 0;
}
