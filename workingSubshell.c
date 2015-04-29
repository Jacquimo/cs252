"`".+"`" {
	int tempin = dup(0);
	int tempout = dup(1);
	int temperr = dup(2);

	char input[strlen(yytext+1) + 2]; input[0] = 0;
	strcat(input, yytext+1);
	input[strlen(input)-1] = '\n'; // remove trailing backtick and add newline
	//fprintf(stderr, "got it \"%s\"", input);

	strcat(input, "\nexit\n");

	int toChild[2];
	int toParent[2];
	pipe(toChild);
	pipe(toParent);

	dup2(toChild[0], 0);
	close(toChild[0]);
	dup2(toParent[1], 1);
	close(toParent[1]);

	int child = fork();
	if (child == 0) {
		close(toChild[1]);
		close(toParent[0]);
		char* stack[2];
		stack[0] = "shell";
		stack[1] = NULL;
		execvp("shell", stack);
		perror("execvp in dot L");
	}
	dup2(toChild[1], 1);
	close(toChild[1]);
	dup2(toParent[0], 0);
	close(toParent[0]);
	
	write(1, input, strlen(input));
	close(1);
	// This commented code showed that the string is being written to the pipe
	//int temp = 1;
	//do {
	//	if (read(0, &temp, sizeof(char)) <= 0) break;
	//	fprintf(stderr, "%c\n", temp);
	//} while (temp != EOF);
	

	int max = 1024, num = 0;
	char* result = (char*)malloc(sizeof(char) * max);
	result[num] = 0;

	int c = 1;
	do {
		if (read(0, &c, sizeof(char)) <= 0) break;
		if (c == '\n') { result[num++] = c; break; }
		if (c != EOF) result[num++] = c;
		if (num+1 >= max) {
			max *= 2;
			result = (char*)realloc(result, sizeof(char) * max);
		}
	} while (c != EOF);
	result[num] = 0;
	close(0);

	char* ret = strdup(result);
	free(result);

	char* lex = ret + strlen(ret) - 1; // get pointer to last character
	while (lex >= ret) {
		unput(*lex);
		--lex;
	}

	dup2(tempin, 0);
	dup2(tempout, 1);
	dup2(temperr, 2);
}