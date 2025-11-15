#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menuEscolherTema(char *nomeArquivo){
    int escolhaAtual = 0;
    while (escolhaAtual < 1 || escolhaAtual > 7) { 
        printf("\n--- JOGO DA FORCA ---\n");
        printf("Escolha uma categoria:\n");
        printf("1. Animal\n");
        printf("2. Comida\n");
        printf("3. Cor\n");
        printf("4. Objetos\n");
        printf("5. Profissoes\n");
        printf("6. Paises\n");
        printf("7. Sair do Jogo\n");
        printf("Sua escolha: ");

        if (scanf("%d", &escolhaAtual) != 1) {
            escolhaAtual = 0; 
        }

        switch (escolhaAtual) {
            case 1: strcpy(nomeArquivo, "animais.txt"); return 1;
            case 2: strcpy(nomeArquivo, "comida.txt"); return 1;
            case 3: strcpy(nomeArquivo, "cor.txt"); return 1;
            case 4: strcpy(nomeArquivo, "objetos.txt"); return 1;
            case 5: strcpy(nomeArquivo, "profissoes.txt"); return 1;
            case 6: strcpy(nomeArquivo, "paises.txt"); return 1;
            case 7: return 0; // Sair
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    }
    return 0;
}

int main(){

    char nomeArquivoTema[30];
    
    if (menuEscolherTema(nomeArquivoTema) == 0) {
        printf("Saindo do jogo...\n");
        return 0;
    }

    printf("Helo World\n");
    printf("Teste\n");
    for(int i = 0; i < 2; i++){
        printf("Teste aprovado!\n");
    }

    return 0;
}