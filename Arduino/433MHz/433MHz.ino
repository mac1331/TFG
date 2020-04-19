#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    else
             Serial.println("init okey");

}

void loop()
{
    const char *msg = "Hello World!";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("sended");
    delay(100);
}
