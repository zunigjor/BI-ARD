int led = 13;
int openV = 10;
int closeV = 9;
void setup() {                
  pinMode(led, OUTPUT);
  pinMode(openV, OUTPUT);
  pinMode(closeV, OUTPUT);
  digitalWrite(openV, LOW);
  digitalWrite(closeV, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);
  digitalWrite(openV, HIGH);
  digitalWrite(closeV, LOW);
  delay(4000);
  digitalWrite(led, LOW);
  digitalWrite(openV, LOW);
  digitalWrite(closeV, HIGH);
  delay(4000);
}
