void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.write("AT+CMGF=1\r\n");
  delay(500);
  Serial1.write("AT+CNMI=2,2,0,0,0\r\n");
  delay(500);
  Serial1.write("AT+CMGL=\"ALL\"\r\n");
  delay(5000);
}

void loop() {
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}
