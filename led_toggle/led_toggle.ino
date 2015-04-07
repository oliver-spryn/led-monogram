int IRledPin =  13;

// LED bar toggle signal on and off durations in 10's of microseconds
int IRsignal[] = {
  890, 442,
  56, 54,
  58, 52,
  60, 52,
  56, 52,
  60, 52,
  58, 54,
  56, 52,
  58, 54,
  58, 164,
  58, 164,
  56, 164,
  60, 162,
  60, 164,
  56, 164,
  58, 164,
  58, 164,
  56, 54,
  58, 52,
  60, 162,
  58, 54,
  58, 162,
  58, 54,
  58, 52,
  58, 52,
  58, 166,
  56, 164,
  58, 54,
  56, 164,
  58, 54,
  56, 164,
  60, 162,
  58, 164,
  56, 3944,
  888, 220,
  58, 2942,
  890, 218,
  60, 2942,
  888, 220,
  58, 2942,
  890, 220,
  58, 2942,
  888, 220,
  60, 2940,
  890, 218,
  60, 2942,
  890, 218,
  60, 2940,
  890, 220,
  58, 0
};

void pulseIR(long microsecs);
void sendOnSignal();

void setup() {
  pinMode(IRledPin, OUTPUT);
  sendOnSignal();
  delay(3000);
}

void loop() {
}

void pulseIR(long microsecs) {
  cli(); // Turns off any background interrupts
 
  while (microsecs > 0) {
   // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei(); // This turns them back on
}
 
void sendOnSignal() {
  for(int i = 0; i < 100; ++i) {
    pulseIR(IRsignal[i] * 10);
    ++i;
    delayMicroseconds(IRsignal[i] * 10);
  }
}
