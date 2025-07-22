#include <iostream>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "cstring"
using namespace std;

#define LENGTH 80

int main() {
    stdio_usb_init();


    char line[LENGTH+1];
    int character;

    while (true) {
        printf("> ");
        for (int i = 0; (i < LENGTH) && ((character = getchar()) != '\n') &&
            (character != EOF); i++) line[i] = (character);
        line[LENGTH + 1] = '\0';

        char *token = strtok(line, " ");
        while (token != NULL) {}

        switch ()
    }

    return 0;
}