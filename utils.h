#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

void fatal(char * message){
	char error_message[100];
	strcpy(error_message, "[!!] Fatal Error ");
	strncat(error_message, message, 83);
	perror(error_message);
	exit(-1);
	
}

int send_string(int sockfd, unsigned char *buffer){
	int sent_bytes, bytes_to_send;
	bytes_to_send = strlen(buffer);
	while(bytes_to_send > 0){
		sent_bytes = send(sockfd, buffer, bytes_to_send, 0);
		if(sent_bytes == -1) return 0;
		bytes_to_send -= sent_bytes;
		buffer += sent_bytes;
	}
	return 1;
}

int recv_line(int sockfd, unsigned char *buffer){
#define EOL "\r\n"
#define EOL_SIZE 2
	
	unsigned char *ptr;
	int eol_matched = 0;

	ptr = buffer;
	while(recv(sockfd, ptr, 1, 0) == 1){ //read one byte
		if(*ptr == EOL[eol_matched]){
			eol_matched++;
			if(eol_matched == EOL_SIZE){
				*(ptr + 1 - EOL_SIZE) = '\0';
				return strlen(buffer);
			}
		} else {
			eol_matched = 0;
		}
		ptr++;
	}

	return 0;

}
