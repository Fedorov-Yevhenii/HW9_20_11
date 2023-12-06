#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handleSIGINT(int signum) {
    printf("SIGINT: %d\n", signum);
}

void handleSIGTERM(int signum) {
    printf("SIGTERM: %d\n", signum);
}

void handleSIGUSR1(int signum) {
    printf("SIGUSR1: %d. Вихід.\n", signum);
    exit(0);
}

/* ВЕРСІЯ ПРОГРАМИ РЕАЛІЗОВАНА ЗА ДОПОМОГОЮ ФУНКЦІЇ SIGACTION */

int main() {

    struct sigaction sa;

    sa.sa_handler = handleSIGINT;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = handleSIGTERM;
    sigaction(SIGTERM, &sa, NULL);

    sa.sa_handler = handleSIGUSR1;
    sigaction(SIGUSR1, &sa, NULL);

    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    printf("Ідентифікатор процесу: %d\n", getpid());
    printf("Очікування сигналів...\n");

    while (1) {
        pause();
    }
}
