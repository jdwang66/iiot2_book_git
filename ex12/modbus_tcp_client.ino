#include <SPI.h>
#include <Ethernet.h>
#include "MgsModbus.h"

MgsModbus Mb;
int inByte = 0;

// Ethernet settings
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xAA };
IPAddress ip(192, 168, 1, 50);  //客戶端IP位址
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


void setup()
{

  // serial setup
  Serial.begin(9600);
  Serial.println("Serial interface started");

  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);   //啟動網路界面
  Serial.println("Ethernet interface started"); 

  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);  //印出客戶端IP
    Serial.print("."); 
  }
  Serial.println();

  // server address
  IPAddress server_ip(192,168,1,20);  //Modbus TCP伺服器IP
  Mb.remSlaveIP = server_ip;
  
  // print menu
  Serial.println("0 - print the first 12 words of the MbData space");  
  Serial.println("1 - FC 3 - read 6 registers from the slave to MbData[0..5]"); 
  Serial.println("2 - Fc 16 - write 6 registers MbData[6..11] to server");

  Serial.print("server ip:");
  Serial.println(Mb.remSlaveIP);  //印出伺服器IP

  for (int i=0;i<12;i++) {
    Mb.MbData[i]=i;    
  }
}

void print_MbData() {  //印出MbData暫存器的值
  for (int i=0;i<12;i++) {
    Serial.print("address: "); 
    Serial.print(i); 
    Serial.print(" Data: "); 
    Serial.println(Mb.MbData[i],HEX);
  }
}
void loop()
{
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    if (inByte == '0') {
      print_MbData();   //輸入0
    }  
    
    if (inByte == '1') {  //輸入1
      Mb.Req(MB_FC_READ_REGISTERS,0,6,0);  //讀取多個暫存器           
    }     
    if (inByte == '2') {  //輸入2
      Mb.Req(MB_FC_WRITE_MULTIPLE_REGISTERS, 0,6,6);  //寫入多個暫存器        
    }
  }

  Mb.MbmRun();  // client recieve data
}
