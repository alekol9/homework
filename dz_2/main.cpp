#include <iostream>
#include <ostream>

using std::cout, std::endl, std::string, std::ostream;

namespace quantities {

class Ampere { 
private:
    long double val;
public:
    Ampere(long double x = 0) : val(x) {}
    long double getValue() const { return val; }
};


class Volt { 
private:
    long double val;
public:
    Volt(long double x = 0) : val(x) {}
    long double getValue() const { return val; }
};


class Ohm { 
private:
    long double val;
public:
    Ohm(long double x = 0) : val(x) {}
    long double getValue() const { return val; }
};


class Joule { 
private:
    long double val;
public:
    Joule(long double x = 0) : val(x) {}
    long double getValue() const { return val; }
};


class Watt { 
private:
    long double val;
public:
    Watt(long double x = 0) : val(x) {}
    long double getValue() const { return val; }
};


class second { 
private:
    long double val;
public:
    second(long double x = 0) : val(x) {}
    long double getValue() const { return val; }
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
    { return (U.getValue() / I.getValue()); }

    Ampere operator/(Volt U, Ohm R)
    { return (U.getValue() / R.getValue()); }

    Volt operator*(Ampere I, Ohm R)
    { return (I.getValue() * R.getValue()); }

    Joule operator*(Watt P, second t)
    { return (P.getValue() * t.getValue()); }

    Watt operator/(Joule A, second t)
    { return (A.getValue() / t.getValue()); }

    second operator/(Joule A, Watt P)
    { return (A.getValue() / P.getValue()); }

    Watt operator*(Volt U, Ampere I)
    { return (U.getValue() * I.getValue()); }

    Volt operator/(Watt P, Ampere I)
    { return (P.getValue() / I.getValue()); }

    template <typename T>
    ostream& operator<<(ostream& os, const T& num)
    { return os << num.getValue(); }
}

namespace devices {

class Device {
private:
    long double min_range, max_range;
    int accuracy;
    string id;
public:
    Device(long double min_ = 0, long double max_ = 0, int accur = 0, string id_ = "") : min_range(min_), max_range(max_), accuracy(accur), id(id_) {}

    long double getMin() const { return min_range; }
    long double getMax() const { return max_range; }
    int getAcc() const { return accuracy; }
    string getId() const { return id; }

    void print() const { cout << id << " Range: " << min_range << " - " << max_range << ", Accuracy: " << accuracy << endl; }
};

class Voltmeter : public Device {
public:
    Voltmeter(long double min_ = 0, long double max_ = 0, int accur = 0, string id_ = "NoName") : Device(min_, max_, accur, id_) {}
};

class Ammetr : public Device {
public:
    Ammetr(long double min_ = 0, long double max_ = 0, int accur = 0, string id_ = "NoName") : Device(min_, max_, accur, id_) {}
};

class Multimeter : public Device {
public:
    Multimeter(long double min_ = 0, long double max_ = 0, int accur = 0, string id_ = "NoName") : Device(min_, max_, accur, id_) {}
};
}

using namespace quantities;
using namespace devices;

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
    cout << endl;
    
    Voltmeter v1;
    Ammetr a1(0.5, 3.333, 1, "AmmetrA1");
    Multimeter m1(0.01, 10.723564, 3, "MultimeterM1");

    v1.print();
    a1.print();
    m1.print();

    return 0;
}