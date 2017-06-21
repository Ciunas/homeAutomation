#include "Responses.h"

int parseRequest( String request ) {

  Serial.println(request);
  String temp = request.substring(10, 13);
  char relay [4] = {};
  temp.toCharArray(relay, 4);
  Serial.println(temp);
  return strtol(relay, 0, 16);

}

void relayControl( EthernetClient client , int rNum) {


  // standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE HTML>");    //Send html response
  client.println("<html>");

  // output the value of each analog input pin
  for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
    int sensorReading = analogRead(analogChannel);
    client.print("analog input ");
    client.print(analogChannel);
    client.print(" is ");
    client.print(sensorReading);
    client.println("<br />");
  }

  digitalWrite(rNum , !digitalRead(rNum ));


  client.println("</html>");

}

//Shut down runeAudio player
void shutdownMusic( IPAddress remote) {

  EthernetClient client;
  
  if (client.connect(remote, 80)) {
    Serial.println("connected");
    client.println("POST /settings/ HTTP/1.0");
    client.println("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    client.print("Content-Length: 15");
    client.println();
    client.println();
    client.println("syscmd=poweroff");

  } else {
    Serial.println("connection failed");
  }

}

