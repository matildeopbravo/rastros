
### Laboratório de Informática 2
### Turno : PL4
###
### Consituição do grupo:

- Henrique Parola Meziara da Costa - nº 93325
- Inês Anes Vicente - nº 93269
- Matilde Oliveira Pizarro Bravo - nº 93246


# Resumo sobre o trabalho efetuado e dificuldades encontradas

	Nessa primeira semana do Projecto realizamos nomeadamente 2 tarefas para dar início a criação do jogo:

- Organização dos módulos em geral
- Implementação das funções da semana

## Primeira tarefa

### Organização dos módulos em geral

	Para dar o pontapé inicial do trabalho foi preciso a criação de algumas camadas no programa, dentre elas:
3 ficheiros com extensão *.c* que possuem papéis diferentes mediante suas funções, isto é, um deles servirá para
a interação *jogador-jogo*, outro para carregar a informação do *estado jogo* e um terceiro para cuidar da lógica/
métrica do programa. Aliado a cada um dos ficheiros criamos um ficheiro "irmão" com extensão *.h* que contém os 
protótipos e irá facilitar a clarifiação do projecto. Tivemos algumas dificuldades à nível de escolher quais os 
"includes"a serem feitos em cada ficheiro de modo a não repetir códigos desncessários e entrar em redundâncias. 
Para resolver isso pensamos como "programadores preguiçosos" e optamos pela solução mais simples e clara.

## Segunda tarefa 

## Implementação do conteúdo das Funções semanais **dividida em 3 subgrupos** 

	A primeira parte desta secção foi a criação da função que inicializa o estado do jogo. Como em qualquer 
outro trabalho,nossa "maior" dificuldade foi a interpretação sobre aquilo que "a função deveria fazer". A priori
nos deparamos com um problema : como iríamos devolver um *Pointer* (para ser utilizado em outras partes do programa)
que seria criado nessa mesma função? (dado que ao criar um *pointer* numa função estamos "limitados" a usá-lo somente
nela). Após um tempo de pesquisa concluimos que a função *malloc* tratava de alocar um espaço de memória para nosso 
tal *pointer*, resolvendo nosso problema. Entretanto nada disso foi preciso dado que tal trabalho/esforço nem era 
necessário fazer por já estar feito no enunciado (porém foi bom para adquirir mais conhecimento). Sendo assim, 
realizar esta função foi trivial, onde colocamos os valores iniciais, correspondentes a um "início de partida", na 
Struct principal do programa : o ***estado do jogo*** (chamado "novo" em nossa função), que será o *Pointer* que irá 
servir como parâmetro de praticamente todas as funções, sendo o motor de funcionamento e interligação do programa.

	A segunda parte deste início de projecto foi a criação de uma função, componente da camada de "Interface" do 
programa, que tem como papel mostrar na tela o tabuleiro atual da partida. Colocamos em prática nosso conhecimento em 
ciclos "for", e mediante simples "condições e loops" conseguimos realizar o "print" do tabuleiro no ecrã. Para isso 
foi preciso acessar a componente do tabuleiro, "tab", que é uma das 5 componentes da Struct principal, passada como 
parâmetro à função (como dito no tópico anterior, o funcionamento de todas as funções dependia desse *Pointer*). Assim, 
unindo estruturas iterativas, ponteiros e componentes de imput/output fizemos a tal função.

	Por fim, fizemos também mais 4 funções, menores mas de igual importância para o jogo, onde acabarão por servir na constante
atualização e auxilio das restantes funções principais, nomeadamente, 3 funções que buscam na Struct principal componentes
individuais para outros fins, e uma função que irá atualizar o tabuleiro do jogo mediante a "última jogada de um jogador".


