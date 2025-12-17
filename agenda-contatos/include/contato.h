#ifndef CONTATO_H
#define CONTATO_H

struct contato{ // Estrutura que tem uma string para o nome, uma string para o número de telefone e um ponteiro para o próximo contato da agenda.
    char nome[21];
    char num[14];
    struct contato* prox;
};
typedef struct contato Contato;

Contato* ctt_cria(void); //Cria um contato vazio, que representa o primeiro contato da lista.
Contato* ctt_insere(char* nome, char* num, Contato* ag); // Insere, ordenado por nome, um contato na agenda. Retorna o ponteiro para primeiro ctt da agenda.
Contato* ctt_remove(Contato* ag, char* nome); // Remove o contato de acordo com o nome recebido por parâmetro.
Contato* ctt_busca(Contato* ag, char* nome); // Busca o contato na agenda de acordo com o nome e retorna o ponteiro para o contato encotrado.
void agenda_mostra(Contato* ag); // Exibe os contatos da agenda na tela.
void agenda_libera(Contato* ag); // Libera toda a agenda que foi alocada na memória.
char* le_nome(void); // Faz a leitura do nome para aplicar no contato, seguindo as restrições necessárias para a quantidade de caracteres.
char* le_numero(void); // Faz a leitura do número de telefone para aplicar no contato, seguindo as restrições necessárias para a quantidade de caracteres.
void menu_principal(Contato* ag); // Mostra menu com funcionalidades do programa, chamando as funções necessárias para o seu funcionamento.
char* formata_num(char* num); // Formata o número de telefone para o formato: xx xxxxx-xxxx

#endif