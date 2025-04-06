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
    if (!novo) return 0;

    strcpy(novo->livro.titulo, titulo);
    strcpy(novo->livro.autor, autor);
    novo->livro.ano = ano;
    strcpy(novo->livro.isbn, isbn);
    novo->livro.status = DISPONIVEL;
    novo->livro.usuario[0] = '\0';
    novo->livro.dataEmprestimo[0] = '\0';

    // Inserir no início
    novo->proximo = b->primeiro;
    b->primeiro = novo;
    b->totalLivros++;

    return 1;
}

void listarTodosLivros(Biblioteca* b) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        Livro* l = &atual->livro;
        printf("%s - %s - %d - %s [%s]\n", 
            l->titulo, l->autor, l->ano, l->isbn,
            l->status == DISPONIVEL ? "Disponível" : "Emprestado");
        atual = atual->proximo;
    }
}

int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {
    NoLivro* atual = b->primeiro;
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
    while (atual != NULL) {
        NoLivro* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    b->primeiro = NULL;
    b->totalLivros = 0;
}
