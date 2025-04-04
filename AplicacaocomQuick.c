#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define max 100

typedef struct{
    char nome[max];
    int numero;
    char email[max];
    char endereco[max];
} contato;

int cod = 0;
contato *contats[max];

void cadastro(contato *p){
    printf("\n================== Cadastrar contato ==================\n");
    printf("Nome: ");
    fgets(p->nome, max, stdin);
    setbuf(stdin, NULL);
    p->nome[strcspn(p->nome, "\n")] = 0;
    
    printf("Número: ");
    scanf("%d", &p->numero);
    setbuf(stdin, NULL);
    
    printf("Email: ");
    fgets(p->email, max, stdin);
    setbuf(stdin, NULL);
    p->email[strcspn(p->email, "\n")] = 0;

    printf("Endereço: ");
    fgets(p->endereco, max, stdin);
    setbuf(stdin, NULL);
    p->endereco[strcspn(p->endereco, "\n")] = 0;
    cod += 1;
    printf(">> Operação realizada com sucesso.\n");
}
void excluir(){
    if(cod > 0){
        int num = 0;
        printf("Digite o contato que deseja excluir: ");
        scanf("%d", &num);
        setbuf(stdin, NULL);
        num -= 1;
        for(int i = num; i < cod - 1; i++) {
            contats[i] = contats[i + 1];
        }
        contats[cod - 1] = NULL;
        cod -= 1;
        printf(">> Operação realizada com sucesso.\n");
    }else{
        printf("\n>> Lista de contatos vazia.\n");
    }
}
void quicksort(int low, int high){ // Método quicksort
    if (high > low) {
        contato *pivot = contats[high];
        int i = low - 1;
        for (int j = low; j < high; j++) { //O(N)
            if (strcmp(contats[j]->nome, pivot->nome) < 0) {
                i++;
                contato *temp = contats[i];
                contats[i] = contats[j];
                contats[j] = temp;
            }
        }
        contato *temp = contats[i + 1];
        contats[i + 1] = contats[high];
        contats[high] = temp;
        int pi = i + 1;
        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}
void exibir(){
    if(cod > 0){
        quicksort(0, cod - 1);
        printf("\n================== Lista de contatos ==================\n");
        printf("%-10s %-10s %-10s %-10s %-10s", "Código", "Nome", "Número", "Email", "Endereço");
        printf("\n-------------------------------------------------------\n");
        for(int x = 0; x < cod; x++){
            printf("%-10d %-10s %-10d %-10s %-10s\n", x+1, contats[x]->nome, contats[x]->numero, contats[x]->email, contats[x]->endereco);
        }
        printf("\n-------------------------------------------------------\n");
    }else{
        printf("\n>> Lista de contatos vazia.\n");
    }
}
int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8"); 
    int opcion = 0;
    int opc = 0;
    while(1){
        contats[cod] = (contato *)malloc(sizeof(contato));
        printf("\n================== Agenda telefônica ==================\n");
        printf("\n[1] Cadastrar \n[2] Excluir \n[3] Atualizar \n[4] Exibir \n[5] Sair\n");
        printf(">> O que deseja fazer? ");
        scanf("%d", &opcion);
        setbuf(stdin, NULL);

        switch (opcion){
        case 1:
            cadastro(contats[cod]);
            break;
        case 2:
            if(cod > 0){
                exibir();
            }
            excluir();
            break;
        case 3:
            if(cod > 0){
                printf("Qual item deseja atualizar? ");
                scanf("%d", &opc);
                setbuf(stdin, NULL);
                if(opc > 0 || opc <= cod){
                    opc--;
                    cadastro(contats[opc]);
                }else{
                    printf(">> Opção inválida, por favor tente novamente.\n");
                }
            }else{
                printf("\n>> Lista de contatos vazia.\n");
            }
            break;
        case 4:
            exibir();
            break;
        case 5:
            printf("\n>> Obrigado, volte sempre.\n");
            return 0;
        default:
            printf("\n>> Opção inválida, por favor tente novamente.\n");
            break;
        }
        free(contats[cod]);
    }
}
