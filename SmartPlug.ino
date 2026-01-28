#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>
#define relay 5

/* 1. Define the WiFi credentials */
#define WIFI_SSID "--------"
#define WIFI_PASSWORD "--------"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyB_tv0vuiHJOxQxbsACSP3kMvlTErNjge0"

/* 3. Define the RTDB URL */
#define DATABASE_URL "esp32-1cd50-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "pvguna45@gmail.com"
#define USER_PASSWORD "Guna@p@ss45"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

void setup()
{

  Serial.begin(115200);
pinMode(relay,OUTPUT);
digitalWrite(relay,1);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KEY;


  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.database_url = DATABASE_URL;

 
  config.token_status_callback = tokenStatusCallback; 

  Firebase.reconnectWiFi(true);

  fbdo.setBSSLBufferSize(4096 );

  
  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);
}

void loop()
{

 String a =""; 

  Firebase.getString(fbdo, "/SAMPLE");
  a = fbdo.stringData();
Serial.println(a);
  
if(a=="1")
  {
digitalWrite(relay,0);
  } 
if(a=="0")
  {
digitalWrite(relay,1);
  } 

 
}