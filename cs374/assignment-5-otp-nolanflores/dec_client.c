#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int string_from_file(char* filename, char* string){
	FILE* file = fopen(filename, "r");
	if(file == NULL){
		fprintf(stderr, "Unable to open file: %s\n", filename);
		return -1;
	}
	int length = 0;
	while(1){
		char c = (char)fgetc(file);
		if(feof(file))
			break;
		if(('A' <= c && c <= 'Z') || c == ' '){
			string[length++] = c;
		}else if(c == '\n'){
			break;
		}else{
			fprintf(stderr, "Invalid character %c in file: %s\n", c, filename);
			return -1;
		}
	}
	string[length++] = '@';
	string[length++] = '@';
	return length;
}

void send_message(int socket_fd, char* message, int bytes_to_send){
	int total_bytes_sent = 0;
	int bytes_remaining = bytes_to_send;
	while(total_bytes_sent < bytes_to_send){
		int n_bytes_sent = send(
			socket_fd,
			message + total_bytes_sent,
			bytes_remaining,
			0
		);
		if(n_bytes_sent != -1){
			total_bytes_sent += n_bytes_sent;
			bytes_remaining -= n_bytes_sent;
		}else{
			fprintf(stderr, "Error sending message\n");
		}
	}	
}

int receive_message(int socket_fd, char* message_received){
	int total_bytes_received = 0;
	int max_bytes_remaining = 1026;
	while(strstr(message_received, "@@") == NULL){
		int n_bytes_received = recv(
			socket_fd,
			message_received + total_bytes_received,
			max_bytes_remaining,
			0
		);
		if(n_bytes_received > 0){
		total_bytes_received += n_bytes_received;
		max_bytes_remaining -= n_bytes_received;
		}else if(n_bytes_received == 0){
			fprintf(stderr, "Socket closed before data was received\n");
			return -1;
		}else{
			fprintf(stderr, "Error receiving data\n");
			return -1;
		}
	}
	size_t len = strlen(message_received);
	message_received[len - 1] = '\0';
	message_received[len - 2] = '\0';
	return (int)len-2;
}

int main(int argc, char* argv[]){
	if(argc < 4){
		fprintf(stderr, "Too few arguments supplied.\n");
		return 1;
	}
	char crypttxt[1026] = {0};
	int ct_len = string_from_file(argv[1], crypttxt);
	if(ct_len == -1)
		return 1;
	char key[1026] = {0};
	int k_len = string_from_file(argv[2], key);
	if(k_len == -1)
		return 1;
	if(k_len < ct_len){
		fprintf(stderr, "Error, key is shorter than encrypted text.\n");
		return 1;
	}


	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1){
		fprintf(stderr, "Failed to create socket!\n");
		return 2;
	}
	struct addrinfo* server_addr_info = NULL;
	struct addrinfo hints = {0};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	int info_result = getaddrinfo(
		"localhost",
		argv[3],
		&hints,
		&server_addr_info
	);
	if(info_result != 0){
		fprintf(stderr, "Error getting address info\n");
		return 2;
	}
	int connect_result = -1;
	struct addrinfo* itr = server_addr_info;
	while(itr != NULL && connect_result == -1){
		connect_result = connect(
			socket_fd,
			itr->ai_addr,
			itr->ai_addrlen
		);
		itr = itr->ai_next;
	}
	if(connect_result == -1){
		printf("Unable to connect\n");
		return 2;
	}
	
	send_message(socket_fd, "D@@", 3);
	char server_type[1026] = {0};
	int rec_result = receive_message(socket_fd, server_type);
	if(rec_result == -1)
		return 2;
	if(server_type[0] != 'D'){
		fprintf(stderr, "Server incompatible (expecting decryption server).\n");
		close(socket_fd);
		freeaddrinfo(server_addr_info);
		return 2;
	}
	send_message(socket_fd, crypttxt, ct_len);
	send_message(socket_fd, key, k_len);
	char message[1026] = {0};
	rec_result = receive_message(socket_fd, message);
	if(rec_result == -1)
		return 2;
	printf("%s\n", message);

	close(socket_fd);
	freeaddrinfo(server_addr_info);
}
