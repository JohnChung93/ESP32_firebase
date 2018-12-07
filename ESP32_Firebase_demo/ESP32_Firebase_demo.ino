/*
 *  ESP32 Firebase demo
 *
 *  Created on: 2018/12/07
 *      Author: John
 */


#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include "ESP32_Firebase_demo.h"
#include "wifi_function.h"
#include "firebase_function.h"

DynamicJsonBuffer jsonBuffer;
WiFiClientSecure client;

int count = 0;
String ResponGet = "";

unsigned int mode = GET_MODE;

//------------------------------------------------Setup--------------------------------------------------------------------
void setup()
{
    Serial.begin(115200);

    pinMode(LED, OUTPUT);

    wifi_init_set();
}

//------------------------------------------------Loop--------------------------------------------------------------------
void loop()
{
    switch (mode)
    {
    case PATCH_MODE: //Firebase Patch example
        patch_example();
        break;
    case GET_MODE: //Firebase Get example
        get_example();
        break;
    case Delete_Mode: //Firebase Delete example
        delete_example();
        break;
    }
}

//------------------------------------------------Example--------------------------------------------------------------------
/*
 *  Firebase realtime database patch example 
 *  It will send "test" to database and updata "test" value by variable 'count'.(If database "test" do not exist it will auot create)
 */
void patch_example()
{
    sendPatchRequest("test", String(count));
    count++;
    if (count > 10)
    {
        count = 0;
    }
}

/*
 *   Firebase realtime database get example 
 *   It will load database "test" value.If "test" value do not equal to 0,it will turn led on.(Makesure text value exist in database and LED pin set correct)
 */
void get_example()
{
    ResponGet = sendGetRequest();
    JsonObject &JsonrRespons = jsonBuffer.parseObject(ResponGet);

    count = JsonrRespons["test"];
    if (count != 0)
    {
        digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }
}

/*
 *   Firebase realtime database delete example 
 *   It will delete database "test" fields
 */
void delete_example()
{
    sendDeleteRequest("test");
}
