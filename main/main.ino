#include <ESP8266WiFi.h>

const char* wifi_ssid = "KCBez";
const char* wifi_password = "W@gw00rd1025";

String httpHeader;

WiFiServer server(80);

String header;

void setup() {
  Serial.begin(115200);

  Serial.print("Connection to ");  
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();  
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client");   
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); 
    client.println("<!DOCTYPE HTML><html><h1>Bell Ringer</h1><input id='t' type='number' step='0.01' value='5.00'><a onclick='st()'><button>Set</button></a><script>function st(){window.location.href='/SET='+document.getElementById('t').value}</script></html>");
    delay(10);
    Serial.println("Client Disconnected");    
  }
}