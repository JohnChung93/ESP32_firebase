//Firebase Setting
#define host "xxxxxxxxxxx.firebaseio.com"              //  Login firebase
#define firebase_auth "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" //  Password firebase
#define user_path "xxxxxx"                             //  Registered user in the firebase database

//------------------------------------------------Firebase Realtime Database--------------------------------------------------------------------
void sendPatchRequest(String str1, String str2);
String sendGetRequest();
void sendDeleteRequest(String str1);
//------------------------------------------------HTTP Set---------------------------------------------------------------------------------------------
String url_set(String http_mode, String user_data);
String head_set(String body);
//------------------------------------------------Check Respons-------------------------------------------------------------------------------------
String checkServerRespons();
