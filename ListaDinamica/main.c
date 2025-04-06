#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca_dinamica.h"

void gerarISBN(int index, char* isbn) {
    sprintf(isbn, "%013d", 1000000000000 + index); // Gera um ISBN único
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
    for (int i = 0; i < b->totalLivros; i += 10) {
        char usuario[] = "AlunoTeste";
        char data[] = "06/04/2025";
        emprestarLivro(b, b->livros[i].isbn, usuario, data);
    }

    for (int i = 0; i < b->totalLivros; i += 20) {
        devolverLivro(b, b->livros[i].isbn);
    }
}

int main() {
    Biblioteca b;
    inicializarBiblioteca(&b);

    // Teste com 5 livros
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
