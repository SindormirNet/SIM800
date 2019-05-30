bool ledStatus = false;
char currentLine[500] = "";     //Guarda la ultima linea recibida en el SIM800
int currentLineIndex = 0;
bool nextLineIsMessage = false; //Pasa a ser true cuando detecta una llamada entrante

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledStatus);
  configura_bearer();
}

void loop() {
  digitalWrite(LED_BUILTIN, ledStatus);     //Enciende o apaga el LED
  Serial1.write("AT+HTTPINIT\r\n");
  delay(100);
  Serial1.write("AT+HTTPPARA=\"CID\",1\r\n");
  delay(100);
  Serial1.write("AT+HTTPPARA=\"URL\",\"iot.sindormir.net/omni/omni.html\"\r\n");
  delay(100);
  Serial1.write("AT+HTTPACTION=0\r\n");
  delay(100);
  Serial1.write("AT+HTTPREAD\r\n");
  delay(100);
  parseo();
  Serial1.write("AT+HTTPTERM\r\n");
  delay(100);
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

void parseo() {
  while (Serial1.available()) {
    char lastCharRead = Serial1.read();
    //Lee cada caracter recibido hasta encontrar un intro y retorno de carro
    if (lastCharRead == '\r' || lastCharRead == '\n') {
      String lastLine = String(currentLine);

      if (lastLine.startsWith("+HTTPREAD")) {
        Serial.println(lastLine);
        nextLineIsMessage = true;

      } 
      else if (lastLine.length() > 0) {

        if (nextLineIsMessage) {
          Serial.println(lastLine);

          //Detecta si la llamada proviene del numero correcto
          if (lastLine.indexOf("[OMNI] ENCENDER") >= 0) {
            ledStatus = 1;
          } 
          else (lastLine.indexOf("[OMNI] APAGAR") >= 0) { 
            ledStatus = 0;
          }

          nextLineIsMessage = false;
        }

      }
      //Borra el array para habilitar la lectura de una nueva línea
      for ( int i = 0; i < sizeof(currentLine);  ++i ) {
        currentLine[i] = (char)0;
      }
      currentLineIndex = 0;
    } 
    else {
      currentLine[currentLineIndex++] = lastCharRead;
    }
  }
}

