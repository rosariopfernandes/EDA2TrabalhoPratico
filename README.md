# EDA2TrabalhoPratico
Meu Trabalho Prático de EDA2. Realizado no 3º ano (2018) de Eng. Informática do ISCTEM.
O enunciado do trabalho pode ser encontrado
[aqui](https://github.com/rosariopfernandes/EDA2TrabalhoPratico/blob/master/Enunciado.pdf).

### Pergunta 1:
**Sintaxe do comando:**
Obedeceu-se a sintaxe do comando que vem no enunciado.

**Validações**
Não há nenhuma validação ao adicionar cidade.
Há validação ao adicionar estrada:
- Não se pode adicionar estrada de uma cidade para ela própria;
- Não se pode adicionar estradas se o número de cidades for ímpar;
- Não se pode adicionar estrada entre cidades que não existe no mapa.

### Pergunta 2:
**Sintaxe do comando:**
Obedeceu-se a sintaxe do comando que vem no enunciado.

**Validações**
Foram efectuadas validações de input ao programa:
- Não se pode actualizar estrada com um número negativo de polícias ou ladrões;
- Não se pode actualizar uma estrada que parte de uma cidade para ela própria;
- Não se pode actualizar estradas entre cidades que não existem no mapa do jogo.

### Pergunta 3:
**Sintaxe do comando:**
Obedeceu-se a sintaxe do comando que vem no enunciado para adicionar casas.
CRIAR_CIDADE_PONTE ID_CASA_ORIGEM ID_CASA_DESTINO DISTANCIA - adicionar pontes que ligam casas.

**Validações**
Foram efectuadas validações de input ao programa:
- Não se pode adicionar um número de casas negativo para cada a.cidade;
- Não se pode adicionar casas antes de criar cidades no mapa;
- Não se pode adicionar casas à uma cidade que não existe no mapa;
- Não se pode adicionar uma ponte que liga uma casa à ela própria;
- Não se pode adicionar uma ponte antes de adicionar cidades ao mapa;
- Não se pode adicionar uma ponte numa cidade que não existe;
- Nao se pode criar uma ponte que liga casas que não existem.

### Pergunta 4:
**Sintaxe do comando:**
Obdeceu-se a sintaxe do comando que vem no enunciado. No fim é necessário introduzir 0 (zero) para continuar.

**Validações**
Foram efectuadas validações de input ao programa:
- Não se adiciona uma rota que inicia numa cidade e termina nela própria;
- Não se adiciona uma rota entre cidades que não existem no mapa mundo;
- Não se adicionar uma rota igual à outra já existente.

### Pergunta 5:
**Sintaxe do comando:**
Obedeceu-se a sintaxe do comando que vem no enunciado.

**Validações**
Foram efectuadas validações de input ao programa. Não se pode gerar calendário com um número ímpar de cidades.

### Pergunta 6:
**Sintaxe do comando:**
Obedeceu-se a sintaxe do comando que vem no enunciado.

**Validações**
Foram efectuadas validações de input ao programa:
- Não aceita viajar entre cidades que não existem no mapa do jogo;
- Não aceita viajar de uma cidade para ela própria;
- Não aceita viajar se não existirem rotas entre as cidades escolhidas;
- Não aceita viajar se for selecionada uma rota que não existe.

### Pergunta 9:
**Sintaxe do comando:**
ASSASSINATO_NO_MAPA_MUNDO CIDADE_ASSASSINATO CIDADE_DOCUMENTO

**Validações**
Foram efectuadas validações de input ao programa:
- Não é possível ocorrer um assassinato numa cidade que não existe no mapa;
- Não é possível existir uma pista numa cidade que não existe no mapa;
- O documento não pode estar na mesma cidade onde ocorreu o assassinato.

## Por Fazer
As perguntas 7, 8 e 10 não foram feitas.

## Licença
> MIT License
> 
> Copyright (c) 2018 Rosário Pereira Fernandes
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.