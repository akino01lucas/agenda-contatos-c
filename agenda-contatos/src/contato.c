#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contato.h"

Contato* ctt_cria(void){
    
    return NULL; // Criação do contato vazio, representado por NULL.
}

Contato* ctt_insere(char* nome, char* num, Contato* ag){
    
    Contato* ant = NULL; // ant guarda o contato anterior ao p, percorrido no loop.
    Contato* p = ag; // p é o ponteiro que percorre todos os contatos da agenda.
    Contato* novo; // Ponteiro para novo contato a ser inserido
    
    while(p != NULL && strcmp(nome, p -> nome) > 0){ // strcmp() vai comparar o nome recebido com o nome na agenda e colocar na posição correta.
        ant = p; // guarda o anterior a p no próximo estágio do loop;
        p = p -> prox; // iteração do contato percorrendo a lista. Sai do loop quando p -> prox == NULL;
    }
    
    novo = (Contato*) malloc(sizeof(Contato)); // Alocação dinâmica do novo contato a ser inserido.
    if(novo == NULL){
        printf("ERRO! Memória insuficiente para alocação");
        exit(1);
    }

    strcpy(novo -> nome, nome); // função para copiar o conteúdo do nome para o campo de nome da struct.
    strcpy(novo -> num, num);
    novo -> prox = ag;

    if (ant == NULL){ // neste caso, o loop não ocorreu, pois ant não recebeu p. Logo, o contato a ser adicionado está no início da agenda.
        novo -> prox = ag; // o proximo contato após o novo passa a ser o primeiro contato da agenda
        ag = novo;
    }
    else{ // contato inserido no meio ou fim da agenda
        novo -> prox = p;
        ant -> prox = novo;
    }

    return ag;
}

Contato* ctt_remove(Contato* ag, char* nome){

    Contato* ant = NULL;
    Contato* p = ag;

    while(p != NULL && strcmp(nome, p -> nome) != 0){
        ant = p;
        p = p -> prox;
    }

    if(p == NULL){ // se p == NULL, então percorreu até o final da lista, logo, o elemento não se encontra na agenda.
        printf("\nContato nao encontrado na agenda!\n");
        return ag;
    }
    else if(ant == NULL)
        ag = p -> prox;
        
    else
        ant -> prox = p -> prox;

    printf("\nContato removido!\n");

    free(p);

    return ag;
}

Contato* ctt_busca(Contato* ag, char* nome){
    
    Contato* p = ag;

    while(p != NULL && strcmp(nome, p -> nome) != 0){ // Percorre a agenda, buscando o contato fornecido por parâmetro (pelo nome).
        p = p -> prox;
    }

    if(p == NULL){
        printf("Contato nao encontrado na agenda!\n");
        return NULL; // Retorna vazio, caso não encontre o contato na agenda.
    }
    else    
        return p; // Retorna o contato encotrado, caso seja.
}

void agenda_mostra(Contato* ag){
    
    Contato* p;
    
    printf("\n");

    for(p = ag; p != NULL; p = p -> prox)
        printf("%s / %s\n", p -> nome, p -> num);
    
    if(ag == NULL) // Neste caso, não temos nenhum contato na lista encadeada.
        printf("Agenda vazia\n");

}

void agenda_libera(Contato* ag){
    Contato* post = NULL; // Ponteiro que será utilizado para guardar o próximo contato da agenda, posterior ao apontado por p.
    Contato* p = ag;

    while(p != NULL){
        post = p -> prox;
        free(p);
        p = post;
    }
}

char* le_nome(void){
    
    char* nome = malloc(21 * sizeof(char)); // Alocação dinâmica para a string, com tamanho máximo de 21 caracteres (20 + '\0').
    if(nome == NULL){
        printf("ERRO! Memroia insuficiente para alocacao.");
        exit(1);
    }
    
    int i;

    do{
    
    i = 0; // Variável i sempre zerando para retomar o loop corretamente.
    printf("Informe o nome(serao computados ate os primeiros 20 caracteres): ");
    fgets(nome, 21, stdin);

    if(nome[0] >='a' && nome[0] <='z') // conversão do primeiro caractere para maiúsculo, facilitando assim a ordenação ao inserir novo contato na agenda.
        nome[0] -= 32; 

    // Limpeza de buffer
    if(strchr(nome, '\n') == NULL){ // Caso não tenha lido o '\n', ou seja, tenha excedido o número limite de caracteres.
        int c;
        while((c = getchar()) != '\n' && c != EOF); // Itera o c, fazendo ele consumir cada caractere como getchar() até alcançar o '\n'.
    }
    
    nome[strcspn(nome, "\n")] = '\0'; // Remove o "\n" do buffer, substituindo por '\0'.
    
    while(nome[i] != '\0')
        i++; // Variável i será o tamanho da string lida e formatada devidamente.

    if(i == 0) // Caso não tenha sido digitado nenhum caractere.
        printf("ERRO! Nome invalido.\n");
    
    }while(i == 0); // Retorna para a obtenção do nome, caso se mantenha inválida a quantidade de caracteres.

    return nome;
}

char* le_numero(void){
   
    char* num = malloc(14 * sizeof(char)); // Alocação dinâmica para a string, com tamanho máximo de 14 caracteres (13 + '\0').
    if(num == NULL){
        printf("ERRO! Memoria insuficiente para alocaçao.");
        exit(1);
    }
    
    int i;

    do{

    i = 0;
    printf("Informe o numero de telefone(1 a 13 digitos): ");
    fgets(num, 14, stdin);

    if(strchr(num, '\n') == NULL){ 
        int c;
        while((c = getchar()) != '\n' && c != EOF); 
    }

    num[strcspn(num, "\n")] = '\0';
        
    while(num[i] != '\0')
       i++;

    if(i == 0)
        printf("ERRO! Numero invalido.\n");

    }while(i == 0);

    num = formata_num(num); // Altera a visualização do número de telefone para o formato xx xxxxx-xxxx

    return num;
}

char* formata_num(char* num){
    
    int i;
    int tam = 0;
    while(num[tam] != '\0') // Definindo o tamanho da string
        tam++;

    if(num[2] != ' '){ // Verificando se o espaço está na posicão correta
        for(i = tam; i >= tam - 9; i--) // Percorre a string deslocando cada caractere para uma posição a frente, até chegar na posição devida ao espaço
            num[i + 1] = num[i];
        num[2] = ' ';
    }

    tam++; // Tamanho aumenta em 1 por causa do caractere de espaço atribuido.

    if(num[8] != '-'){ // Repete o processo, agora para a posição adequada do '-'.
        for(i = tam; i >= tam - 4; i--)
            num[i + 1] = num[i];
        num[8] = '-';
    }

    return num;
}

void menu_principal(Contato* ag){
    printf("*******************\n");
    printf(" Agenda Telefonica\n");
    printf("*******************\n");
    
    int flag = 0; // Flag para saída do do while, dependendo da entrada do usuário.
    do{
        // Exibição do menu de opções com as funcionalidades do programa.
        printf("\n1- Ver agenda telefonica\n2- Adicionar contato\n3- Buscar contato\n4- Remover Contato\n5- Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &flag); // Flag utilizada no switch case para escolha da funcionalidade.
        getchar();

        // Declaração de ponteiros para os tipos a serem utilizados dentro do funcionamento do programa.
        char* nome;
        char* num;
        Contato* c;

        switch(flag){
            case 1: // Mostra todos os contatos da agenda.
                agenda_mostra(ag);
                break;
            case 2: // Adiciona um contato na agenda.
                nome = le_nome();
                num = le_numero();
                ag = ctt_insere(nome, num, ag);
                printf("\nContato adicionado!\n");
                free(nome);
                free(num);
                break;
            case 3: // Busca o contato de acordo com o nome.
                nome = le_nome();
                c = ctt_busca(ag, nome);
                if(c != NULL) 
                    printf("\nContato encontrado!\n%s / %s\n", c -> nome, c -> num);
                free(nome);
                break;
            case 4: // Remove o contato de acordo com o nome.
                nome = le_nome();
                ag = ctt_remove(ag, nome);
                free(nome);
                break;
            case 5: // Sai do programa.
                printf("Encerrando programa...\n");
        }
    }while(flag != 5);

}
