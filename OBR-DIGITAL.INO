// Definindo os pinos dos sensores
const int sensorDireito = A0;
const int sensorEsquerdo = A1;
const int trigPin = A2;  // Porta Trigger do sensor ultrassônico
const int echoPin = A3;  // Porta Echo do sensor ultrassônico

// Definindo os pinos da ponte H
const int IN1 = 8;  // Controle da direção do motor M1 (frente)
const int IN2 = 9;  // Controle da direção do motor M1 (tras)
const int IN3 = 10; // Controle da direção do motor M2 (frente)
const int IN4 = 11; // Controle da direção do motor M2 (tras)

// Definindo os valores para controle
int valorSensorDireito = 0;
int valorSensorEsquerdo = 0;
int valorCorte = 500;  // Valor para corte dos sensores de linha

void setup() {
  // Iniciando a comunicação serial
  Serial.begin(9600);

  // Configurando os pinos como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Definindo as portas como entrada para os sensores de linha
  pinMode(sensorDireito, INPUT);
  pinMode(sensorEsquerdo, INPUT);

  // Definindo as portas do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Leitura dos sensores de linha
  valorSensorDireito = analogRead(sensorDireito);
  valorSensorEsquerdo = analogRead(sensorEsquerdo);

  // Imprimindo os valores dos sensores de linha no monitor serial
  Serial.print("Leitura Direito: ");
  Serial.print(valorSensorDireito);
  Serial.print(" | Leitura Esquerdo: ");
  Serial.println(valorSensorEsquerdo);

  // Medindo a distância com o sensor ultrassônico
  long duracao, distancia;
  
  // Limpando o trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Configurando o trigPin para HIGH por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leitura do tempo de retorno do som (echoPin)
  duracao = pulseIn(echoPin, HIGH);

  // Calculando a distância em centímetros
  distancia = duracao * 0.034 / 2;

  // Imprimindo a distância no monitor serial
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Verificando a presença de obstáculos
  if (distancia < 20) {  // Se houver um obstáculo a menos de 20 cm
    PararMotores();      // Para os motores
  } else {
    SeguirLinha();       // Continua seguindo a linha
  }

  // Aguarda um pouco antes de fazer a próxima leitura
  delay(100);
}

void SeguirLinha() {
  if ((valorSensorEsquerdo > valorCorte) && (valorSensorDireito > valorCorte)) {
    // Ambos os sensores sobre a linha, andar reto
    AndarReto();
  } else if ((valorSensorEsquerdo > valorCorte) && (valorSensorDireito < valorCorte)) {
    // Sensor esquerdo na linha, virar para a esquerda
    CurvaEsquerda();
  } else if ((valorSensorEsquerdo < valorCorte) && (valorSensorDireito > valorCorte)) {
    // Sensor direito na linha, virar para a direita
    CurvaDireita();
  } else {
    // Caso não detecte a linha, parar
    PararMotores();
  }
}

void AndarReto() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void CurvaEsquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void CurvaDireita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void PararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
