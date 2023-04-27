# ESP32 GPS Firebase

This is a simple Arduino sketch for an ESP32 board that retrieves GPS location data using the TinyGPS++ library and sends it to a Firebase Realtime Database using the FirebaseESP32 library. 

## Prerequisites

In order to use this code, you will need:

- An ESP32 board
- A NEO-6M GPS module connected to the board's RX and TX pins
- A Firebase Realtime Database
- The following libraries installed in your Arduino IDE:
  - Wire.h
  - TinyGPS++.h
  - WiFi.h
  - FirebaseESP32.h

## Getting started

To use this code, you will need to make the following changes:

1. Set the values of the following constants to match your WiFi network and Firebase Realtime Database credentials:

   `
   #define FIREBASE_HOST "your-firebase-host-url"
   #define FIREBASE_AUTH "your-firebase-auth-token"
   #define WIFI_SSID "your-wifi-ssid"
   #define WIFI_PASSWORD "your-wifi-password"
   

2. Set the values of the following constants to match the RX and TX pins of your GPS module:

   `
   #define GPS_RX_PIN 16
   #define GPS_TX_PIN 17
   

3. Upload the sketch to your ESP32 board.

## How it works

The sketch initializes the GPS module, connects to the WiFi network, and connects to the Firebase Realtime Database. It then enters an infinite loop where it reads location data from the GPS module and sends it to the Firebase Realtime Database.

The location data is sent to the Firebase Realtime Database in the form of two separate strings representing the latitude and longitude, respectively. The path in the database where the data is stored is configurable using the `path1` and `path2` variables.

If the data is successfully sent to the Firebase Realtime Database, the sketch outputs a message to the serial monitor indicating success. If there is an error sending the data, an error message is output to the serial monitor.
