#define COIL1 11


void setup() {
  Serial.begin(9600);
  pinMode(COIL1,OUTPUT);
  digitalWrite(COIL1,LOW);
}

void loop() {
  if(Serial.read()=='1'){
    digitalWrite(COIL1,HIGH);
    digitalWrite(LED_BUILTIN, digitalRead(COIL1));
    delay(5);
    digitalWrite(COIL1,LOW);
    digitalWrite(LED_BUILTIN, digitalRead(COIL1));
    Serial.println("ok!");
  }
}
