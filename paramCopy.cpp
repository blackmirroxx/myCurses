#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

class Parameter{
    private:
        int psize;
        std::vector<std::string> arguments;
    public:
        Parameter(){}; // needed to initialize the class Session

        Parameter(int psize){
            this->psize = psize;
        };

        ~Parameter(){};

        auto getSize(void) -> int
        {
            return psize;
        }

        auto setArguments(std::vector<std::string> args) -> void
        {
            arguments = args;
        }

        auto getArguments(int i) -> std::string
        {
            if(i>=psize)
            {
                i = 0; // check overflow
            }
            return arguments[i];
        }

};

class Session{
    private:
        Parameter p;
    public:
        Session(Parameter p){
            this-> p = p;
        };
        ~Session(){};

        auto interactWithUser() -> void
        {
            int pos;

            std::cout << "Set number for parameter's position: ";
            std::cin >> pos;
            std::cout << p.getArguments(pos) << std::endl;
        }
};

auto main( int argc, char **argv) -> int
{
    std::vector<std::string> args(argc);

    std::transform( argv, argv+argc, args.begin(),
        [&]( char*arg ){ return std::string(arg); } );

    Parameter p(argc);
    p.setArguments(args);

    Session s(p);
    s.interactWithUser();

    return EXIT_SUCCESS;
}
