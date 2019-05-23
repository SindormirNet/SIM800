void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  configura_bearer() ;
}

void loop() {
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }

  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}

void configura_bearer() {
  Serial1.write("AT+CREG?\r\n");
  delay(500);
  Serial1.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");
  delay(500);
  Serial1.write("AT+SAPBR=3,1,\"APN\",\"orangeworld\"\r\n");
  delay(500);
  Serial1.write("AT+SAPBR=1,1\r\n");
  delay(500);
  Serial1.write("AT+SAPBR=2,1\r\n");
  delay(500);
  Serial1.write("AT+CGATT=1\r\n");
  delay(500);
  Serial.println("Configuracion terminada");
  delay(500);
}
