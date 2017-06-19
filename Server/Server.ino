
#include <UIPEthernet.h>
#include "Responses.h"

// Enter a MAC address and IP address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 10, 2);
EthernetServer server(80);    // (port 80 is default for HTTP):
String request;               // string to hold  GET request

void setup() {


  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  request = String();
  pinMode(2, OUTPUT); 
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP()); 
  
  
  Serial.println();
}


void loop() {

  // listen for incoming clients
  EthernetClient client = server.available();

  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    boolean currentLineFirst = true;
    
    while (client.connected()) {

      if (client.available()) {

        char c = client.read();
        Serial.write(c);
        if(currentLineFirst){
          request =  request + c;
        }
        
        //Recieved two "\n" in a row, send response.
        if (c == '\n' && currentLineIsBlank) {

 
          relayControl( client, parseRequest( request) );

          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
          currentLineFirst  =  false;

        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

