#include "NmeaHandler.h"

/*/
std::string NmeaHandler::pre_read(std::string msg)
{
    // TODO: add regex read to array? aka [0] = "type" [*] = data
    return std::string();
}
*/


/*
int main() {
    // Create NMEA message handlers
    GgaMessageHandler ggaHandler;
    RmcMessageHandler rmcHandler;
    VtgMessageHandler vtgHandler;

    // Create NMEA message dispatcher
    NmeaMessageDispatcher dispatcher;
    dispatcher.addHandler(GGA_MESSAGE, &ggaHandler);
    dispatcher.addHandler(RMC_MESSAGE, &rmcHandler);
    dispatcher.addHandler(VTG_MESSAGE, &vtgHandler);

    // Create NMEA message queue
    NmeaMessageQueue messageQueue;

    // Enqueue some sample messages
    messageQueue.enqueue("$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47");
    messageQueue.enqueue("$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A");
   // messageQueue.enqueue("$GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*

   return 0;
   */