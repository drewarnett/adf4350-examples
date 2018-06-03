// Assume long integers are at least 32 bits.
// Park clock and data low when not in use.

// begin customizing here

#define LE_PIN 10
#define CLK_PIN 11
#define DATA_PIN 12

#define REREAD_SWITCH_PIN 6
#define FREQ_SWITCH_PIN_3 5
#define FREQ_SWITCH_PIN_2 4
#define FREQ_SWITCH_PIN_1 3
#define FREQ_SWITCH_PIN_0 2

// end customizing here

#define REGISTER_5_10368 0x00580005U
#define REGISTER_4_10368 0x008A01FCU
#define REGISTER_3_10368 0x000004B3U
#define REGISTER_2_10368 0x02004E42U
#define REGISTER_1_10368 0x08008029U
#define REGISTER_0_10368 0x00550010U

#define REGISTER_5_5760 0x00580005U
#define REGISTER_4_5760 0x008A01FCU
#define REGISTER_3_5760 0x000004B3U
#define REGISTER_2_5760 0x02004E42U
#define REGISTER_1_5760 0x08008029U
#define REGISTER_0_5760 0x00460010U

#define REGISTER_5_3456 0x00580005U
#define REGISTER_4_3456 0x008A01FCU
#define REGISTER_3_3456 0x000004B3U
#define REGISTER_2_3456 0x02004E42U
#define REGISTER_1_3456 0x08008029U
#define REGISTER_0_3456 0x00528018U

#define REGISTER_5_3400 0x00580005U
#define REGISTER_4_3400 0x008A01FCU
#define REGISTER_3_3400 0x000004B3U
#define REGISTER_2_3400 0x02004E42U
#define REGISTER_1_3400 0x08008029U
#define REGISTER_0_3400 0x00510020U

#define REGISTER_5_2304 0x00580005U
#define REGISTER_4_2304 0x009A01FCU
#define REGISTER_3_2304 0x000004B3U
#define REGISTER_2_2304 0x02004E42U
#define REGISTER_1_2304 0x08008011U
#define REGISTER_0_2304 0x006C0000U

#define SWITCH_10368 0
#define  SWITCH_5760 1
#define  SWITCH_3456 2
#define  SWITCH_3400 4
#define  SWITCH_2304 8

#define DELAY 1

void setup_ports() {
  pinMode(LE_PIN, OUTPUT);
  digitalWrite(LE_PIN, HIGH);

  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  digitalWrite(CLK_PIN, LOW);
  digitalWrite(DATA_PIN, LOW);

  pinMode(REREAD_SWITCH_PIN, INPUT_PULLUP);
  pinMode(FREQ_SWITCH_PIN_3, INPUT_PULLUP);
  pinMode(FREQ_SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(FREQ_SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(FREQ_SWITCH_PIN_0, INPUT_PULLUP);
}

int read_reread_switch() {
  int sample1;
  int sample2;
  int sample3;

  for (;;) {
    sample1 = digitalRead(REREAD_SWITCH_PIN);
    sample2 = digitalRead(REREAD_SWITCH_PIN);
    sample3 = digitalRead(REREAD_SWITCH_PIN);
    if (sample1 == sample2 && sample2 == sample3) break;
  }
  return sample1;
}

int read_freq_switches_once() {
  int sample;
  sample = (
      (digitalRead(FREQ_SWITCH_PIN_3) << 3)
      | (digitalRead(FREQ_SWITCH_PIN_2) << 2)
      | (digitalRead(FREQ_SWITCH_PIN_1) << 1)
      | (digitalRead(FREQ_SWITCH_PIN_0) << 0));
  return sample;
}

int read_freq_switches() {
  int sample1;
  int sample2;
  int sample3;

  for (;;) {
    sample1 = read_freq_switches_once();
    sample2 = read_freq_switches_once();
    sample3 = read_freq_switches_once();
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
  switch (switch_value) {
    case SWITCH_10368:  {
      write_register(REGISTER_5_10368);
      write_register(REGISTER_4_10368);
      write_register(REGISTER_3_10368);
      write_register(REGISTER_2_10368);
      write_register(REGISTER_1_10368);
      write_register(REGISTER_0_10368);
      break;
    }
    case SWITCH_5760:  {
      write_register(REGISTER_5_5760);
      write_register(REGISTER_4_5760);
      write_register(REGISTER_3_5760);
      write_register(REGISTER_2_5760);
      write_register(REGISTER_1_5760);
      write_register(REGISTER_0_5760);
      break;
    }
    case SWITCH_3456:  {
      write_register(REGISTER_5_3456);
      write_register(REGISTER_4_3456);
      write_register(REGISTER_3_3456);
      write_register(REGISTER_2_3456);
      write_register(REGISTER_1_3456);
      write_register(REGISTER_0_3456);
      break;
    }
    case SWITCH_3400:  {
      write_register(REGISTER_5_3400);
      write_register(REGISTER_4_3400);
      write_register(REGISTER_3_3400);
      write_register(REGISTER_2_3400);
      write_register(REGISTER_1_3400);
      write_register(REGISTER_0_3400);
      break;
    }
    case SWITCH_2304:  {
      write_register(REGISTER_5_2304);
      write_register(REGISTER_4_2304);
      write_register(REGISTER_3_2304);
      write_register(REGISTER_2_2304);
      write_register(REGISTER_1_2304);
      write_register(REGISTER_0_2304);
      break;
    }
    default: {
      break;
    }
  }
}   

int last_value;
int current_value;
int reread;

void setup() {
  setup_ports();
  delay(1000);
  reread = read_reread_switch();
  current_value = read_freq_switches();
  write_synthesizer(current_value);
  last_value = current_value;
}

void loop() {
  if (reread) {
    current_value = read_freq_switches();
    if (current_value != last_value) {
      write_synthesizer(current_value);
      last_value = current_value;
    }
  }
}
