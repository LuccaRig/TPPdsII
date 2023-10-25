# TPPdsII
Esse repositório tem a finalidade de realizar um controle de versão do código feito para a disciplina PDS2, além disso ele está sendo utilizado para a correção e acompanhamento do projeto pelo monitor/professor. Nosso projeto tem como objetivo colocar em prática os conceitos aprendidos durante o semestre, como Classes, Herança, Vetores, Polimorfismo e técnicas de desenvolvimento de software mais eficientes. Para isso decidimos criar um jogo de estratégia estilo RPG e incluimos uma bibilioteca gráfica, para auxiliar na visualização dos objetos do jogo, além de tornar a experiência de desenvolvimento mais completa.


Checar a Pasta logic para correção da entrega no dia 27/10(Arquivos .h e cartões CRC estão nela)


# User Storys

### Game

Como jogador, busco um jogo divertido e estratégico, no qual sou capaz de derrotar os monstros que aparecem na masmorra, atacando os inimigos e lançando magias. Para isso utilizamos um sistema no qual o jogador controla 3 personagens durante seu turno e se prepara para o ataque dos inimigos no turno seguinte.

### Board

Como jogador, devo ser capaz de me locomover na masmorra, por isso será utizado um tabuleiro quadriculado 5x5, e com isso serei capaz de realizar minhas ações clicando no mapa e ver meus inimigos se aproximando dos meus personagens para me preparar contra o perigo. 

### Hero

Como jogador, quero poder controlar 3 diferentes heróis, que me permitam atacar os monstros de formas diferentes ao entender as características de cada herói. Também sendo capaz de movimentar meus heróis e utilizar habilidades especiais com cada um deles.

### Spells

Como jogador, quero que cada herói seja capaz de utilizar uma magia(habilidade especial), tornando as batalhas contra os monstros mais estratégicas e mais divertidas.

# Pasta Logic

Como o trabalho de PDS2 tem a finalidade de testar nossos conhecimentos sobre implementação das classes, métodos e organização de software, percebemos que não havia motivo para implementarmos diretamente a nossa bibilioteca gráfica, ja que ela exige um conhecimento não relacionado ao exigidos pelo trabalho prático(entendimento das bibiliotecas unicas do SFML, renderização e outros). Portanto decidimos criar uma pasta chamada logic que auxiliará na correção pois não terá nada relacionado a bibilioteca gráfica, além de possuir alguns casos de teste que nos ajudará a encontrar alguns erros não perceptíveis na parte gráfica

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
    make clean
```

```
    make
```

```
    ./Game.app
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
