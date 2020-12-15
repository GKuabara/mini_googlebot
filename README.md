# Mini_Googlebot
Projeto da universidade da disciplina Algoritmos e Estruturas de Dados.

Este projeto é apenas um simples googlebot. Lemos um arquivo csv e construímos uma árvore AVL para armazenar as informações dos sites. A partir desse ponto existem 7 implementações para modificar ou usar os dados da nossa estrutura de dados, como inserir e remover sites, atualizar dados sobre eles, e sugestões de sites baseadas nas especificações de cada um.

## Participants
* Gabriel Alves Kuabara - N° USP 11275043 - gabrielalveskuabara@usp.br
* Gabriel Freitas Ximenes de Vasconcelos - N° USP 11819084 - gabriel.vasconcelos@usp.br

## Compilador
GNU Compiler Collection (GCC).

## Planejamento do Trabalho
Anteriormente tinhamos implementado uma lista simplesmente encadeada como estrutura de dados principal. Agora decidimos mudar para uma árvore AVL como estrutura principal, e uma árvore TRIE como estrutura auxiliar para otimizarmos as novas funções implementadas ao nosso programa.

### Arquivo .csv de Entrada
O arquivo que usamos para carregar a informação de sites trata-se de um arquivo do tipo csv, sem espaços com os seguintes parâmetros respectivamente: a chave de identificação do site, o nome do site, seu nome, seu valor de relevancia, seu endereço(URL), e suas palavras-chaves(no máximo 10).

### Árvore AVL
Considerando as estruturas disponíveis para construir nosso projeto, uma árvore AVL nos permite fazer uma busca pela chave de um site com complexidade O(log(n)) (busca binária, devido a ordenação da AVL de acordo com o valor da chave), sendo mais rápida do que estruturas de dados sequenciais, como uma lista encadeada usada anteriormente, cuja eficiencia é O(n). Dessa forma, é possivel fazer busca por sites, inserções e remoções de maneira mais eficiente que a lista.

Além disso, quando pensamos nas funções de busca de uma palavra-chave em cada site (nova e função principal do programa), para usar uma árvore ou uma lista não existe uma grande diferença porque precisamos acessar todos os sites em ambos os casos. Portanto, preferimos usar a árvore AVL com chaves ordenadas para melhorar a eficiência de outras funções do programa.

### Árvore TRIE
Um tipo de árvore que se encaixa perfeitamente com a otimização do problema de armazenar multíplas palavras chaves. Nessa árvore, cada aponta para outros 26 nós (vetor de ponteiros nós de 0-25), cada um representando uma letra do alfabeto. Dessa maneira é possível fazer com que tenhamos todas as possibilidades de palavras na árvore sem repetí-las. 

Ademais, trata-se de uma estrutura otimizada, pois cada busca inserção e busca na árvore depende diretamento do tamanho da palavra, que resulta em complexidade O(c) no pior caso, sendo 'c' o tamanho da palavra.

### Busca por Palavra-Chave (nova e principal função do programa)
Como solicitado, essa função recebe como parâmetro uma palavra-chave que deve ser usada para verificar qual sites a contém, retornando os sites ordenados por maior relevância. Para resolver esse problema, primeiro lemos a palavra-chave e então percorremos a árvore de maneira recursiva passando por cada site, verificando se a palavra existe dentro das especificações do site. Caso um site conter tal palavra-chave, então, realocamos um vetor de ponteiros SITES para armarzenar o ponteiro para esse site. 

Após percorrer a árvore inteira, usamos um Heap Sort (complexidade O(nlog(n)), e memória O(1)) para realizar a ordenação dos sites recolhidos e imprimí-los de acordo com sua relevância. No pior caso, a complexidade dessa busca trata-se de passar por todas as palavras-chaves de cada site, ou seja, 10nc, sendo 'n' o número de sites e 'c' o tamanho de cada palavra.

### Sugestões de sites:
Em primeiro lugar, usamos a mesma função de "Busca por Palavra-Chave" para construir o vetor de sites com a palavra-chave de entrada. Então, o próximo passo foi usar um árvore TRIE para armazenar todas as palavras-chave dos sites encontrados anteriormente.

Depois disso, precisamos procurar todos os sites que contenham pelo menos uma das palavras-chave dentro do TRIE. Assim, percorremos recursivamente nossa árvore AVL verificando se as palavras-chaves sites correspondem a pelo menos uma palavra-chave dentro da TRIE. Se houver correspondência de uma palavra, adicionamos esse site a um vetor de ponteiros para os sites e ignoramos as seguintes palavras-chave deste site, indo para o próximo nó através da AVL, já que a condição é pelo menos uma palavra correspondente.

Agora, temos um vetor de ponteiros para sites que precisamos classificar por relevância. Neste caso específico, precisamos apenas dos 5 sites com maior relevância, então não precisamos ordenar todo o array, ao pensar sobre isso comparamos os algoritmos de ordenação, geralmente usados, de complexidade O(nlog(n)), como o Heap Sort, com o Bubble Sort. A complexidade do Bubble Sort nesse caso específico será 5n, pois precisamos percorrer o vetor de tamanho 'n', 5 vezes para posicionar os sites de maior relevancia no final do vetor. Comparando as duas complexidades, quando 'n'  = 32, temos que os algoritmos de ordenação vão ser praticamente de mesma eficiência, pois 5 * 32 = 32 * log32. Considerando que estaríamos classificando uma grande quantidade de sites, o número de sites que recolheriamos nessas funções seria muito superior a 32. Logo, o Bubble Sort mostra-se a opção, enquanto sua complexidade é linear(O(n)) e não aloca mais memória(O(1)). Por fim, podemos apenas imprimir os 5 últimos sites da matriz.

## Instruções de uso
Ao executar o programa, ele primeiro lerá um arquivo csv chamado "googlebot.txt". Portanto, também pode ser alterado dentro do main.c. Então, algumas mensagens iniciais serão exibidas para o usuário, mostrando quais comandos numéricos são possíveis neste programa.

**1. Inserção de um site:**
	* Pede para o usuário inserir uma linha no formato de csv, de acordo com os parâmetros especificados anteriormente no README.

**2. Remoção de um Site:**
	* Requisita o código de um site para removê-lo.

**3. Adicionar Palavra-Chave a Site:**
	* Requisita o código do site e a palavra-chave para adicioná-lo, caso houver espaço.

**4. Atualizar Relevancia de um Site:**
	* Requisita o código do site e a nova relevancia a ser alterada.

**5. Busca por Palavra-Chave(Função Principal):**
	* Requisita somente uma palavra-chave de entrada e imprime todos os sites com ela.

**6. Sugestões de Sites:**
	* Requisita somente uma palavra-chave de entrada e procura sites com palavras-chaves relacionadas como já explicado mais a fundo em outro tópico.

**7. Encerra o Programa:**
	* Desaloca toda a memória que o programa usa no momento e encerra o programa.
