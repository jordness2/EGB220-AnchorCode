/* Code by Team A1 
 * - Duane Johnston 
 * - Saumyaa Balakanthan
 * - Yang Yang
 * - Connor Harvey
 * - William Grant
 */

// Give each pin a descriptive name
#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4
#define S6 A5
#define IN1 1 
#define IN2 2
#define IN3 3
#define IN4 4
#define ENA 5
#define ENB 6

// Globals

// int sensor1, sensor2, sensor3, sensor4, sensor5, sensor6;

// Set foreward driving speed
int driving_speed = 210;

// Define a threshold for line sensing
int threshold = 600;

void setup() {
  // Set pin I/O status
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  // Start serial monitor
  Serial.begin(9600);  
}

void loop() {
  // If the left and Right sensor are reading white, Drive foreward.
  if (analogRead(S6)<=threshold && analogRead(S1)<=threshold) //go forward Anchor!
  {
    Serial.println("Anchor is going Forward");
    analogWrite(ENA, driving_speed);
    analogWrite(ENB, driving_speed);
    drive_forward();  
  }  

  // Else if the right sensor is reading the line turn right to correct
  else if(!analogRead(S6)<=threshold && analogRead(S1)<=threshold) //turn right Anchor!
  {
    Serial.println("Anchor is turning right");
    //Serial.println(S6)
    analogWrite(ENA, 254);
    analogWrite(ENB, 254);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  // Else if the left sensor is reading the line turn left to correct
  else if(analogRead(S6)<=threshold && !analogRead(S1)<=threshold) //turn left Anchor!
  {
    Serial.println("Anchor is turning left");
    analogWrite(ENA, 254);
    analogWrite(ENB, 254);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  // Else if not reading any surface stop all movement
  else if(!analogRead(S6)<=threshold && !analogRead(S1)<=threshold) //STOP Anchor!
  {
    Serial.println("Anchor is not moving");
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

// Function List //

// Sets the outputs to Motor driver to drive foreward
void drive_forward(){
  // Set Input pins on H-Bridge to Forward on both motors
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  return;
}
