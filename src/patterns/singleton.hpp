
#ifndef __LPSTD_SINGLETON_HPP__
#define __LPSTD_SINGLETON_HPP__
namespace lpstd
{
    template <typename T>
    class Singleton
    {
    public:
        static T &Instance()
        {
            static T _instance;
            return _instance;
        }

    protected:
        Singleton() {}
        ~Singleton() {}

    private:
        Singleton(Singleton const &);
        Singleton &operator=(Singleton const &);
    };
}

#endif // __LPSTD_SINGLETON_HPP__