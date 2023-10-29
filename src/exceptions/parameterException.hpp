#ifndef PARAMETEREXCEPTION_HPP
#define PARAMETEREXCEPTION_HPP

#include "generic_exception.hpp"

namespace lpstd
{
    namespace exceptions
    {
        class ParameterException : public generic_exception
        {
        public:
            ParameterException(std::string message = "ParameterException") : generic_exception(message)
            {
            }
        };

    } // namespace exceptions

} // namespace lpstd

#endif // PARAMETEREXCEPTION_HPP