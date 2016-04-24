// Assume long integers are at least 32 bits.
// Park clock and data low when not in use.
// Switch value = LOW closed, HIGH open.

// begin customizing here

#define LE_PIN 10
#define CLK_PIN 11
#define DATA_PIN 12

#define SWITCH_PIN 9

#define REGISTER_5_OPEN 0x00580005U
#define REGISTER_4_OPEN 0x00B500FCU
#define REGISTER_3_OPEN 0x000004B3U
#define REGISTER_2_OPEN 0x00004E42U
#define REGISTER_1_OPEN 0x08008011U
#define REGISTER_0_OPEN 0x00A00000U

#define REGISTER_5_CLOSED 0x00580005U
#define REGISTER_4_CLOSED 0x00B500FCU
#define REGISTER_3_CLOSED 0x000004B3U
#define REGISTER_2_CLOSED 0x00004E42U
#define REGISTER_1_CLOSED 0x08008011U
#define REGISTER_0_CLOSED 0x00A00000U

// end customizing here

#define DELAY 1

void setup_ports() {
  pinMode(LE_PIN, OUTPUT);
  digitalWrite(LE_PIN, HIGH);

  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  digitalWrite(CLK_PIN, LOW);
  digitalWrite(DATA_PIN, LOW);

  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

int read_switch() {
  int sample1;
  int sample2;
  int sample3;

  for (;;) {
    sample1 = digitalRead(SWITCH_PIN);
    sample2 = digitalRead(SWITCH_PIN);
    sample3 = digitalRead(SWITCH_PIN);
    if (sample1 == sample2 && sample2 == sample3) break;
  }
  return sample1;
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

void write_synthesizer(int switch_value) {
  if (switch_value == HIGH) {
    write_register(REGISTER_5_OPEN);
    write_register(REGISTER_4_OPEN);
    write_register(REGISTER_3_OPEN);
    write_register(REGISTER_2_OPEN);
    write_register(REGISTER_1_OPEN);
    write_register(REGISTER_0_OPEN);
  }
  else {
    write_register(REGISTER_5_CLOSED);
    write_register(REGISTER_4_CLOSED);
    write_register(REGISTER_3_CLOSED);
    write_register(REGISTER_2_CLOSED);
    write_register(REGISTER_1_CLOSED);
    write_register(REGISTER_0_CLOSED);
  }
}

int last_value;
int current_value;

void setup() {
  setup_ports();
  delay(1000);
  last_value = read_switch();
  write_synthesizer(last_value);
}

void loop() {
  current_value = read_switch();
  if (current_value != last_value) {
    write_synthesizer(current_value);
    last_value = current_value;
  }
}
