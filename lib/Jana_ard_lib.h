#ifndef MAKRO_J
#define MAKRO_J

#include <Arduino.h>
// Za svaki segment na broju postoji odgovarajuci bit
#define SEG_A 0x01
#define SEG_B 0x02
#define SEG_C 0x04
#define SEG_D 0x08
#define SEG_E 0x10
#define SEG_F 0x20
#define SEG_G 0x40
#define SEG_DP 0x80

#define NUM_DIGITS 4
#define REFRESH_INTERVAL 2

class Jana_ard_lib{
 public:
    Jana_ard_lib(int rclkPin, int sclkPin, int dioPin, bool commonAnode = true);

    void begin();
    void loop();

    void print(int num, bool zeroPad = false);
    void print(const char* text);
    void printTime(int hours, int minutes, bool colon = true);

    void clear();
    void off();
    void on();

    void delay(unsigned long ms);
    void yield();

    void setDot(int position, bool state = true);
    void setSegments(int position, uint8_t segments);
    void setChar(int position, char c);
    void setNum(int position, int num);
    void showErr();

  private:
    int _sclkPin;
    int _rclkPin;
    int _dioPin;
    bool _enabled;
    bool _commonAnode;
    
    uint8_t _buffer[NUM_DIGITS];
    bool _dots[NUM_DIGITS];
    uint8_t _currentDigit;
    unsigned long _lastRefresh;
    

    void _shiftOut(uint8_t data);
    void _latch();
    void _writeDigit(uint8_t position, uint8_t segments);
    void _printInt(int num, bool zeroPad);
    void _printStr(const char* text);
    static uint8_t _charToSegments(char c);




};


#endif