void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.write("AT+CMGF=1\r\n");                  //configuramos el modo texto
  Serial1.write("AT+CMGS=\"+34676124XXX\"\r\n");  //número al que mandamos el mensaje
  delay(500);
  Serial1.write("MI SMS");                          //mensaje
  delay(500);
  Serial1.write((char)26);  //Equivale a CNTRL+Z                      
}

void loop() {
}
