//
// Created by lab on 22/07/25.
//

#ifndef SHELL_HPP
#define SHELL_HPP

namespace shell {

enum class CommandType {
    led = "led",
    set = "set",
    echo = "echo",
    sleep = "sleep",
    speaker = "speaker"
};

class Command {
private:
    CommandType type_;
public:
    // constructors
    Command(CommandType type);
    Command(std::string command);

    // setters and getters
    set
}
}

#endif //SHELL_HPP
