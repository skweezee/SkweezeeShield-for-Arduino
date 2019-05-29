/*
   Reads the status of all electrode pairs and sends this information
   to the serial port.
   The resistance between two electrode pairs is measured through
   a voltage divider and read in on pin A0
   Serial communication works in its simplest way.
   Arduino keeps on sending data.  The PC reads out.
   The hardware includes multiplexers 74HCT4051
   and a buffer with op-amp MCP602.
   The Arduino board needs to generate the Enable
   signal (active low) and the select inputs for
   the multiplexer.
*/

// first define the functions of the digital I/O pins
// the following pins control the multiplexers (enable and select)
#define EN 13
#define S0_A 12
#define S1_A 11
#define S2_A 10
#define S0_B 9
#define S1_B 8
#define S2_B 7

int val = 0; // variable to store the value read

void setup() {
  Serial.begin(9600); // baud rate 9600 bps
  pinMode(EN, OUTPUT);
  pinMode(S0_A, OUTPUT);
  pinMode(S1_A, OUTPUT);
  pinMode(S2_A, OUTPUT);
  pinMode(S0_B, OUTPUT);
  pinMode(S1_B, OUTPUT);
  pinMode(S2_B, OUTPUT);
}

void loop() {
  // Enable the multiplexer
  
  digitalWrite(EN, HIGH);
  Serial.write(0);

  // Loop through all the relevant combinations of the multiplexers
  for (int i=0; i<8; i++) {
     for (int j=i+1; j<8; j++) {
        digitalWrite(S2_A, bitRead(i,2) );
        digitalWrite(S1_A, bitRead(i,1) );
        digitalWrite(S0_A, bitRead(i,0) );
        digitalWrite(S2_B, bitRead(j,2) );
        digitalWrite(S1_B, bitRead(j,1) );
        digitalWrite(S0_B, bitRead(j,0) );
        delayMicroseconds(30); // time needed to go from L to H
        val = analogRead(0)>>2;
        Serial.write(val);
     } 
  }

  // Now disable the multiplexer (not really necessary)
  digitalWrite(EN, LOW);
  delay(20);
  
}


