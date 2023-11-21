#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "obras.h"

const char *areas[] = { "A", "B", "C", "D" };

void imprimirCabecalho(){
    puts("***********************************************************************");
    puts("*                                                                     *");
    puts("*                      MUSEU MULTITEMÁTICO                            *");
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
        // O arquivo não existe, não há obras para ler.
        return;
    }

    while (*contador < MAX_OBRAS) {
        char area[2];
        char titulo[MAX_TITULO];
        char descricao[MAX_DESCRICAO];

        if (fscanf(arquivo, "Área: %1s\n", area) != 1 ||
            fscanf(arquivo, "Título: %99[^\n]\n", titulo) != 1 ||
            fscanf(arquivo, "Descrição: %499[^\n]\n", descricao) != 1) {
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

    fprintf(arquivo, "Área: %s\n", areas[obra->area]);
    fprintf(arquivo, "Título: %s\n", obra->titulo);
    fprintf(arquivo, "Descrição: %s\n", obra->descricao);
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
        fprintf(arquivo, "Área: %s\n", areas[obras[i].area]);
        fprintf(arquivo, "Título: %s\n", obras[i].titulo);
        fprintf(arquivo, "Descrição: %s\n", obras[i].descricao);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void adicionarObra(struct Obra *obras, int *contador) {
    if (*contador < MAX_OBRAS) {
        struct Obra novaObra;

        printf("Digite o título da obra: ");
        scanf(" %99[^\n]", novaObra.titulo);

        printf("Digite a descrição da obra: ");
        scanf(" %499[^\n]", novaObra.descricao);

        while (1) {
            printf("Escolha uma área: \nA - 100 anos da semana de arte moderna\nB - 150 anos de Santos Dumont\nC - Jogos olímpicos de Paris 2024\nD - O legado de Pelé\n");
            char area[2];
            scanf(" %1s", area);
            area[0] = toupper(area[0]);

            if (area[0] >= 'A' && area[0] <= 'D') {
                novaObra.area = area[0] - 'A';
                break;
            } else {
                printf("Área inválida. Tente novamente.\n");
            }
        }

        salvarNoArquivo(&novaObra);
        obras[(*contador)++] = novaObra;
        printf("Obra adicionada à área %s com sucesso!\n", areas[novaObra.area]);
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
            printf("Título: %s\n", obras[i].titulo);
            printf("Descrição: %s\n", obras[i].descricao);
            printf("Área: %s\n", areas[obras[i].area]);
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
        printf("Escolha o número da obra a ser excluída (1 a %d), ou digite 0 para cancelar: ", *contador);
        int numObra;
        scanf("%d", &numObra);

        if (numObra == 0) {
            return 0; // Cancelar a exclusão
        }

        if (numObra >= 1 && numObra <= *contador) {
            for (int i = numObra - 1; i < *contador - 1; i++) {
                obras[i] = obras[i + 1];
            }
            (*contador)--;
            atualizarArquivo(obras, *contador);
            return 1; // Exclusão bem-sucedida
        } else {
            printf("Número de obra inválido. Tente novamente.\n");
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
        printf("Escolha o número da obra a ser editada (1 a %d), ou digite 0 para cancelar: ", contador);
        int numObra;
        scanf("%d", &numObra);

        if (numObra == 0) {
            return 0; // Cancelar a edição
        }

        if (numObra >= 1 && numObra <= contador) {
            printf("Escolha o que deseja editar:\n");
            printf("1. Título\n");
            printf("2. Descrição\n");
            printf("0. Cancelar\n");
            int escolha;
            scanf("%d", &escolha);

            if (escolha == 0) {
                return 0; // Cancelar a edição
            }

            if (escolha == 1) {
                // Editar título
                printf("Título atual: %s\n", obras[numObra - 1].titulo);
                printf("Digite o novo título: ");
                scanf(" %99[^\n]", obras[numObra - 1].titulo);
            } else if (escolha == 2) {
                // Editar descrição
                printf("Descrição atual: %s\n", obras[numObra - 1].descricao);
                printf("Digite a nova descrição: ");
                scanf(" %499[^\n]", obras[numObra - 1].descricao);
            } else {
                printf("Opção inválida. Tente novamente.\n");
            }

            atualizarArquivo(obras, contador);
            return 1; // Edição bem-sucedida
        } else {
            printf("Número de obra inválido. Tente novamente.\n");
        }
    }
}

// Função para escolher uma das áreas
char escolherArea() {
    char escolha;
    printf("\nEscolha uma das áreas (A, B, C, D): ");
    limparBuffer();
    scanf("%c", &escolha);
    return toupper(escolha);
}

// Função para exibir as obras de uma área e selecionar uma das obras
int escolherObraPorArea(const struct Obra *obras, int contador, char areaEscolhida) {
    printf("\nObras na área '%c':\n", areaEscolhida);
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
        return escolha - 1; // Subtrai 1 para obter o índice da obra escolhida
    } else {
        printf("Não há obras na área '%c'.\n", areaEscolhida);
        return -1; // Retorna -1 para indicar que não há obras na área
    }
}

// Função para imprimir o título da obra e sua descrição
void imprimirTituloDescricao(const struct Obra *obras, int indiceObra) {
    if (indiceObra != -1) {
        printf("\nTítulo da obra: %s\n", obras[indiceObra].titulo);
        printf("Descrição da obra: %s\n", obras[indiceObra].descricao);
    } else {
        printf("\nNenhuma obra encontrada na área selecionada.\n");
    }
}
