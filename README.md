# Tarefa 29/01/2025 - Clocks e Temporizadores

Este repositório contém a implementação de dois sistemas de temporização

# Atividade 1: Temporizador Periódico

Tem o objetivo de desenvolver um semáforo utilizando a função add_repeating_timer_ms(), garantindo a alternância dos LEDs conforme o fluxo definido na especificação da atividade.

## Componentes Utilizados

Raspberry Pi Pico W

3 LEDs (vermelho, amarelo e verde)

3 resistores de 330 Ω

## Funcionalidades

A função repeating_timer_callback() gerencia a mudança de estado dos LEDs automaticamente.

A partir disso o sistema simula um semáforo, que alterna entre as cores vermelho, amarelo e verde.

O sistema também envia mensagens automáticas a cada segundo informando que ele está funcionando e qual cor está ativa.

Possibilidades de testes adicionais utilizando os LED RGB nos GPIOs 11, 12 e 13 na ferramenta BitDogLab.

## Como executar 

Primeiramente clone o repositório para seu ambiente local.

Antes de abrir algum dos projetos, é necessário garantir que todas as extensões e ferramentas estão devidamente instaladas.

Instalar o Pico SDK e extensão Raspberry Pi Pico: Siga as instruções do Pico SDK para configurar o ambiente de desenvolvimento no VS Code e instale a extensão Raspberry Pi Pico.

Instalar a Extensão Wokwi: Permite simular o Raspberry Pi Pico W no ambiente de desenvolvimento. Instale a extensão Wokwi Simulator no catálogo extensões do VS Code e depois habilite a mesma com uma licença de 30 dias gratuita.

Abra o projeto referente a atividade 1, temporizadorPeriodico em seu VS Code.

Compile o código a partir da Pico SDK.

Execute no Raspberry Pi Pico W ou no simulador Wokwi integrado a partir do arquivo diagram.json na pasta do projeto.

A partir do inicio da execução, será possivel visualizar a troca de estados dos leds a cada 3 segundos.

Ao abrir o terminal, será possivel também ver as mensagens enviadas pela porta serial a cada 1 segundo, sinalizando o seu estado de funcionamento e cor atual.

# Atividade 2: Temporizador de um Disparo (One Shot)

Essa atividade tem o objetivo de desenvolver um sistema de temporização utilizando a função add_alarm_in_ms(), permitindo o desligamento sequencial de LEDs após um determinado periodo de tempo.

## Componentes Utilizados

Raspberry Pi Pico W

3 LEDs (azul, vermelho e verde)

3 resistores de 330 Ω

1 botão (pushbutton)

## Funcionalidades

Pressionar o botão liga todos os LEDs, que vão apagando um por um a cada 3 segundos.

add_alarm_in_ms() define um atraso de 3 segundos para cada LED ser apagado.

Implementação de debounce por software para evitar acionamentos acidentais.

Durante o ciclo de temporização, novas interações são bloqueadas.

Possibilidades de testes adicionais utilizando os LED RGB nos GPIOs 11, 12 e 13 e o botão A no GPIO 05 na ferramenta BitDogLab.

## Como executar 

Primeiramente clone o repositório para seu ambiente local.

Antes de abrir algum dos projetos, é necessário garantir que todas as extensões e ferramentas estão devidamente instaladas.

Instalar o Pico SDK e extensão Raspberry Pi Pico: Siga as instruções do Pico SDK para configurar o ambiente de desenvolvimento no VS Code e instale a extensão Raspberry Pi Pico.

Instalar a Extensão Wokwi: Permite simular o Raspberry Pi Pico W no ambiente de desenvolvimento. Instale a extensão Wokwi Simulator no catálogo extensões do VS Code e depois habilite a mesma com uma licença de 30 dias gratuita.

Abra o projeto referente a atividade 1, TemporizadorOneShot em seu VS Code.

Compile o código a partir da Pico SDK.

Execute no Raspberry Pi Pico W ou no simulador Wokwi integrado a partir do arquivo diagram.json na pasta do projeto.

A partir do inicio da execução, aperte o botão para ver iluminação dos LEDs e em seguida eles sendo apagados em sequencia pelo temporizador de 3 segundos.


# Projeto desenvolvido por Alex Rodrigo Porto Barbosa


