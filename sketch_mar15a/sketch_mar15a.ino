# include <Wire.h>
# include <TinyGPS++.h>
# include <WiFi.h>
# include <FirebaseESP32.h>

# define FIREBASE_HOST "esp32-gps-firebase-8ac4c-default-rtdb.firebaseio.com"
# define FIREBASE_AUTH "WokOGuauR6C0eYXGy250K1BdIgHTECvEGQOmNjgu"
# define WIFI_SSID "Bakry"
# define WIFI_PASSWORD "bakry3224411"
# define GPS_RX_PIN 16
# define GPS_TX_PIN 17

TinyGPSPlus gps;
FirebaseData firebaseData;

void setup () {
  Serial.begin( 115200 );
  // Initialize GPS module
  Serial.println( "Initializing NEO-6M GPS module..." );
  Serial1.begin( 9600 , SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  // Initialize WiFi connection
  Serial.println( "Connecting to WiFi..." );
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  
  // Initialize Firebase connection
   Serial.println( "Connecting to Firebase..." );
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   Firebase.reconnectWiFi(true);

}

void loop () {
  
   // Read data from GPS module
   while (Serial1.available() >0 ) {
     if (gps.encode(Serial1.read())) {
       // Check if location data is valid
       if (gps.location.isValid()) {
         // Get latitude and longitude
         double latitude = gps.location.lat();
         double longitude = gps.location.lng();
         // Print location data to serial monitor
         Serial.print("Latitude: ");
         Serial.println(latitude,6);
         Serial.print("Longitude: ");
         Serial.println(longitude,6);

         // Send location data to Firebase
         String path1 = "/latitude"; // The path in the database where you want to store the data
         String value1 = String(latitude,6) ; // The value you want to store as a string
         String path2 = "/longitude"; // The path in the database where you want to store the data
         String value2 = String(longitude,6) ; // The value you want to store as a string
         

         if (Firebase.setString(firebaseData,path1,value1)) { 
           // If successful, print the result to serial monitor
           Serial.print("Location data sent to Firebase: ");
           Serial.println(firebaseData.stringData());
           
          }if (Firebase.setString(firebaseData,path2,value2)) { 
           // If successful, print the result to serial monitor
           Serial.print("Location data sent to Firebase: ");
           Serial.println(firebaseData.stringData());
           
          }
           else { 
            // If failed, print the error message to serial monitor 
            Serial.print("Error sending location data: ");
            Serial.println(firebaseData.errorReason());
          }
       } else {
        // If location data is not valid, print a message to serial monitor 
        Serial.println("Invalid location data");
       }
     }
   }
}
