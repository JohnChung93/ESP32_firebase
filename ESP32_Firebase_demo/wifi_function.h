//WIFI Setting
#define ssid "xxxxxx"        // WIFI ssid
#define password "xxxxxxxxxx" // WIFI password

//------------------------------------------------WIFI--------------------------------------------------------------------
void wifi_init();
char wifi_alive();
IPAddress wifi_local_ip();
void wifi_init_set();
