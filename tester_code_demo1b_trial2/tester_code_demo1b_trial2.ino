//* Code by Team A1 
// * - Saumyaa Balakanthan
// * - William Grant
// * - Connor Harvey
// * - Duane Johnston 
// * - Yang Yang
// */


// Give each pin a descriptive name
#define S1 A0 
#define S2 A1 
#define S3 A2 //this is the 4th sensor from the right (might be the other way around
#define S4 A3 //this is the 4th sensor from the left
#define S5 A4
#define S6 A5

#define IN1 1 
#define IN2 2
#define IN3 3
#define IN4 4
#define ENA 5
#define ENB 6

// Globals
using namespace std;
// int sensor1, sensor2, sensor3, sensor4, sensor5, sensor6;

// Set forward driving speed default(fast)
int driving_speed = 210;

//bool for the fast or slow
bool fast = true;

//set fast driving speed
int fast_speed = 210;

//set slow driving speed
int slow_speed = 110;

//set stopped driving speed
int stop_speed = 0;

// Define a threshold for line sensing
int threshold = 600;

//list for the error recovery function

//initialise the list:
char ERROR_ARRAY[] = {'S','S','S','S'};
//S = stop
//F = forwards
//L = left
//R = right

// Function List //
void go_fast(){
  return;
}
void go_slow(){
  return;
}

// Sets the outputs to Motor driver to drive foreward
void drive_forward(){
  // Set Input pins on H-Bridge to Forward on both motors
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  return;
}
void drive_backwards(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  return;
}
void drive_right(){
  //fill in with how to make it turn right
  return;
}
void drive_left() {
  //fill in with how to make it turn left
  return;
}
void drive_backwards_right(){
  //fill in with how to make it turn backwards right
  return;
}
void drive_backwards_left(){
  //fill in with how to make it turn backwards left
  return;
}
void stop_moving(){
  //fill in with how to make it stop moving
  return;
}
//making a function to update the array:
void update_array(char LastMove){
  ERROR_ARRAY[0] = ERROR_ARRAY[1];
  ERROR_ARRAY[1] = ERROR_ARRAY[2];
  ERROR_ARRAY[2] = ERROR_ARRAY[3];
  ERROR_ARRAY[3] = LastMove; 
}

//fills the array with Stop commands 1 slot at a time:
void reset_array(){
  ERROR_ARRAY[3] = ERROR_ARRAY[2];
  ERROR_ARRAY[2] = ERROR_ARRAY[1];
  ERROR_ARRAY[1] = ERROR_ARRAY[0];
  ERROR_ARRAY[0] = 'S'; 
  
}
//error recovery function:
void error_recover(){
 for(int i =0; i<=4; i++){
  if(ERROR_ARRAY[3]=='F'){
    drive_backwards();
    delay(250);
  }
  else if(ERROR_ARRAY[3]=='R'){
    drive_backwards_right();
    delay(250);
  }
  else if(ERROR_ARRAY[3]=='L'){
    drive_backwards_left();
    delay(250);
  }
  else if(ERROR_ARRAY[3]=='S'){
    stop_moving();
    delay(250);
  }
  reset_array();
 }
}

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
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  // Start serial monitor
  Serial.begin(9600);  

  //set the speed to fast
  bool fast = true;

  //adjust light levels///////////////////////////////////////////////////////not done//////////////////////////////////////////
}
//now for the line scanning logic////////////////////////////////////////////////not done, all movement is not currently working, and the outer sensors arent currently attatched///////////////////////////////////////////////////////
void loop() {
  {
  
//when it sees a line on the outside either speed up or slow down (only allow this if the robot is on the centre line otherwise adjust first)
   if (analogRead(S1)<=threshold && analogRead(S3)<=threshold && analogRead(S4)<=threshold) //Go faster/ if faster go slower.
    if ( fast=true){
      //make anchor go fast
      driving_speed=fast_speed;
    }
    else if (fast=false){
      //make anchor go slowly
      driving_speed=slow_speed;
    }
   fast = !fast;
   }
   
//when it sees the line under the two middle sensors go forwards or when it encounters a line under the two middle sensors and under the two outer sensors also go forwards
   if ((analogRead(S3)<=threshold && analogRead(S4)<=threshold) || (analogRead(S3)<=threshold && analogRead(S4)<=threshold && analogRead(S1)<=threshold && !analogRead(S6)<=threshold)) //go forward Anchor!
  {
    Serial.println("Anchor is going Forward");
    analogWrite(ENA, driving_speed);
    analogWrite(ENB, driving_speed);
    drive_forward();
    update_array('F');
  } 

//when it encounters error adjust left or right

//adjust right
    else if(!analogRead(S4)<=threshold && analogRead(S3)<=threshold)
  {
    Serial.println("Anchor is turning right");
    //Serial.println(S6)
    analogWrite(ENA, driving_speed);
    analogWrite(ENB, driving_speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    update_array('R');
  }
  
//adjust left
    else if(!analogRead(S3)<=threshold && analogRead(S4)<=threshold)
  {
    Serial.println("Anchor is turning left");
    //Serial.println(S6)
    analogWrite(ENA, driving_speed);
    analogWrite(ENB, driving_speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    update_array('L');
  }
  
//then if there is no line stop (and then after a couple seconds start error recovery process)
  else if(!analogRead(S6)<=threshold && !analogRead(S1)<=threshold && !analogRead(S3)<=threshold && !analogRead(S4)<=threshold) //STOP Anchor!
  {
    Serial.println("Anchor is not moving");
    analogWrite(ENA, stop_speed);
    analogWrite(ENB, stop_speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    //start error recovery
    update_array('S');
  }
}
