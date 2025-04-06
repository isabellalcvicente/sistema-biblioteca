#include "biblioteca_dinamica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INICIAL 10

void inicializarBiblioteca(Biblioteca *b)
{
    b->livros = (Livro *)malloc(INICIAL * sizeof(Livro));
    b->capacidade = INICIAL;
    b->totalLivros = 0;
}

// Esta função realoca o vetor de livros com nova capacidade
void redimensionarBiblioteca(Biblioteca* b, int novaCapacidade) {
    Livro* temp = realloc(b->livros, novaCapacidade * sizeof(Livro));
    if (temp != NULL) {
        b->livros = temp;
        b->capacidade = novaCapacidade;
    } else {
        printf("Erro ao realocar memória!\n");
        exit(1);
    }
}


// Cadastrar livro (com verificação de ISBN e redimensionamento automático)
int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {
    // Verifica se ISBN já existe
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0) {
            return 0; // ISBN duplicado
        }
    }

    // Redimensionar se necessário
    if (b->totalLivros >= b->capacidade) {
        redimensionarBiblioteca(b, b->capacidade * 2);
    }

    Livro* novo = &b->livros[b->totalLivros];
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    novo->ano = ano;
    strcpy(novo->isbn, isbn);
    novo->status = DISPONIVEL;
    novo->usuario[0] = '\0';
    novo->dataEmprestimo[0] = '\0';

    b->totalLivros++;
    return 1;
}


// Listar todos os livros
void listarTodosLivros(Biblioteca* b) {
    for (int i = 0; i < b->totalLivros; i++) {
        printf("%s - %s - %d - %s [%s]\n", 
            b->livros[i].titulo, 
            b->livros[i].autor, 
            b->livros[i].ano, 
            b->livros[i].isbn,
            b->livros[i].status == DISPONIVEL ? "Disponível" : "Emprestado"
        );
    }
}


// Emprestar livro
int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0 && b->livros[i].status == DISPONIVEL) {
            b->livros[i].status = EMPRESTADO;
            strcpy(b->livros[i].usuario, usuario);
            strcpy(b->livros[i].dataEmprestimo, data);
            return 1;
        }
    }
    return 0;
}


// Devolver livro
int devolverLivro(Biblioteca* b, char* isbn) {
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0 && b->livros[i].status == EMPRESTADO) {
            b->livros[i].status = DISPONIVEL;
            b->livros[i].usuario[0] = '\0';
            b->livros[i].dataEmprestimo[0] = '\0';
            return 1;
        }
    }
    return 0;
}


// Buscar livro pelo ISBN
Livro* consultarLivroPorISBN(Biblioteca* b, char* isbn) {
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0) {
            return &b->livros[i];
        }
    }
    return NULL;
}


// Liberar memória
void destruirBiblioteca(Biblioteca *b)
{
    free(b->livros);
    b->livros = NULL;
    b->capacidade = 0;
    b->totalLivros = 0;
}