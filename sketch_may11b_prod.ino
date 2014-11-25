int bit2btn[16] = {
  7, 11, 10,  6,  9,  5,  1,  2, // D3
  -1, -1, -1, -1,  8, 12,  3,  4  // D4
};

int latch = 2; // set the latch pin
int clock = 3; // set the clock pin
int data3 = 5;
int data4 = 6;

byte controller_data3 = 0;
byte controller_data4 = 0;

byte buttons[4*3 + 1];

void setup() {
  Serial.begin(9600);
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);

  pinMode(data3,INPUT);
  pinMode(data4,INPUT);

  digitalWrite(latch,HIGH);
  digitalWrite(clock,HIGH);
}

/* POWER PAD READ */
void data2button() {
  controller_data3 = 0;
  controller_data4 = 0;
  digitalWrite(latch,LOW);
  digitalWrite(clock,LOW);

  digitalWrite(latch,HIGH);
  delayMicroseconds(2);

  if (digitalRead(data3) == 0) {
    buttons[bit2btn[7]] = true;
  } 
  else {
    buttons[bit2btn[7]] = false;
  }
  if (digitalRead(data4) == 0) {
    buttons[bit2btn[15]] = true;
  } 
  else {
    buttons[bit2btn[15]] = false;
  }

  digitalWrite(latch,LOW);

  for (int i = 1; i <= 7; i++) {
    digitalWrite(clock,HIGH);
    delayMicroseconds(2);

    if (digitalRead(data3) == 0) {
      buttons[bit2btn[7-i]] = true;
    } 
    else {
      buttons[bit2btn[7-i]] = false;
    }
    if (digitalRead(data4) == 0) {
      if (bit2btn[15-i] != -1) {
        buttons[bit2btn[15-i]] = true;
      }
    } 
    else {
      buttons[bit2btn[15-i]] = false;
    }

    delayMicroseconds(4);
    digitalWrite(clock,LOW);
  }
}

void printButtons() {
  String signal = String(27);
  signal = String("s,");
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 4; col++) {
      signal += String(buttons[row*4 + col + 1]) + ",";
    }
  }
  signal += String("e,");
  Serial.print(signal);
}

void loop() {
  data2button();
  printButtons();
  delay(10);
}
