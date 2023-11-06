#ifndef __LPSTD_WEBSERVER_H__
#define __LPSTD_WEBSERVER_H__

#include "../patterns/singleton.hpp"
#include <iostream>
#include <string>
#include <vector>


namespace lpstd
{
    namespace classes
    {

        namespace web
        {
            struct route
            {
                std::string path;
                std::string method;
                void (*func)();
            };
        }

        class WebServer : public lpstd::Singleton<WebServer>
        {

        private:
            std::vector<web::route> routes = {};

        public:
            WebServer(/* args */)
            {
            }
            ~WebServer()
            {
            }

            void addRoute(web::route route)
            {
                this->routes.push_back(route);
            }

            void addRoute(std::string path, std::string method, void (*func)())
            {
                web::route route = {path : path, method : method, func : func};
                this->routes.push_back(route);
            }

            void get(std::string path, void (*func)())
            {
                this->addRoute(path, "GET", func);
            }

            void post(std::string path, void (*func)())
            {
                this->addRoute(path, "POST", func);
            }

            void put(std::string path, void (*func)())
            {
                this->addRoute(path, "PUT", func);
            }

            void patch(std::string path, void (*func)())
            {
                this->addRoute(path, "PATCH", func);
            }

            void del(std::string path, void (*func)())
            {
                this->addRoute(path, "DELETE", func);
            }

            void run(int port = 3000)
            {
                for (auto &route : this->routes)
                {
                    std::cout << route.path << std::endl;
                }

                std::cout << "Running on port " << port << std::endl;

                std::cout << "Listening..." << std::endl;
            }
        };

    } // namespace classes

} // namespace

#endif // __LPSTD_WEBSERVER_H__