const int X_AXIS = 0;
const int BUTTON = 7;
int i;

void setup() {
  Serial.begin(9600);
  digitalWrite(BUTTON, HIGH);
  i = 0;
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    i ++;
    Serial.print("Button Pressed");
    Serial.println(i);
  }
  delay(250);
  }
