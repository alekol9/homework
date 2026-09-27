#include <iostream>
#include <ostream>
#include <string>
#include <stdexcept>


using std::cout, std::endl, std::string, std::ostream;

namespace quantities {

struct Ampere { long double value = 0; };

struct Volt { long double value = 0; };

struct Ohm { long double value = 0; };

struct Joule { long double value = 0; };

struct Watt { long double value = 0; };

struct second { long double value = 0; };


Ampere operator""_mA(long double x) { return { x / 1000.0L }; }

Volt operator""_V(long double x) { return { x }; }

Ohm operator""_Ohm(long double x) { return { x }; }

Joule operator""_J(long double x) { return { x }; }

Watt operator""_W(long double x) { return { x }; }

second operator""_s(long double x) { return { x }; }


Ohm operator/(Volt U, Ampere I) {
    if (I.value == 0) throw std::runtime_error("Деление на ноль: I = 0");
    return { U.value / I.value };
}

Ampere operator/(Volt U, Ohm R) {
    if (R.value == 0) throw std::runtime_error("Деление на ноль: R = 0");
    return { U.value / R.value };
}

Volt operator*(Ampere I, Ohm R) { return { I.value * R.value }; }
Volt operator*(Ohm R, Ampere I) { return { R.value * I.value }; }

Joule operator*(Watt P, second t) { return { P.value * t.value }; }
Joule operator*(second t, Watt P) { return { t.value * P.value }; }

Watt operator/(Joule A, second t) {
    if (t.value == 0) throw std::runtime_error("Деление на ноль: t = 0");
    return { A.value / t.value };
}

second operator/(Joule A, Watt P) {
    if (P.value == 0) throw std::runtime_error("Деление на ноль: P = 0");
    return { A.value / P.value };
}

Watt operator*(Volt U, Ampere I) { return { U.value * I.value }; }
Watt operator*(Ampere I, Volt U) { return { I.value * U.value }; }

Volt operator/(Watt P, Ampere I) {
    if (I.value == 0) throw std::runtime_error("Деление на ноль: I = 0");
    return { P.value / I.value };
}

ostream& operator<<(ostream& os, const Ampere& num) { return os << num.value << " A"; }
ostream& operator<<(ostream& os, const Volt& num) { return os << num.value << " V"; }
ostream& operator<<(ostream& os, const Ohm& num) { return os << num.value << " O"; }
ostream& operator<<(ostream& os, const Joule& num) { return os << num.value << " J"; }
ostream& operator<<(ostream& os, const Watt& num) { return os << num.value << " W"; }
ostream& operator<<(ostream& os, const second& num) { return os << num.value << " s"; }
}

namespace devices {

class Device {
private:
    long double min_range, max_range;
    int accuracy;
    string id;
public:
    Device(long double min_ = 0, long double max_ = 0, int accur = 0, string id_ = "NoName") : min_range(min_), max_range(max_), accuracy(accur), id(id_) {
        if (min_range > max_range)
            throw std::runtime_error("Параметры утсройства: min > max");
        if (accuracy < 0)
            throw std::runtime_error("Параметры утсройства: accuracy < 0");
        if (id.empty())
            throw std::runtime_error("Параметры утсройства: пустой id");
    }

    virtual void measure() {}

    virtual ~Device() = default;
};

class Voltmeter : public Device {
public:
    Voltmeter(long double min_ = 0, long double max_ = 0, int accur = 0, string id_ = "NoName") : Device(min_, max_, accur, id_) {}
};

class Ammeter : public Device {
public:
    Ammeter(long double min_ = 0, long double max_ = 0, int accur = 0, string id_ = "NoName") : Device(min_, max_, accur, id_) {}
};

class Multimeter : public Device {
public:
    Multimeter(long double min_ = 0, long double max_ = 0, int accur = 0, string id_ = "NoName") : Device(min_, max_, accur, id_) {}
};
}

using namespace quantities;
using namespace devices;

int main() {
    Ampere I{10};
    Ohm R{25};
    Watt P{40};
    second t{15};
    auto I_1 = 10000.0_mA;
    auto U_1 = 25.0_V;

    Ohm R_1 = U_1 / I_1;
    Volt U = I * R;
    Joule A = P * t;

    cout << "R_1 = U_1 / I_1 = " << R_1 << endl;
    cout << "U = I * R = " << U << endl;
    cout << "A = P * t = " << A << endl;
    cout << endl;
    
    Voltmeter v1;
    Ammeter a1(0.5, 3.333, 1, "AmmeterA1");
    Multimeter m1(0.01, 10.723564, 3, "MultimeterM1");

    try {
        Ampere A_zero;
        Volt U2{5};
        Ohm R2 = U2 / A_zero;
    } catch (const std::exception& e) {
        cout << "error: " << e.what() << endl;
    }

    return 0;
}