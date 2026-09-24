#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int foreground_mode = 0;

void handle_SIGTSTP(int signo){
	if(!foreground_mode){
        	char* msg = "\nEntering foreground-only mode (& is now ignored)\n";
        	write(STDOUT_FILENO, msg, strlen(msg));
        	foreground_mode = 1;
	}else{
        	char* msg = "\nExiting foreground-only mode\n";
        	write(STDOUT_FILENO, msg, strlen(msg));
        	foreground_mode = 0;
	}
}

void print_status(int status){
	if(WIFEXITED(status))
		printf("exit value %d\n", WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("terminated by signal %d\n", WTERMSIG(status));
}

int check_background_children(pid_t* children, int n){
	for(int i = 0; i < n; i++){
		int status;
		pid_t pid = waitpid(children[i], &status, WNOHANG);
		if(pid > 0){
       			printf("background pid %d is done: ", pid);
			print_status(status);
			children[i] = children[n-1];
			n--;
			i--;
		}
	}
	return n;
}
	

int get_cmd_line(char* cmd){
	char* line = NULL;
	size_t len = 0;
	ssize_t n = getline(&line, &len, stdin);
	if(n <= 1 || line[0] == '#'){
		free(line);
		clearerr(stdin);
		return 1;
	}
	int cmd_i = 0;
	for(int i = 0; i < n-1; i++){
		if(line[i] == '$' && line[i+1] == '$'){
			pid_t pid = getpid();
			char pid_string[8];
 			int pid_n = sprintf(pid_string, "%d", pid);
			for(int j = 0; j < pid_n; j++){
				cmd[cmd_i++] = pid_string[j];
			}
			i++;
		}else{
			cmd[cmd_i++] = line[i]; 
		}
	}
	cmd[cmd_i] = '\0';
	free(line);
	return 0;
}

int tokenize_cmd(char* buffer, char** arguments, char** f_in, char** f_out){
	char* saveptr = NULL;
	int num_args = 0;
	int foreground = 1;

	char* buff_arg = strtok_r(buffer, " ", &saveptr);
	while(buff_arg != NULL){
		if(buff_arg[0] == '<'){
			buff_arg = strtok_r(NULL, " ", &saveptr);
			*f_in = strdup(buff_arg);
		}else if(buff_arg[0] == '>'){
			buff_arg = strtok_r(NULL, " ", &saveptr);
			*f_out = strdup(buff_arg);
		}else if(buff_arg[0] == '&'){
			foreground = 0;
		}else{
			arguments[num_args++] = strdup(buff_arg);
		}
		buff_arg = strtok_r(NULL, " ", &saveptr);
	}
	return foreground;
}

void free_cmd_tokens(char** arguments, char* f_in, char* f_out){
	for(int i = 0; i < 20; i++){
		free(arguments[i]);
	}
	free(f_in);
	free(f_out);
}

void change_directory(char* target_dir){
	if(target_dir == NULL)
		chdir(getenv("HOME"));
	else if(chdir(target_dir) != 0)
		printf("Unable to change directory\n");
}



int main(){
	struct sigaction SIGINT_action = {0};
	SIGINT_action.sa_handler = SIG_IGN;
	sigfillset(&SIGINT_action.sa_mask);
	SIGINT_action.sa_flags = 0;
	sigaction(SIGINT, &SIGINT_action, NULL);

	struct sigaction SIGTSTP_action = {0};
	SIGTSTP_action.sa_handler = handle_SIGTSTP;
	sigfillset(&SIGTSTP_action.sa_mask);
	SIGTSTP_action.sa_flags = 0;
	sigaction(SIGTSTP, &SIGTSTP_action, NULL);

	pid_t processes[100];
	int num_processes = 0;

	int last_status = 0;
	
	while(1){
		num_processes = check_background_children(processes, num_processes);		

		printf(":");
		fflush(stdout);
		
		char line[2049];
		if(get_cmd_line(line))
			continue;

		char* arguments[21] = {NULL};
		char* f_in = NULL;
		char* f_out = NULL;
		int foreground = tokenize_cmd(line, arguments, &f_in, &f_out);
		if(foreground_mode)
			foreground = 1;
		
		if(strcmp(arguments[0], "exit") == 0){
			free_cmd_tokens(arguments, f_in, f_out);
			break;
		}else if(strcmp(arguments[0], "cd") == 0){ 
			change_directory(arguments[1]);
		}else if(strcmp(arguments[0], "status") == 0){
			print_status(last_status);
		}else{
			pid_t child_pid = fork();
			if(child_pid == 0){
				//child
				if(foreground){
					SIGINT_action.sa_handler = SIG_DFL;
    					sigaction(SIGINT, &SIGINT_action, NULL);
				}
				SIGTSTP_action.sa_handler = SIG_IGN;
				sigaction(SIGTSTP, &SIGTSTP_action, NULL);
				
				if(f_in != NULL || !foreground){
					char* file = (f_in != NULL) ? f_in : "/dev/null";
					int fd_in = open(file, O_RDONLY);
					if(fd_in == -1){
						fprintf(stderr, "cannot open %s for input\n", file);
						exit(1);
					}
					dup2(fd_in, STDIN_FILENO);
					close(fd_in);
				}
				if(f_out != NULL || !foreground){
					char* file = (f_out != NULL) ? f_out : "/dev/null";
					int fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if(fd_out == -1){
						fprintf(stderr, "Cannout open %s for output\n", file);
						exit(1);
					}
					dup2(fd_out, STDOUT_FILENO);
					close(fd_out);
				}

				execvp(arguments[0], arguments);
				printf("Bad exec\n");
				exit(1);
			}else{
				//parent
				if(foreground){
					waitpid(child_pid, &last_status, 0);
				}else{
					printf("background pid is %d\n", child_pid);
					processes[num_processes++] = child_pid;
				}
			}
		}
		free_cmd_tokens(arguments, f_in, f_out);
	}
	return 0;
}
