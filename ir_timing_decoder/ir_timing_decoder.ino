int IRsignal[] = {
// ON, OFF (in 10's of microseconds)
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
	58, 0};

// This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
int IRledPin =  13;    // LED connected to digital pin 13
 
// The setup() method runs once, when the sketch starts
 
void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
 
  Serial.begin(9600);
}
 
void loop()                     
{
  Serial.println("Sending IR signal");
 
  SendNikonCode();
 
  delay(60*1000);  // wait one minute (60 seconds * 1000 milliseconds)
}
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}
 
void SendNikonCode() {
  while(true) {
    for(int i = 0; i < 100; ++i) {
      pulseIR(IRsignal[i] * 10);
      ++i;
      delayMicroseconds(IRsignal[i] * 10);
    }
    
    delay(65); // wait 65 milliseconds before sending it again
  }
}
