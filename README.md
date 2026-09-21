# Arduino biblioteka za 4-digit 7 segment displej koja koristi 74HC595 shift register
***
## Mapiranje pinova:

| Function | Pin |
|---|---|
| SCLK (SH_CP) | clock |
| RCLK (ST_CP) | latch |
| DIO (DS) | Data input |
| VCC | 3.3V ili 5V |
| GND | Ground - 0V |

## Primer:

```
#include <Jana_ard_lib.h>

#define SCLK_PIN 7 #Digitalni pin
#define RCLK_PIN 6 #Digitalni pin
#define DIO_PIN 5 #Digitalni pin

Jana_ard_lib display(RCLK_PIN, SCLK_PIN, DIO_PIN);

void setup(){

display.begin();
display.print(1234);


}

void loop(){
   
   display.loop();
}
```

