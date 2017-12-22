// Author : Nazim SAIBI
// Date : 22/12/2017

#include "IOT.h"


void setup() {
  IOT node;
  node.useSerial(115200);
  node.setWIFI("NAZIM", "password");

  node.setMQTT("192.168.1.21", "topic1", "topic2", "nazim", "nazim");
  
  //node.setMessage("message");
  node.go();
}


void loop() {

}
