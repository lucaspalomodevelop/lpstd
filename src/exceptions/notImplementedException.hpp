#ifndef NotImplementedException_HPP
#define NotImplementedException_HPP

#include "generic_exception.hpp"

namespace lpstd
{
    namespace exceptions
    {
        class NotImplementedException  : public generic_exception
        {
        public:
            NotImplementedException() : generic_exception("Not implemented exception")
            {
            }
        };

    } // namespace exceptions

} // namespace lpstd

#endif // NotImplementedException_HPP