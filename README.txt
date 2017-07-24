%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants07
https://github.com/todisorder/Ants07.git
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

>> Jul 2017.
Muitas coisas, não tenho atualizado o readme.
Funciona bem.

>> 4 Abril 2017

Com muitas não dá. Vou tentar outras maneiras de
guardar a feromona.

>> 16 Março 2017

> vou juntar os dois códigos, o linearizado e o não.
> vou fazer tempos iniciais diferentes para elas.
> OK

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants06
https://github.com/todisorder/Ants06.git
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

>> 10 Janeiro 2017

> O modelo total.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants05
https://github.com/todisorder/Ants05.git
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

>> 10 Janeiro 2017
> Funciona bem, defini a fero analiticamente,
	Mas no final não dá porque, como é o problema linearizado,
	a normalização dá negativa, que não pode!
> Mas consegue bem o caso do trilho dado.
> 7 março: vou fazer com normalização de ordem zero, deve dar!


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM GitHub:
New Repository
https://github.com/todisorder/Ants05.git
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

>> 12 de maio 2016
> Agora vou tentar definir a fero analiticamente!
> não é simples…
> Acho que percebo porque é que os outros fizeram isso.
> não é possível que a fero, assim, tenha em conta o bordo, acho eu.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM GitHub:
New Repository
https://github.com/todisorder/Ants04.git
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

>> 10 de maio 2016:
> Muita coisa! Está quase pronto para fazer o mesmo que aqueles da Argentine Ant:
	Ou seja, feromona exploratória.
> Para isso, falta fazer a difusão no UpdatePhero.
> Continua a faltar um cálculo decente do gradiente… :(


>> 3 de maio 2016: 
Mudanças feitas em Ants02 que incorporei neste:
> Uma espécie de Sensitivity.
> No fundo é substituir c(t,X) por max(eps, c(t,X))! 
> Assim, andam mesmo sem feromona; é como se a indeterminação 0/0 que dá quando 
	não há feromona ficasse igual a Lambda em vez de zero.
> Ou então substituir c por \sqrt{c^2 + eps^2}, é do mesmo tipo.
> eps é o Threshold.
> Também quero que o random seja diferente. Vai ser um acréscimo pequeno a F, aleatório numa pequena bola; ou seja, um theta uniforme em (0,2pi)e um r (ou um 1-r) normal em (0,r_0).
> E o random é mesmo random, com seed da hora atual.


25 de Abril 2016:

>> Mudei as matrizes. AGORA USO Matrix.cpp !!!!

25 de Abril 2016:
>> O objetivo é fazer **simulação completa**
>> com coletivo e tudo. Coisas principais:

- Path integration para as que voltam;
- Mínimos quadrados para calcular o gradiente a partir de quatro 
	pontos;
- Usar classes;
- Poder retirar um rectângulo do domínio, dinamicamente.
- Jesus Christ!


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM GitHub:
New Repository
https://github.com/todisorder/Ants03.git
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Este não tem nada, troquei-me todo com o git
e não consigo resolver. Esquece.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM GitHub:
New Repository
https://github.com/todisorder/Ants02.git
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


>> Comecei a alterar matriz.h. O objetivo é interpolar o gradiente com um método least squares.
	Para isso preciso de todas as operações em matrizes.

>> 19 abril 2016. algumas melhorias tipo LastResult.

>> Atenção que mudei l.787, 790 o random walk. Pus um delta_t a multiplicar.
	Isto porque não sei o que estou a fazer com o RW.

>> Resolvi isso mas só temporário com zero. Também alterei a regularização para ser periódico.

>> Neste momento: dá erro do my_matrix quando chega ao limite do domínio. é normal.
Não posso calcular muitas iterações por causa disso.
No plots2.plt está um plot com a sobreposição da feromona e do trajeto.

>> plots de 
http://stackoverflow.com/questions/33774180/transparent-background-picture-and-the-color-of-certain-points
e de
http://gnuplot-surprising.blogspot.com.br/2011/09/gnuplot-background-image.html
Ver também este que dá círculos nos pontos:
http://stackoverflow.com/questions/20252698/r-style-point-background-in-gnuplot

>> Agora vou fazer com feromona qualquer,
mas não produzida por ela.

4 Mar 2016

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM GitHub:
Branch Weber
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
26 fev 2016

Para respeitar a lei de Weber,
vou introduzir uma normalização
pelo integral da feromona.

Uau! Funciona!


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM GitHub:
https://github.com/todisorder/Ants.git
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
11 fev 2016

Acho que resulta. 

Vou tentar no GitHub agora. OK.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM 04:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
2 fev 2016

—> Havia erro na def. da func. Angle, argumentos 
   trocados no atan2.
-> No anterior fiz sem relaxação, mas agora vou 
voltar à relaxação.

-> Não dimensional!
-> Expressão da feromona modificada para
	exp^(-|x|).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM 03:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
22 jan 2016

Ok fiz outro tão rápido porque vou
experimentar sem relaxação, diretamente
com a força.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM 02:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
22 jan 2016
O 01 funciona mas os resultados não são bons.
Nem sei fazer bem só com random walk.

OBS: mudei o Executar…sh e o makefile
de modo a se escrever o numero da versão 
só uma vez (para cada um deles) em cada ficheiro!



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ants IBM 01:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
9 jan 2016
Individual-based model for Ants.



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Predator 02:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
28 Set 2015

Novo programa baseado em Formigas 17, para simular equações predador-presa.



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 17:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
15 Mai 2015

Este é para fazer outras experiências a variar parâmetros.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 16:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
10 Mai 2015

Agora sim, com Runge Kutta 4. 

Também grava o campo de vetores da velocidade de u1, mas não dá para ver nada.

O anterior (Formigas 15) apenas tem as funções RK mas com o método Upwind a funcionar. (sim, é o que o Formigas 14 dizia que tinha, mas a função RK agora está melhor).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 15:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
7 Mai 2015

Agora com Runge Kutta 4.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 14:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
5 Mai 2015

Refazer todo o método numérico para atender a mais revisões do JTB:
Ruge Dutta 4 em tempo e Upwind em espaço.
Nesta versão, apenas Upwind (OK) e definir as funções RK.
— Erro corrigido: agora usa um food_phero_aux.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 13:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
16 Jan 2015

Igual ao  12 mas com outra maneira de fazer simulações paralelas.
Mudei a formula da cond. fronteira do u2 e ficou melhor.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 12:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
15 Jan 2015

Este é igual ao Formigas 10, mas para fazer experiências mais variadas
em consequência das alterações propostas pelo referee do Journal of Theoretical Biology.

Tem uma coisa horrorosa para poder fazer duas simulações ao mesmo tempo e guardar os resultados em pastas diferentes.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 10:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
28 Ago 2014

--> Igual a Formigas 9, mas com diferentes disposições de comida, ou outras experiências.
--> Entretanto resolvi dois erros, um na BC e outro na equação da comida!

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 9:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
01 Ago 2014
--> Para fazer as figuras definitivas, pelo menos para o SIAM LS 2014.




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 8:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

10 jul 2014
--> Pq preciso acabar isto até ao fim do mês para ir 
apresentar em Charlotte!
--> Escrever não dimensionais (tem de ser!)
--> Fronteira (tem de ser!)

Basicamente são estas duas coisas.

EDIT: Este fica para tentar fazer coisas com obstáculos e escolha de caminhos.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 7:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

--> Ver condições de Fronteira 		WIP
--> Escrever as equações com variáveis não dimensionais 		WIP
--> Revolucionar o código?   Ainda não...



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 6:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

--> 20 mar 2014 - Limpar e comentar tudo.   check
	Não percebo o que se passa pq o make faz sempre
	c++    -c -o Formigas-06.o Formigas-06.cpp
	independentemente do que eu escrever lá!!!

--> Fazer um Log! check
--> Ver condições de Fronteira 		Não
--> Escrever as equações com variáveis não dimensionais 		Não

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 4:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Vou tentar condições de Neumann.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Formigas 3:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Vou tentar encontrar uma maneira de não se ter de dar o campo que leva à comida. A única hipótese de que me lembro é o gradiente da feromona...
ok, mais: a difusão de u1 depende de food_phero (diminui para elas irem melhor no carreiro)
