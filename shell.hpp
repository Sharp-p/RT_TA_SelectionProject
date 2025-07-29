//
// Created by lab on 22/07/25.
//

#ifndef SHELL_HPP
#define SHELL_HPP
#include <cstdint>
#include <map>
#include <string>

constexpr uint32_t LED_RED = 14;
constexpr uint32_t LED_GREEN = 13;
constexpr uint32_t LED_BLUE = 12;
constexpr uint32_t LED_DEFAULT = LED_BLUE;
constexpr uint32_t SPEAKER = 8;

namespace shell {

    enum class CommandType {
        LED,
        SET,
        ECHO,
        SLEEP,
        SPEAKER,
        UNKNOWN = -1
    };

    class Shell {
        private:
            std::map<std::string, std::string> variables_;
            // red green blue
            bool leds[3] = {false, false, false};
        public:
            // could be returned by reference (&) for performance reasons,
            // at the cost of breaking the encapsulation, but for this exercise
            // is not necessary, so we will respect the encapsulation
            std::map<std::string, std::string> getVariables();
            // if a variable is already in the map it will be overwritten
            void setVariable(const std::string& key, const std::string& value);
            // led is in [0,2]
            void setLeds(int led, bool value);
            void printLeds();
    };

    class Command{
        private:
            std::string command_;
            CommandType type_;
            std::string argument_;
            Shell& shell_;

            static CommandType fromString(const std::string& command);

        public:
            // constructors
            explicit Command(std::string& command, Shell& shell);

            // setters and getters
            CommandType getType() const;
            std::string getCommand() const;
            std::string getArgument() const;

            // utilities
            bool isValid() const;
            void execute() const;

            // there could be a new method that sets a new command, so there
            // wouldn't be the necessity to create a new object for each new
            // command executed
    };

    // actual operations
    void led(const std::string& arguments, Shell& shell);
    void set(const std::string& arguments, Shell& shell);
    void echo(const std::string& arguments);
    void sleep(const std::string& arguments);
    void speaker(const std::string& arguments);
}

#endif //SHELL_HPP
