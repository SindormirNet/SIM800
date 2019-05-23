bool ledStatus = false;
char currentLine[500] = "";         //Guarda la ultima linea recibida en el SIM800
int currentLineIndex = 0;
bool nextLineIsMessage = false;   //Pasa a ser true cuando detecta una mensaje entrante

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledStatus);
  Serial1.write("AT+CMGF=1\r\n");                       
  Serial1.write("AT+CNMI=1,2,0,0,0\r\n"); 
}

void loop() {
  digitalWrite(LED_BUILTIN, ledStatus);          //Enciende o apaga el LED                   
  parseo(); 
}

void parseo() {
  while (Serial1.available()) {
    char lastCharRead = Serial1.read();
    //Lee cada caracter recibido hasta encontrar un intro y retorno de carro
    if (lastCharRead == '\r' || lastCharRead == '\n') {
      String lastLine = String(currentLine);

      if (lastLine.startsWith("+CMT:")) {
        Serial.println(lastLine);
        nextLineIsMessage = true;

      } 
      else if (lastLine.length() > 0) {

        if (nextLineIsMessage) {
          Serial.println(lastLine);

          //Detecta si la llamada proviene del número correcto
          if (lastLine.indexOf("LED ON") >= 0) {
            ledStatus = 1;
          } 
          else if (lastLine.indexOf("LED OFF") >= 0) {
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

