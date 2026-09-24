#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1) {
		printf("Failed to create socket!\n");
		return 1;
	}
	
	// Get linked list of addrinfo structures for all TCP/IP server sockets
	// listening on localhost (this machine), port 51728
	struct addrinfo* server_addr_list = NULL;
	struct addrinfo hints = {0};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	int info_result = getaddrinfo(
		"localhost",
		"51728",
		&hints,
		&server_addr_list
	);
	if (info_result != 0) {
		printf("Error on getaddrinfo!\n");
		return 1;
	}
	
	// Keep trying to connect until we succeed or until we've tried all of
	// the addresses in the list. In practice, if there's a TCP/IP server
	// running on port 51728 on this machine, the list will have a single
	// addrinfo structure in it referencing that server's listening socket.
	// Else, the list will be empty (in which case we probably would have
	// already printed an error and exited in the previous step)
	int connect_result = -1;
	struct addrinfo* itr = server_addr_list;
	while (itr != NULL && connect_result == -1) {
		connect_result = connect(
			socket_fd,
			itr->ai_addr,
			itr->ai_addrlen
		);
		itr = itr->ai_next;
	}

	// If connect_result is still -1, then we failed to connect
	if (connect_result == -1) {
		printf("Error on connect!\n");
		return 1;
	}

	// Message can be at most 256 characters, plus @@, plus null terminator
	// (259 chars total)
	char message_to_send[259] = {0};
	printf("Enter a message to send to the server (max 256 characters): ");
	fgets(message_to_send, 257, stdin); // 2nd arg includes null terminator
	// Strip \n and add @@ to the end
	size_t len = strlen(message_to_send);
	message_to_send[len - 1] = '@';
	message_to_send[len] = '@';
	
	// Send the message
	int total_bytes_sent = 0;
	int bytes_to_send = strlen(message_to_send); // Don't send the null terminator
	int bytes_remaining = bytes_to_send;
	while (total_bytes_sent < bytes_to_send) {
		int n_bytes_sent = send(
			socket_fd,
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

	// Receive response. Suppose it has the same requirements (same max
	// size, ends in @@)
	char message_received[259] = {0};
	int total_bytes_received = 0;
	int max_bytes_remaining = 258; // Null terminator is not sent in message
	while (strstr(message_received, "@@") == NULL) { // Until end of message
		int n_bytes_received = recv(
			socket_fd,
			message_received + total_bytes_received, // ptr arithmetic
			max_bytes_remaining,
			0
		);
		if (n_bytes_received > 0) {
			total_bytes_received += n_bytes_received;
			max_bytes_remaining -= n_bytes_received;
		} else if (n_bytes_received == 0) {
			printf("The writer is terminating communication (closed"
				"socket or called shutdown())\n");
			return 1;
		} else {
			printf("Error on recv()!\n");
			return 1;
		}
	}
	// Strip "@@" off of the end of the message
	len = strlen(message_received);
	message_received[len - 1] = '\0';
	message_received[len - 2] = '\0';
	printf("Response received from server: %s\n", message_received);

	shutdown(socket_fd, SHUT_RDWR);
	close(socket_fd);
	freeaddrinfo(server_addr_list);
}
