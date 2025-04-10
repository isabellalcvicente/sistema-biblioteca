//importando outros arq 
#include "biblioteca_estatica.h"
#include <string.h>
#include <stdio.h>
void inicializarBiblioteca(Biblioteca *b)
{
    b->totalLivros = 0;
    //b é apelido e ponteiro de biblioteca, é o mesmo que (*b).totalLivros = 0 
    //definindo a biblioteca = 0 sem livros
}

int cadastrarLivro(Biblioteca *b, char *titulo, char *autor, int ano, char *isbn)
//cria funcao cadastrar, que aponta o objeto e seu end de memoria, e os atributos tem q 
//colocar o tipo char ou int antes de apontar

{
    if (b->totalLivros >= MAX_LIVROS)
    //se biblioteca cheia 
        return 0;
        //nao cadastre  o livro pq deu errado
    Livro *novo = &b->livros[b->totalLivros];
    // cria um ponteiro para um novo livro onde irá apontar para a posicao onde será armazenado  
    // &b -> livros= acessa o prox end de memoria onde o novo livro será salvo 
    // [b->totalLivros] = ta snedo usado como indice da posicao, listando do total 
    
    //transforma os dados de entrada em str
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    strcpy(novo->isbn, isbn);
    novo->ano = ano;
    novo->status = DISPONIVEL;
    novo->usuario[0] = '\0';
    novo->dataEmprestimo[0] = '\0';
    b->totalLivros++;
    //soma +1 no total 
    return 1;
    //retorna o livro cadastrado deu certo
}
void listarTodosLivros(Biblioteca *b)
{
    //itera sobre o vetor totallivros 
    for (int i = 0; i < b->totalLivros; i++)
    {
        //mostra cada dado do livro
        printf("%s - %s - %d - %s\n", b->livros[i].titulo, b->livros[i].autor,
            b->livros[i].ano, b->livros[i].isbn);
    }
}

int emprestarLivro(Biblioteca *b, char *isbn, char *usuario, char *data)
{
    for (int i = 0; i < b->totalLivros; i++)
    {
        if (strcmp(b->livros[i].isbn, isbn) == 0 && b->livros[i].status == DISPONIVEL)
        //strcmp compara duas strins, sendo b->livros[i].isbn nos livros e isbn o que estaamos procurando
        // se for igual retorna 0 diznedo q achou, e verificamos se está disponivel, se sim emprestamos no if
        {
            b->livros[i].status = EMPRESTADO;
            //mudar status para emprestado e passar o nome do usuario e data
            strcpy(b->livros[i].usuario, usuario);
            strcpy(b->livros[i].dataEmprestimo, data);
            return 1;
        }
    }
    return 0;
}
int devolverLivro(Biblioteca *b, char *isbn)
{
    for (int i = 0; i < b->totalLivros; i++)
    {
        //strcmp compara duas strins, sendo b->livros[i].isbn nos livros e isbn o que estaamos procurando
        // se for igual retorna 0 diznedo q achou, e verificamos se está emprestado, se sim devolve no if
        if (strcmp(b->livros[i].isbn, isbn) == 0 && b->livros[i].status == EMPRESTADO)
        {
            b->livros[i].status = DISPONIVEL;
            //coloca disponivel no livro e passa 0/nenhum para o resto dos campos
            b->livros[i].usuario[0] = '\0';
            b->livros[i].dataEmprestimo[0] = '\0';
            return 1;
        }
    }
    return 0;
}
Livro *consultarLivroPorISBN(Biblioteca *b, char *isbn)
{
    for (int i = 0; i < b->totalLivros; i++)
    {
        //aqui ele que ver se existe tal livro na lista, vai iterar na lista e vai iterar sobre os isbn comparando-os
        if (strcmp(b->livros[i].isbn, isbn) == 0)
        {
            //se livro for encontrado, imprimir os dados dele 
            printf("Livro encontrado: %s - %s - %d - %s\n",
                b->livros[i].titulo, b->livros[i].autor,
                b->livros[i].ano, b->livros[i].isbn);
                //para imprimir se está disponivel ou emprestado, verificar a disponibilidade 
            printf("Status: %s\n", b->livros[i].status == DISPONIVEL ? "Disponível" : "Emprestado");
            return &b->livros[i];
            //retorna o tal livro
        }
    }
    return NULL;
}