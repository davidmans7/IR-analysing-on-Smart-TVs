/*
**** Master Thesis - UC3M ****
* DAVID MANZANO SÁNCHEZ
* david.manzano@alumnos.uc3m.es
* 
* Receiving IR signals and displaying: ( Protocol , Address , Command )
* 
* This code uses IRremote Arduino library from Ken Shirriff y Rafi Khan.
* Available: https://github.com/z3t0/Arduino-IRremote
* 
*/
#include <IRremote.h>

int count = 0;
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long myKey = 0;

/* SETUP function */
void setup(){
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

/* LOOP function */
void loop(){
  if (irrecv.decode(&results)){
    count++;
    if (results.value == 0XFFFFFFFF)
      results.value = myKey;
    myKey = results.value;
    Serial.print(count); Serial.print(" - ");
    Serial.print("Protocol: "); Serial.print(results.decode_type);
    switch (results.decode_type){
        case NEC: Serial.print(" (NEC)"); break ;
        case SONY: Serial.print(" (SONY)"); break ;
        case RC5: Serial.print(" (RC5)"); break ;
        case RC6: Serial.print(" (RC6)"); break ;
        case DISH: Serial.print(" (DISH)"); break ;
        case SHARP: Serial.print(" (SHARP)"); break ;
        case JVC: Serial.print(" (JVC)"); break ;
        case SANYO: Serial.print(" (SANYO)"); break ;
        case MITSUBISHI: Serial.print(" (MITSUBISHI)"); break ;
        case SAMSUNG: Serial.print(" (SAMSUNG)"); break ;
        case LG: Serial.print(" (LG)"); break ;
        case WHYNTER: Serial.print(" (WHYNTER)"); break ;
        case AIWA_RC_T501: Serial.print(" (AIWA_RC_T501)"); break ;
        case PANASONIC: Serial.print(" (PANASONIC)"); break ;
        case DENON: Serial.print(" (DENON)"); break ;
        case PRONTO: Serial.print(" (PRONTO)"); break;
        case LEGO_PF: Serial.print(" (LEGO_PF)"); break;
        case UNKNOWN: Serial.print(" (unknown_prot)"); break;
      default:
        Serial.print("UNKNOWN"); break ;
      }
    Serial.print("   |   Address: ");
    Serial.print(results.address);
    Serial.print("   |   Key: ");
    Serial.println(myKey);
    irrecv.resume(); 
  }
}
