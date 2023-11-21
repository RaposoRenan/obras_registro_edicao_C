#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "obras.h"

const char *areas[] = { "A", "B", "C", "D" };

void imprimirCabecalho(){
    puts("***********************************************************************");
    puts("*                                                                     *");
    puts("*                      MUSEU MULTITEM�TICO                            *");
    puts("*                                                                     *");
    puts("*                                                          ADS - UNIP *");
    puts("***********************************************************************");
}

void limparBuffer(){
    fflush(stdin);
}

void limparTela(){
    char ent;
    puts("\nPressione ENTER para continuar...");
    limparBuffer();
    getchar();
    system("cls");
}

void lerArquivo(struct Obra *obras, int *contador) {
    FILE *arquivo = fopen("registro_obras.csv", "r");
    if (arquivo == NULL) {
        // O arquivo n�o existe, n�o h� obras para ler.
        return;
    }

    while (*contador < MAX_OBRAS) {
        char area[2];
        char titulo[MAX_TITULO];
        char descricao[MAX_DESCRICAO];

        if (fscanf(arquivo, "�rea: %1s\n", area) != 1 ||
            fscanf(arquivo, "T�tulo: %99[^\n]\n", titulo) != 1 ||
            fscanf(arquivo, "Descri��o: %499[^\n]\n", descricao) != 1) {
            break;
        }

        struct Obra novaObra;
        novaObra.area = area[0] - 'A';
        strcpy(novaObra.titulo, titulo);
        strcpy(novaObra.descricao, descricao);

        obras[(*contador)++] = novaObra;
    }

    fclose(arquivo);
}

void salvarNoArquivo(const struct Obra *obra) {
    FILE *arquivo = fopen("registro_obras.csv", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de registro.\n");
        return;
    }

    fprintf(arquivo, "�rea: %s\n", areas[obra->area]);
    fprintf(arquivo, "T�tulo: %s\n", obra->titulo);
    fprintf(arquivo, "Descri��o: %s\n", obra->descricao);
    fprintf(arquivo, "\n");

    fclose(arquivo);
}

void atualizarArquivo(const struct Obra *obras, int contador) {
    FILE *arquivo = fopen("registro_obras.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de registro.\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        fprintf(arquivo, "�rea: %s\n", areas[obras[i].area]);
        fprintf(arquivo, "T�tulo: %s\n", obras[i].titulo);
        fprintf(arquivo, "Descri��o: %s\n", obras[i].descricao);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void adicionarObra(struct Obra *obras, int *contador) {
    if (*contador < MAX_OBRAS) {
        struct Obra novaObra;

        printf("Digite o t�tulo da obra: ");
        scanf(" %99[^\n]", novaObra.titulo);

        printf("Digite a descri��o da obra: ");
        scanf(" %499[^\n]", novaObra.descricao);

        while (1) {
            printf("Escolha uma �rea: \nA - 100 anos da semana de arte moderna\nB - 150 anos de Santos Dumont\nC - Jogos ol�mpicos de Paris 2024\nD - O legado de Pel�\n");
            char area[2];
            scanf(" %1s", area);
            area[0] = toupper(area[0]);

            if (area[0] >= 'A' && area[0] <= 'D') {
                novaObra.area = area[0] - 'A';
                break;
            } else {
                printf("�rea inv�lida. Tente novamente.\n");
            }
        }

        salvarNoArquivo(&novaObra);
        obras[(*contador)++] = novaObra;
        printf("Obra adicionada � �rea %s com sucesso!\n", areas[novaObra.area]);
    } else {
        printf("O limite de obras foi atingido.\n");
    }
}

void exibirTodasObras(const struct Obra *obras, int contador) {
    printf("\nTodas as obras registradas:\n");
    if (contador == 0) {
        printf("SEM OBRA REGISTRADA\n");
    } else {
        for (int i = 0; i < contador; i++) {
            printf("\nObra %d:\n", i + 1);
            printf("T�tulo: %s\n", obras[i].titulo);
            printf("Descri��o: %s\n", obras[i].descricao);
            printf("�rea: %s\n", areas[obras[i].area]);
        }
    }
}

int excluirObra(struct Obra *obras, int *contador) {
    if (*contador == 0) {
        printf("SEM OBRA REGISTRADA para excluir.\n");
        return 0;
    }

    exibirTodasObras(obras, *contador);

    while (1) {
        printf("Escolha o n�mero da obra a ser exclu�da (1 a %d), ou digite 0 para cancelar: ", *contador);
        int numObra;
        scanf("%d", &numObra);

        if (numObra == 0) {
            return 0; // Cancelar a exclus�o
        }

        if (numObra >= 1 && numObra <= *contador) {
            for (int i = numObra - 1; i < *contador - 1; i++) {
                obras[i] = obras[i + 1];
            }
            (*contador)--;
            atualizarArquivo(obras, *contador);
            return 1; // Exclus�o bem-sucedida
        } else {
            printf("N�mero de obra inv�lido. Tente novamente.\n");
        }
    }
}

int editarObra(struct Obra *obras, int contador) {
    if (contador == 0) {
        printf("SEM OBRA REGISTRADA para editar.\n");
        return 0;
    }

    exibirTodasObras(obras, contador);

    while (1) {
        printf("Escolha o n�mero da obra a ser editada (1 a %d), ou digite 0 para cancelar: ", contador);
        int numObra;
        scanf("%d", &numObra);

        if (numObra == 0) {
            return 0; // Cancelar a edi��o
        }

        if (numObra >= 1 && numObra <= contador) {
            printf("Escolha o que deseja editar:\n");
            printf("1. T�tulo\n");
            printf("2. Descri��o\n");
            printf("0. Cancelar\n");
            int escolha;
            scanf("%d", &escolha);

            if (escolha == 0) {
                return 0; // Cancelar a edi��o
            }

            if (escolha == 1) {
                // Editar t�tulo
                printf("T�tulo atual: %s\n", obras[numObra - 1].titulo);
                printf("Digite o novo t�tulo: ");
                scanf(" %99[^\n]", obras[numObra - 1].titulo);
            } else if (escolha == 2) {
                // Editar descri��o
                printf("Descri��o atual: %s\n", obras[numObra - 1].descricao);
                printf("Digite a nova descri��o: ");
                scanf(" %499[^\n]", obras[numObra - 1].descricao);
            } else {
                printf("Op��o inv�lida. Tente novamente.\n");
            }

            atualizarArquivo(obras, contador);
            return 1; // Edi��o bem-sucedida
        } else {
            printf("N�mero de obra inv�lido. Tente novamente.\n");
        }
    }
}

// Fun��o para escolher uma das �reas
char escolherArea() {
    char escolha;
    printf("\nEscolha uma das �reas (A, B, C, D): ");
    limparBuffer();
    scanf("%c", &escolha);
    return toupper(escolha);
}

// Fun��o para exibir as obras de uma �rea e selecionar uma das obras
int escolherObraPorArea(const struct Obra *obras, int contador, char areaEscolhida) {
    printf("\nObras na �rea '%c':\n", areaEscolhida);
    int obraEncontrada = 0;

    for (int i = 0; i < contador; i++) {
        if (obras[i].area == (areaEscolhida - 'A')) {
            obraEncontrada = 1;
            printf("%d. %s\n", i + 1, obras[i].titulo);
        }
    }

    if (obraEncontrada) {
        int escolha;
        do {
            printf("Escolha uma obra (1-%d): ", contador);
            scanf("%d", &escolha);
        } while (escolha < 1 || escolha > contador);
        return escolha - 1; // Subtrai 1 para obter o �ndice da obra escolhida
    } else {
        printf("N�o h� obras na �rea '%c'.\n", areaEscolhida);
        return -1; // Retorna -1 para indicar que n�o h� obras na �rea
    }
}

// Fun��o para imprimir o t�tulo da obra e sua descri��o
void imprimirTituloDescricao(const struct Obra *obras, int indiceObra) {
    if (indiceObra != -1) {
        printf("\nT�tulo da obra: %s\n", obras[indiceObra].titulo);
        printf("Descri��o da obra: %s\n", obras[indiceObra].descricao);
    } else {
        printf("\nNenhuma obra encontrada na �rea selecionada.\n");
    }
}
