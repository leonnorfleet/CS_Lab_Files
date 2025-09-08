#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{

	int pipefd[2];
	pid_t pid;

	if (argc < 2) {
		//perror("invalid arguments");
		exit(EINVAL);
	}

	if (pipe(pipefd) == -1) {
		//perror("pipe");
        exit(EXIT_FAILURE);
	}

	for(int i = 1; i < argc; ++i) {
		pipe(pipefd);
		pid = fork();

		if (pid < 0) {
			//perror("fork failed");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) { //child process

			if (i != argc - 1) {
				//STDOUT --> write end of pipe {sending from child to parent}
				if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
					//perror("redirect error");
					exit(1);
				}
				close(pipefd[1]); // close write end
				close(pipefd[0]); // close read end
			}

			execlp(argv[i], argv[i], NULL);
			//perror("exec error");
			exit(errno);
		}
		else { //parent process
			//wait for child
			int status = 0;
			int result = waitpid(pid, &status, 0);

			//check if child exited with success
			if (result < 0) {
				//fprintf(stderr, "wait failed\n");
				exit(1);
			}
			else if (WEXITSTATUS(status) || !WIFEXITED(status)) {
				//fprintf(stderr, "exec call failed\n");
				exit(1);
			}

			if (i != argc - 1) {
				//redirect from write end to stdout [!!change this later]
				if (dup2(pipefd[0], STDIN_FILENO) == -1) {
					//perror("redirect error");
					exit(errno);
				}

				close(pipefd[1]); // close write end
				close(pipefd[0]); // close read end
			}
		}

	}
	
	return 0;
}
