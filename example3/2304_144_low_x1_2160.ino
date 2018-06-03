// Assume long integers are at least 32 bits.
// Park clock and data low when not in use.

// begin customizing here

#define LE_PIN 10
#define CLK_PIN 11
#define DATA_PIN 12

// end customizing here

#define REGISTER_5 0x00580005U
#define REGISTER_4 0x009A01FCU
#define REGISTER_3 0x000004B3U
#define REGISTER_2 0x02004E42U
#define REGISTER_1 0x08008011U
#define REGISTER_0 0x006C0000U

#define DELAY 1

void setup_ports() {
  pinMode(LE_PIN, OUTPUT);
  digitalWrite(LE_PIN, HIGH);

  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  digitalWrite(CLK_PIN, LOW);
  digitalWrite(DATA_PIN, LOW);
}

void write_register(unsigned long value) {
  digitalWrite(LE_PIN, LOW);
  delayMicroseconds(DELAY);
  for (int i=31; i >= 0; i--) {
    if ((value >> i) & 1)
      digitalWrite(DATA_PIN, HIGH);
    else
      digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(DELAY);
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(DELAY);
    digitalWrite(CLK_PIN, LOW);
    delayMicroseconds(DELAY);
  }
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(LE_PIN, HIGH);
  delayMicroseconds(DELAY);
}

void setup() {
  setup_ports();
  delay(1000);
  write_register(REGISTER_5);
  write_register(REGISTER_4);
  write_register(REGISTER_3);
  write_register(REGISTER_2);
  write_register(REGISTER_1);
  write_register(REGISTER_0);
}

void loop() {
}
