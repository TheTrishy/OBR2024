// Definindo as portas dos sensores
const int sensorDireto = A0;
const int sensorEsquerdo = A1;
const int trigPin = A2;  // Porta Trigger do sensor ultrassônico
const int echoPin = A3;  // Porta Echo do sensor ultrassônico
const int Velocidade1 = 5;
const int Velocidade2 = 6;
const int Direcao1 = 4;
const int Direcao2 = 7;

int Valor_Sensor = 0;
int Valor_Corte = 700;
int SensorEsquerdo = 0;
int SensorDireito = 0;

void setup() {
  // Iniciando a comunicação serial
  Serial.begin(9600);

  // Definindo as portas como entrada para os sensores de linha
  pinMode(sensorDireto, INPUT);
  pinMode(sensorEsquerdo, INPUT);

  // Definindo as portas do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configurando portas de controle do motor
  pinMode(Velocidade1, OUTPUT);
  pinMode(Velocidade2, OUTPUT);
  pinMode(Direcao1, OUTPUT);
  pinMode(Direcao2, OUTPUT);

  // Configurações iniciais
  Saida_Digital();
}

void loop() {
  // Exemplo de leitura de sensores e execução de movimento
  Leitura_Sensor_N(1);
  SensorEsquerdo = Valor_Sensor;
  Leitura_Sensor_N(2);
  SensorDireito = Valor_Sensor;

  Serial.print("Esquerdo: ");
  Serial.println(SensorEsquerdo);
  Serial.print("Direito: ");
  Serial.println(SensorDireito);

  Andar_Reto();
  Curva_Direita();
  Curva_Esquerda();

  delay(500);
}

void Saida_Digital(){
  analogWrite(Velocidade1, 155);
  analogWrite(Velocidade2, 155);
  digitalWrite(Direcao1, HIGH);
  digitalWrite(Direcao2, HIGH);
}

void Leitura_Sensor_N(int sensor) {
  if (sensor == 1) {
    Valor_Sensor = analogRead(sensorEsquerdo);
  } else if (sensor == 2) {
    Valor_Sensor = analogRead(sensorDireto);
  }
}

void Andar_Reto(){
  if(((SensorEsquerdo > Valor_Corte)  &&  (SensorDireito > Valor_Corte))  ||  ((SensorEsquerdo < Valor_Corte)  &&  (SensorDireito < Valor_Corte))){
    digitalWrite(Direcao1, LOW);
    digitalWrite(Direcao2, LOW);
    analogWrite(Velocidade1, 155);
    analogWrite(Velocidade2, 155);
  }
}

void Curva_Direita(){
  if((SensorEsquerdo < Valor_Corte)  &&  (SensorDireito > Valor_Corte)){
    digitalWrite(Direcao1, LOW);
    digitalWrite(Direcao2, HIGH);
    analogWrite(Velocidade1, 155);
    analogWrite(Velocidade2, 155);
  }
}

void Curva_Esquerda(){
  if((SensorEsquerdo > Valor_Corte)  &&  (SensorDireito < Valor_Corte)){
    digitalWrite(Direcao1, HIGH);
    digitalWrite(Direcao2, LOW);
    analogWrite(Velocidade1, 155);
    analogWrite(Velocidade2, 155);
  }
}
