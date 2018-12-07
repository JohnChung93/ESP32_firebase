#include <WiFi.h>
#include <WiFiClientSecure.h>

#include "wifi_function.h"

extern WiFiClientSecure client;

//------------------------------------------------WIFI--------------------------------------------------------------------
/*
 * Protocol to WIFI begin
 */
void wifi_init()
{
   WiFi.begin(ssid, password);
}

/*
 * Check wifi alive 
 * If alive return 1,if not reurn 0
 */
char wifi_alive()
{
   if (WiFi.status() != WL_CONNECTED)
   {
      return 1;
   }

   return 0;
}

/*
 * Retrun wifi local IP
 */
IPAddress wifi_local_ip()
{
   return WiFi.localIP();
}

/*
 *  WIFI initial setting 
 *  Check will alive and check network connection work
 */
void wifi_init_set()
{
   wifi_init();

   Serial.print("connecting");

   while (wifi_alive())
   {
      Serial.print(".");
      delay(500);
   }
   Serial.println();
   Serial.print("connected: ");
   Serial.println(wifi_local_ip());

   delay(2000);
}
