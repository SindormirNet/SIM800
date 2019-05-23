
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  configura_bearer();
  envio_mail();
}

void loop() {
}

void configura_bearer() {
  Serial1.write("AT+CREG?\r\n");
  delay(100);
  Serial1.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");
  delay(100);
  Serial1.write("AT+SAPBR=3,1,\"APN\",\"orangeworld\"\r\n");
  delay(100);
  Serial1.write("AT+SAPBR=1,1\r\n");
  delay(100);
  Serial1.write("AT+SAPBR=2,1\r\n");
  delay(100);
  Serial1.write("AT+CGATT=1\r\n");
  delay(100);
  Serial.println("Configuracion terminada");
  delay(100);
}

void envio_mail() {
  Serial1.write("AT+EMAILCID=1\r\n");
  delay(100);
  Serial1.write("AT+EMAILTO=30\r\n");
  delay(100);
  Serial1.write("AT+SMTPSRV=\"mail.sindormir.net\",25\r\n");            //configura direccion SMTP y puerto
  delay(100);
  Serial1.write("AT+SMTPAUTH=1,\"omnivision\",\"3938s827\"\r\n");         //configura nombre de usuario y contraseña
  delay(100);
  Serial1.write("AT+SMTPFROM=\"omnivision@sindormir.net\",\"omnivision\"\r\n");     //From
  delay(100);
  Serial1.write("AT+SMTPRCPT=0,0,\"guillermo@sindormir.net\",\"guillermo\"\r\n"); //To
  delay(100);
  Serial1.write("AT+SMTPSUB=\"Asunto\"\r\n");                       //Subject
  delay(100);
  Serial1.write("AT+SMTPBODY=15\r\n");                            //Cuerpo del Mail
  delay(100);
  Serial1.write("Esto es un mail nuevo\r\n");                       //Contenido del cuerpo
  delay(100);
  Serial1.write("AT+SMTPSEND\r\n");
  delay(100);
  Serial.println("Mail enviado");
}

