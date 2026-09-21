#include <Jana_ard_lib.h>

#define SCLK_PIN 7
#define RCLK_PIN 6
#define DIO_PIN 5

Jana_ard_lib display(RCLK_PIN, SCLK_PIN, DIO_PIN);

void setup(){

display.begin();
display.print(1234);


}

void loop(){
   
   display.loop();
}