#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "obras.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Obra obras[MAX_OBRAS];
    int contador = 0;

    // Ler as obras do arquivo no início do programa
    lerArquivo(obras, &contador);

    while (1) {
        imprimirCabecalho();
        printf("\nEscolha uma opção:\n");
        printf("1. Adicionar obra\n");
        printf("2. Exibir obras\n");
        printf("3. Excluir obra\n");
        printf("4. Editar obra\n");
        printf("5. Sair\n");
        printf("Opção: ");
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
                    printf("Obra excluída com sucesso!\n");
                } else {
                    printf("Exclusão cancelada.\n");
                }
                break;
            case 4:
                if (editarObra(obras, contador)) {
                    printf("Edição concluída com sucesso!\n");
                } else {
                    printf("Edição cancelada.\n");
                }
                break;
            case 5:
                printf("Saindo do programa. Até logo!\n");
                // Salvar antes de sair
                atualizarArquivo(obras, contador);
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        limparTela();
    }
}
