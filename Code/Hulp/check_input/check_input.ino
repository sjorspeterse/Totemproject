void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(15,INPUT);
  pinMode(19,INPUT);
  pinMode(23,INPUT);
  pinMode(27,INPUT);
  pinMode(31,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(11));
  Serial.print(" ");
  Serial.print(digitalRead(15));
  Serial.print(" ");
  Serial.print(digitalRead(19));
  Serial.print(" ");
  Serial.print(digitalRead(23));
  Serial.print(" ");
  Serial.print(digitalRead(27));
  Serial.print(" ");
  Serial.println(digitalRead(31));

}
