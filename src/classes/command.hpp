#ifndef __LPSTD_COMMAND_H__
#define __LPSTD_COMMAND_H__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>
#include <iterator>
#include "../patterns/singleton.hpp"

namespace lpstd
{
    namespace classes
    {

        struct commandInfo
        {
            std::string name;
            std::string description;
            void (*func)();
            std::vector<std::string> args;
        };

        class Command : public lpstd::Singleton<Command>
        {

        private:
            std::list<commandInfo> commands = {};
            std::string defaultCommandName = "help";

            commandInfo currentCommand = {name : "",
                                          description : "",
                                          func : nullptr,
                                          args : {}};

        public:
            Command(/* args */)
            {
            }

            ~Command()
            {
            }

            commandInfo getCurrentCommand()
            {
                return this->currentCommand;
            }

            template <typename... Args>
            bool existsArg(Args &&...arg)
            {

                for (auto &argToFind : {arg...})
                {
                    std::vector<std::string>::iterator it = std::find(this->currentCommand.args.begin(), this->currentCommand.args.end(), argToFind);
                    if (it != this->currentCommand.args.end())
                    {
                        return true;
                    }
                }

                return false;
            }

            template <typename... Args>
            std::string getArg(Args &&...arg)
            {

                if (this->currentCommand.args.size() == 0)
                {
                    return "";
                }

                std::vector<std::string> args = this->currentCommand.args;
                std::vector<std::string> argsToFind = {arg...};
                std::vector<std::string> values = {};
                for (auto &argToFind : argsToFind)
                {
                    std::vector<std::string>::iterator it = std::find(args.begin(), args.end(), argToFind);
                    if (it != args.end())
                    {
                        values.push_back(*(it + 1));
                    }
                }
                return values.size() > 0 ? values[0] : "";
            }

            void addCommand(std::string name, std::string description, void (*func)(void))
            {
                commandInfo command;
                command.name = name;
                command.description = description;
                command.func = func;
                this->commands.push_back(command);
            }

            // void addCommand(std::string name, std::string description, void (*func)(int argc, char *argv[]))
            // {
            //     commandInfo command;
            //     command.name = name;
            //     command.description = description;
            //     command.func = func;
            //     this->commands.push_back(command);
            // }

            std::string getHelpAsString()
            {
                std::string help = "";
                std::list<commandInfo> sortedCommands = this->commands;

                sortedCommands.sort([](const commandInfo &a, const commandInfo &b)
                                    { return a.name < b.name; });

                for (auto &commandInfo : sortedCommands)
                {
                    help += commandInfo.name + " - " + commandInfo.description + "\n";
                }

                return help;
            }

            void callCommand(std::string command, int argc, char *argv[])
            {
                std::vector<std::string> args;
                for (int i = 2; i < argc; i++)
                {
                    args.push_back(argv[i]);
                }

                for (auto &commandInfo : this->commands)
                {
                    if (commandInfo.name == command)
                    {
                        commandInfo.args = args;
                        currentCommand = commandInfo;
                        commandInfo.func();
                        return;
                    }
                }
                std::cout << "Command not found" << std::endl;
            }

            void execute(int argc, char *argv[])
            {

                if (argc < 2)
                {
                    std::cout << "Command not found \n"
                              << std::endl;
                    // throw lpstd::exceptions::ParameterException("argc < 2");

                    this->callCommand(defaultCommandName, argc, argv);

                    return;
                }

                std::string command = argv[1];
                std::vector<std::string> args;
                for (int i = 2; i < argc; i++)
                {
                    args.push_back(argv[i]);
                }

                for (auto &commandInfo : this->commands)
                {
                    if (commandInfo.name == command)
                    {
                        commandInfo.args = args;
                        currentCommand = commandInfo;
                        commandInfo.func();
                        return;
                    }
                }
                std::cout << "Command not found" << std::endl;
            }
        };

    } // namespace classes
} // namespace lpstd

#endif // __LPSTD_COMMAND_H__