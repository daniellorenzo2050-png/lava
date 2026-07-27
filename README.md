# 🌋 Linguagem de Programação Lava

<div align="center">

[![Licença Apache 2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![Versão da Lava](https://img.shields.io/badge/Lava-v0.5%20(Stable)-orange.svg)]()
[![Plataforma](https://img.shields.io/badge/Platform-Termux%20%7C%2C%20Linux%20%7C%2C%20Unix-success.svg)]()

*Uma linguagem de programação moderna, leve e orientada a alta performance, projetada com compilador próprio (`lavac`), Máquina Virtual dedicada (`LavaVM`) e foco em sistemas de baixo e médio nível.*

</div>

---

## 📖 Índice
1. [Sobre o Projeto](#-sobre-o-projeto)
2. [Arquitetura do Ecossistema](#-arquitetura-do-ecossistema)
3. [Guia de Instalação e Configuração](#-guia-de-instalação-e-configuração)
4. [Especificação do Compilador e Bytecode](#-especificação-do-compilador-e-bytecode)
5. [Como Contribuir](#-como-contribuir)
6. [Licença](#-licença)

---

## 🔍 Sobre o Projeto

A linguagem **Lava** nasceu com o propósito de unir a expressividade de sintaxes modernas com o controle estrito de memória e desempenho de linguagens compiladas nativas. O ecossistema foi construído desde os seus fundamentos para rodar de forma otimizada em ambientes restritos de linha de comando, como o **Termux** em dispositivos Android, bem como em distribuições Unix/Linux tradicionais.

O projeto é composto por três pilares tecnológicos centrais:
- **`lavac`**: O compilador e interpretador de bytecode integrado que analisa, traduz e executa arquivos de código-fonte.
- **`LavaVM`**: A máquina virtual baseada em pilha (*stack-based virtual machine*) responsável por processar o bytecode de forma segura e determinística.
- **Infraestrutura de Scripting**: Ferramentas de automação e integração contínua voltadas para o desenvolvedor.

---

## 🏗️ Arquitetura do Ecossistema

O fluxo de execução do código na linguagem Lava segue rigorosas etapas de engenharia de compiladores:

1. **Análise Léxica (Lexer):** O código-fonte bruto em formato `.lava` é varrido caractere por caractere para a geração de tokens tipados.
2. **Análise Sintática e AST (Parser):** Os tokens são processados por um analisador descendente recursivo que valida a gramática, respeitando a precedência de operadores matemáticos e construindo a Árvore de Sintaxe Abstrata.
3. **Geração de Bytecode:** A árvore é traduzida para instruções de baixo nível encapsuladas em arquivos com a extensão `.lava-bytecode`.
4. **Execução na Máquina Virtual:** A `LavaVM` interpreta as instruções na pilha de execução, gerenciando variáveis, operações aritméticas e chamadas de sistema com isolamento e segurança.

---

## 🚀 Guia de Instalação e Configuração

Para instalar o ambiente de desenvolvimento da Lava de forma totalmente automatizada no seu terminal (Linux ou Termux), utilize o script oficial de instalação fornecido no repositório.

### Pré-requisitos
Certifique-se de possuir o compilador **GCC** e o utilitário **Make** instalados em seu sistema. No Termux, execute:
```bash
pkg update && pkg install clang make git
