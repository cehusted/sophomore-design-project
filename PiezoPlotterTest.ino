int Sensor = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(Sensor));
  if(Serial.available() > 0){
    int incomingByte = Serial.read();
    Serial.println(incomingByte);
  }
}