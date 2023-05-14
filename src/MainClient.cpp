/*
	UDP Client routine
*/

#include <stdio.h>
#include <thread>
#include <iostream>
#include <../sha3/sha3_model.h>
#include <../sha3/lzw_c_alg.c>
#include "UDPSocket.h"
using namespace std;

void sizer(int n)
{
	if (n == 0)
		cout << "Wrong input" << endl;
}

int main(int argc, char* argv[])
{
	// SOCKET s;
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);

	char buf[BUFLEN];
	char message[BUFLEN];

	unsigned short srv_port = 0;
	char srv_ip_addr[40];
	memset(srv_ip_addr, 0, 40);

	//create socket
	UDPSocket client_sock;

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;

	//si_other.sin_port = htons(PORT);
	//si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	if (1 == argc)
	{
		si_other.sin_port = htons(PORT);
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
		printf("1: Server - addr=%s , port=%d\n", SERVER, PORT);
	}
	else if (2 == argc)
	{
		//  si_other.sin_port = htons(PORT);
		//  si_other.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		si_other.sin_port = htons(atoi(argv[1]));
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
		printf("2: argv[0]: Server - addr=%s , port=%d\n", SERVER, atoi(argv[1]));
	}
	else
	{
		si_other.sin_port = htons(atoi(argv[2]));
		si_other.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		printf("3: Server - addr=%s , port=%d\n", argv[1], atoi(argv[2]));
	}

	//start communication  lifecircle
	while (1)
	{
		printf("\nEnter message : ");
		gets_s(message, BUFLEN);

		//send the message
		thread functorTest(sizer, strlen(message));
		int length = len(filename);
		functorTest.join();
		char filename[] = “message.bin”;
		transaction_t trans;
		unsigned char text[(int)strlen(message)];
		f_read(text, filename);
		trans.algo = SHA3_512;
		trans.message_bytes = length;
		trans.message = test;
		trans.result_digest = malloc(get_digest_length(trans.algo));
		trans.finalize = true;
		int error_code = sha3_dgst_calc(&trans);
		if (error_code == 0) {
			print_transaction(trans);
		}
		vector<int> message = compress(test);
		client_sock.SendDatagram(message, length, &trans, result_digest);
		free(trans.result_digest);
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call

		client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);

		puts(buf);
	}

	return 0;
}
