#include "Jana_ard_lib.h"

static const uint8_t DIG_MAP[] PROGMEM = {
0x3F, // 0
0x06, // 1
0x5B, // 2
0x4F, // 3
0x66, // 4
0x6D, // 5
0x7D, // 6
0x07, // 7
0x7F, // 8
0x6F // 9
};

static const uint8_t DIGIT_PATTERNS[NUM_DIGITS] = {0x08, 0x04, 0x02, 0x01};

uint8_t Jana_ard_lib::_charToSegments(char c){

if(c >= '0' && c <= '9'){
  return pgm_read_byte(&DIG_MAP[c - '0']);
}

switch(c){
 case 'A': case 'a': return 0x77;
        case 'B': case 'b': return 0x7C;
        case 'C':           return 0x39;
        case 'c':           return 0x58;
        case 'D': case 'd': return 0x5E;
        case 'E': case 'e': return 0x79;
        case 'F': case 'f': return 0x71;
        case 'G':           return 0x3D;
        case 'g':           return 0x6F;
        case 'H':           return 0x76;
        case 'h':           return 0x74;
        case 'I':           return 0x06;
        case 'i':           return 0x04;
        case 'J': case 'j': return 0x1E;
        case 'L': case 'l': return 0x38;
        case 'N':           return 0x37;
        case 'n':           return 0x54;
        case 'O':           return 0x3F;
        case 'o':           return 0x5C;
        case 'P': case 'p': return 0x73;
        case 'R':           return 0x77;
        case 'r':           return 0x50;
        case 'S': case 's': return 0x6D;
        case 'T': case 't': return 0x78;
        case 'U':           return 0x3E;
        case 'u':           return 0x1C;
        case 'Y': case 'y': return 0x6E;
        case ' ':           return 0x00;
        case '-':           return 0x40;
        case '_':           return 0x08;
        default:            return 0x00;

}


}


Jana_ard_lib::Jana_ard_lib(int rclkPin, int sclkPin, int dioPin,bool commonAnode){
  _sclkPin = sclkPin;
  _rclkPin = rclkPin;
  _dioPin = dioPin;
  _commonAnode = commonAnode;
  _currentDigit = 0;
  _lastRefresh = 0;
  _enabled = true;
  for(int i = 0; i < NUM_DIGITS; i++){
    _buffer[i] = 0x00;
    _dots[i] = false;
  }
}

void Jana_ard_lib::begin(){

  pinMode(_sclkPin, OUTPUT);
  pinMode(_rclkPin, OUTPUT);
  pinMode(_dioPin, OUTPUT);

  digitalWrite(_sclkPin, LOW);
  digitalWrite(_rclkPin, LOW);
  digitalWrite(_dioPin, LOW);
  }

void Jana_ard_lib::_shiftOut(uint8_t data){

  for(int i=7; i>=0; i--){
     
     digitalWrite(_dioPin, (data >> i) & 1);
     digitalWrite(_sclkPin, LOW);
     digitalWrite(_sclkPin, HIGH);


  }

}

void Jana_ard_lib::_latch(){
  digitalWrite(_rclkPin, LOW);
  digitalWrite(_rclkPin, HIGH);

}


void Jana_ard_lib::_writeDigit(uint8_t position, uint8_t segments){
  uint8_t segData;
  if(_commonAnode){
    segData = (~segments) & 0xFF;

  }
  else {
    segData = segments & 0xFF;
  }
  uint8_t dataPosition = DIGIT_PATTERNS[position];
  _shiftOut(segData);
  _shiftOut(dataPosition);
  _latch();
}

void Jana_ard_lib::loop(){
  if(!_enabled) return;

  unsigned long now = millis();
  if(now - _lastRefresh >= REFRESH_INTERVAL){
    _lastRefresh = now;
    uint8_t segments = _buffer[_currentDigit];
    if(_dots[_currentDigit]){
      segments |= SEG_DP;
    }
  _writeDigit(_currentDigit, segments);
  _currentDigit = (_currentDigit + 1) % NUM_DIGITS;

  }

}

void Jana_ard_lib::clear(){

  for(int i = 0; i < NUM_DIGITS; i++){
    _buffer[i] = 0x00;
    _dots[i] = false;
  }
}

void Jana_ard_lib::print(int num, bool zeroPad){
    _printInt(num, zeroPad);
}

void Jana_ard_lib::_printInt(int num, bool zeroPad){
  clear();

  if(num > 9999 || num < -999){
    _buffer[1] = _charToSegments('e');
    _buffer[2] = _charToSegments('r');
    _buffer[3] = _charToSegments('r');
    return;
  }

  bool negative = num < 0;
  if(negative){
    num = -num;
  }

  int dig[4];
  int count = 0;
  if(num == 0){
    dig[0] = 0;
    count = 1;
  }
  else {
    int temp = num;
    while(temp > 0){
      dig[3 - count] = temp % 10;
      count++;
      temp /= 10;
    }
  }
  int maxDigits = negative ? 3 : NUM_DIGITS;   

  if( zeroPad && ( ! negative ) ){
    int dif = maxDigits - count;
    int ct = 0;
    while(ct < dif){
      dig[ct] = 0;
      ct++;
      count++;
    }
  }

  int startPos = NUM_DIGITS - count;

  if(negative && startPos > 0){

    _buffer[startPos - 1] = _charToSegments('-');

  }
  for(int i = 0; i < count; i++){
    int pos = startPos + i;
    if(pos >= 0 && pos <= 3){
      _buffer[pos] = _charToSegments('0' + dig[pos]);
    }

  }

}










