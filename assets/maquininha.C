#include <stdlib.h>
#include <stdio.h>
int main();
typedef struct{
    char name[20];
    int code;
    float price;
}Products;
Products product[100];
Products cart[100];


void flist(int n){
    printf("------LISTA DE PRODUTOS------\n\n");
    int aux;
    for(int i=0;i<n;i++){
        printf("Nome: %s\nCódigo: %d\nPreço: R$%.2f\n\n", product[i].name, product[i].code, product[i].price);
    }
}
void faddtocart(int n){
    int x, j=0, aux, z=0;
        char aux2='S';
            printf("Insira o código do item que deseja comprar: ");
            scanf("%d", &x);
                for(int i=0;i<n;i++){
                    if(product[i].code == x){
                        printf("Produto selecionado:\nNome: %s\nCódigo: %d\nPreço: %.2f\n", product[i].name, product[i].code, product[i].price);
                        printf("Quantas unidades do produto? ");
                        scanf("%d", &z);
                        cart[i]=product[i];
                        if(z!=1){
                            cart[i].price = z*product[i].price;
                            printf("Preço das %d unidades: R$%.2f\n", z, cart[i].price);
                        }
                    }
                }   
                printf("\n");
}
int fbuy(int n);

int addtocartf(int n){
    char aux='S';
    while(aux=='S'){
        faddtocart(n);
        printf("Deseja adicionar mais itens ao carrinho? (S/N) ");
        fflush(stdin);
        scanf("%c", &aux);
        system("cls");
    }
    return fbuy(n);
}

void fccart(int n){
    char aux;
    float tvalue;
    int j=0;
        for(int i=0;i<n;i++){
            tvalue+=cart[i].price;
        }
        printf("Valor total do carrinho: R$%.2f\n\n", tvalue);
        for(int i=0;i<n;i++){
            if(cart[i].code!=0){
                printf("%d. Nome: %s\nCódigo: %d\nPreço: %.2f\n", j+1, cart[i].name, cart[i].code, cart[i].price);
                j++;
            }
        }

}

void removecart(int n){
    int aux;
    printf("Insira o código do produto que deseja remover: ");
    scanf("%d", &aux);
    for(int i=0;i<n;i++){
        if(aux==cart[i].code){
            printf("O produto %s foi removido do carrinho.\n", cart[i].name);
            cart[i].code=0;
            cart[i].price=0;
        }
    }
}

int removecartf(int n){
    char aux='S';
    while(aux=='S'){
        removecart(n);
        printf("Deseja remover mais itens do carrinho? (S/N) ");
        fflush(stdin);
        scanf("%c", &aux);
        system("cls");
    }
    return fbuy(n);
}

int ccartf(int n){
    char aux;
    system("cls");
    fccart(n);        
    printf("\nDeseja remover algum produto do carrinho? (S/N) ");
     fflush(stdin);
    scanf("%c", &aux);
    system("cls");
    if(aux=='S'){
        return removecartf(n);
    }else{
        return fbuy(n);
    }
}

int finishbuy(int n){
    int j=0;
    float tvalue=0;
    char aux;
    for(int i=0;i<n;i++){
        tvalue+=cart[i].price;
    }
    printf("Deseja finalizar a compra num total de: R$%.2f? (S/N) ", tvalue);
    fflush(stdin);
    scanf("%c", &aux);
    if(aux=='S'){
        printf("Compra concluída! Nota fiscal foi emitida.");
        FILE *nfe;
        nfe = fopen("nFe.txt", "w");
        fprintf(nfe, "Total: R$%.2f\n\n", tvalue);
        for(int i=0;i<n;i++){
            if(cart[i].code!=0){
                fprintf(nfe, "%d. Nome: %s\nCódigo: %d\nPreço: R$%.2f\n", j+1, product[i].name, product[i].code, product[i].price);
                j++;
            }
        }
        fclose(nfe);
    }else{
        return fbuy(n);
    }
}

int fbuy(int n){
    int aux;
    printf("------PÁGINA DE COMPRA------\n\n");
    printf("1. Adicionar itens ao carrinho;\n");
    printf("2. Consultar e alterar carrinho;\n");
    printf("3. Concluir compra;\n");
    printf("4. Cancelar compra.\n");
    printf("5. Voltar\n\n");
    printf("Insira a opção que deseja acessar: ");
    scanf("%d", &aux);
    if(aux==1){
        system("cls");
        addtocartf(n);
    }else if(aux==2){
        ccartf(n);
    }else if(aux==3){
        finishbuy(n);
    }else if(aux==4){
        system("cls");
        printf("Compra cancelada. Saindo do programa.\n\n");
        system("PAUSE");
        return 0;
    }else if(aux==5){
        return main();
    }
}

int listf(int n){
    flist(n);
    printf("\n");
    system("PAUSE");
    system("cls");
    return main();
}

int main(){
    system("cls");
    FILE* file = fopen("registered-products.dat", "r");
    char buffer[200];
    fgets(buffer, 200, file);
    int i=0;
    while(!feof(file)){
        Products* p = product + i;
        sscanf(buffer, "%s %d %f", &p->name, &p->code, &p->price);
        fgets(buffer, 200, file);
        i++;
    }
    int n = i;
    int slctr;
    printf("------PÁGINA INICIAL------\n\n");
    printf("1. Conferir produtos cadastrados;\n");
    printf("2. Comprar produto(s);\n");
    printf("3. Sair.\n\n");
    printf("Insira o número da opção que deseja acessar: ");
    fflush(stdin);
    scanf("%d", &slctr);
    if(slctr==1){
        system("cls");
        listf(n);
    }else if(slctr==2){
        system("cls");
        fbuy(n);
    }else if(slctr==3){
        system("cls");
    }
}