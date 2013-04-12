
#include <util/delay.h>
#include <avr/pgmspace.h>
//#include <cstring>

#define F_CPU 16000000UL

int val[8];
byte mask = 1;
byte key = 0;

// !'s still need to be defined and map has errors, very wip
const char Keymap[] = { '!', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '!',
                        '!', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '!',
                        '!', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '!',
                        '!', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '!',
                        '!', '!', '!', '!', ' ', ' ', '!', '!', '!' }; 

const char ShiftKeymap[] = { '!', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '!',
                             '!', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '!',
														 '!', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '!',
                             '!', '\|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '/', '!'
                             '!', '!', '!', '!', ' ', ' ', '!', '!', '!'};
                    
  



void setup() {
  attachInterrupt(1, capture, RISING);
  Serial.begin(115200);
}


void loop() {
  _delay_ms(1000);
  
}

void capture() {
  char c;
  key = 0;
  mask = 1;
  
  for (int j =0; j <=7; j++) {
    _delay_us(102);
    val[j] = bitRead(PIND, 3);
  }

  for (int i = 0; i <=6; i++) {
    if (val[i]) key |= mask;
    mask = mask << 1;
  }
  
  key = ~key;
  key <<= 1;
  key >>= 1;
  
  c = getMappedkey(key);
  
  if( key != 0x7F ){
    Serial.print(c );  
    if (val[7] == 1){
      Serial.println("   Pressed");
    }
    else if (val[7] == 0) {
      Serial.println("   Released");
    }
  }
    
}


char getMappedkey(int key) {
  
  int s;
  char c;
  
  s = 0;
  c = NULL;
  
  if (key != 0x7F){
   s = key;
  }
  if (s !=0){
  c = Keymap[s-1];
  }
 
 return c;
  
} 









