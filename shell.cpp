//
// Created by lab on 23/07/25.
//

#include "shell.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "pico/stdlib.h"
#include <sstream>
#include <vector>

using namespace shell;

std::map<std::string, std::string> Shell::getVariables() {
    return this->variables_;
}

void Shell::setVariable(const std::string& key, const std::string& value) {
    this->variables_[key] = value;
}

Command::Command(std::string& command, Shell& shell): shell_(shell) {
    // TODO: need to add some checks on the string
    const size_t endToken = command.find(' ');
    this->command_ = command.substr(0, endToken);
    this->argument_ = command.substr(endToken + 1);
    this->type_ = fromString(this->command_);
}

CommandType Command::fromString(const std::string& command) {
    if (command == "led") return CommandType::LED;
    if (command == "set") return CommandType::SET;
    if (command == "echo") return CommandType::ECHO;
    if (command == "sleep") return CommandType::SLEEP;
    if (command ==  "speaker") return CommandType::SPEAKER;
    return CommandType::UNKNOWN;
}


CommandType Command::getType() const {
    return this->type_;
}

std::string Command::getCommand() const {
    return this->command_;
}

std::string Command::getArgument() const {
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
            set(this->argument_, this->shell_);
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

void led(const std::string& arguments) {
    const size_t endToken = arguments.find(' ');
    const std::string action = arguments.substr(0, endToken);
    const std::string arg = arguments.substr(endToken + 1);

    // checks the action
    if (action == "on") {
        // checks the argument
        if (arg == "red") {
            gpio_init(LED_RED);
            gpio_set_dir(LED_RED, GPIO_OUT);
            gpio_put(LED_RED, true);
        }
        else if (arg == "blue") {
            gpio_init(LED_BLUE);
            gpio_set_dir(LED_BLUE, GPIO_OUT);
            gpio_put(LED_BLUE, true);
        }
        else if (arg == "green") {
            gpio_init(LED_GREEN);
            gpio_set_dir(LED_GREEN, GPIO_OUT);
            gpio_put(LED_GREEN, true);
        }
        else {
            printf("[ERROR] led color not valid: %s", arg.c_str());
        }
    }
    else if (action == "off") {
        // checks the argument
        if (arg == "red") {
            gpio_put(LED_RED, false);
            gpio_deinit(LED_RED);
        }
        else if (arg == "blue") {
            gpio_put(LED_BLUE, false);
            gpio_deinit(LED_BLUE);
        }
        else if (arg == "green") {
            gpio_put(LED_GREEN, false);
            gpio_deinit(LED_GREEN);
        }
        else {
            printf("[ERROR] led color not valid: %s", arg.c_str());
        }
    }
    else {
        printf("[ERROR] Invalid action: %s", action.c_str());
    }
}

void set(const std::string& arguments, Shell& shell) {
    if (arguments.empty()) return;

    std::stringstream stream(arguments);
    std::string buffer;
    std::vector <std::string> tokens;

    while (std::getline(stream, buffer, ' ')) {
        tokens.push_back(buffer);
    }

    std::string name;
    std::string value;

    if (tokens.size() >= 2) {
        name = tokens[0];
        value = tokens[1];
    }
    else if (tokens.size() == 1) {
        name = tokens[0];
        value = "";
    }
    else {
        return;
    }

    // overwrites a variable with the same name
    shell.setVariable(name, value);
}

void echo(const std::string& arguments) {
    if (arguments.empty()) return;
    std::stringstream stream(arguments);
    std::string value;

    std::getline(stream, value, ' ');

    printf("%s", value.c_str());
}