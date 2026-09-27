#include <iostream>
#include <ostream>


namespace quantities {

    class Ampere { 
    private:
        long double val;
    public:
        Ampere(long double x = 0) : val(x) {}
        long double value() const { return val; }
    };

    class Volt { 
    private:
        long double val;
    public:
        Volt(long double x = 0) : val(x) {}
        long double value() const { return val; }
    };

    class Ohm { 
    private:
        long double val;
    public:
        Ohm(long double x = 0) : val(x) {}
        long double value() const { return val; }
    };

    class Joule { 
    private:
        long double val;
    public:
        Joule(long double x = 0) : val(x) {}
        long double value() const { return val; }
    };

    class Watt { 
    private:
        long double val;
    public:
        Watt(long double x = 0) : val(x) {}
        long double value() const { return val; }
    };

    class second { 
    private:
        long double val;
    public:
        second(long double x = 0) : val(x) {}
        long double value() const { return val; }
    };


    Ampere operator""_mA(long double x) 
    { return { x / 1000.0L }; }

    Volt operator""_V(long double x) 
    { return (x); }

    Ohm operator""_Ohm(long double x) 
    { return { x }; }

    Joule operator""_J(long double x) 
    { return { x }; }

    Watt operator""_W(long double x) 
    { return { x }; }\

    second operator""_s(long double x) 
    { return { x }; }


    Ohm operator/(Volt U, Ampere I)
    { return (U.value() / I.value()); }

    Ampere operator/(Volt U, Ohm R)
    { return (U.value() / R.value()); }

    Volt operator*(Ampere I, Ohm R)
    { return (I.value() * R.value()); }

    Joule operator*(Watt P, second t)
    { return (P.value() * t.value()); }

    Watt operator/(Joule A, second t)
    { return (A.value() / t.value()); }

    second operator/(Joule A, Watt P)
    { return (A.value() / P.value()); }

    Watt operator*(Volt U, Ampere I)
    { return (U.value() * I.value()); }

    Volt operator/(Watt P, Ampere I)
    { return (P.value() / I.value()); }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const T& num)
    { return os << num.value(); }
}

using namespace quantities;
using std::cout, std::endl;

int main() {
    Ampere I(10);
    Volt U(10);
    Ohm R(25);
    Joule A(100);
    Watt P(40);
    second t(15);
    auto I_1 = 10000.0_mA;
    auto U_1 = 25.0_V;
    Ohm R_1 = U_1 / I_1;
    
    cout << R_1 << endl;

    return 0;
}