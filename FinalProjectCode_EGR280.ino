/*            
 *             Cameron Husted
 *              Ryan Fecteau
 *            Joseph DiTrapani
 *   ***Unmanned Autonomous Turret***
 *  
 *  Outside of the setup() and the loop() functions,
 *  there are only just a few major methods:
 *  
 *  checkTheDefenses() reads the piezo sensors and
 *    checks whether any of the values are greater
 *    than the threshold.
 *  readJoystick() checks to see if the joystick
 *    is being titled in either direction.
 *  createTerminator() handles the sequence of 
 *    events dealing with the autonomous control.
 *    
 */

#include <Servo.h>
int threshold = 150;                            //Piezo sensor must read a value this high to count as a hit
int angle;
const int SERVO = 3;
Servo myServo;
const int X_AXIS = 0;                           //Joystick x-axis --- analog pin # A0
const int SWITCH = 7;                           //Joystick button --- digital pin # 7
const int ELEMENT0 = 1;
const int ELEMENT45 = 2;        
const int ELEMENT90 = 3;                        //Piezo thangs on analog pins
const int ELEMENT135 = 4;
const int ELEMENT180 = 5;
const int LASER = 8;                            //Laser on Digital pin 8

void setup() {
  Serial.begin(9600);
  angle = 90;                                   //Angle starts at 90 degrees
  myServo.attach(SERVO);
  digitalWrite(SWITCH, HIGH);
  pinMode(SERVO, OUTPUT);
  pinMode(LASER, OUTPUT);
}

void loop() {
/*Serial.print(analogRead(ELEMENT0));
Serial.print("  ");
Serial.print(analogRead(ELEMENT45));
Serial.print("  ");
Serial.print(analogRead(ELEMENT90));                        //Previously used for debugging
Serial.print("  ");
Serial.print(analogRead(ELEMENT135));
Serial.print("  ");
Serial.println(analogRead(ELEMENT180));*/
checkTheDefenses();                             //Read armor plates
angle = readJoystick(X_AXIS, angle);            //See if joystick is being used
angle = constrain(angle, 0, 179);               //Make sure the angle stays within bounds the servo can write to
if (digitalRead(SWITCH) == LOW) {               //Find if joystick switch is pressed
  digitalWrite(LASER, HIGH);
}
else {
  digitalWrite(LASER, LOW);
}
myServo.write(angle);                           //Turn servo
delay(10);                                      //Refresh every 10 milliseconds
}

int readJoystick(int axis, int ang) {
  int val = analogRead(axis);
  val = map(val, 0, 1023, -100, 100);           //Make data more friendly-looking
  if (val > 30) {
    ang += 2;                                   //Increment angle by 2
    return ang;
  }
  else if (val < -30) {
    ang -= 2;                                   //Decrease angle by 2
    return ang;      
    }
    else {
      return ang;                               //Angle remains the same, if joystick is at rest
    }
}

void checkTheDefenses() {
  int plate0 = analogRead(ELEMENT0);                 //Read piezo sensors
  int plate45 = analogRead(ELEMENT45);
  int plate90 = analogRead(ELEMENT90);
  int plate135 = analogRead(ELEMENT135);
  int plate180 = analogRead(ELEMENT180);
if (plate0 > threshold) {                            //0-Degree-Plate Analysis
  Serial.println("ZERO HIT");
  createTerminator(0, plate0);
  delay(2000);
}
else if (plate45 > (threshold + 100)) {             //45-Degree-Plate Analysis
  Serial.println("FORTY FIVE HIT");
  createTerminator(45, plate45);
  delay(2000);
}
else if (plate90 > threshold) {                     //90-Degree-Plate Analysis
  Serial.println("NINETY HIT");
  createTerminator(90, plate90);
  delay(2000);
}
else if (plate135 > threshold) {                    //135-Degree-Plate Analysis
  Serial.println("ONE HUNDRED THIRTY FIVE HIT");
  createTerminator(135, plate135);
  delay(2000);
}
else if (plate180 > threshold) {                    //180-Degree-Plate Analysis
  Serial.println("ONE HUNDRED EIGHTY HIT");
  createTerminator(179, plate180);
  delay(2000);
}
}

void createTerminator(int EnemyDirection, int impactSeverity) {                 //We theorized a concept like this was how Terminator got started
  int firingTime = map(impactSeverity, 0, 1023, 1, 6);
  /*Serial.print("Plate");
  Serial.println(EnemyDirection);
  Serial.print("Impact Severity: ");               //Previously used for debugging
  Serial.println(impactSeverity);
  Serial.println(firingTime);*/
  myServo.write(EnemyDirection);                   //Turn laser to correct plate
  delay(1000);
  digitalWrite(LASER, HIGH);                       //Laser ON
  delay(firingTime*1000);                               //Length of time laser stays on
  Serial.print(firingTime);
  digitalWrite(LASER, LOW);                        //Laser OFF
  delay(50);
  angle = 90;
  myServo.write(angle);                            //Turn laser back to center
}
