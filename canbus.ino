/* Define Joystick connection pins */
#define UP     8//PINC1 // PCINT9
#define DOWN   PINC3 // PCINT11
#define LEFT   PINC2 // PCINT10
#define RIGHT  PINC5 // PCINT13
#define CLICK  PINC4 // PCINT12
// PCCICR PCIE1 = PCINT[8:14]
// PCMSK1 enable interrupt per pin

boolean interrupt = false;
int pinc = 0;

ISR (PCINT1_vect) {
  interrupt = true;
  pinc = PINC;
}

void func()
{
  Serial.print("INTERRRUPT on pins: ");
        Serial.println(pinc);
  interrupt = true;
  pinc = PINC;
    //Serial.print("arduino interrupt ");
    //Serial.println(PINC);
}


void setup() {
    //Initialize pins with pullup 
    PORTC = 0b00111110; //(1<<PC5) | (1<<PC4) | (1<<PC3) | (1<<PC2) | (1<<PC1);

    // set as input
    DDRC = 0b00000000;//(1<<UP) | (1<<DOWN) | (1<<LEFT) | (1<<RIGHT) | (1<<CLICK);
    DDRB |= (1<<DDB0); 

    cli();
    PCICR |= (1<<PCIE1);
    PCMSK1 |= /*(1<<PCINT14) | (1<<PCINT13) | (1<<PCINT12) | (1<<PCINT11) | (1<<PCINT10) |*/ (1<<PCINT9); 
    //EICRA |= (1<<ISC01) | (1<<ISC00); // Falling edge
    EICRA |= (1<<ISC11) ;//| (1<<ISC10); // Falling edge
    EIMSK |= (1<<INT1);
    
    sei();

    //PINC = (1<<PINC5) | (1<<PINC4) | (1<<PINC3) | (1<<PINC2) | (1<<PINC1);

    //pinMode(UP,INPUT);
    //pinMode(DOWN,INPUT);
    //pinMode(LEFT,INPUT);
    //pinMode(RIGHT,INPUT);
    //pinMode(CLICK,INPUT);
    
    //Pull analog pins high to enable reading of joystick movements
    //digitalWrite(UP, HIGH);
    ///digitalWrite(DOWN, HIGH);
    //digitalWrite(LEFT, HIGH);
    //digitalWrite(RIGHT, HIGH);
    //digitalWrite(CLICK, HIGH);
 

    Serial.begin(115200);
    Serial.println("Serial ready!");
    delay(1000);

    int port = PORTC;
    int ddr = DDRC;
    int pin = PINC;
    Serial.print("PORTC: ");
    Serial.println(port);
    Serial.print("DDRC: ");
    Serial.println(ddr);
    Serial.print("PINC: ");
    Serial.println(pin);

    Serial.print("SREG: ");
    Serial.println(SREG);
    //delay(999999);
}

void loop() {
    if (interrupt){
        interrupt = false;
        PORTB |= (1<<PORTB0);
        Serial.print("INTERRRUPT on pins: ");
        Serial.println(pinc);
        pinc = 0;
    }
  //Scan analog pins. If pin reads low, print the corresponding joystick movement.
    //if (digitalRead(UP) == 0) {
   /* if ((PINC & (1<<UP)) == 0){
      Serial.println("Up");
    }
        
    if ((PINC & (1<<DOWN)) == 0) {
        Serial.println("Down");
    }
        
    if ((PINC & (1<<LEFT)) == 0) {
        Serial.println("Left");
    }
    
    if ((PINC & (1<<RIGHT)) == 0) {
        Serial.println("Right");
    }

    if ((PINC & (1<<CLICK)) == 0) {
       Serial.println("Click");
    }
    delay(250);
*/

}
