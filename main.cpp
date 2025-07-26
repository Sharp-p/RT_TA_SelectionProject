#include <iostream>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "shell.hpp"
using namespace std;
using namespace shell;

#define LENGTH 80

int main() {
    stdio_usb_init();
    // variables will be relative to a single session
    Shell shell;

    string line;
    int character;


    while (true) {
        printf("> ");
        // reads a line from the prompt
        for (int i = 0; (i < LENGTH) && ((character = getchar()) != '\n') &&
            (character != EOF); i++) line.append(1, character);

        // creates a command object
        Command command (line, shell);
        // executes the command
        command.execute();
    }

    return 0;
}