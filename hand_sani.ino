//Pins connected to the ultrasonic sensor
#define trigPin  2
#define echoPin 3

//LED pins
#define ledr 11
#define ledg 10

#define pump 8

int range = 5;//range in inches

void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  //initialize the sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //initialize LED pins
  pinMode(ledr, OUTPUT);
  pinMode(ledg, OUTPUT);

  pinMode(pump, OUTPUT);

  //set LEDs
  digitalWrite(ledg, HIGH);
  digitalWrite(ledr, LOW);  
  digitalWrite(pump, LOW);
}

void loop()
{
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  // Take reading on echo pin
  duration = pulseIn(echoPin, HIGH);
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if(inches < 2.5) {
    Serial.println("hand sanitized");
    digitalWrite(ledr, HIGH);
    digitalWrite(ledg, HIGH);
    digitalWrite(pump, HIGH);
    delay(200);
    digitalWrite(pump, LOW);
  } 
  else {
    Serial.println("no hand");
     digitalWrite(ledr, LOW);
     digitalWrite(ledg, HIGH);
     digitalWrite(pump, LOW);
     delay(200);
  }  
  delay(1000);
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
