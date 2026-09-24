#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
	// Create socket
	int listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	// Bind to port 51728 and all network interfaces
	struct sockaddr_in bind_addr;
	bind_addr.sin_family = AF_INET;
	bind_addr.sin_port = htons(51728);
	bind_addr.sin_addr.s_addr = INADDR_ANY;
	int bind_result = bind(
		listen_socket_fd,
		(struct sockaddr*) &bind_addr,
		sizeof(bind_addr)
	);
	if (bind_result == -1) {
		printf("Error on bind!\n");
		return 1;
	}
	
	// Enable the socket to listen for up to 5 connections at a time
	int listen_result = listen(listen_socket_fd, 5);
	if (listen_result == -1) {
		printf("Error on listen!\n");
		return 1;
	}

	// Tell the listening socket to accept a new connection from a client,
	// which will then be represented as a new communication socket with
	// its own file descriptor
	while (1) {
		struct sockaddr_in client_addr;
		socklen_t client_addr_size = sizeof(client_addr);
		int communication_socket_fd = accept(
			listen_socket_fd,
			(struct sockaddr*) &client_addr,
			&client_addr_size
		);
		if (communication_socket_fd == -1) {
			printf("Error on accept!\n");
			return 1;
		}

		// Receive message from client. Recall that it will end in
		// "@@"
		char message_received[259] = {0};
		int total_bytes_received = 0;
		int max_bytes_remaining = 258; // Null terminator is not sent in message
		while (strstr(message_received, "@@") == NULL) { // Until end of message
			int n_bytes_received = recv(
				communication_socket_fd,
				message_received + total_bytes_received, // ptr arithmetic
				max_bytes_remaining,
				0
			);
			if (n_bytes_received > 0) {
				total_bytes_received += n_bytes_received;
				max_bytes_remaining -= n_bytes_received;
			} else if (n_bytes_received == 0) {
				printf("The writer is terminating "
					"communication (closed socket or "
					"called shutdown())\n");
				return 1;
			} else {
				printf("Error on recv()!\n");
				return 1;
			}
		}
		
		// Strip "@@" off of the end of the message
		size_t len = strlen(message_received);
		message_received[len - 1] = '\0';
		message_received[len - 2] = '\0';
		printf("Message received from client: %s\n", message_received);
		
		// Send response
		char* message_to_send;
		if (strcmp(message_received, "open sesame") == 0) {
			message_to_send = "You guessed the secret passphrase! "
				"Excellent work. Here, have a cookie :)@@";
		} else if (strcmp(message_received, "what's your name?") == 0) {
			message_to_send = "I'm ChatBot9001, the world's "
				"smartest chatbot!@@";
		} else {
			message_to_send = "Sorry, I don't know what that "
				"means.@@";
		}
		int total_bytes_sent = 0;
		int bytes_to_send = strlen(message_to_send); // Don't send the null terminator
		int bytes_remaining = bytes_to_send;
		while (total_bytes_sent < bytes_to_send) {
			int n_bytes_sent = send(
				communication_socket_fd,
				message_to_send + total_bytes_sent, // ptr arithmetic
				bytes_remaining,
				0
			);
			if (n_bytes_sent != -1) {
				total_bytes_sent += n_bytes_sent;
				bytes_remaining -= n_bytes_sent;
			} else {
				printf("Error on send()!\n");
			}
		}

		shutdown(communication_socket_fd, SHUT_RDWR);
		close(communication_socket_fd);
	}
}
