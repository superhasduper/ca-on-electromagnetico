#define COIL1 11
#define SEN1 4
#define SEN2 5

#define LONGITUD 21.8

#define T_TIMEOUT 50
#define T_COIL1    2

bool SEN1_ant=0;
long t0=0, tSEN1=0;

void setup() {
  Serial.begin(115200);
  
  pinMode(COIL1,OUTPUT);
  
  pinMode(SEN1,INPUT);
  pinMode(SEN2,INPUT);
  
  digitalWrite(COIL1,LOW);
}

void loop() {
  Disparar();
  SEN1_Measure();
  Parar();
  Timeout();
  
  
  digitalWrite(LED_BUILTIN, digitalRead(COIL1));
}

void Disparar(){
  if(Serial.read()=='1'){
    ActualizarSensores();
    t0=micros();
    digitalWrite(COIL1,HIGH);
    Serial.println("Info: disparo iniciado T=0");
  }
}

void SEN1_Measure(){
  if(digitalRead(SEN1)==0 && digitalRead(SEN1)!= SEN1_ant && digitalRead(COIL1)==1){
    Serial.print("info: SEN1 on T=");
    Serial.println((float)(micros()-t0)/1000);
    ActualizarSensores();
  }
  if(digitalRead(SEN1)==1 && digitalRead(SEN1)!= SEN1_ant && digitalRead(COIL1)==1){
    tSEN1=micros();
    Serial.print("info: SEN1 off T=");
    Serial.println((float)(micros()-t0)/1000);
    ActualizarSensores();
  }
}

void Parar(){
  if(tSEN1!=0 && (micros()-tSEN1)/1000>=T_COIL1 && digitalRead(COIL1)==1){
    digitalWrite(COIL1,LOW);
    Serial.print("Info: disparo terminado T=");
    Serial.println((float)(micros()-t0)/1000);
    tSEN1=0;
  }
}

void Timeout(){
  if((((micros()-t0))/1000>=T_TIMEOUT || (micros()-t0)<0)&& digitalRead(COIL1)==1){
    digitalWrite(COIL1,LOW);
    Serial.print("ERROR: Timeout T=");
    Serial.println((float)(micros()-t0)/1000);
  }
}

void ActualizarSensores(){
  SEN1_ant=digitalRead(SEN1);
}
