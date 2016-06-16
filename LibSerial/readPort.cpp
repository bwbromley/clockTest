#include "SerialStream.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>

using std::string;
using namespace LibSerial;
using std::cout;
using std::cerr;
using std::endl;

SerialStream serialStream;

void checkStatus(string message) {
	if (!serialStream.good()) {
		cerr << message << endl;
		exit(1);
	}
}

int main(int argc, char** argv) {
	serialStream.Open("/dev/ttyAMA0");
	checkStatus( "Error: Could not open serial port.");
	serialStream.SetBaudRate(SerialStreamBuf::BAUD_9600);
	checkStatus("Error: Could not set the baud rate.");
	serialStream.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
	checkStatus( "Error: Could not set the character size.");
	serialStream.SetParity(SerialStreamBuf::PARITY_NONE);
	checkStatus("Error: Could not disable the parity.");
	serialStream.SetNumOfStopBits(1);
	checkStatus("Error: Could not set the number of stop bits.");
	serialStream.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
	checkStatus("Error: Could not use hardware flow control.");
	while(true) {
		char next_byte;
		serialStream.get(next_byte);
		std::cout << (unsigned char) next_byte;
		usleep(100000); // works
	}
	return 0;
}
