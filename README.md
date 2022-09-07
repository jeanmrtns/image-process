# C�digo de exemplo para prop�sito acad�mico
## Simples implementa��o C de uma calculadora
## estruturada em forma de projeto

Autor: Prof. Claudio Correa



## Resumo

Esse � um exemplo de implementa��o de uma calculadora
para as quatro opera��es aritm�ticas b�sicas, escrita 
em linguagem C, com o prop�sito de ilustrar a estrutura 
de desenvolvimento do projeto organizada em diret�rios:

. include
. lib
. src

S�o disponibilizados recursos para gerar, automaticamente, 
os objetos para preparar uma biblioteca est�tica, compilar 
o c�digo principal e ligar com a biblioteca para gerar o
execut�vel final.

O procedimento pode ser realizado por meio das ferramentas
make (com aux�lio do Makefile) e cmake (com aux�lio do 
CMakeLists.txt)

IMPORTANTE: o c�digo principal (<it>main()</it>) est� em src

## make

Duas formas simples de gerar o execut�vel:

<ul>
  <li>make calc</li>: compila��o tradicional (sem gerar a biblioteca)</li>
  <li>make</li>: gera os objetos, a biblioteca est�tica e ent�o, o execut�vel</li>
</ul>

## cmake b�sico
### Ref.: <a href="https://cmake.org/examples">https://cmake.org/examples</a>
<ul>
  <li>	cmake -S . -B build</li>
  <li>	cmake --build build</li>
  <li>	cmake --build build --target test</li>
</ul>
### or
<ul>
  <li>	mkdir build && cd build</li>
  <li>	cmake .. && make VERBOSE=1</li>
  <li>	make test && doas make install/strip</li>
</ul>

A imagem apresenta a estrutura de diret�rios:
 
 <img src="images/calcdirs.png">
 
## Descri��o dos arquivos

CMakeLists.txt
Makefile
README.md
mycalc.pc.in

include:
calc.h

lib:
funcoesarit.c
funcoesaux.c

src:
calculadora.c

## git
### Ref.:

https://ilegra.com/blog/do-zero-git-github-como-criar-primeiro-repositorio-e-subir-seu-primeiro-projeto/#Instalacao_do_Git
https://ilegra.com/blog/do-zero-git-github-como-criar-primeiro-repositorio-e-subir-seu-primeiro-projeto/

http://devfuria.com.br/git/tutorial-para-iniciar-com-o-git-e-o-github/

https://medium.com/reprogramabr/git-e-github-por-onde-come%C3%A7ar-ca88a783c223#:~:text=Criando%20uma%20conta%20no%20GitHub,formul%C3%A1rio%20de%20cadastro%2C%20conforme%20imagem.

$ git config --global user.name "Your Name"
$ git config --global user.email "you@example.com"
