
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  configura_bearer();
}

void loop() {
  int var0 = analogRead(A0);
  int var1 = analogRead(A0);
  int var2 = analogRead(A0);
  envia_dato_http(var0, var1, var2);
  delay(1000);
}

void configura_bearer() {
  Serial1.write("AT+CREG?\r\n");                  //comprueba el estado de la red
  delay(100);
  Serial1.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");
  delay(100);
  Serial1.write("AT+SAPBR=3,1,\"APN\",\"orangeworld\"\r\n");
  delay(100);
  Serial1.write("AT+SAPBR=1,1\r\n");
  delay(100);
  Serial1.write("AT+SAPBR=2,1\r\n");
  delay(100);
  Serial1.write("AT+CGATT=1\r\n");                  //enciende GPRS
  delay(100);
  Serial.println("Configuracion terminada");
}

void envia_dato_http(int dato0, int dato1, int dato2) {
  Serial1.write("AT+HTTPINIT\r\n");
  delay(100);
  Serial1.write("AT+HTTPPARA=\"CID\",1\r\n");
  delay(100);
  Serial1.write("AT+HTTPPARA=\"URL\",");
  delay(100);

  Serial1.write("\"iot.sindormir.net/omni/datos.php?");
  Serial1.write("A0=");
  Serial1.print(dato0);
  Serial1.write("&");
  Serial1.write("A1=");
  Serial1.print(dato1);
  Serial1.write("&");
  Serial1.write("A2=");
  Serial1.print(dato2);
  Serial1.write("\"\r\n");

  delay(100);

  Serial1.write("AT+HTTPDATA=100,100\r\n");
  delay(100);
  Serial1.write("AT+HTTPACTION=1\r\n");
  delay(100);
  Serial1.write("AT+HTTPTERM\r\n");
  delay(100);
  Serial.println("DATOS ENVIADOS");
}

