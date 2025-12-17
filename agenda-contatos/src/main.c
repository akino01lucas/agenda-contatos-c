#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contato.h"

int main(void){

    Contato* ag = ctt_cria(); // Criação do primeiro nó da lista encadeada, sendo o ponteiro para o primeiro contado da agenda.
    
    menu_principal(ag); 

    agenda_libera(ag); // Libera a memória alocada para a agenda.

    
    return 0;
}