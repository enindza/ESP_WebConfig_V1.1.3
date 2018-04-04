
/*

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#include "IFTTTwebhooks.h"

IFTTTwebhooks::IFTTTwebhooks(String key)	{
  _key = key;
}

String IFTTTwebhooks::sendTriggerEvent(String eventName) {
	String response="";
  bool finishedHeaders = false;
  bool currentLineIsBlank = true;
	long now;
	bool avail;
	// Connect with IFTTT
	if (connect(HOST, SSL_PORT)) {
		//Serial.println(".... connected to server");
		String a="";
		char c;
		int ch_count=0;
		this->println("GET https://maker.ifttt.com/trigger/"+eventName+"/with/key/"+_key);
		now=millis();
		avail=false;
    //Serial.println("starting timer");
		while (millis()-now<1500) {
			while (available()) {
				char c = read();
				//Serial.print(c);
        response = response + c;
			}
		}
	}
  return response;
}

String IFTTTwebhooks::sendTriggerEventWithData(String eventName, JsonObject& payload) {
	String response="";
  bool finishedHeaders = false;
  bool currentLineIsBlank = true;
	long now;
	bool avail;
	// Connect with IFTTT
	if (connect(HOST, SSL_PORT)) {
		//Serial.println(".... connected to server");
		String a="";
		char c;
		int ch_count=0;
		this->print("POST /trigger/"+eventName+"/with/key/"+_key);
    this->println(" HTTP/1.1");
    // Host header
    this->print("Host:"); this->println(HOST);
    // JSON content type
    this->println("Content-Type: application/json");
    // Content length
    int length = payload.measureLength();
    this->print("Content-Length:"); this->println(length);
    // End of headers
    this->println();
    // POST message body
    String out;
    payload.printTo(out);
    //Serial.println(out);
    this->println(out);

    now=millis();
		avail=false;
    //Serial.println("starting timer");
		while (millis()-now<1500) {
			while (this->available()) {
				char c = this->read();
				//Serial.print(c);
        response = response + c;
			}
		}
	}

  //Serial.println("response");
  //Serial.println(response);
  return response;
}

bool IFTTTwebhooks::triggerEvent(String eventName , String value1, String value2, String value3){

  DynamicJsonBuffer jsonBuffer;
  JsonObject& payload = jsonBuffer.createObject();
  if(value1 != ""){
    payload["value1"] = value1;
  }
  if(value2 != ""){
    payload["value2"] = value2;
  }
  if(value3 != ""){
    payload["value3"] = value3;
  }

  String response = sendTriggerEventWithData(eventName, payload);
  if(checkForSucessResponse(response)){
    return true;
  }
  return false;
}

bool IFTTTwebhooks::checkForSucessResponse(String response) {

  int index = response.indexOf("Congratulations!");

  return index > -1;
}
