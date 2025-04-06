#include <stdio.h>
#include "biblioteca_estatica.h"
int main()
{
    Biblioteca b;
    inicializarBiblioteca(&b);
    cadastrarLivro(&b, "O Senhor dos Anéis", "J.R.R. Tolkien", 1954, "1234567890123");
    cadastrarLivro(&b, "1984", "George Orwell", 1949, "9876543210987");
    cadastrarLivro(&b, "A Revolução dos Bichos", "George Orwell", 1945, "1234567890124");
    cadastrarLivro(&b, "Dom Casmurro", "Machado de Assis", 1899, "1234567890125");
    listarTodosLivros(&b);
    consultarLivroPorISBN(&b, "1234567890123");
    emprestarLivro(&b, "1234567890123", "João", "2023-10-01");
    consultarLivroPorISBN(&b, "1234567890123");
    devolverLivro(&b, "1234567890123");
    consultarLivroPorISBN(&b, "1234567890123");
    return 0;
}