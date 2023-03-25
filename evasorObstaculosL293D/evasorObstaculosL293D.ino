/*
  TRIG      Arduino pin 8
  ECHO		Arduino pin 9
  L293D.2   Arduino pin 2
  L293D.7   Arduino pin 3
  L293D.10  Arduino pin 4
  293M2.15  Arduino pin 5
*/

#define trig 8
#define echo 9
#define Motor1F 2
#define Motor1B 3
#define Motor2F 4
#define Motor2B 5

long duracion, distancia;

void setup(){
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);   //GENERA UN PULSO DE TRIGER POR 10ms
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duracion = pulseIn(echo, HIGH);
  distancia = (duracion / 2) / 29;    //CALCULA LA DISTANCIA EN cm

  if (distancia >= 500 || distancia <= 0) { //SI DISTANCIA ES MAYOR A 500cm Y MENOR DE 0cm
    Serial.println("---");
    stop();
  }
  else {
    Serial.print(distancia);  //ENTONCES SI DISTANCIA ES MENOR A 500cm Y MAYOR A 0cm
    Serial.println(" cm");    //NOS MOSTRARA EN EL MONITOR SERIAL LA DISTANCIA MEDIDA
    digitalWrite(13, LOW);    //EL LED PERMANECERA APAGADO
    foward();
  }
  if (distancia <= 10 && distancia >= 1) {  //SI LA DISTANCIA ES MENOR A 10cm
    digitalWrite(13, HIGH);                 //ENCIENDE EL LED Y NOS MUESTRA UN MSG DE
    Serial.println("Alamra......");         //ALARMA
    backward();
  }
  delay(100);
}

void foward(){
  digitalWrite(Motor1F, HIGH);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2F, HIGH);
  digitalWrite(Motor2B, LOW);
}
void stop(){
  digitalWrite(Motor1F, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2F, LOW);
  digitalWrite(Motor2B, LOW);
}

void backward(){
  digitalWrite(Motor1F, LOW);
  digitalWrite(Motor1B, HIGH);
  digitalWrite(Motor2F, LOW);
  digitalWrite(Motor2B, HIGH);
}
 
