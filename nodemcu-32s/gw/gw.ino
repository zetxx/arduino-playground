 /*
 * https://how2electronics.com/wp-content/uploads/2020/10/circuit-ESP32-nRF24L01.png
 * https://lastminuteengineers.b-cdn.net/wp-content/uploads/iot/ESP32-Pinout.png
 *
 * | IO   | RF24 | RFM69 | RFM95 |
 * |------|------|-------|-------|
 * | MOSI | 23   | 23    | 23    |
 * | MISO | 19   | 19    | 19    |
 * | SCK  | 18    | 18    | 18   |
 * | CSN  | 05   | 5     | 5     |
 * | CE   | 04   | -     | -     |
 * | RST  | -    | 17    | 17    |
 * | IRQ  | 16*  | 16    | 16    |
 * * = optional
 */

#define MY_RADIO_RF24
#define MY_RF24_CS_PIN 5
#define MY_RF24_CE_PIN 4

#define MY_GATEWAY_SERIAL
#define MY_GATEWAY_ESP32
#define MY_HOSTNAME "ESP32MQTTGW"

#define MY_GATEWAY_MQTT_CLIENT
#define MY_MQTT_PUBLISH_TOPIC_PREFIX "mygateway1-out"
#define MY_MQTT_SUBSCRIBE_TOPIC_PREFIX "mygateway1-in"
#define MY_MQTT_CLIENT_ID "mysensors-1"
#define MY_PORT 1883
#define MY_CONTROLLER_IP_ADDRESS 10,100,100,22

#define MY_DEBUG
#define MY_DEBUG_VERBOSE
#define MY_DEBUG_VERBOSE_GATEWAY
#define MY_DEBUG_VERBOSE_SIGNING
#define MY_DEBUG_VERBOSE_RF24
#define MY_DEBUG_VERBOSE_TRANSPORT


#define MY_SIGNING_SOFT
#define MY_SIGNING_REQUEST_SIGNATURES
#define MY_INCLUSION_MODE_FEATURE

#include "private.h"
#include <MySensors.h>

void setup() {}


void loop() {}
