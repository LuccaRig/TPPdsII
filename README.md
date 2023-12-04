
# TPPdsII
Esse repositório tem a finalidade de realizar um controle de versão do código feito para a disciplina PDS2, além disso ele está sendo utilizado para a correção e acompanhamento do projeto pelo monitor/professor. Nosso projeto tem como objetivo colocar em prática os conceitos aprendidos durante o semestre, como Classes, Herança, Vetores, Polimorfismo e técnicas de desenvolvimento de software mais eficientes. Para isso decidimos criar um jogo de estratégia estilo RPG e incluimos uma bibilioteca gráfica, para auxiliar na visualização dos objetos do jogo, além de tornar a experiência de desenvolvimento mais completa.

# User Storys

### Game

Como jogador, busco um jogo divertido e estratégico, no qual sou capaz de derrotar os monstros que aparecem na masmorra, atacando os inimigos e lançando magias. Para isso utilizamos um sistema no qual o jogador controla 3 personagens durante seu turno e se prepara para o ataque dos inimigos no turno seguinte.

### Board

Como jogador, devo ser capaz de me locomover na masmorra, por isso será utizado um tabuleiro quadriculado 5x5, e com isso serei capaz de realizar minhas ações clicando no mapa e ver meus inimigos se aproximando dos meus personagens para me preparar contra o perigo. 

### Hero

Como jogador, quero poder controlar 3 diferentes heróis, que me permitam atacar os monstros de formas diferentes ao entender as características de cada herói. Também sendo capaz de movimentar meus heróis e utilizar habilidades especiais com cada um deles.

### Monster

Como jogador, quero ser capaz de enfrentar e derrotar diferentes tipos de monstros (todos capazes de se movimentar), cada um dotado de características específicas relacionadas ao número de pontos de vida, quantidade de dano do ataque e aparência estética. Além disso, ao serem derrotados, quero que os monstros deixem experiência para ser coletada e deve existir uma chance de eles deixarem um item vantajoso ao herói que coletá-lo.

### Itens

Como jogador, quero que meus heróis possam coletar itens que esporadicamente são deixados por monstros no local onde foram derrotados. Adicionalmente, quero que o item proporcione alguma vantagem ao herói que o coletou, como um aumento nos seus pontos de vida, um aumento na quantidade de dano infligido pelo seu ataque normal ou especial.

### Skills

Como jogador, quero que cada herói seja capaz de utilizar uma habilidade especial, tornando as batalhas contra os monstros mais estratégicas e mais divertidas.

# Como jogar

Todas as opções do jogo devem ser selecionadas utilizando as setinhas do teclado e pressionando o enter.

## Menu do jogador

Durante o turno do herói é necessário selecionar uma das ações do herói, caso você tente realizar uma ação invalida(ex: atacar um alvo invalido ou se mover para a parede), é possível selecionar outra ação. As possíveis ações são:
<dl>
    <dd>Mover: Após selecionar mover, aperte novamente as setinhas para escolher qual direção o herói vai se mexer.</dd>
    <dd>Atacar: Após selecionar essa ação é necessario apertar a setinhas novamente e escolher a direção do ataque, lembre-se que todos os heróis atacam apenas um quadrado de distância e não atacam na diagonal.</dd>
    <dd>Habilidade: Cada herói possui uma habilidade única e essa opção ativa esse poder.</dd>
    <dd>Esperar: Muitas vezes a jogada mais sábia é apenas esperar, por isso essa ação passa a vez de um herói para seu próximo companheiro.</dd>
</dl>

<img src="https://github.com/LuccaRig/TPPdsII/blob/main/Resources/MenuDoHeroi.png">

## Nivel do heroi e barras de vida

Todos os heróis quando confrontados por um novo desafio são capazes de se adaptar e ficam cada vez mais fortes, por isso quando um número de inimigos é derrotado o herói sobe de nível, aumentando todos os seus status.
Já quando um herói é atacado sua barra de vida cai, quando ela chegar a zero o herói morre abandonando seus aliados.

<img src="https://github.com/LuccaRig/TPPdsII/blob/main/Resources/NiveisEBarrasDevida.png">

## Itens no tabuleiro



## Cooldown

Para aumentar a estratégia do jogo, colocamos uma mecânica que as habilidade não podem ser utilizadas múltiplas vezes, caso você tente pode acabar perdendo um turno! No entanto fique tranquilo, colocamos um aviso para quando a habilidade
for selecionada, mas não pode ser utilizada, para te auxiliar nas decisões

# Personagens do jogador

## Mago
<img src="https://github.com/LuccaRig/TPPdsII/blob/main/Resources/NovicePyromancerIdle.gif" width="60" height="60"/> 
<dl>
  <dt>Magia de chamas</dt>
  <dd>Quando utiliza sua habilidade, realiza um ataque devastador em todos os inimigos na linha e na coluna onde está posicionado</dd>
  <dt>Tempo de recuperação elevado</dt>
  <dd>Por ter uma habilidade muito poderosa, se cansa muito com o uso, é necessário esperar 2 turnos para utiliza-la novamente</dd>
  <dt>Ataque e vida medianos</dt>
  <dd>Seu ponto forte é sua magia, por isso não possui um ataque muito forte nem uma vida muito alta</dd>
</dl>

## Ladino
<img src="https://github.com/LuccaRig/TPPdsII/blob/main/Resources/HalflingAssassinIdleSide.gif" width="60" height="60"/>
<dl>
  <dt>Ataque letal</dt>
  <dd>Quando utiliza sua habilidade, faz com que seus ataques fiquem permanentemente mais poderosos, tornando-se um perigo para os inimigos no final do jogo</dd>
  <dt>Tempo de recuperação baixo</dt>
  <dd>Sua habilidade se basea em afiar as suas armas, logo pode se recuperar em um turno e utiliza-la novamente</dd>
  <dt>Ataque alto e vida extremamente baixa</dt>
  <dd>Sua habilidade faz com que o ladino seja extremamente mortal, isso se você conseguir mante-lo fora da linha de frente, e utiliza-lo em momentos estratégicos</dd>
</dl>

## Guerreiro
<img src="https://github.com/LuccaRig/TPPdsII/blob/main/Resources/RadiantPaladinIdleSide.gif" width="60" height="60"/>
<dl>
  <dt>Vontade inabalável</dt>
  <dd>Quando utiliza sua habilidade, recupera parte da sua vida perdida, se mantendo em combate por mais tempo</dd>
  <dt>Tempo de recuperação elevado</dt>
  <dd>Não é capaz de regenerar todas feridas a todo momento, por isso precisa esperar 2 turnos para usar sua habilidade novamente</dd>
  <dt>Ataque médio e vida extremamente alta</dt>
  <dd>Por ter muita vida e conseguir se regenerar, o guerreiro é o mais durável no campo de batalha, podendo resistir ataques inimigos e manter seus aliados longe do combate</dd>
</dl>

# Instalação e Execução da parte gráfica

Para conseguir instalar e executar o nosso jogo basta seguir os seguintes passos:

AVISO: Nosso projeto está feito para funcionar exclusivamente em linux, não fizemos testes nem desenvolvemos nenhuma forma do código ser executado no windows 

Instalar a bibilioteca gráfica SFML no terminal linux:

```
    sudo apt-get install libsfml-dev
```

*Link do Site oficial do SFML: https://www.sfml-dev.org/tutorials/2.6/start-linux.php

Logo em seguida é necessário fazer um clone do repositório do projeto:

```
    git clone https://github.com/LuccaRig/TPPdsII.git
```


Para compilar e executar é necessário estar no diretório onde o repositório foi clonado e em seguida executar os comandos:

```
    make clean; make; ./Game.app
```

Se tudo estiver correto uma janela com o jogo funcionando deverá ser aberta, Divirta-se 😉


## Colaboradores

<table>
  <tr>
    <td align="center">
      <a href="#">
        <sub>
          <b><a href="https://github.com/LuccaRig">Lucca Rigueira</a></b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <sub>
          <b><a href="https://github.com/DaviZTS">Davi Zumpano</a></b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <sub>
          <b><a href="https://github.com/pedr0caversan">Pedro Caversan</a></b>
        </sub>
      </a>
  </tr>
</table>
