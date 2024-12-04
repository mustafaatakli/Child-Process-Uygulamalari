#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Child process olusturuldu
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("Dosya icerigi ekrana yazdiriliyor:\n");
        //Child process dosya icerigini ekrana yazdirir. (cat komutunu calistirarak)
        execlp("cat", "cat", "dosya.txt", NULL);
        perror("execlp");
        _exit(1); 
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process tamamlandi, cikis kodu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process beklenmedik sekilde sonlandi!\n");
        }
    }

    return 0;
}