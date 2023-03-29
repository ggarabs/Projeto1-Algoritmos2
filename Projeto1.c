#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAXN 200
#define TAM 6621
#define WORDLEN 5

int main(){
    FILE *arc;
    const char input_adress[] = "palavras.txt";
    bool right_lenght = false;
    char drawn_word[MAXN];

    srand(time(NULL));

    while (!right_lenght) {
        int random_number = rand() % TAM + 1;

        arc = fopen(input_adress, "r");

        if(NULL == arc) {
            printf("Erro ao tentar abrir o arquivo.\n");
            return -1;
        }

        for (int i = 1; i <= random_number; i++) fscanf(arc, "%s", drawn_word);

        fclose(arc);

        if(strlen(drawn_word) == WORDLEN) right_lenght = true;
    }

    const int chances = 6;
    bool got_word = false;
    int n_attemps = 0;
    clock_t start, end;

    start = clock();

    for(int i = 1; i <= chances && !got_word; i++){

        printf("%dª Tentativa\n%s\n", i, drawn_word);

        char attemp[MAXN];
        n_attemps++;

        bool in_dic = false;

        do{
            printf("Digite uma palavra de cinco letras: ");
            scanf("%s", attemp);

            char line[MAXN];

            arc = fopen(input_adress, "r");

            if(NULL == arc) {
                printf("Erro ao tentar abrir o arquivo.\n");
                return -1;
            }

            for (int i = 1; i <= TAM; i++){
                fscanf(arc, "%s", line);
                if(strcmp(line, attemp) == 0 && strlen(attemp) == WORDLEN) in_dic = true;
            }

            if(!in_dic) printf("Palavra de tamanho inválido ou não encontrada na base de dados.\n");

            printf("\n");

        }while(!in_dic);

        if(strcmp(attemp, drawn_word) == 0){
            got_word = true;
        }

        printf("+-----------+\n| ");

        for(int j = 0; j < strlen(attemp); j++){
            printf("%c ", toupper(attemp[j]));
        }

        printf("|\n| ");

        bool parcial[] = {0, 0, 0, 0, 0};

        for(int j = 0; j < WORDLEN; j++){
            bool in_word = false;
            for(int k = 0; k < WORDLEN; k++){
                if(!parcial[k] && attemp[j] == drawn_word[k]){
                    in_word = true;
                    if(j == k){
                        printf("^ ");
                        parcial[k] = true;
                    }else{
                        printf("! ");
                    }
                    break;
                }
            }
            if(!in_word) printf("x ");
        }

        printf("|\n+-----------+\n");

        printf("\n");
    }

    end = clock();

    double play_time = ((double)start - (double)end)/CLOCKS_PER_SEC;

    FILE *output_arc;
    const char output_adress[] = "scores.txt";

    if(!got_word){
        printf("VOCÊ PERDEU! Mais sorte da próxima vez!\n");
        printf("A palavra sorteada foi: %s\n\n", drawn_word);
    }else{
        printf("PARABÉNS! Você venceu!\n");

        char player_name[MAXN];
        char std_space[] = "              ";

        printf("Digite seu nome: ");
        getchar();
        fgets(player_name, MAXN, stdin);

        int tam = strlen(player_name);
        player_name[tam-1] = '\0';

        output_arc = fopen(output_adress, "a");

        if(NULL == output_arc){
            printf("Erro ao tentar abrir o arquivo!");
            return -1;
        }

        fprintf(output_arc, "%s%s%s%s%d%s%d%s\n", player_name, std_space, drawn_word, std_space, n_attemps, std_space, play_time, std_space);

        fclose(output_arc);
        
    }

    return 0;

}