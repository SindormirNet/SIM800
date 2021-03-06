bool ledStatus = false;
char currentLine[500] = "";     //Guarda la ultima linea recibida en el SIM800
int currentLineIndex = 0;
bool nextLineIsMessage = false; //Pasa a ser true cuando detecta una llamada entrante

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledStatus);
}

void loop() {
  //Enciende o apaga el LED
  digitalWrite(LED_BUILTIN, ledStatus);
  parseo();
}

void parseo() {
  while (Serial1.available()) {
    char lastCharRead = Serial1.read();
    //Lee cada caracter recibido hasta encontrar un intro y retorno de carro
    if (lastCharRead == '\r' || lastCharRead == '\n') {
      String lastLine = String(currentLine);

      if (lastLine.startsWith("RING")) {
        Serial.println(lastLine);
        nextLineIsMessage = true;

      } 
      else if (lastLine.length() > 0) {

        if (nextLineIsMessage) {
          Serial.println(lastLine);

          //Detecta si la llamada proviene del numero correcto
          if (lastLine.indexOf("+CLIP: \"676124XXX\"") >= 0) {
            ledStatus = 1;
            Serial1.write("ATA\r\n");                       //Descuelga la llamada
            delay(2000);
            Serial1.write("ATH\r\n");                       //finaliza la llamada
          } 
          else {
            ledStatus = 0;
            Serial1.write("ATH\r\n");                       //finaliza la llamada
          }

          nextLineIsMessage = false;
        }

      }
      //Borra el array para habilitar la lectura de una nueva linea
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

