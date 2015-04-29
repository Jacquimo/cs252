#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <sys/wait.h>

#define killCommand "pkill -SIGKILL $(pgrep -u $USER -l |grep -m 1 -vE \"(bash|sh|awesomeSauce|arena)\"| cut -d' ' -f2)"

void sigChildHandler(int signum);

int main(int argc, char** argv) {
		int handled = 0;
		while (1) {
			if (system(killCommand) < 0) {
				char* args[4];
				args[0] = "/bin/bash";
				args[1] = "-c";
				args[2] = killCommand;
				args[3] = NULL;
				execv(args[0], args);
				perror("System function execvp failed");
			}

			int frk = fork();
			if (frk < 0) {
				pid_t pid = getpid();
				int bound = atoi(argv[1]);

				for (int i = 0; i < bound; ++i) {
					kill(pid + i, SIGHUP);
				}
				
				

				/*char* args[4];
				args[0] = "bash";
				args[1] = "-c";
				args[2] = killCommand;
				args[3] = NULL;
				execvp(args[0], args);
				*/
			}
			else if (frk == 0) {
				main(argc, argv);
			}

			if (!handled) {
				struct sigaction newChild;
				newChild.sa_handler = sigChildHandler;
				newChild.sa_flags = SA_NOCLDWAIT | SA_RESTART;
				sigaction(SIGCHLD, &newChild, NULL);
				sigaction(SIGTERM, &newChild, NULL);
				sigaction(SIGINT, &newChild, NULL);
				sigaction(SIGQUIT, &newChild, NULL);
				sigaction(SIGHUP, &newChild, NULL);
				handled = 1;
			}

			//sched_yield();
		}
}


void sigChildHandler(int signum) {
	pid_t pid;
	while ((pid = waitpid(-1, NULL, WNOHANG|WUNTRACED)) > -1) ;

	int ret = fork();
	if (ret == 0) {
		char* args[4];
		args[0] = "awesomeSauce";
		args[1] = "30";
		args[2] = "2";
		args[3] = NULL;
		main(3, args);
	}
}
