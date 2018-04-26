/*  HTTPS on ESP8266 with follow redirects, chunked encoding support
 *  Version 2.1
 *  Author: Sujay Phadke
 *  Github: @electronicsguy
 *  Copyright (C) 2017 Sujay Phadke <electronicsguy123@gmail.com>
 *  All rights reserved.
 *
 *  Example Arduino program
 */


#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include "DebugMacros.h"
#include <Config.h>
//#include "HTTPSRedirect.h"
//#include "helpers.h"


// for stack analytics
extern "C" {
#include <cont.h>
  extern cont_t g_cont;
}

boolean HTTPSRedirectFirstRunFlag = true;
// Fill ssid and password with your network credentials
//const char* ssid = "";
//const char* password = "";

const char* host = "script.google.com";
// Replace with your own script id to make server side changes
const char *GScriptId = "AKfycbw9txFwPnjbdvm29XBvnPv97gGjfZiL4_J4HSYYGaegQiPYBcQ";

const int httpsPort = 443;

// echo | openssl s_client -connect script.google.com:443 |& openssl x509 -fingerprint -noout
const char* fingerprint = "";

// Write to Google Spreadsheet
String url = String("/macros/s/") + GScriptId + "/exec?value=Hello";
// Fetch Google Calendar events for 1 week ahead
String url2 = String("/macros/s/") + GScriptId + "/exec?cal";
// Read from Google Spreadsheet
String url3 = String("/macros/s/") + GScriptId + "/exec?read";

String payload_base =  "{\"command\": \"appendRow\", \
                    \"sheet_name\": \"DataLogger\", \
                    \"values\": ";
String payload = "";

HTTPSRedirect* client = nullptr;
// used to store the values of free stack and heap
// before the HTTPSRedirect object is instantiated
// so that they can be written to Google sheets
// upon instantiation
unsigned int free_heap_before = 0;
unsigned int free_stack_before = 0;

const uint8 HTTPSredirectscaleMax = 30;
uint8 HTTPSredirectscale = 0;

void HTTPSredirectsetup() {
//  Serial.begin(115200);
//  Serial.flush();

  free_heap_before = ESP.getFreeHeap();
  free_stack_before = cont_get_free_stack(&g_cont);
  Serial.printf("Free heap before: %u\n", free_heap_before);
  Serial.printf("unmodified stack   = %4d\n", free_stack_before);
}
void HTTPSredirectFirstRun(){
//  Serial.println();
//  Serial.print("Connecting to wifi: ");
//  Serial.println(ssid);
  // flush() is needed to print the above (connecting...) message reliably,
  // in case the wireless connection doesn't go through
//  Serial.flush();

/*/
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



*/
  if((WiFi.status() == WL_CONNECTED) and HTTPSRedirectFirstRunFlag){
    // Use HTTPSRedirect class to create a new TLS connection
    Serial.println("First run HTTPSredirect");
    HTTPSready = false;
    HTTPSreadylasttime = millis();
    client = new HTTPSRedirect(httpsPort);
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");

    Serial.print("Connecting to ");
    Serial.println(host);

    // Try to connect for a maximum of 5 times
    bool flag = false;
    for (int i=0; i<2; i++){
      Serial.print("Wifi.status:"); Serial.println(WiFi.status());
      Serial.print("retrival number: "); Serial.println(i,DEC);
      int retval = client->connect(host, httpsPort);
      if (retval == 1) {
         flag = true;
         HTTPSRedirectFirstRunFlag = false;
         Serial.println("google script connected");
         break;
      }
      else {
        Serial.println("Connection failed. Retrying...");
      }
        //Serial.println("Connection failed. Retrying...");
    }

    if (!flag){
      Serial.print("Could not connect to server: ");
      Serial.println(host);
      Serial.println("Exiting...");
      return;
    }
    /*
    if (client->verify(fingerprint, host)) {
      Serial.println("Certificate match.");
    } else {
      Serial.println("Certificate mis-match");
    }
  */
    // Send memory data to Google Sheets
    Serial.println("sending memory data to google sheets");
    //payload = payload_base + "\"" + free_heap_before + "," + free_stack_before + "\"}"; //cont_get_free_stack(&g_cont)
    //client->POST(url2, host, payload, false);
    payload = payload_base + "\"" + " ," + DateTime.hour + ":" + DateTime.minute + "," + config.Temperatura[0] + "," + config.MidTemperature + "," + config.MaxTemperature + "," + config.Mode + "," + config.NTPUpdateStatus + "," + ESP.getFreeHeap() + ", first run" + "\"}";
    client->POST(url2, host, payload, false);

    //Serial.println("\nGET: Write into cell 'A1'");
    //Serial.println("=========================");

    // fetch spreadsheet data
    //client->GET(url, host);

    // Send memory data to Google Sheets
    //payload = payload_base + "\"" + ESP.getFreeHeap() + "," + cont_get_free_stack(&g_cont) + "\"}";
    //client->POST(url2, host, payload, false);

    //Serial.println("\nGET: Fetch Google Calendar Data:");
    //Serial.println("================================");

    // fetch spreadsheet data
    //client->GET(url2, host);

    // Send memory data to Google Sheets
    //payload = payload_base + "\"" + ESP.getFreeHeap() + "," + cont_get_free_stack(&g_cont) + "\"}";
    //client->POST(url2, host, payload, false);

    //Serial.println("\nSeries of GET and POST requests");
    //Serial.println("===============================");

    Serial.printf("Free heap: %u\n", ESP.getFreeHeap());
    Serial.printf("unmodified stack   = %4d\n", cont_get_free_stack(&g_cont));

    // delete HTTPSRedirect object
    delete client;
    client = nullptr;
  }
}

void HTTPSredirectloop() {
  #include "Config.h"
  HTTPSredirectscale++;
  HTTPSready = false; //disable ifttt and other https requests
  HTTPSreadylasttime = millis();
  if((WiFi.status() == WL_CONNECTED) and (HTTPSredirectscale >= HTTPSredirectscaleMax) and !HTTPSRedirectFirstRunFlag){
      // Use HTTPSRedirect class to create a new TLS connection
    Serial.println("Enter HTTPSredirect");
    client = new HTTPSRedirect(httpsPort);
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");

    HTTPSredirectscale = 0;
    static int error_count = 0;
    //static int connect_count = 0;
    //const unsigned int MAX_CONNECT = 20;
    //static bool flag = false;
    //Serial.printf("Free heap: %u\n", ESP.getFreeHeap());
    //Serial.printf("unmodified stack   = %4d\n", cont_get_free_stack(&g_cont));
    // Try to connect for a maximum of 5 times
    /*
    bool flag = false;
    for (int i=0; i<2; i++){
      Serial.print("Wifi.status:"); Serial.println(WiFi.status());
      Serial.print("retrival number: "); Serial.println(i,DEC);
      int retval = client->connect(host, httpsPort);
      if (retval == 1) {
         flag = true;
         HTTPSRedirectFirstRunFlag = false;
         Serial.println("google script connected");
         break;
      }
      else {
        Serial.println("Connection failed. Retrying...");
      }
        //Serial.println("Connection failed. Retrying...");
    }


    if (!flag){
      //free_heap_before = ESP.getFreeHeap();
      //free_stack_before = cont_get_free_stack(&g_cont);
      client = new HTTPSRedirect(httpsPort);
      flag = true;
      client->setPrintResponseBody(true);
      client->setContentTypeHeader("application/json");
    }
*/
    if (client != nullptr){
      if (!client->connected()){
        Serial.print("connectin client again,---");
        client->connect(host, httpsPort);
        Serial.println("PASSED");
      }
      else{Serial.println("Client already connected, ---");}
      if (client->connected()){
        payload = payload_base + "\"" + " ," + DateTime.hour + ":" + DateTime.minute + "," + config.Temperatura[0] + "," + config.MidTemperature + "," + config.MaxTemperature + "," + config.Mode + "," + config.NTPUpdateStatus + "," + ESP.getFreeHeap() + "\"}";
        if(client->POST(url2, host, payload)){Serial.println("Client post return TRUE"); config.NTPUpdateStatus = false;}
        else {Serial.println("Client post return FALSE");}
        Serial.print("Status code: "); Serial.println(client->getStatusCode());
        Serial.print("Reason phrase: "); Serial.println(client->getReasonPhrase());
      } else{Serial.println("Client still not connected, skip, ---");}
    }
    else{
      //DPRINTLN("Error creating client object!");
      Serial.println("Error creating client object!");
      error_count = 5;
    }
/*
    if (connect_count > MAX_CONNECT){
      //error_count = 5;
      connect_count = 0;
      flag = false;
      delete client;
      client = nullptr;
      DPRINTLN("connect_count > MAX_CONNECT");
      return;
    }
*/

/*
    Serial.println("GET Data from cell 'A1':");
    if (client->GET(url3, host)){
      ++connect_count;
    }
    else{
      ++error_count;
      DPRINT("Error-count while connecting: ");
      DPRINTLN(error_count);
    }
*/
/*
    Serial.println("POST append memory data to spreadsheet:");
    payload = payload_base + "\"" + "x ," + config.Temperatura[0] + "," + config.MaxTemperature + "," + config.Mode + "," + config.PowerOutput + "," + ESP.getFreeHeap() + "," + cont_get_free_stack(&g_cont) + "\"}";
    if(client->POST(url2, host, payload)){
      ;
    }
    else{
      ++error_count;
      DPRINT("Error-count while connecting: ");
      DPRINTLN(error_count);
    }
*/
    /*
    if (!(client.reConnectFinalEndpoint())){
      ++error_count;
      DPRINT("Error-count while connecting: ");
      DPRINTLN(error_count);
    }
    else
      error_count = 0;
    */

    if (error_count > 500){
      Serial.println("Halting processor...");
      delete client;
      client = nullptr;
      Serial.printf("Final free heap: %u\n", ESP.getFreeHeap());
      Serial.printf("Final unmodified stack   = %4d\n", cont_get_free_stack(&g_cont));
      Serial.flush();
      ESP.deepSleep(0);
    }

    // In my testing on a ESP-01, a delay of less than 1500 resulted
    // in a crash and reboot after about 50 loop runs.
    //delay(4000);
  }
  delete client;
  client = nullptr;
}
