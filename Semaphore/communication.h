/*
 * communication.h
 *
 *  Created on: May 23, 2020
 *      Author: cssouza
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_


class Communication{
public:

	static void open(int baudRate);
	static void send(const char *buffer, int size);
	static void recv(char *buffer, int size);
	static void close();
};


#endif /* COMMUNICATION_H_ */
