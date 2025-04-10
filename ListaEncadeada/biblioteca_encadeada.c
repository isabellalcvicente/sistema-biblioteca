#include "biblioteca_encadeada.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void inicializarBiblioteca(Biblioteca *b)
{
    b->primeiro = NULL;
    b->totalLivros = 0;
}
int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {
    // Verificar se ISBN já existe
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->livro.isbn, isbn) == 0) return 0;
        atual = atual->proximo;
    }

    // Criar novo nó
    NoLivro* novo = (NoLivro*) malloc(sizeof(NoLivro));
    // malloc aloca a memoria do tamanho de um no, o retorno tem que ser um ponteiro(nolivro*)o end de memoria
    if (!novo) return 0;
    //se nao for novo, retorna errado
    strcpy(novo->livro.titulo, titulo);
    // a regiao de memoraia apontada por novo desse campo vai receber x
    strcpy(novo->livro.autor, autor);
    novo->livro.ano = ano;
    strcpy(novo->livro.isbn, isbn);
    novo->livro.status = DISPONIVEL;
    novo->livro.usuario[0] = '\0';
    novo->livro.dataEmprestimo[0] = '\0';

    // Inserir no início
    novo->proximo = b->primeiro;
    //o o proximo aponta par ao proximo da lista e recebe o primeiro/novo
    b->primeiro = novo;
    b->totalLivros++;

    return 1;
}

void listarTodosLivros(Biblioteca* b) {
    //imprime lista 
    NoLivro* atual = b->primeiro;
    // do atual até o primeiro da lista
    while (atual != NULL) {
        //se essa lista noa for vazia, vai ter uma regiao de memoria 
        Livro* l = &atual->livro;
        //cria um ponteiro 1 que aponta para o livro do nó (posicao) atual
        printf("%s - %s - %d - %s [%s]\n", 
            l->titulo, l->autor, l->ano, l->isbn,
            l->status == DISPONIVEL ? "Disponível" : "Emprestado");
        atual = atual->proximo;
        //vai para o proximo nó
    }
}

int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {
    NoLivro* atual = b->primeiro;
    //o ponteiro atual recebe primeiro da lista
    while (atual != NULL) {
        if (strcmp(atual->livro.isbn, isbn) == 0 && atual->livro.status == DISPONIVEL) {
            atual->livro.status = EMPRESTADO;
            strcpy(atual->livro.usuario, usuario);
            strcpy(atual->livro.dataEmprestimo, data);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

int devolverLivro(Biblioteca* b, char* isbn) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->livro.isbn, isbn) == 0 && atual->livro.status == EMPRESTADO) {
            atual->livro.status = DISPONIVEL;
            atual->livro.usuario[0] = '\0';
            atual->livro.dataEmprestimo[0] = '\0';
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

NoLivro* consultarLivroPorISBN(Biblioteca* b, char* isbn) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->livro.isbn, isbn) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void destruirBiblioteca(Biblioteca* b) {
    NoLivro* atual = b->primeiro;
    //Cria um ponteiro atual e o inicializa com o primeiro nó da lista 
    while (atual != NULL) {
        //enquanto nao estiver vazia, tem livro
        NoLivro* temp = atual;
        //cria o ponteiro temp para o mesmo nó que o atual,
        //para ter uma reserva do reserva antes de apagar o nó e perder a poscicao/ garçom e o conteudo 
        atual = atual->proximo;
        // avança para o próximo nó da lista antes de liberar o atual,
        // pq se nao perde o acesso ao resto da lista dps do free
        free(temp);
    }
    b->primeiro = NULL;
    b->totalLivros = 0;
}


//usamos ponteiros pq quando o a funcao rodar a info seja guardada o ponteiro é global
//se usarmos a var a info vai sumir com qq alteração pq é uma var local 