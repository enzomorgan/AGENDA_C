#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 32

struct contato
{
    char *nome;
    char *telefone;
    char *email;
};

//criando contatos
struct contato *criar_contato(){
    struct contato *novo = (struct contato *)malloc(sizeof(struct contato));
    novo->nome = (char *)malloc(sizeof(char));
    novo->telefone = (char *)malloc(sizeof(char));
    novo->email = (char *)malloc(sizeof(char));

    printf("Digite o do nome contato: ");
    scanf("%s", novo->nome);
    printf("Digite o do telefone contato: ");
    scanf("%s", novo->telefone);
    printf("Digite o do email contato: ");
    scanf("%s", novo->email);


    return novo;
}

//funcao hash
double funcHashMult(int key){
    return (key * 0.2) / size;
}

//funcao de sondagem direta
int concatenacao(char c[]){
    int key = 0, i = 0;
    while(c[i] != '\0'){
        key += c[i];
        i++; 
    } 
    return key % size;
}
//agenda
typedef struct contato *agenda_ctt[size];

//funcao para inserir na tabela hash
int inserir(agenda_ctt Hash, struct contato *c){
    int key = concatenacao(c->nome);
    key = funcHashMult(key);
    int key_inicio = key;


    while(1){
        if(Hash[key] == 0){
            Hash[key] = c;
            break;
        }
        key++;

        if(key_inicio == key){
            break;
        }

        if(key > size){
            key = key%size;
            key_inicio = key;
        }
    }
}

// nao conseguimos fazer a funcao pra exportar :(

//funcao para buscar na tabela hash
struct contato *buscarContato (agenda_ctt Hash, struct contato *c){
    size_t key = concatenacao(c->nome);
    key = funcHashMult(key);
    struct contato *novo = NULL;
    int m = 0;
    do{
        
        if (strcmp(Hash[key]->nome, c->nome) == 0 && strcmp(Hash[key]->telefone, c->telefone) == 0 && strcmp(Hash[key]->email, c->email) == 0){
        novo = Hash[key];
        break;
            }
        
        key++;

        if(key > size){
            key = key%size;
            m++;
            if (m>=2){
                break;
            }
            
        }

    }while(1);
    return novo;
}

//funcao para listar
void listarContatos(agenda_ctt Hash){
    int i ;
    for(i = 0 ; i < size; i++){
        if (Hash[i] != NULL){
        printf("\n Nome: %s \n Telefone: %s \n Email: %s\n", Hash[i]->nome , Hash[i]->telefone, Hash[i]->email);        
        }
}
}


//funcao para remover da tabela
void removerContato(agenda_ctt Hash, struct contato *c){
    struct contato *novo = buscarContato(Hash, c);
     if (novo != NULL) {
        
        size_t key = concatenacao(c->nome);
        key = funcHashMult(key);

        while (Hash[key] != novo) {
            key++;
            if (key >= size) {
                key = key % size;
            }
        }
        free(Hash[key]);
        Hash[key] = NULL;
    }

}

int main(){
    struct contato *novo = (struct contato*)malloc(sizeof(struct contato));
    struct contato *busca = (struct contato*)malloc(sizeof(struct contato));
    agenda_ctt agenda;
    int i;
    for (i = 0; i < size; i++) {
        agenda[i] = NULL; // Inicialize todos os elementos da agenda como NULL
    }

    int op = 0;
    while (op != 5){
        printf(" 1-Criar contato\n2-Buscar contato\n3-Excluir contato\n4-listar\n5-Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case (1):
            novo = criar_contato();
            inserir(agenda, novo);
            break;
        case (2) :
            busca = criar_contato();
            novo = buscarContato(agenda, busca);
            if (novo !=NULL){
            printf("\n Nome: %s \n Telefone: %s \n Email: %s\n", novo->nome , novo->telefone, novo->email);
            }
           
            break;
        case (3) :
            novo = criar_contato();
            removerContato(agenda,novo);
            break;
        case (4) :
            listarContatos(agenda);
        default:
            break;
        }
        
    }
    
}