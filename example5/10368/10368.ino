// Assume long integers are at least 32 bits.
// Park clock and data low when not in use.

// begin customizing here

#define LE_PIN 10
#define CLK_PIN 11
#define DATA_PIN 12
#define KEY_PIN 5
#define SIDETONE_PIN 3

#define SIDETONE_FREQ 700

#define REGISTER_5 0x00580005U
// see below for REGISTER_4
#define REGISTER_3 0x000004B3U
#define REGISTER_2 0x02004E42U
#define REGISTER_1 0x08008C81U
#define REGISTER_0 0x00560A08U

#define KEYDOWN    0X008A003CU
#define KEYDOWN_M3 0X008A0034U
#define KEYDOWN_M6 0X008A002CU
#define KEYDOWN_M9 0X008A0024U
#define KEYUP      0X008A0004U
#define REGISTER_4 KEYUP
// end customizing here

#define DELAY 1

void setup_ports() {
  pinMode(LE_PIN, OUTPUT);
  digitalWrite(LE_PIN, HIGH);

  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  digitalWrite(CLK_PIN, LOW);
  digitalWrite(DATA_PIN, LOW);

  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);

  // sidetone on SIDETONE_PIN

  pinMode(KEY_PIN, INPUT_PULLUP);
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

void shaped_keydown() {
  tone(SIDETONE_PIN, SIDETONE_FREQ);
  digitalWrite(LED_BUILTIN, HIGH);
  write_register(KEYDOWN_M9);
  write_register(KEYDOWN_M6);
  write_register(KEYDOWN_M3);
  write_register(KEYDOWN);
}

void shaped_keyup() {
  write_register(KEYDOWN_M3);
  write_register(KEYDOWN_M6);
  write_register(KEYDOWN_M9);
  write_register(KEYUP);
  digitalWrite(LED_BUILTIN, LOW);
  noTone(SIDETONE_PIN);
}

int read_key() {
  int sample1;
  int sample2;
  for (;;) {
    sample1 = digitalRead(KEY_PIN);
    sample2 = digitalRead(KEY_PIN);
    if (sample1 == sample2) break;
  }

  return sample1;
}

int last_key;

void setup() {
  setup_ports();
  delay(1000);
  write_register(REGISTER_5);
  write_register(REGISTER_4);
  write_register(REGISTER_3);
  write_register(REGISTER_2);
  write_register(REGISTER_1);
  write_register(REGISTER_0);
  last_key = read_key();
  if (last_key == LOW) {
    shaped_keydown();
  }
}

int current_key;

void loop() {
  current_key = read_key();
  if (current_key != last_key) {
    if (current_key == LOW) {
      shaped_keydown();
    }
    else {
      shaped_keyup();
    }
    last_key = current_key;
  }
}
