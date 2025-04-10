#include <stdio.h>
#include <string.h>
#include "biblioteca_estatica.h"

void gerarISBN(int index, char* isbn) {
    //gera um isbn aleatorio, passando um index e o ponteiro de onde sera armazenado 
    sprintf(isbn, "%013d", 1000000000000 + index);
    // sprintf escreve o resultado em uma variável, nesse caso o isbn 
    // sprintf(destino, "formato (13 digitos)", valor);
    // sprintf (isbn, "%013d", 1000000000000 + 2)  ex. entrada:2, saída 10000000000002; 
}

void cadastrarNLivros(Biblioteca* b, int quantidade) {
    char titulo[100], autor[100], isbn[14];
    for (int i = 0; i < quantidade; i++) {
        //criacao automatica mokada 
        sprintf(titulo, "Livro %d", i + 1);
        sprintf(autor, "Autor %d", i + 1);
        gerarISBN(i, isbn);
        //se nao der certo de cadastrar o livro 
        if (!cadastrarLivro(b, titulo, autor, 2000 + (i % 24), isbn)) {
            //gera esse erro e via pro proximo 
            printf("Erro ao cadastrar o livro %d\n", i + 1);
        }
    }
}

    //empresta e devolve ao memso tempo
void emprestarEDevolverAlguns(Biblioteca* b) {
    //a cada 10 livros empresta 1 
    for (int i = 0; i < b->totalLivros; i += 10) {
        emprestarLivro(b, b->livros[i].isbn, "Aluno", "06/04/2025");
    }
    // a cada 20 livros, devolve 1
    for (int i = 0; i < b->totalLivros; i += 20) {
        devolverLivro(b, b->livros[i].isbn);
    }
}

int main() {
    Biblioteca b;
    inicializarBiblioteca(&b);

    printf("==== Teste com 5 livros ====\n");
    cadastrarNLivros(&b, 5);
    listarTodosLivros(&b);

    printf("\n==== Teste com 50 livros ====\n");
    inicializarBiblioteca(&b);
    cadastrarNLivros(&b, 50);
    emprestarEDevolverAlguns(&b);
    listarTodosLivros(&b);

    printf("\n==== Teste com 500 livros ====\n");
    inicializarBiblioteca(&b);
    cadastrarNLivros(&b, 500);
    emprestarEDevolverAlguns(&b);
    printf("Total de livros cadastrados: %d\n", b.totalLivros);

    return 0;
}
