#include <stdio.h>
#define MAXN 200

int main(){
    char nome[MAXN];

    fgets(nome, MAXN, stdin);

    printf("%s", nome);

    return 0;

}