#include <WiFi.h>
#include <WiFiClientSecure.h>

#include "firebase_function.h"
#include "wifi_function.h"

extern WiFiClientSecure client;

//------------------------------------------------Firebase Realtime Database--------------------------------------------------------------------

/*
 *  Firebase realtime database http patch function
 *  str1: Database fields
 *  str2: Database value
 */
void sendPatchRequest(String str1, String str2)
{
  if (!client.connect(host, 443))
  {
    //Connection failed fail reconnection
    Serial.println("Connection failed!");
    wifi_init_set();
  }
  else
  {
    Serial.println("Connected to server!");
    String req_url_str = url_set("PATCH", "");
    String body = "{\"" + str1 + "\":\"" + str2 + "\"}";
    String head = head_set(body);

    client.print(req_url_str);
    client.print(head);
    client.print(body);

    Serial.println("============ HTTP PATCH request ============");
    Serial.print(req_url_str);
    Serial.print(head);
    Serial.println(body);

    checkServerRespons();

    delay(2);
    client.stop();
    delay(2);
  }
}

/*
 *  Firebase realtime database http get function
 *  Return  database data to string(use json decode) 
 */
String sendGetRequest()
{
  String ResponString;
  if (!client.connect(host, 443))
  {
    //Connection failed fail reconnection
    Serial.println("Connection failed!");
    wifi_init_set();
  }
  else
  {
    Serial.println("Connected to server!");

    String req_url_str = url_set("GET", "");
    String body = "";
    String head = head_set(body);

    client.print(req_url_str);
    client.print(head);
    client.print(body);

    Serial.println("============ HTTP GET request ============");
    Serial.print(req_url_str);
    Serial.print(head);
    Serial.println(body);

    ResponString = checkServerRespons();

    delay(2);
    client.stop();
    delay(2);
  }

  return ResponString;
}

/*
 *  Firebase realtime database http delete function
 *  str1: Database fields
 *  str1 example "test" , "/test"(If user_path set) ,"obj/test"
 */
void sendDeleteRequest(String str1)
{
  if (!client.connect(host, 443))
  {
    //Connection failed fail reconnection
    Serial.println("Connection failed!");
    wifi_init_set();
  }
  else
  {
    Serial.println("Connected to server!");
    String req_url_str = url_set("DELETE", str1);
    String body = "";
    String head = head_set(body);

    client.print(req_url_str);
    client.print(head);
    client.print(body);

    Serial.println("============ HTTP DELETE request ============");
    Serial.print(req_url_str);
    Serial.print(head);
    Serial.println(body);

    checkServerRespons();

    delay(2);
    client.stop();
    delay(2);
  }
}

//------------------------------------------------HTTP Set--------------------------------------------------------------------------------------------

/*
 *  HTTP  request url set 
 */
String url_set(String http_mode, String user_data)
{
  String req_url_str;
  req_url_str = http_mode;
  req_url_str += " /";
  req_url_str += user_path;
  req_url_str += user_data;
  req_url_str += ".json?auth=";
  req_url_str += String(firebase_auth);
  req_url_str += " HTTP/1.1\r\n";
  return req_url_str;
}

/*
 *  HTTP head set 
 */
String head_set(String body)
{
  String head;
  head = "Host: ";
  head += String(host) + "\r\n";
  head += "Connection: keep-alive\r\n";
  head += "Content-Length: ";
  head += String(body.length()) + "\r\n";
  head += "\r\n";

  return head;
}

//------------------------------------------------Check Respons-------------------------------------------------------------------------------------
/*
 *  Check http resppons and save database data to string(use json decode) 
 */
String checkServerRespons()
{
  String sum = "";
  //It is important to receive all responses from the Firebase server
  Serial.println("============ Firebase Server HTTP answer ============");
  while (client.connected())
  {
    String resp_str = client.readStringUntil('\n'); //Read the string
    Serial.println(resp_str);

    if (resp_str == "\r") //Blank line
    {
      Serial.println("-------------Response Header------------");
      break;
    }
  }
  //Upon return of the response header, the body part returns
  while (client.available())
  {
    char c = client.read();
    Serial.print(c);
    sum = sum + c;
  }
  Serial.println("\r\n-----------Received Body------------");
  return sum;
}
