//
// Created by lab on 23/07/25.
//

#include "shell.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "pico/stdlib.h"
using namespace shell;

Command::Command(char* command) {
    this->command_ = strtok(command, " ");
    this->argument_ = strtok(nullptr, "\0");

    switch (this->command_) {
        case CommandType::LED:
            this->type_ = CommandType::LED;
            break;
        case CommandType::SET:
            this->type_ = CommandType::SET;
            break;
        case CommandType::ECHO:
            this->type_ = CommandType::ECHO;
            break;
        case CommandType::SLEEP:
            this->type_ = CommandType::SLEEP;
            break;
        case CommandType::SPEAKER:
            this->type_ = CommandType::SPEAKER;
            break;
        default:
            this->type_ = CommandType::UNKNOWN;
    }
}

CommandType Command::getType() const {
    return this->type_;
}

char* Command::getCommand() const {
    return this->command_;
}

char* Command::getArgument() const {
    return this->argument_;
}

bool Command::isValid() const {
    return this->type_ == CommandType::UNKNOWN;
}

void Command::execute() const {
    switch (this->type_) {
        case CommandType::LED:
            led(this->argument_);
            break;
        case CommandType::SET:
            set(this->argument_);
            break;
        case CommandType::ECHO:
            echo(this->argument_);
            break;
        case CommandType::SLEEP:
            sleep(this->argument_);
            break;
        case CommandType::SPEAKER:
            speaker(this->argument_);
            break;
        case CommandType::UNKNOWN:
            printf("ERROR: Command not found\n");
    }
}

void led(char* arguments) {
    char* action = strtok(arguments, " ");
    char* arg = strtok(nullptr, "\0");

    // checks the action
    if (strcmp(action, "on") == 0) {
        // checks the argument
        if (strcmp(arg, "red") == 0) {
            gpio_init(LED_RED);
            gpio_set_dir(LED_RED, GPIO_OUT);
            gpio_put(LED_RED, true);
        }
        else if (strcmp(arg, "blue") == 0) {
            gpio_init(LED_BLUE);
            gpio_set_dir(LED_BLUE, GPIO_OUT);
            gpio_put(LED_BLUE, true);
        }
        else if (strcmp(arg, "green") == 0) {
            gpio_init(LED_GREEN);
            gpio_set_dir(LED_GREEN, GPIO_OUT);
            gpio_put(LED_GREEN, true);
        }
        else {
            printf("[ERROR] led color not valid: %s", arg);
        }
    }
    else if (strcmp(action, "off") == 0) {

        if (strcmp(arg, "red") == 0) {
            gpio_put(LED_RED, false);
            gpio_deinit(LED_RED);
        }
        else if (strcmp(arg, "blue") == 0) {
            gpio_put(LED_BLUE, false);
            gpio_deinit(LED_BLUE);
        }
        else if (strcmp(arg, "green") == 0) {
            gpio_put(LED_GREEN, false);
            gpio_deinit(LED_GREEN);
        }
    }
    else {
        printf("[ERROR] Invalid action: %s", action);
    }
}