# U1A3
Este projeto implementa uma estação de monitoramento de cheias utilizando a placa BitDog Lab com o microcontrolador RP2040 e o sistema operacional em tempo real FreeRTOS. Os dados simulados de nível da água e volume de chuva são obtidos via joystick analógico, e são processados por tarefas concorrentes que se comunicam por filas.

__Aluno:__
Lucas Carneiro de Araújo Lima

## ATIVIDADE 

__Para este trabalho, os seguintes componentes e ferramentas se fazem necessários:__
1) Microcontrolador Raspberry Pi Pico W.
2) Ambiente de trabalho VSCode.
3) LEDs RGB.
4) _Display_ SSD1306.
5) 2 Botões Pull-Up.
7) Ferramenta educacional BitDogLab.
8) Matriz de LEDs 5x5.
9) FreeRTOS

__O resultado do projeto pode ser assistido através deste link: [Vídeo de Apresentação - Estação de Alerta de Enchentes Inteligente](https://youtu.be/rIkyXRGFPso).__

## Instruções de Uso

### 1. Clone o repositório
Abra o terminal e execute o comando abaixo para clonar o repositório em sua máquina:
```bash
git clone https://github.com/LucasCarneiro3301/U1A3.git
```

### 2. Configure o ambiente de desenvolvimento
Certifique-se de que o [SDK do Raspberry Pi Pico](https://github.com/raspberrypi/pico-sdk) esteja instalado e configurado corretamente no seu sistema.

### 3. Instale o CMake
Certifique-se de que o [CMake](https://cmake.org/download/) esteja instalado e configurado corretamente no seu sistema.

### 4. Clone o repositório do FreeRTOS
Certifique-se de clonar o repositório do FreeRTOS. Repositório: [FreeRTOS](https://github.com/FreeRTOS/FreeRTOS-Kernel.git).

### 5. Conexão com a Rapberry Pico
1. Conecte o Raspberry Pi Pico ao seu computador via USB.
2. Inicie o modo de gravação pressionando o botão **BOOTSEL** e **RESTART**.
3. O Pico será montado como um dispositivo de armazenamento USB.
4. Execute através do comando **RUN** a fim de copiar o arquivo `U1A3.uf2` para o Pico.
5. O Pico reiniciará automaticamente e executará o programa.

### 5. Observações (IMPORTANTE !!!)
2. Manuseie a placa com cuidado.

## Recursos e Funcionalidades

### 1. Botão

| BOTÃO                            | DESCRIÇÃO                                     | 
|:----------------------------------:|:---------------------------------------------:|
| A                                  | Status do Sistema ou Nível de Água na Matriz de LEDs              | 
| B                                  | Modo de Gravação              | 

### 2. Display OLED
Monitora os valores de nível de água e volume de chuva, além de informar o modo de operação atual do sistema.

### 3. Matriz de LEDs (5x5)
Informa o status do sistema ou ilustraa o nível da água através das linhas da matriz.

### 4. LED RGB
Representa visualmente os estados do sistema.

### 5. BUZZER
Sinaliza através de efeitos sonoros o modo de alerta.

### 6. Interrupções
As interrupções são usadas para detectar a borda de descida do Botão A e B de forma assíncrona, com tratamento de debounce para evitar leituras falsas por oscilações elétricas, eliminando a necessidade de polling contínuo.

### 7. Comunicação Serial
Envia mensagens do sistema via USB para o terminal do computador.

### 5. Tasks e FreeRTOS
Modulariza o programa em subprogramas chamados de tasks. Cada task é responsável por uma função de um componente do BitDogLab.
