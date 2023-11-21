#define MAX_OBRAS 10
#define MAX_DESCRICAO 500
#define MAX_TITULO 100

enum Area { A, B, C, D };

struct Obra {
    char titulo[MAX_TITULO];
    char descricao[MAX_DESCRICAO];
    enum Area area;
};

void imprimirCabecalho();
void limparBuffer();
void limparTela();
void lerArquivo(struct Obra *obras, int *contador);
void salvarNoArquivo(const struct Obra *obra);
void atualizarArquivo(const struct Obra *obras, int contador);
void adicionarObra(struct Obra *obras, int *contador);
void exibirTodasObras(const struct Obra *obras, int contador);
int excluirObra(struct Obra *obras, int *contador);
int editarObra(struct Obra *obras, int contador);

