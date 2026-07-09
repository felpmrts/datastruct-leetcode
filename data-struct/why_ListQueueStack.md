# Resumo de Estruturas de Dados: Fila, Pilha e Lista Encadeada

---

## 1. Fila (Queue)

### 📌 Quando usar?
* **Sistemas de Atendimento e Impressão:** Filas de banco, sistemas de chamados de suporte ou envio de documentos para uma impressora.
* **Processamento de Tarefas/Mensagens:** Buffers de dados, sistemas de mensageria (como RabbitMQ ou Kafka) e transferência de dados assíncrona.
* **Algoritmos de Grafos:** Busca em Largura (BFS), onde é necessário explorar os nós vizinhos antes de avançar para os níveis mais profundos.

### ⚙️ Por que usar?
* **Garantia de Ordem (FIFO):** O princípio *First In, First Out* (Primeiro a Entrar, Primeiro a Sair) garante que os elementos sejam processados estritamente na ordem cronológica de chegada.
* **Isolamento de Processos:** Permite que o emissor envie dados e continue trabalhando, enquanto o receptor processa as informações no seu próprio ritmo, sem travar o sistema.

---

## 2. Pilha (Stack)

### 📌 Quando usar?
* **Mecanismos de Desfazer/Refazer (Undo/Redo):** Histórico de ações em editores de texto (Ctrl+Z) ou softwares de edição.
* **Navegação de Páginas:** O botão "Voltar" de navegadores web, que remove a página atual e retorna à imediatamente anterior.
* **Execução de Funções (Call Stack):** Gerenciamento interno do compilador/interpretador para controlar o escopo de variáveis e a ordem de execução das funções chamadas.
* **Validação de Delimitadores:** Verificação de sintaxe para garantir o fechamento correto de parênteses `()`, colchetes `[]` e chaves `{}`.

### ⚙️ Por que usar?
* **Acesso Inverso (LIFO):** O princípio *Last In, First Out* (Último a Entrar, Primeiro a Sair) é ideal quando o dado mais recente inserido é o mais importante a ser manipulado imediatamente.
* **Rastreabilidade de Caminho:** Permite retroceder exatamente pelas mesmas etapas percorridas pelo programa até aquele momento.

---

## 3. Lista Encadeada (Linked List)

### 📌 Quando usar?
* **Aplicações com Tamanho Volátil:** Situações em que o número total de elementos varia constantemente e não pode ser previsto (evitando as limitações de tamanho fixo dos vetores).
* **Inserções e Remoções Frequentes no Meio:** Sistemas que exigem reorganização constante de elementos, como gerenciadores de playlists de música ou listas de tarefas prioritárias.
* **Construção de Outros TADs:** Serve como uma base flexível e eficiente para implementar pilhas e filas de tamanho dinâmico.

### ⚙️ Por que usar?
* **Crescimento Dinâmico Infcionável:** A alocação de memória ocorre sob demanda (utilizando `malloc`). A estrutura ocupa apenas o espaço estritamente necessário na memória RAM e elimina o risco de estouro de capacidade (*overflow*).
* **Inserção Eficiente:** Inserir um elemento não exige o deslocamento dos demais itens na memória (como ocorre em vetores). Basta alterar os ponteiros de referência dos nós vizinhos.

---

## 📊 Resumo Comparativo Rápido

| Estrutura | Regra de Acesso | Ponto Forte | Maior Fraqueza |
| :--- | :--- | :--- | :--- |
| **Fila** | FIFO (Primeiro a entrar, primeiro a sair)  | Organização sequencial justa e ordenada  | Acesso restrito (só é possível espiar a cabeça)  |
| **Pilha** | LIFO (Último a entrar, primeiro a sair) | Facilidade para reverter históricos de operações | Acesso restrito (só é possível manipular o topo) |
| **Lista** | Sequencial por Ponteiros  | Flexibilidade de tamanho e inserção rápida | Busca lenta (exige varrer a lista nó por nó) |