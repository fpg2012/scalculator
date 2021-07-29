#include "backend.h"
#include <sstream>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>

Backend::Backend()
{
}

Backend::~Backend()
{
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
    pipe(bc_in_pipe);
    pipe(bc_out_pipe);

    bc_in = fdopen(bc_in_pipe[1], "w");
    bc_in_fd = bc_in_pipe[1];
    bc_out =fdopen(bc_out_pipe[0], "r");
    bc_out_fd = bc_out_pipe[0];

    pid_t pid;
    if (pid = fork()) {
        fprintf(bc_in, "scale=10\n");
        fprintf(bc_in, "%s\n", input.c_str());
        fprintf(bc_in, "quit\n");
        fclose(bc_in);
        close(bc_in_fd);
        waitpid(pid, NULL, 0);
        close(bc_out_pipe[1]);

        printf("bc has calculate result\n");
        char buf[64];
        int len = fread(buf, 1, 64 - 1, bc_out);
        buf[len] = '\0';
        std::string out(buf);

        fclose(bc_out);
        close(bc_out_fd);
        return out;
    }
    else {
        dup2(bc_in_pipe[0], STDIN_FILENO);
        dup2(bc_out_pipe[1], STDOUT_FILENO);
        execlp("bc", "bc", "-l", NULL);
        printf("there is no program bc!!!\n");
    }
}

