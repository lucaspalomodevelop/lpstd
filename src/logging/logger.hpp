
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>
#include "../patterns/singleton.hpp"
#include "../exceptions/exceptions.hpp"

namespace lpstd
{
    namespace logging
    {
        enum LogLevel
        {
            LOG_DEBUG,
            LOG_INFO,
            LOG_WARNING,
            LOG_ERROR,
            LOG_FATAL
        };

        enum Logmode
        {
            CONSOLE,
            FILE,
            BOTH
        };

        class Logger : public lpstd::Singleton<Logger>
        {
        private:
            Logmode mode = Logmode::CONSOLE;
            std::map<LogLevel, std::string> level_filename;
            std::map<LogLevel, std::ofstream> level_file;
            std::string filename = "log.txt";
            std::ofstream file;
            LogLevel level = LogLevel::LOG_DEBUG;
            std::string message = "";

            std::ofstream getFile()
            {
                throw lpstd::exceptions::NotImplementedException();
                // return this->getFile(this->level);
            }

            // std::ofstream getFile(LogLevel level)
            // {
            //     std::string filename = "";

            //     if (this->level_filename.find(level) == this->level_filename.end())
            //     {
            //         filename = this->level_filename[level];
            //     }
            //     else
            //     {
            //         filename = this->filename;
            //     }

            //     return this->level_file[level];
            // }

            void LogToLogmode(std::string message, LogLevel level)
            {
                switch (this->mode)
                {
                case Logmode::CONSOLE:
                    std::cout << message << std::endl;
                    break;
                case Logmode::FILE:
                    this->file << message << std::endl;
                    break;
                case Logmode::BOTH:
                    std::cout << message << std::endl;
                    this->file << message << std::endl;
                    break;
                default:
                    break;
                }
            }

            void initFile()
            {
                this->file.open(this->filename, std::ios::app);
            }

        public:
            Logger()
            {
            }

            ~Logger()
            {
                this->file.close();
            }

            void LevelToFile(LogLevel level, std::string filename)
            {
                throw lpstd::exceptions::NotImplementedException();
                // this->level_filename[level] = filename;
            }

            void setLogmode(Logmode mode)
            {
                this->mode = mode;
            }

            void setFilename(std::string filename)
            {
                this->filename = filename;
                if (this->file.is_open())
                {
                    this->file.close();
                }
                this->initFile();
            }

            void setLevel(LogLevel level)
            {
                this->level = level;
            }

            void log(std::string message)
            {
                this->log(this->level, message);
            }

            void log(LogLevel level, std::string message)
            {
                if (file.is_open() == false)
                {
                    this->initFile();
                }

                std::time_t t = std::time(nullptr);
                std::tm tm = *std::localtime(&t);
                std::ostringstream oss;
                oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
                std::string str = oss.str();

                message = "[" + str + "] " + message;

                switch (level)
                {
                case LogLevel::LOG_DEBUG:
                    this->message = "[DEBUG] " + message;
                    break;
                case LogLevel::LOG_INFO:
                    this->message = "[INFO] " + message;
                    break;
                case LogLevel::LOG_WARNING:
                    this->message = "[WARNING] " + message;
                    break;
                case LogLevel::LOG_ERROR:
                    this->message = "[ERROR] " + message;
                    break;
                case LogLevel::LOG_FATAL:
                    this->message = "[FATAL] " + message;
                    break;
                default:
                    break;
                }

                this->LogToLogmode(this->message, level);
            }

            void debug(std::string message)
            {
                this->log(LogLevel::LOG_DEBUG, message);
            }

            void info(std::string message)
            {
                this->log(LogLevel::LOG_INFO, message);
            }

            void warning(std::string message)
            {
                this->log(LogLevel::LOG_WARNING, message);
            }

            void error(std::string message)
            {
                this->log(LogLevel::LOG_ERROR, message);
            }

            void fatal(std::string message)
            {
                this->log(LogLevel::LOG_FATAL, message);
            }
        };

    } // namespace logging
} // namespace lpstd
#endif // LOGGER_HPP
