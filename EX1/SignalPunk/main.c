#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
 * Напишіть програму, у якій
 * визначте користувацьку реакцію процесу на сигнали SIGINT,
 * SIGTERM (вивід інформації про захоплення відповідного сигналу)
 * та SIGUSR1 (завершення роботи програми),
 * відновіть поведінку за замовчуванням для сигналу SIGPROF та ігноруйте сигнал SIGHUP.
 * + Для затримки виконання процесу використовуйте функцію pause() у безкінечному циклі.
 * Переконайтеся в працездатності програми (за допомогою команди kill оболонки надішліть процесу необхідний сигнал і простежте за реакцією).
 * Реалізуйте дві версії програми: за допомогою функції signal
 * і за допомогою функції sigaction.
*/

void handleSIGINT(int signalValue) {
    printf("SIGINT: %d\n", signalValue);
}

void handleSIGTERM(int signalValue) {
    printf("SIGTERM: %d\n", signalValue);
}

void handleSIGUSR1(int signalValue) {
    printf("SIGUSR1: %d. Вихід.\n", signalValue);
    exit(0);
}

/* ВЕРСІЯ ПРОГРАМИ РЕАЛІЗОВАНА ЗА ДОПОМОГОЮ ФУНКЦІЇ SIGNAL */

int main() {

    // Для сигналів SIGINT і SIGTERM обробники виводять відповідне повідомлення.
    signal(SIGINT, handleSIGINT);
    signal(SIGTERM, handleSIGTERM);

    // Для сигналу SIGUSR1 обробник відповідає завершенням роботи.
    signal(SIGUSR1, handleSIGUSR1);

    // Для сигналів SIGPROF і SIGHUP обробники нічого не роблять.
    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    printf("Ідентифікатор процесу: %d\n", getpid());
    printf("Очікування сигналу...\n");

    while (1) {
        pause(); // Безкінечний цикл для затримки виконання процесу
    }
}
