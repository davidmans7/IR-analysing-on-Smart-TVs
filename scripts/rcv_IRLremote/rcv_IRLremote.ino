/*
**** Master Thesis - UC3M ****
* DAVID MANZANO SÁNCHEZ
* david.manzano@alumnos.uc3m.es
* 
* Receiving IR signals and displaying: ( Protocol , Address , Command )
* 
* This code uses IRLremote Arduino library from Nico Hood.
* Available: https://github.com/NicoHood/IRLremote
* 
*/
#include <IRLremote.h>

int count = 0;
int INTERRUPTION = 0;

uint8_t  myProtocol = 0;
uint16_t myAddress  = 0;
uint32_t myKey      = 0;

uint8_t oldSREG;

/* 
* IRLEvent function
* Rewritting IREvent function to control the reception of IR params... 
*/
void IREvent (uint8_t protocol, uint16_t address, uint32_t command) {
  count++;
  if(address == 0){
      command = myKey;
  }
  myKey = command;
  myProtocol = protocol;
  myAddress = address;
}

/* SETUP function */
void setup() {
   IRLbegin<IR_ALL>(INTERRUPTION);
   Serial.begin(115200);
}

/* LOOP function */
void loop() {
  // Block other interruptions to avoid IR code execution to be interrupted again
  oldSREG = SREG; // backup of registry
  cli(); // modifies 7th bit of registry to avoid interruptions

  if(myProtocol != 0) {    
    if(myProtocol == 3 && myAddress == 0){
      Serial.print("***NEC continuous pressed: "); Serial.print("("); Serial.print(myProtocol); Serial.print(","); Serial.print(myAddress); Serial.print(","); Serial.print(myKey); Serial.println(")");
    }
    else{
      Serial.print(count); Serial.print(" - ");
      Serial.print("Protocol: ");
      Serial.print(myProtocol);
      switch(myProtocol){
        case 3: Serial.print(" (NEC)      "); break;
        case 4: Serial.print(" (PANASONIC)"); break;
        default: Serial.print("unknown_prot"); break;
      }
      Serial.print("   |   Address: ");
      Serial.print(myAddress);
      Serial.print("   |   Key: ");
      Serial.println(myKey);
    }
    myProtocol=0; myAddress=0; myKey=0; // reset IR values
  }
  // Restoring registry to recover interruptions
  SREG = oldSREG;
}
