#include "backend.h"
#include <sstream>
#include <cstdio>
#include <unistd.h>

Backend::Backend()
{
	pipe(bc_in_pipe);
	pipe(bc_out_pipe);

	bc_in = fdopen(bc_in_pipe[1], "w");
	bc_in_fd = bc_in_pipe[1];
	bc_out =fdopen(bc_out_pipe[0], "r");
	bc_out_fd = bc_out_pipe[0];
}

Backend::~Backend()
{
	fprintf(bc_in, "quit\n");
}

CalcResult::CalcResult(std::string str) : is_error(false), str(str) {

}

CalcResult::CalcResult(const char *str) : is_error(false), str(str) {

}

CalcResult::CalcResult(CalcError ce) : is_error(false), ce(ce) {

}

CalcResult Backend::calc(std::string input) {
    return "Not Implemented";
}

std::string Backend::calcNoExcp(std::string input) {
	pid_t pid;
	if (pid = fork()) {
		fprintf(bc_in, "scale=10\n");
		fprintf(bc_in, "%s\n", input.c_str());
		fprintf(bc_in, "quit\n");
		fflush(bc_in);
		fd_set set;
		FD_ZERO(&set);
		FD_SET(bc_out_fd, &set);
		struct timeval wait;
		wait.tv_sec = 1;
		wait.tv_usec = 0;
		if (select(FD_SETSIZE, &set, NULL, NULL, &wait))
		{
			printf("bc has calculate result\n");
			char buf[64];
			fscanf(bc_out, "%s", buf);
			std::string out(buf);
			return out;
		}
		else
		{
			printf("error while calculate\n");
			return std::string("0");
		}
	}
	else {
		dup2(bc_in_pipe[0], STDIN_FILENO);
		dup2(bc_out_pipe[1], STDOUT_FILENO);
		execlp("bc", "bc", NULL);
		printf("there is no program bc!!!\n");
	}
}

