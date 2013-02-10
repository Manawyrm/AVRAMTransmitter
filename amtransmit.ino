/*
AM Transmitter with Modulation Data Input via UART
Written 2010-2013 by Tobias Mädel (t.maedel@alfeld.de)
http://tbspace.de

Runs only on m168 and m328 AVRs
Help for porting to an m1280 and m2560 (Arduino Mega) is gladly appreciated!
*/

//Magic. Don't touch.
const byte CarrierPin = 9;
const byte SignalPin  = 6; 
void setup(void)
{
  Serial.begin(115200); //Makes the data income with somewhat near 11025 Byte/s (11025 Hz Audiofrequency)
  
  TCCR1A = _BV (COM1A0);           // toggle OC1A on Compare Match
  TCCR1B = _BV(WGM12) | _BV(CS10); // CTC, no prescaler
  OCR1A =  9;                      // compare A register value to 10 (zero relative)
  TCCR0A=0x83;                     // Timer/Counter 0 initialization
  TCCR0B=0x01;                     // Clock source: System Clock and Clock value: 16000,000 kHz
  TCNT0=0x00;                      // Mode: Fast PWM top=FFh
  OCR0A=0x00;                      // OC0A output: Non-Inverted PWM
  OCR0B=0x00;                    // OC0B output: Disconnected
  pinMode (CarrierPin, OUTPUT);
  pinMode (SignalPin, OUTPUT);
}


void loop()
{
  unsigned char i;
  
  for(i = 0; i < 44; i++)
  {  // ignore 44 bytes header data of WAV file
     while(Serial.available() == 0); 
     Serial.read();
  }
  
  while(1)
  {
     while(Serial.available() == 0);  // wait for data
     OCR0A = (unsigned char)Serial.read(); // write data to SignalPin
  }
}

