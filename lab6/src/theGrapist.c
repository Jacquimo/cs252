#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

//#define killCommand "pkill -SIGKILL $(pgrep -u $USER -l |grep -m 1 -vE \"(bash|sh|awesomeSauce|arena)\"| cut -d' ' -f2)"

void sigChildHandler(int signum);
void executeAttack();
char** args;
int numArgs;

int main(int argc, char** argv) {
	//system("pkill -KILL flash");

	numArgs = argc;
	args = argv;

	if (strncmp(args[0], "./", 2) == 0)
		args[0] = args[0] + 2;
	
	/*struct sigaction newChild;
	newChild.sa_handler = sigChildHandler;
	newChild.sa_flags = SA_NOCLDWAIT | SA_RESTART;
	sigaction(SIGCHLD, &newChild, NULL);
	sigaction(SIGTERM, &newChild, NULL);
	sigaction(SIGINT, &newChild, NULL);
	sigaction(SIGQUIT, &newChild, NULL);
	sigaction(SIGHUP, &newChild, NULL);
	*/

	executeAttack();
}

void executeAttack() {
	int mypid = getpid();
	char searchStr[100];
	sprintf(searchStr, "/proc/%d/stat", mypid);

	FILE* stat = fopen(searchStr, "r");
	int mygroupID;
	fscanf(stat, "%*d %*s %*c %*d %d", &mygroupID);
	fclose(stat);
	//fprintf(stderr, "group id: %d\n", mygroupID);

	//int count = 1;
	while (1) {
		//fprintf(stderr, "executing yay!!!\n");
		int childID = fork();
		if (childID == 0) {
			//printf("Child successfully forked\n");
			executeAttack();
		}
		if (childID > 0) {
			waitpid(childID, NULL, WNOHANG|WUNTRACED);
		}

		//int count = 0;
		int bound = mypid + 50;// * count;
		for (int attackID = mypid - 50; attackID < bound; ++attackID) {
			sprintf(searchStr, "/proc/%d/stat", attackID);
			FILE* pros = fopen(searchStr, "r");
			
			if (pros != NULL) {
				int groupID;
				fscanf(pros, "%*d %s %*c %*d %d", (char*)&searchStr, &groupID);

				char* attackName = searchStr + 1;
				attackName[strlen(attackName)-1] = 0;

				if (strcmp(args[0], attackName) != 0
						//&& strcmp(attackName, "arena") != 0 
						&& strcmp(attackName, "bash") != 0 
						&& groupID < 2 * attackID
						&& strcmp(attackName, "su") != 0
						&& strcmp(attackName, "sudo") != 0) {

						kill(attackID, SIGKILL);
					if (groupID != mygroupID) {
						kill(groupID, SIGKILL);
						setpgid(mypid, groupID);

						char buf[100];
						buf[0] = 0;
						char* command = strcat(buf, "pkill -KILL ");
						command = strcat(command, attackName);
						system(command);

						childID = fork();
						if (childID == 0)
							executeAttack();
						
					}

					//fprintf(stderr, "Killed group process %d\t name: %s\tprogram: \"%s\"\n", groupID, attackName, args[0]);
				}
				fclose(pros);
			}
		}
		//++count;
	}
}


void sigChildHandler(int signum) {
	fprintf(stderr, "Signal handler activated\n");

	pid_t pid;
	while ((pid = waitpid(-1, NULL, WNOHANG|WUNTRACED)) > -1) ;

	int ret = fork();
	if (ret == 0) {
		/*char* args[4];
		args[0] = "awesomeSauce";
		args[1] = "30";
		args[2] = "2";
		args[3] = NULL;
		main(3, args);
		*/
		main(numArgs, args);
	}
}
