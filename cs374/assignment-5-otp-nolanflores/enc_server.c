#include <stdio.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char* message, int message_length, char* key, char* encrypted_message){
	for(int i = 0; i < message_length; i++){
		int m, k;
		if(message[i] == ' ')
			m = 26;
		else
			m = ((int)message[i])-65;
		if(key[i] == ' ')
			k = 26;
		else
			k = ((int)key[i])-65;
		int e = (m + k) % 27;
		if(e < 26)
			encrypted_message[i] = (char)(e+65);
		else
			encrypted_message[i] = ' ';
	}
	encrypted_message[message_length] = '@';
	encrypted_message[message_length+1] = '@';
}

void send_message(int socket_fd, char* message){
	int total_bytes_sent = 0;
	int bytes_to_send = strlen(message);
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
			fprintf(stderr, "Error sending\n");
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
	if(argc <= 1){
		fprintf(stderr, "Listening port not specified.\n");
		return 1;
	}
	int port = (int)strtol(argv[1], NULL, 10);
	int listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in bind_addr;
	bind_addr.sin_family = AF_INET;
	bind_addr.sin_port = htons(port);
	bind_addr.sin_addr.s_addr = INADDR_ANY;
	int bind_result = bind(
		listen_socket_fd,
		(struct sockaddr*)&bind_addr,
		sizeof(bind_addr)
	);
	if(bind_result == -1){
		fprintf(stderr, "Binding Error.\n");
		return 1;
	}

	int listen_result = listen(listen_socket_fd, 5);
	if(listen_result == -1){
		fprintf(stderr, "Listening Error.\n");
		return 1;
	}

	pid_t children[5];
	int num_children = 0;
	while(1){
		for(int i = 0; i < num_children; i++){
			int status = 0;
			pid_t result = waitpid(children[i], &status, WNOHANG);
			if(result > 0){
				children[i] = children[num_children-1];
				num_children--;
				i--;
			}
		}
		if(num_children >= 5)
			continue;

		struct sockaddr_in client_addr;
		socklen_t client_addr_size = sizeof(client_addr);
		int communication_socket_fd = accept(
			listen_socket_fd,
			(struct sockaddr*)&client_addr,
			&client_addr_size
		);
		if(communication_socket_fd == -1){
			fprintf(stderr, "Accepting Error.\n");
			return 1;
		}
		
		pid_t child_pid = fork();
		if(child_pid == 0){//child
			char client_type[1024] = {0};
			receive_message(communication_socket_fd, client_type);
			send_message(communication_socket_fd, "E@@");
			if(client_type[0] != 'E'){
				fprintf(stderr, "Client is incompatible (expected encryption client).\n");
			}else{
				char message[1026] = {0};
				int m_len = receive_message(communication_socket_fd, message);
				char key[1026] = {0};
				receive_message(communication_socket_fd, key);
				char encrypted_message[1026] = {0};
				encrypt(message, m_len, key, encrypted_message);
				send_message(communication_socket_fd, encrypted_message);
			}
			close(communication_socket_fd);
			exit(0);
		}else{//parent
			children[num_children++] = child_pid;
		}
	}
}
