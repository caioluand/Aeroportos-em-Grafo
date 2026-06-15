# Aeroportos em Grafo

Este projeto foi desenvolvido com o objetivo de exercitar os conceitos de grafos utilizando a representação por **matriz de esparsa**. A aplicação consiste em uma estrutura de dados para o cadastro de aeroportos (vértices) e o gerenciamento dos voos que os interligam (arestas).

### Tempo Dedicado
* **Total:** ~25 horas de desenvolvimento e implementação.

---

### Contexto Acadêmico
* **Instituição:** Pontifícia Universidade Católica de Campinas (PUC-Campinas)
* **Unidade:** Escola Politécnica / Faculdade de Análise de Sistemas
* **Curso:** Sistemas de Informação
* **Disciplina:** Estrutura e Recuperação de Dados II

---

### Aeroportos Inicialmente Cadastrados
O sistema comporta a expansão para quantos aeroportos forem desejados, iniciando por padrão com:
* Belo Horizonte (CNF)
* Brasília (BSB)
* Rio de Janeiro (GIG)
* Salvador (SSA)
* São Paulo (GRU)

A organização interna utiliza um vetor para indexar os aeroportos cadastrados e uma matriz associada para registrar a existência de conexões aéreas.

---

### Compilação e Execução

Para compilar o projeto com todos os seus Tipos Abstratos de Dados (TADs) e rodar o executável, utilize os comandos abaixo no terminal:

```bash
gcc main.c tad/listar.c tad/indice_aeroporto.c tad/matriz_voo.c -o grafo.exe
.\grafo.exe