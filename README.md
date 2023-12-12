Análise do Código: Sistema de Gerenciamento de Tabelas


funções do código, o que fazem e suas implementações:



0.0 - Função criarDiretorio:

O que faz: Essa função é responsável por criar um diretório chamado "tabelas" no sistema de arquivos, onde os arquivos das tabelas serão armazenados.
Implementação: Utiliza a função mkdir para criar o diretório. A escolha entre mkdir(DIRETORIO_TABELAS) e mkdir(DIRETORIO_TABELAS, 0700) é feita condicionalmente com base na macro _WIN32, indicando se o sistema operacional é Windows.

0.1 - Função limparBuffer:

O que faz: Limpa o buffer do teclado, descartando qualquer caractere remanescente até encontrar uma quebra de linha ou o final do arquivo.
Implementação: Utiliza um loop while para ler caracteres do buffer até encontrar uma quebra de linha ou o final do arquivo.

0.2 - Função salvarDadosArquivo:

O que faz: Salva os dados de uma tabela em um arquivo no diretório "tabelas".
Implementação: Abre um arquivo em modo de escrita, formata e escreve os dados da tabela no arquivo.

0.3 - Função carregarDadosArquivo:

O que faz: Carrega os dados de uma tabela a partir de um arquivo no diretório "tabelas".
Implementação: Abre um arquivo em modo de leitura, lê e interpreta os dados, preenchendo a estrutura da tabela.

0.4 - Função liberarMemoriaRegistros:

O que faz: Libera a memória alocada para os registros de uma tabela.
Implementação: Utiliza loops para percorrer a estrutura de registros e colunas, liberando a memória alocada dinamicamente.

0.5 - Função criarTabela:

O que faz: Solicita ao usuário informações para criar uma nova tabela e salva os dados no arquivo.
Implementação: Usa entradas do usuário para definir o nome da tabela, número de colunas, nomes e tipos das colunas. Posteriormente, salva esses dados no arquivo.

0.6 - Função listarTabelas:

O que faz: Lista todas as tabelas existentes no diretório "tabelas".
Implementação: Utiliza a biblioteca dirent.h para percorrer os arquivos no diretório e imprime os nomes das tabelas.

0.7 - Função listarDadosTabela:

O que faz: Lista os dados de uma tabela específica.
Implementação: Solicita ao usuário o nome da tabela desejada, encontra a tabela correspondente e imprime seus dados.

0.8 - Função inserirRegistro:

O que faz: Solicita ao usuário dados para inserir um novo registro em uma tabela existente.
Implementação: Pede ao usuário o nome da tabela, a chave primária e os valores para cada coluna. Verifica a unicidade da chave primária antes de inserir o registro.

0.9 - Função liberarMemoria:

O que faz: Libera a memória alocada para todas as tabelas.
Implementação: Utiliza loops para percorrer todas as tabelas, liberando a memória de registros e colunas.

0.10 - Função apagarTupla:
O que faz: Remove um registro específico de uma tabela.
Implementação: Pede ao usuário o nome da tabela e a chave primária do registro a ser removido. Remove o registro da tabela e atualiza o arquivo correspondente.

0.11 - Função apagarTabela:
O que faz: Remove uma tabela específica.
Implementação: Pede ao usuário o nome da tabela a ser removida, remove a tabela da lista e exclui o arquivo correspondente.

0.12 - Função main:
O que faz: Controla o fluxo principal do programa, oferecendo um menu interativo para o usuário.
Implementação: Inicializa o diretório, carrega dados existentes, apresenta um menu interativo e chama as funções correspondentes às escolhas do usuário. Ao final, libera a memória alocada e salva os dados.






1 - O que foi feito:

O código implementa um sistema simples de gerenciamento de tabelas, permitindo a criação, listagem, inserção de registros, exclusão de registros e exclusão de tabelas.
Foi implementada a persistência de dados em arquivos, onde as tabelas e seus registros são armazenados em arquivos no sistema de arquivos.

2 - O que não foi feito:

Não foram implementadas verificações mais robustas para a entrada de dados do usuário, como validações de tipos ou limites para os valores das chaves primárias.
Não há uma funcionalidade de atualização de registros existentes.
A funcionalidade extra não foi implementada neste código.

3 - O que faria de forma diferente:

Não foi feita a função "pesquisar valor", encontrei muita dificuldade ao implementar ela, acabou que achei melhor enviar somente as que consegui fazer.
Para melhorar a robustez, seria interessante implementar funções específicas para a validação dos tipos de dados inseridos, garantindo que os dados fornecidos pelo usuário correspondam aos tipos definidos para as colunas.
Poderia ser implementada uma funcionalidade para atualização de registros, permitindo a modificação de dados já existentes.
A alocação de memória para strings fixas, como nomes de tabelas e tipos de colunas, poderia ser feita de forma mais eficiente usando arrays estáticos.

4 - Como compilar o projeto:

O projeto pode ser compilado usando um compilador C padrão.
Certifique-se de que as bibliotecas padrão (stdio.h, stdlib.h, string.h, sys/stat.h, dirent.h) estão disponíveis no sistema.
O código utiliza a função mkdir, que pode ter comportamento diferente em sistemas operacionais distintos. No código, há uma verificação condicional para sistemas Windows usando _WIN32.
Não foram utilizadas bibliotecas externas que precisam ser instaladas.

5 - Conclusão:
O código fornece uma estrutura básica de um sistema de gerenciamento de tabelas em linguagem C, demonstrando conceitos de alocação dinâmica de memória e manipulação de arquivos. Contudo, para aplicações mais robustas, seria necessário aprimorar a validação de entrada de dados, implementar funcionalidades adicionais e adotar boas práticas de programação, como modularização do código em funções mais especializadas.





