
#include <iostream>
#include <functional>

#ifdef _WIN32
#include <cstdio>
#include <windows.h>
#endif

namespace lpstd
{
    namespace testing
    {

        struct Results
        {
            int passed = 0;
            int failed = 0;
        };

        Results Results;

        void drawResults()
        {
            std::cout << std::endl;
            if (Results.failed == 0)
            {
                std::cout << "=== ✅ All tests passed ===" << std::endl;
            }
            else
            {
                std::cout << "=== ❌ " << Results.failed << " tests failed ===" << std::endl;
            }
        }

        template <typename T>
        class Expect
        {
        public:
            Expect(T value)
            {

#ifdef _WIN32
                // Set console code page to UTF-8 so console known how to interpret string data
                SetConsoleOutputCP(CP_UTF8);

                // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
                setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif

                this->value = value;
            }

            bool toBe(T expected)
            {
                bool result = this->value == expected;
                if (result)
                {
                    std::cout << "✅ Expected " << this->value << " to be " << expected << std::endl;
                    Results.passed++;
                }
                else
                {
                    std::cout << "❌ Expected " << expected << " but got " << this->value << std::endl;
                    Results.failed++;
                }
                return result;
            }

            bool toBeGreaterThan(T expected)
            {
                bool result = this->value > expected;
                if (result)
                {
                    std::cout << "✅ Expected " << this->value << " to be greater than " << expected << std::endl;
                    Results.passed++;
                }
                else
                {
                    std::cout << "❌ Expected " << this->value << " to be greater than " << expected << std::endl;
                    Results.failed++;
                }

                return result;
            }

            bool toBeLessThan(T expected)
            {
                bool result = this->value < expected;
                if (result)
                {
                    std::cout << "✅ Expected " << this->value << " to be less than " << expected << std::endl;
                    Results.passed++;
                }
                else
                {
                    std::cout << "❌ Expected " << this->value << " to be less than " << expected << std::endl;
                    Results.failed++;
                }
                return result;
            }

            bool toBeTrue()
            {
                bool result = this->value;
                if (result)
                {
                    std::cout << "✅ Expected " << this->value << " to be true" << std::endl;
                    Results.passed++;
                }
                else
                {
                    std::cout << "❌ Expected " << this->value << " to be true" << std::endl;
                    Results.failed++;
                }
                return result;
            }

            bool toBeFalse()
            {
                bool result = !this->value;
                if (result)
                {
                    std::cout << "✅ Expected " << this->value << " to be false" << std::endl;
                    Results.passed++;
                }
                else
                {
                    std::cout << "❌ Expected " << this->value << " to be false" << std::endl;
                    Results.failed++;
                }
                return result;
            }

            bool toBeCloseTo(T expected, T delta = 0.01)
            {
                bool result = this->value >= expected - delta && this->value <= expected + delta;
                if (result)
                {
                    std::cout << "✅ Expected " << this->value << " to be close to " << expected << std::endl;
                    Results.passed++;
                }
                else
                {
                    std::cout << "❌ Expected " << this->value << " to be close to " << expected << std::endl;
                    Results.failed++;
                }
                return result;
            }

        private:
            T value;
        };

        template <typename T>
        Expect<T> expect(T value)
        {
            return Expect<T>(value);
        }

        // void test(std::string description, void (*test)())
        // {
        //     std::cout << description << std::endl;
        //     test();
        // }

        // Custom test function to execute a single test case
        void test(std::string description, std::function<void()> testCase)
        {
            std::cout << description << std::endl;
            testCase();
        }

        // Custom describe function to group related test cases
        void describe(std::string description, std::function<void()> testSuite)
        {
            std::cout << "Describing " << description << std::endl;
            testSuite();
        }

    }
}
