#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) { 
        FILE *fp = fopen("nonexistent_file.txt", "r");
        if (fp == NULL) {
            perror("fopen");
            abort(); //Zorla cikis
        } else {
            fclose(fp);
            exit(0); //Basarili cikis
        }
    } else { 
        int status;
        //Durumların analizi
        waitpid(pid, &status, 0);

        if (WIFSIGNALED(status)) {
            printf("Child process sinyal ile sonlandi: %d\n", WTERMSIG(status));
        } else if (WIFEXITED(status)) {
            printf("Child process normal şekilde sonlandi, cikis kodu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process beklenmedik sekilde sonlandi\n");
        }
    }

    return 0;
}