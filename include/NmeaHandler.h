#pragma once
/*
#include <string>

class NmeaHandler
{
public:
	std::string pre_read(std::string msg);


private:
	// TODO: decribe specific handlers here call em from main handler pre_read
};
*/

#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std; // @todo: get rid of

// NMEA message types
const string GGA_MESSAGE = "$GPGGA";
const string RMC_MESSAGE = "$GPRMC";
const string VTG_MESSAGE = "$GPVTG";

// Base class for NMEA message handlers
class NmeaMessageHandler {
public:
    virtual void handle(const string& message) = 0;
};

// GGA message handler
class GgaMessageHandler : public NmeaMessageHandler {
public:
    void handle(const string& message) {
        // Handle GGA message
        cout << "Handling GGA message: " << message << endl;
    }
};

// RMC message handler
class RmcMessageHandler : public NmeaMessageHandler {
public:
    void handle(const string& message) {
        // Handle RMC message
        cout << "Handling RMC message: " << message << endl;
    }
};

// VTG message handler
class VtgMessageHandler : public NmeaMessageHandler {
public:
    void handle(const string& message) {
        // Handle VTG message
        cout << "Handling VTG message: " << message << endl;
    }
};

// NMEA message dispatcher class
class NmeaMessageDispatcher {
public:
    void addHandler(const string& messageType, NmeaMessageHandler* handler) {
        handlers[messageType] = handler;
    }

    void dispatch(const string& message) {
        // Extract message type from message
        string messageType = message.substr(0, 6);

        // Check if handler exists for message type
        if (handlers.find(messageType) != handlers.end()) {
            // Dispatch message to handler
            handlers[messageType]->handle(message);
        }
        else {
            cout << "No handler found for message type: " << messageType << endl;
        }
    }

private:
    map <string, NmeaMessageHandler*> handlers;
};

// NMEA message queue class
class NmeaMessageQueue {
public:
    void enqueue(const string& message) {
        messages.push(message);
    }

    void process(NmeaMessageDispatcher& dispatcher) {
        while (!messages.empty()) {
            // Dequeue message from queue
            string message = messages.front();
            messages.pop();

            // Dispatch message to appropriate handler
            dispatcher.dispatch(message);
        }
    }

private:
    queue<string> messages;
};
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