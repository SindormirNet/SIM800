void setup() {
  Serial1.begin(9600);
}

void loop() {
  Serial1.write("ATD+34676124XXX;\r\n");
  delay(7000);
  Serial1.write("ATH\r\n");
  delay(2000);
}

