# Sistemas-Embebidos---TW2---GreenSense-Solutions-



🌱 Sistema Automatizado de Rega e Monitorização de Estufa

Sistema embebido desenvolvido para monitorização e controlo automático de uma estufa agrícola. O sistema lê dados de temperatura, humidade e nível de água, atuando sobre válvulas de irrigação e ventilação de forma autónoma, com interface de utilizador via LCD e joystick.

📋 Funcionalidades

- Monitorização contínua de temperatura (DS18B20)
- Controlo automático de irrigação via servo motor
- Controlo de ventilação via motor de passo (step motor)
- Deteção do nível de água no reservatório (HC-SR04)
- Alertas visuais (LEDs) e sonoros (buzzer) para condições críticas
- Interface de menu navegável em LCD 16x2 via joystick
- Ativação manual do sistema através de botão físico


🔧 Hardware utilizado

| Componente | Função |
|-----------|--------|
| DS18B20 | Sensor de temperatura da estufa |
| HC-SR04 | Sensor ultrassónico — medição do nível de água |
| Servo Motor | Controlo da válvula de irrigação |
| Step Motor | Controlo das aberturas de ventilação |
| Display LCD 16x2 (I2C) | Interface de informação ao utilizador |
| Joystick | Navegação no menu LCD |
| Buzzer | Alerta sonoro de temperatura crítica |
| LEDs | Indicadores visuais de estado |
| Push Button | Liga/desliga o sistema |


🏗️ Arquitetura do sistema

┌─────────────────────────────────────────────────┐
│               Microcontrolador                  │
│                                                 │
│  Sensores            Atuadores                  │
│  ─────────           ──────────                 │
│  DS18B20  ──────────► Servo (irrigação)         │
│  HC-SR04  ──────────► Step Motor (ventilação)   │
│  Joystick ──────────► LCD 16x2 (menu)           │
│  Button   ──────────► Buzzer + LEDs (alertas)   │
└─────────────────────────────────────────────────┘


⚙️ Lógica de controlo

**Temperatura**
- Leitura contínua via DS18B20  
- Se temperatura > limite máximo → buzzer ativa + LED vermelho + step motor abre ventilação  
- Valor exibido em tempo real no LCD  

**Nível de água**
- HC-SR04 mede a distância ao nível da água  
- Se nível baixo → alerta no LCD + LED amarelo  
- Se nível acima do máximo → alerta no LCD  

**Irrigação**
- Servo motor ativa/desativa a válvula com base na humidade do solo (simulada)  
- Pode também ser controlado manualmente através do menu  

**Menu LCD**
- Navegação com joystick (cima / baixo / selecionar)  
- Opções:
  - Ver temperatura  
  - Ver nível de água  
  - Ativar/desativar irrigação  
  - Estado geral  


🚀 Como correr

1. Instalar o Arduino IDE  
2. Instalar as bibliotecas necessárias (Sketch → Include Library → Manage Libraries):
   - OneWire  
   - DallasTemperature  
   - LiquidCrystal_I2C  
   - Servo  
   - Stepper  

3. Ligar o hardware conforme o esquema em `docs/esquema_ligacoes.png`  
4. Fazer upload do `src/TW2-SE.ino` para o microcontrolador  
5. Abrir o Serial Monitor (9600 baud) para debug  


🖼️ Demonstração

(docs/imagem.png)


🎓 Contexto académico

Projeto desenvolvido no âmbito da unidade curricular de Sistemas Embebidos, com o objetivo de simular um sistema real de monitorização agrícola utilizando microcontroladores e diversos componentes de hardware.


👤 Autor

Ruben Gomes  
https://github.com/RubenCG21
