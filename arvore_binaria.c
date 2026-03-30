#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 //definindo a estrutura do nó da arvore com todos o elementos
typedef struct No {
    int matricula;
    char nome[100];   
    char cargo[50];  
    float salario;
    struct No *left;    // ponteiro pro filho esquerdo
    struct No *right;   // Ponteiro pro filho direito
} No;


 //funcao pra criar um novo nó na memoria
 //aloca o espaço necessario e inicializa os valroes
No* criarNo(int matricula, char* nome, char* cargo, float salario) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    novoNo->matricula = matricula;
    strcpy(novoNo->nome, nome);
    strcpy(novoNo->cargo, cargo);
    novoNo->salario = salario;
    novoNo->left = NULL;
    novoNo->right = NULL;
    
    return novoNo;
}

 //insere novo funcionario respeitando a regra da arvore
 //menor pra ezquerda e maior pra direita
No* inserir(No* raiz, int matricula, char* nome, char* cargo, float salario) {
    //se a arvore tiver vaziam cria e retorna o nó
    if (raiz == NULL) {
        return criarNo(matricula, nome, cargo, salario);
    }

    //se a matricula for menor, vai pra subarvore esquerda
    if (matricula < raiz->matricula) {
        raiz->left = inserir(raiz->left, matricula, nome, cargo, salario);
    } 
    //se a matrícula for maior, vai pra subarvore direita
    else if (matricula > raiz->matricula) {
        raiz->right = inserir(raiz->right, matricula, nome, cargo, salario);
    } 
    //se for igual a matricula ja existe, nao insere duplicado
    else {
        printf("Erro: Funcionario com a matricula %d ja esta cadastrado!\n", matricula);
    }

    return raiz;
}


//busca funcionario por matricula, retorna o ponteiro do nó se encontrar ou null se nao existir
No* buscar(No* raiz, int matricula) {
    //caso base: raiz nula(nao encontrou) ou encontrou a matricula
    if (raiz == NULL || raiz->matricula == matricula) {
        return raiz;
    }

    //se a matricula for menor, continua buscandona esquerda
    if (matricula < raiz->matricula) {
        return buscar(raiz->left, matricula);
    }

    //se formaior continua a busca na direita
    return buscar(raiz->right, matricula);
}


 //usa a funcao de bbsuca para encontrar o funcionario e altera os dados
void atualizar(No* raiz, int matricula) {
    No* funcionario = buscar(raiz, matricula);
    
    if (funcionario != NULL) {
        printf("\n--- Funcionario Encontrado ---\n");
        printf("Nome atual: %s\n", funcionario->nome);
        
        //coleta os novos dados, o espaco no scanf evita problemas de buffer com espaco no texto
        printf("Digite o novo Nome: ");
        scanf(" %[^\n]", funcionario->nome);
        
        printf("Digite o novo Cargo: ");
        scanf(" %[^\n]", funcionario->cargo);
        
        printf("Digite o novo Salario: ");
        scanf("%f", &funcionario->salario);
        
        printf("Dados atualizados com sucesso!\n");
    } else {
        printf("Funcionario com matricula %d nao encontrado.\n", matricula);
    }
}


 //percorre a arvore em ordem simetrica
 //garante que os funcionarios sejam impressos em ordem crescente de matricula
void exibirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->left); //visita o filho esqeurdo
        
        // processa (imprime) a raiz atual
        printf("Matricula: %d | Nome: %-15s | Cargo: %-15s | Salario: R$ %.2f\n", 
               raiz->matricula, raiz->nome, raiz->cargo, raiz->salario);
               
        exibirEmOrdem(raiz->right); //visita o filho direito
    }
}



//funcao pra limpar memoria quando sair do programa
//percorre a arvore em pos ordem(left, right, raiz)
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->left);
        liberarArvore(raiz->right);
        free(raiz);
    }
}

//funcao principal e menu
int main() {
    No* raiz = NULL; // inicializa a arovre vazia
    int opcao, matricula;
    char nome[100], cargo[50];
    float salario;

    do {
        printf("\n-----------------------------------------\n");
        printf("   SISTEMA DE CADASTRO DE FUNCIONARIOS\n");
        printf("-----------------------------------------\n");
        printf("1. Inserir Funcionario\n");
        printf("2. Buscar Funcionario\n");
        printf("3. Atualizar Funcionario\n");
        printf("4. Listar Funcionarios\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\nInserir Novo Funcionario\n");
                printf("Matricula: ");
                scanf("%d", &matricula);
                printf("Nome: ");
                scanf(" %[^\n]", nome); //lê string com espaco
                printf("Cargo: ");
                scanf(" %[^\n]", cargo);
                printf("Salario: ");
                scanf("%f", &salario);
                
                raiz = inserir(raiz, matricula, nome, cargo, salario);
                printf("Operacao concluida!\n");
                break;
                
            case 2:
                printf("\nBuscar Funcionario\n");
                printf("Digite a Matricula: ");
                scanf("%d", &matricula);
                
                No* encontrado = buscar(raiz, matricula);
                if (encontrado != NULL) {
                    printf("\nFuncionario Localizado:\n");
                    printf("Matricula: %d\nNome: %s\nCargo: %s\nSalario: R$ %.2f\n", 
                           encontrado->matricula, encontrado->nome, encontrado->cargo, encontrado->salario);
                } else {
                    printf("Funcionario nao encontrado!\n");
                }
                break;
                
            case 3:
                printf("\nAtualizar Funcionario\n");
                printf("Digite a Matricula do funcionario que deseja atualizar: ");
                scanf("%d", &matricula);
                atualizar(raiz, matricula);
                break;
                
            case 4:
                printf("\nLista de Funcionarios (por matricula)\n");
                if (raiz == NULL) {
                    printf("Nenhum funcionario cadastrado.\n");
                } else {
                    exibirEmOrdem(raiz);
                }
                break;
                
            case 5:
                printf("Encerrando o sistema e liberando memoria\n");
                liberarArvore(raiz);
                break;
                
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 5);

    return 0;
}
