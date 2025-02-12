#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>

class MyComplex{
    private:
        float imaginary, real;
    public:
        // costructor
        MyComplex(float real, float imaginary){
            this->imaginary = imaginary;
            this->real = real;
        }

        // destructor
        ~MyComplex(){}

        // overload the + operator
        MyComplex operator + (const MyComplex& obj){
            MyComplex temp(0,0);
            temp.imaginary = this->imaginary + obj.imaginary;
            temp.real = this->real + obj.real;
            return temp;
        }

        // overload the * operator
        /*
            It is just the "FOIL" method after a little work:
                (a+bi)(c+di) 	= 	ac + adi + bci + bdi2 	  	FOIL method
                = 	ac + adi + bci − bd 	  	(because i2=−1)
                = 	(ac − bd) + (ad + bc)i 	  	(gathering like terms)

            And there you have the (ac − bd) + (ad + bc)i  pattern.
            This rule is certainly faster, but if you forget it, just remember the FOIL method.
        */
        MyComplex operator * (const MyComplex& obj){
            MyComplex temp(0,0);
            int a, b, c, d;
            a = this->real;
            b = this->imaginary;
            c = obj.real;
            d = obj.imaginary;

            // fallowing the (ac - bd) + (ad + bc)i pattern
            temp.real = (a*c) - (b*d);
            temp.imaginary = (a*d) + (b*c);

            return temp;
        }

        auto output (void) -> void
        {
            if(this->imaginary < 0)
                std::cout << "Complex number is: " << this->real << this->imaginary << "i" << std::endl;
            else
                std::cout << "Complex number is: " << this->real << "+" << this->imaginary << "i" << std::endl;
        }

        auto getReal(void) -> float
        {
            return this->real;
        }

        auto getImaginary() -> float
        {
            return this->imaginary;
        }
};


auto main(int argc, char** argv) -> int
{
    MyComplex c1(std::stof(argv[1]), std::stof(argv[2]));
    MyComplex c2(std::stof(argv[3]), std::stof(argv[4]));
    MyComplex temp(0,0);

    // + operator modified XD
    temp = c1 + c2;
    temp.output();

    // * operator modified XD
    temp = c1 * c2;
    temp.output();

    return EXIT_SUCCESS;
}
