#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

char* Arquivo_da_categoria(char categoria[30]){

    if(strcmp(categoria, "animais") == 0){
        return "animais.txt";
    }
    
    else if(strcmp(categoria, "comidas") == 0){
        return "comida.txt";
    }
    
    else if(strcmp(categoria, "cores") == 0){
        return "cores.txt";
    }
    
    else if(strcmp(categoria, "objetos") == 0){
        return "objetos.txt";
    }

    else if(strcmp(categoria, "paises") == 0){
        return "paises.txt";

    }

    else if(strcmp(categoria, "profissões") == 0 || strcmp(categoria, "profissoes") ==0){
        return "profissoes.txt";
    }

    else{
    return NULL;
    }    
}
 
char* Sorteio_palavra(const char* arquivo){
    FILE *f = fopen(arquivo, "r");

    if(!f){
        printf("Erro ao ler arquivo\n");
        return 0;
    }

    char linha[200][50];
    int total = 0;

    while(total < 200 && fgets(linha[total], 50, f) != NULL){
        linha[total][strcspn(linha[total], "\n")] = '\0';
        total++;
    }

    fclose(f);

    if(total == 0){
        return NULL;
    }

    int indice = rand() % total;
    char *palavra = malloc(strlen(linha[indice]) + 1);

    if(!palavra){
        printf("Erro\n");
        return NULL;
    }

    strcpy(palavra, linha[indice]);
    return palavra;
}

void Jogo_da_forca(const char *palavra){

    time_t inicio = time(NULL);

    int tamanho = strlen(palavra);
    char exibicao[tamanho + 1];

    char palavraLower[tamanho + 1];
    for(int i = 0; i < tamanho; i++){
        palavraLower[i] = tolower(palavra[i]);
    }
    palavraLower[tamanho] = '\0';

    for(int i = 0; i < tamanho; i++){
        exibicao[i] = '_';
    }
    exibicao[tamanho] = '\0';

    int erros = 0;
    int acertos = 0;
    int tentativas = 6;

    char usadas[50];
    int total_usadas = 0;

    while(erros < tentativas && acertos < tamanho){
        system("cls");

        printf(" %s\n", exibicao);
        printf(" Erros: %d/%d \n", erros, tentativas);

        printf(" Letras usadas: ");
        for(int i = 0; i < total_usadas; i++){
            printf("%c ", usadas[i]);
        }
        printf("\n");

        char entrada[50];
        printf("Digite uma letra ou tente adivinhar a palavra: ");
        scanf(" %49s", entrada);

        for(int i = 0; entrada[i]; i++){
            entrada[i] = tolower(entrada[i]);
        }

        if(strlen(entrada) > 1){
            if(strcmp(entrada, palavraLower) == 0){
                time_t fim = time(NULL);
                double tempo = difftime(fim, inicio);

                printf("\nParabéns! Você acertou a palavra inteira!\n");
                
                printf("A palavra era: ");
                for(int i = 0; i < tamanho; i++){
                    printf("%c ", toupper(palavra[i]));
                }

                printf("\nTempo total: %.0f segundos.\n", tempo);
                return;
            }
            else{
                erros++;
                continue;
            }
        }

        char letra = entrada[0];

        int repetida = 0;
        for(int i = 0; i < total_usadas; i++){
            if(usadas[i] == letra){
                repetida = 1;
                break;
            }
        }

        if(repetida){
            continue;
        }

        usadas[total_usadas] = letra;
        total_usadas++;

        printf("Posições encontradas: ");

        int encontrou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (palavraLower[i] == letra && exibicao[i] == '_') {
                exibicao[i] = palavra[i];
                acertos++;
                encontrou = 1;
                printf("%d ", i + 1);
            }
        }

        if (!encontrou) {
            printf("Nenhuma");
            erros++;
        }

        printf("\n");
    }

    time_t fim = time(NULL);
    double tempo = difftime(fim, inicio);
        
    if (acertos == tamanho) {
        printf("\nParabéns! Você ganhou!\n");
    }

    else {
        printf("\nVocê perdeu!\n");
    }

    printf("A palavra era: ");
    for(int i = 0; i < tamanho; i++){
        printf("%c ", toupper(palavra[i]));
    }

    printf("\nTotal de erros cometidos: %d\n", erros);
    printf("Tempo total: %.0f segundos.\n", tempo);
}

int main(){

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    srand(time(NULL));
    char categoria[30];

    printf("\n JOGO DA FORCA \n");
    printf("Escolha qual categoria vc deseja jogar, sendo elas:\n");
    printf("Animais\n");
    printf("Comidas\n");
    printf("Cores\n");
    printf("Objetos\n");
    printf("Paises\n");
    printf("Profissões\n");

    printf("\nInsira a categoria para começar a jogar: ");
    fflush(stdout);

    fgets(categoria, 30, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    for(int i=0; categoria[i]; i++){
        categoria[i] = tolower(categoria[i]);
    }

    char *arquivo = Arquivo_da_categoria(categoria);

    if(arquivo == NULL){
        printf("Categoria invalida");
        return 0;
    }

    char *palavra = Sorteio_palavra(arquivo);

    if (palavra) {
        printf("\nPalavra sorteada com sucesso\n");
        Sleep(1000);
    } else {
        printf("Nao foi possivel sortear palavra.\n");
    }

    Jogo_da_forca(palavra);
    free(palavra);
    return 0;
}