#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void create_file() {
    FILE *fp = fopen("parallel_task_file.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    fclose(fp);
}

void write_file() {
    FILE *fp = fopen("parallel_task_file.txt", "a");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    fprintf(fp, "Dosyaya veri ekleniyor.\n");
    fclose(fp);
}

void read_file() {
    FILE *fp = fopen("parallel_task_file.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);
}

int main() {
    pid_t pid1, pid2, pid3;

    //Dosya Olusturma
    pid1 = fork();
    if (pid1 == 0) {
        create_file();
        exit(0);
    }

    //Dosyaya Veri Yazma
    pid2 = fork();
    if (pid2 == 0) {
        write_file();
        exit(0);
    }
    
    //Dosya Icerigini Okuma
    pid3 = fork();
    if (pid3 == 0) {
        read_file();
        exit(0);
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    printf("Tüm child process'ler tamamlandi.\n");
    return 0;
}