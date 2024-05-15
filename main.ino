#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "NhacuaDiem"
#define WIFI_PASSWORD "abc.12345678"
#define API_KEY "AIzaSyAHrSVaAOc8s7q5k3BKYLGAlBWZjFqBjd0"
#define DATABASE_URL "esp8266-blueroler-default-rtdb.firebaseio.com"
#define USER_EMAIL "test@blueroler.com"
#define USER_PASSWORD "Blueroler@12345"

int cnt=300;
int cnt2=100;

FirebaseData data1;
FirebaseAuth auth;
FirebaseConfig config;

String value;

void setup() {
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  Serial.begin(115200);
  Serial.print("Đang kết nối đến Wi-Fi ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  { 
    digitalWrite(D1, LOW);
    delay(100);
    digitalWrite(D1, HIGH);
    delay(100);
    Serial.println(cnt2);
    if (cnt2==0){
      Serial.println("Restart...");
      ESP.restart();}
    cnt2--;
  }
  digitalWrite(D3, LOW);
  Serial.println();
  Serial.print("Địa chỉ IP: ");
  Serial.println(WiFi.localIP());

  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  Firebase.begin(&config, &auth);
}

void loop() {
  //Firebase.setString(data1, ("DataButton/test"), 12345);

  if (Firebase.getString(data1, "Check/connect")) {
      value = data1.stringData();
      }
  if (value == "1"){
    Firebase.setString(data1, ("DataCheck/connect"), 0);
    }

  Firebase.getString(data1, "DataButton/test");
      value = data1.stringData();
  if (value == "1"){
    digitalWrite(D2, HIGH);
    Firebase.setString(data1, ("DataPlus/test"), 1);
    }
  else{
    digitalWrite(D2, LOW);
    Firebase.setString(data1, ("DataPlus/test"), 0);}
    Firebase.setString(data1, ("DataButton/timer"), cnt);
    delay(10);
  if (cnt==0){
    Serial.println("Restart...");
    ESP.restart();}
  cnt--;
  
  while (WiFi.status() != WL_CONNECTED)
  { ESP.restart();
    }
}
