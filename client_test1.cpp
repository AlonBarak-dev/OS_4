// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#define PORT 3490

using namespace std;

int main(int argc, char const* argv[])
{
	cout << "client1" << endl;
	int sock = 0, valread = 0;
	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

    // open the FILE
    FILE* f = fopen("client1.txt", "r");


    char command[1024] = {0};
    while (true)
    {
        fgets(command, 5, f);
        send(sock, command, strlen(command), 0);
        if (strncmp(command, "TOP",3) == 0)
        {
			bzero(command, 1024);
            recv(sock, command, 1024,0);
			if (strcmp(command, "-") == 0)
			{
				printf("OUTPUT:\n");
			}
			else{
				printf("OUTPUT:%s\n", command);
			}
        }
        bzero(command, 1024);
        
    }
    
	valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);
	return 0;
}
