//
// Created by lab on 22/07/25.
//

#ifndef SHELL_HPP
#define SHELL_HPP
#include <cstdint>

constexpr uint32_t LED_RED = 14;
constexpr uint32_t LED_GREEN = 13;
constexpr uint32_t LED_BLUE = 12;
constexpr uint32_t LED_DEFAULT = LED_BLUE;
constexpr uint32_t SPEAKER = 8;

namespace shell {

    enum class CommandType {
        LED = "led",
        SET = "set",
        ECHO = "echo",
        SLEEP = "sleep",
        SPEAKER = "speaker",
        UNKNOWN = -1
    };

    class Command {
        private:
            char* command_;
            CommandType type_;
            char* argument_;

        public:
            // constructors
            explicit Command(char* command);

            // setters and getters
            CommandType getType() const;
            char* getCommand() const;
            char* getArgument() const;

            // utilities
            bool isValid() const;
            void execute() const;
    };

    // actual operations
    void led(char* arguments);
    void set(char* arguments);
    void echo(char* arguments);
    void sleep(char* arguments);
    void speaker(char* arguments);
}

#endif //SHELL_HPP
