#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/*
 * Напишіть програму "будильник":
 * програма через командний рядок отримує необхідний інтервал часу (у секундах, для зручності налагодження та демонстрації)
 * і текстове повідомлення;
 * завершує основний процес,
 *
 * а в дочірньому
 * за допомогою функцій alarm і pause
 * через вказаний час
 * виводить заданий текст у стандартний потік виведення.
*/

void alarmHandler(int signal) {
    printf("Час вичерпано!\n");
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <interval> <message>\n", argv[0]);
        return 1;
    }

    int interval = atoi(argv[1]);
    char *message = argv[2];

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        return 0;
    }

    signal(SIGALRM, alarmHandler);
    printf("(!) Будильник спрацює через %d секунд з повідомленням: \"%s\"\n", interval, message);
    alarm(interval);
    pause();
    printf("%s\n", message);
    exit(0);
}