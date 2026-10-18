#include <cstdint>
#include <stdexcept>
#include <string>

using Cents = std::int64_t;
using Grams = std::int64_t;

enum class Zone {
    Local,
    Remote
};

enum class Customer {
    Regular,
    NonRegular
};

struct Shipment { 
    Cents subtotal;
    Grams mass = 1000;
    Zone zone = Zone::Local;
    Customer type = Customer::NonRegular;
};

struct Carrier {
    virtual ~Carrier() = default;
    virtual std::string reserve(Cents fee, Grams mass) = 0;
};

struct Notification {
    virtual ~Notification() = default;
    virtual void send(const std::string& tracking) = 0;
};

class DeliveryPolicy {
public:
    Cents quote(const Shipment& s) const {
        if (s.subtotal < 0) throw std::invalid_argument("Negative order subtotal!");
        if (s.mass < 1 || s.mass > 20000) throw std::invalid_argument("Weight is out of range!");
        if (s.zone == Zone::Remote) return 70000;
        if (s.subtotal >= 500000) return 0;
        return 30000;
    }
};

class BookingRejected : public std::runtime_error {
public:
    BookingRejected() : std::runtime_error("Carrier rejected shipment!") {}
};

class BookingService {
    DeliveryPolicy policy;
    Carrier& carrier;
    Notification& notification;
public:
    BookingService(Carrier& c, Notification& n) : carrier(c), notification(n) {}
    std::string book(const Shipment& s) {
        const auto fee = policy.quote(s);
        auto tracking = carrier.reserve(fee, s.mass);
        if (tracking.empty()) throw BookingRejected();
        notification.send(tracking);
        return tracking;
    };
};