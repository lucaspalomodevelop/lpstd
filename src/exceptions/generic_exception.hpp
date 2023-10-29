#ifndef GENERIC_EXCEPTION_HPP
#define GENERIC_EXCEPTION_HPP

#include <exception>
#include <string>

namespace lpstd
{

    namespace exceptions
    {

        class generic_exception : public std::exception
        {
        private:
            std::string message;

        public:
            generic_exception(std::string message)
            {
                this->message = message;
            }
            const char *what() const throw()
            {
                return this->message.c_str();
            }
        };
    }

} // namespace lpstd::

#endif // GENERIC_EXCEPTION_HPP