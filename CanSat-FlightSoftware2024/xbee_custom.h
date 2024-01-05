#ifndef xbee_custom_h
#define xbee_custom_h

#include <XBee.h>

class XBEE_CUSTOM
{
  public:
    long int addr1,addr2;
    XBEE_CUSTOM(long int add1,long int add2)
    {
      addr1=add1;
      addr2=add2;
    };
    XBee xbee = XBee();
    XBeeResponse response = XBeeResponse();
    ZBRxResponse rx = ZBRxResponse();
    ModemStatusResponse msr = ModemStatusResponse();
    XBeeAddress64 addr64 = XBeeAddress64(addr1, addr2);
    bool gotResponse,ack,associated,errorAfterPacketRecieved,errorReadingPacket,errorAfterResponseRecieved; //FOR DEGUBBING PURPOSE

    void begin(Stream &serial)
    {
      xbee.begin(serial);
    }

  void sendPacket(String dataToSend)
  {
    String data = dataToSend;
    
    int data_len = data.length()+1; //Declare data_len var
    
    char temp[data_len]; //Create a temporary Character array
    
    uint8_t payload[data_len]; // Create the payload array
    
    data.toCharArray(temp,data_len); //Convert string(data) to char array(temp)
    
    for(int i=0;i<data_len;i++)
    {
      payload[i] = (uint8_t)temp[i]; //typecast char to uint8_t
    }
    
    ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
    
    xbee.send(zbTx);
  }


  String readRXPacket()
  {
    xbee.readPacket();
    if (xbee.getResponse().isAvailable()) 
    {
        // got something
        gotResponse = true;
        
        if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
        {
          // got a zb rx packet
          // now fill our zb rx class
          xbee.getResponse().getZBRxResponse(rx);
          associated = true;
              
            if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)
            {
              ack = true;
            }
            else 
            {
              // we got it (obviously) but sender didn't get an ACK
              ack = false;
              return "ACK FALSE";
            }
            char temp[rx.getDataLength() +1];
            for (int i = 0; i < rx.getDataLength(); i++) 
            { 
              temp[i] = rx.getData(i);
            } 
            String recievedData = String(temp);
            Serial.println(recievedData);
            return recievedData;
        } 
        else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) 
        {
          xbee.getResponse().getModemStatusResponse(msr);
        
          
          if (msr.getStatus() == ASSOCIATED)
          {
            associated = true;
            return "ASSOCIATED = True but error";
          }
          else if (msr.getStatus() == DISASSOCIATED) 
          {
            associated = false;
            return "ASSOCIATED FALSE";
          }
          else 
          {
            errorAfterResponseRecieved = true;
            return "ERROR AFTER RESPONSE RECIEVED";
          }
        }
        else 
        {
          errorAfterPacketRecieved = true;
          return "UNEXPECTED ERROR" ;
        }
      } 
      else if (xbee.getResponse().isError()) 
      {
        errorReadingPacket = true;
        return "ERROR READING PACKET";
      }
  }

};

#endif
