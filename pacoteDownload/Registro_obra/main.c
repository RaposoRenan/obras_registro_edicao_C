#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "obras.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Obra obras[MAX_OBRAS];
    int contador = 0;

    // Ler as obras do arquivo no in�cio do programa
    lerArquivo(obras, &contador);

    while (1) {
        imprimirCabecalho();
        printf("\nEscolha uma op��o:\n");
        printf("1. Adicionar obra\n");
        printf("2. Exibir obras\n");
        printf("3. Excluir obra\n");
        printf("4. Editar obra\n");
        printf("5. Sair\n");
        printf("Op��o: ");
        int opcao;
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarObra(obras, &contador);
                break;
            case 2:
                exibirTodasObras(obras, contador);
                break;
            case 3:
                if (excluirObra(obras, &contador)) {
                    printf("Obra exclu�da com sucesso!\n");
                } else {
                    printf("Exclus�o cancelada.\n");
                }
                break;
            case 4:
                if (editarObra(obras, contador)) {
                    printf("Edi��o conclu�da com sucesso!\n");
                } else {
                    printf("Edi��o cancelada.\n");
                }
                break;
            case 5:
                printf("Saindo do programa. At� logo!\n");
                // Salvar antes de sair
                atualizarArquivo(obras, contador);
                return 0;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
        limparTela();
    }
}
