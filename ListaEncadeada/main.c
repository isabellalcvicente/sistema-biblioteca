#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca_encadeada.h"

void gerarISBN(int index, char* isbn) {
    sprintf(isbn, "%013d", 1000000000000 + index);
}

void cadastrarNLivros(Biblioteca* b, int quantidade) {
    char titulo[100], autor[100], isbn[14];
    for (int i = 0; i < quantidade; i++) {
        sprintf(titulo, "Livro %d", i + 1);
        sprintf(autor, "Autor %d", i + 1);
        gerarISBN(i, isbn);
        cadastrarLivro(b, titulo, autor, 2000 + (i % 24), isbn);
    }
}

void emprestarEDevolverAlguns(Biblioteca* b) {
    NoLivro* atual = b->primeiro;
    int i = 0;
    while (atual != NULL) {
        if (i % 10 == 0) emprestarLivro(b, atual->livro.isbn, "Usuário", "06/04/2025");
        if (i % 20 == 0) devolverLivro(b, atual->livro.isbn);
        atual = atual->proximo;
        i++;
    }
}

int main() {
    Biblioteca b;
    inicializarBiblioteca(&b);

    printf("==== Teste com 5 livros ====\n");
    cadastrarNLivros(&b, 5);
    listarTodosLivros(&b);
    destruirBiblioteca(&b);

    printf("\n==== Teste com 50 livros ====\n");
    inicializarBiblioteca(&b);
    cadastrarNLivros(&b, 50);
    emprestarEDevolverAlguns(&b);
    listarTodosLivros(&b);
    destruirBiblioteca(&b);

    printf("\n==== Teste com 500 livros ====\n");
    inicializarBiblioteca(&b);
    cadastrarNLivros(&b, 500);
    emprestarEDevolverAlguns(&b);
    printf("Total de livros: %d\n", b.totalLivros);
    destruirBiblioteca(&b);

    return 0;
}
