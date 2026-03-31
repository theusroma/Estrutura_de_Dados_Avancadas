# Sistema de Cadastro de Funcionários

Sistema de gerenciamento de funcionários implementado em C utilizando uma **Árvore Binária de Busca (BST)**. Os registros são organizados automaticamente pela matrícula, garantindo buscas eficientes e listagem ordenada.

---

## Funcionalidades

- **Inserir** novo funcionário (matrícula, nome, cargo e salário)
- **Buscar** funcionário por matrícula
- **Atualizar** dados de um funcionário existente
- **Listar** todos os funcionários em ordem crescente de matrícula
- **Liberar** memória alocada ao encerrar o programa

---

## Como Compilar e Executar

**Pré-requisito:** compilador GCC instalado.

```bash
# Compilar
gcc -o sistema_funcionarios main.c

# Executar
./sistema_funcionarios
```

> No Windows, substitua `./sistema_funcionarios` por `sistema_funcionarios.exe`.

---

## Estrutura do Projeto

```
.
└── main.c    # Código-fonte completo com estrutura, funções e menu principal
```

### Campos de cada funcionário

| Campo       | Tipo    | Tamanho máx. |
|-------------|---------|--------------|
| `matricula` | int     | —            |
| `nome`      | char[]  | 100 chars    |
| `cargo`     | char[]  | 50 chars     |
| `salario`   | float   | —            |

---

## Estrutura de Dados: Árvore Binária de Busca

Cada nó da árvore armazena um funcionário e dois ponteiros (`left` e `right`). A regra de organização é:

```
matrícula menor  →  subárvore esquerda
matrícula maior  →  subárvore direita
```

Isso garante que a listagem em **ordem simétrica** (in-order) produza os funcionários em ordem crescente de matrícula, sem nenhuma ordenação extra.

---

## Funções Principais

| Função             | Descrição                                                        |
|--------------------|------------------------------------------------------------------|
| `criarNo()`        | Aloca e inicializa um novo nó na memória                         |
| `inserir()`        | Insere um funcionário respeitando a regra da BST                 |
| `buscar()`         | Busca recursiva por matrícula; retorna `NULL` se não encontrado  |
| `atualizar()`      | Localiza o funcionário e permite editar nome, cargo e salário    |
| `exibirEmOrdem()`  | Percurso in-order: exibe funcionários em ordem de matrícula      |
| `liberarArvore()`  | Percurso pós-ordem para liberar toda a memória alocada           |

---

## Complexidade

| Operação | Caso médio | Pior caso (árvore degenerada) |
|----------|------------|-------------------------------|
| Inserir  | O(log n)   | O(n)                          |
| Buscar   | O(log n)   | O(n)                          |
| Listar   | O(n)       | O(n)                          |

> O pior caso ocorre quando as matrículas são inseridas em ordem estritamente crescente ou decrescente, formando uma lista encadeada. Para evitar isso, pode-se usar uma árvore AVL ou Red-Black Tree.

---

## Exemplo de Uso

```
-----------------------------------------
   SISTEMA DE CADASTRO DE FUNCIONARIOS
-----------------------------------------
1. Inserir Funcionario
2. Buscar Funcionario
3. Atualizar Funcionario
4. Listar Funcionarios
5. Sair
Escolha uma opcao: 1

Inserir Novo Funcionario
Matricula: 1042
Nome: Ana Lima
Cargo: Analista
Salario: 4500.00
Operacao concluida!
```

---

## Possíveis Melhorias Futuras

- Implementar remoção de funcionários
- Balancear a árvore (AVL ou Red-Black Tree) para garantir O(log n) mesmo no pior caso
- Adicionar persistência em arquivo (salvar/carregar dados em disco)
- Busca por nome além da matrícula

---

## Autores

Desenvolvido como projeto de estudo de estruturas de dados em C por Matheus Santos e Rebecca Beccari.
