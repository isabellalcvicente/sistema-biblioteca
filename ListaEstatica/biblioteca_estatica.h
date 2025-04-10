//definicao de variaveis e do cabeçalho
#ifndef BIBLIOTECA_ESTATICA_H
#define BIBLIOTECA_ESTATICA_H
#define MAX_LIVROS 600
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_ISBN 14
#define MAX_USUARIO 100
#define MAX_DATA 11

//definindo struct objeto enum para status do livro
typedef enum
{
    DISPONIVEL,
    EMPRESTADO
} StatusLivro;

//definindo struct de objeto para livro usando as variaveis definidas 
typedef struct
{
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    char isbn[MAX_ISBN];
    StatusLivro status;
    char usuario[MAX_USUARIO];
    char dataEmprestimo[MAX_DATA];
} Livro;

//definindo tamanho da biblioteca e seu acervo 
typedef struct
{
    Livro livros[MAX_LIVROS];
    int totalLivros;
} Biblioteca;

// Prototipos (os alunos deverão implementar no .c)
void inicializarBiblioteca(Biblioteca *b);
//void pq nao retorna nada, apenas  inicializa
int cadastrarLivro(Biblioteca *b, char *titulo, char *autor, int ano, char *isbn);
void listarTodosLivros(Biblioteca *b);
int emprestarLivro(Biblioteca *b, char *isbn, char *usuario, char *data);
int devolverLivro(Biblioteca *b, char *isbn);
Livro *consultarLivroPorISBN(Biblioteca *b, char *isbn);
//retorna um ponteiro para um livro, ou seja retorna o end onde livro sera armazenado
//(parametros da funcao), passando a struct biblio e um ponteiro pra ela, como se o ponteiro 
// fosse um garçom mostrando a mesa do cliente apontado, ponteiro para isbn em str
#endif