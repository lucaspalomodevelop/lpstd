#ifndef FAKER_FILE_HPP
#define FAKER_FILE_HPP

#include <string>
namespace lpstd
{
    namespace faker
    {
        class file
        {
        public:
            std::string virtualPath;
            file()
            {
                this->virtualPath = "C:\\Users\\Public\\Documents\\lpstd\\faker\\file.txt";
            }
            std::ofstream get_ofStream()
            {
                std::ofstream file;
                file.open(this->virtualPath);
                return file;
            }
        };
    } // namespace faker
} // namespace lpstd

#endif // FAKER_FILE_HPP
