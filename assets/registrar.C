#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char name[10];
    int code;
    float price;
}Products;
Products product[100];
Products productaux;
int main();
int n;

void fregister(int x){
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
    fclose(file);
    x = i;
    int aux;
    printf("------CADASTRO DE PRODUTOS------\n\n");
    printf("Insira quantos produtos você deseja cadastrar: ");
    fflush(stdin);
    scanf("%d", &n);
    for(int i=x;i<n+x;i++){
        printf("Nome do %d° produto: ", i+1);
        scanf("%s", &product[i].name);
        printf("Código do %d° produto: ", i+1);
        scanf("%d", &product[i].code);
        for(int j=0;j<(n+x)-1;j++){
            while(product[i].code==product[j].code && i!=j){
                printf("Já existe um código com este produto! Insira outro código: ");
                scanf("%d", &product[i].code);
            }
        }
        printf("Preço do %d° produto: ", i+1);
        scanf("%f", &product[i].price);
        printf("O produto %s foi cadastrado!\n\n", product[i].name, product[i].code);
    }

    FILE *products_print;
    products_print = fopen("registered-products.dat", "w");
    for(int i=0;i<n+x;i++){
        fprintf(products_print, "%s %d %f\n", product[i].name, product[i].code, product[i].price);
    }
    fclose(products_print);
}

void fconsult(int x){
    char aux;
    int aux2;
    char aux3;
    printf("------CONSULTA DE PRODUTOS------\n\n");
    for(int i=0;i<x && product[i].name!=NULL;i++){
        printf("Nome: %s\n", product[i].name);
        printf("Código: %d\n", product[i].code);
        printf("Preço: R$%.2f\n\n", product[i].price);
    }
    printf("Deseja alterar o preço de algum produto? (S/N) ");
    fflush(stdin);
    scanf("%c", &aux);
    while(aux == 'S'){
        printf("Insira o código do produto que deseja alterar: ");
        scanf("%d", &aux2);
        for(int i=0;i<=n+x;i++){
            if(product[i].code == aux2){
                printf("Produto selecionado: %s\n", product[i].name);
                printf("Digite o novo preço do produto (preço atual: R$%.2f): ", product[i].price);
                scanf("%f", &product[i].price);
                printf("O novo preço de %s é: R$%.2f", product[i].name, product[i].price);
            }
        }
        printf("\n\nDeseja alterar o preço de outro produto? (S/N) ");
        fflush(stdin);
        scanf("%c", &aux);
    }
    FILE *products_print;
    products_print = fopen("registered-products.dat", "w");
    for(int i=0;i<x;i++){
        fprintf(products_print, "%s %d %f\n", product[i].name, product[i].code, product[i].price);
    }
    fclose(products_print);
} 

int registerf(int x){
    fregister(x);
    return main();
}

int consultf(int x){
    fconsult(x);
    return main();
}

int cleanf(){
    FILE *products_clean;
    products_clean = fopen("registered-products.dat", "w");
    fprintf(products_clean, "");
    fclose(products_clean);
    return main();
}

int main(){
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
    int x = i;
    char aux;
    int slctr;
    system("cls");
    printf("------PÁGINA INICIAL------\n\n");
    printf("1. Cadastrar novos produtos;\n");
    printf("2. Consultar produtos cadastrados e alterá-los;\n");
    printf("3. Limpar lista de produtos cadastrados;\n");
    printf("4. Sair.\n\n");

    printf("Insira o número da opção que deseja acessar: ");
    scanf("%d", &slctr);
    if(slctr==1){
        system("cls");
        registerf(x);
    }else if(slctr==2){
        system("cls");
        consultf(x);
    }else if(slctr==3){
        system("cls");
        cleanf();
    }else if(slctr==4){
        system("cls");
        printf("Tem certeza de que deseja sair? (S/N) ");
        fflush(stdin);
        scanf("%c", &aux);
        if(aux=='S' || aux=='s'){
            return 0;
        }else if(aux=='N' || aux=='n'){
            return main();
        }
    }
}