#include "delivery.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <string>

TEST(DeliveryTest, LocalOrderHasBaseFee) {
    DeliveryPolicy policy;
    Shipment shipment{100000};
    const auto fee = policy.quote(shipment);
    EXPECT_EQ(fee, 30000);
}

TEST(DeliveryTest, LocalOrderHasZeroFee) {
    DeliveryPolicy policy;
    Shipment shipment{500000};
    const auto fee = policy.quote(shipment);
    EXPECT_EQ(fee, 0);
}

TEST(DeliveryTest, NegativeSubtotalIsRejected) {
    DeliveryPolicy policy;
    EXPECT_THROW(policy.quote(Shipment{-1, 1000, Zone::Remote}), std::invalid_argument);
}

TEST(DeliveryTest, RemoteOrderHasBaseFee) {
    DeliveryPolicy policy;
    const auto fee_1 = policy.quote(Shipment{500000, 1000, Zone::Remote});
    const auto fee_2 = policy.quote(Shipment{100000, 1000, Zone::Remote});
    EXPECT_EQ(fee_1, 70000);
    EXPECT_EQ(fee_2, 70000);
}

class LocalShipmentTest : public ::testing::Test {
protected:
    DeliveryPolicy policy;
    Shipment shipment{100000,1000, Zone::Local};
    void SetUp() override { shipment.mass = 1000; }
};

TEST_F(LocalShipmentTest, ZeroWeightRejected) {
    shipment.mass = 0;
    EXPECT_THROW(policy.quote(shipment), std::invalid_argument);
}

TEST_F(LocalShipmentTest, OverWeightRejected) {
    shipment.mass = 20001;
    EXPECT_THROW(policy.quote(shipment), std::invalid_argument);
}

TEST_F(LocalShipmentTest, EachTestStartsWithValidWeight) {
    EXPECT_EQ(policy.quote(shipment), 30000);
}

struct FeeCase {
    const char* name;
    Shipment shipment;
    Cents expected;
};

class FeeMatrixTest : public ::testing::TestWithParam<FeeCase> {};

TEST_P(FeeMatrixTest, FollowsTariff) {
    const auto& p = GetParam();
    DeliveryPolicy policy;
    EXPECT_EQ(policy.quote(p.shipment), p.expected);
}

const FeeCase fee_cases[] = {
    {"LoalBelow", {499999, 1000, Zone::Local}, 30000},
    {"LocalAt", {500000, 1000, Zone::Local}, 0},
    {"LocalAbove", {500001, 1000, Zone::Local}, 0},
    {"RemoteBelow", {499999, 1000, Zone::Remote}, 70000},
    {"RemoteAt", {500000, 1000, Zone::Remote}, 70000},
    {"RemoteAbove", {500001, 1000, Zone::Remote}, 70000}
};

INSTANTIATE_TEST_CASE_P(Tariffs, FeeMatrixTest, ::testing::ValuesIn(fee_cases), [](const ::testing::TestParamInfo<FeeCase>& info) {
    return std::string{info.param.name};
});


class AcceptedWeightTest : public ::testing::TestWithParam<int> {};
TEST_P(AcceptedWeightTest, KeepsBaseFee) {
    DeliveryPolicy policy;
    EXPECT_EQ(policy.quote(Shipment{100000, GetParam()}), 30000);
}
INSTANTIATE_TEST_SUITE_P(Boundaries, AcceptedWeightTest, ::testing::Values(1, 1000, 20000));

class RejectedWeightTest : public ::testing::TestWithParam<int> {};
TEST_P(RejectedWeightTest, RefuseShipment) {
    DeliveryPolicy policy;
    EXPECT_THROW(policy.quote(Shipment{100000, GetParam()}), std::invalid_argument);
}
INSTANTIATE_TEST_SUITE_P(Boundaries, RejectedWeightTest, ::testing::Values(-1, 0, 20001));


class MockCarrier : public Carrier {
public:
    MOCK_METHOD(std::string, reserve, (Cents fee, Grams grams), (override));
};

class MockNotification : public Notification {
public:
    MOCK_METHOD(void, send, (const std::string& tracking), (override));
};

TEST(BookingTest, SuccessfulBookingReservesAndNotifies) {
    testing::StrictMock<MockCarrier> carrier;
    testing::StrictMock<MockNotification> notification;
    BookingService service{carrier, notification};
    testing::InSequence order;
    EXPECT_CALL(carrier, reserve(30000, 1000))
    .WillOnce(testing::Return("SHIP-17"));
    EXPECT_CALL(notification, send("SHIP-17")).Times(1);
    EXPECT_EQ(service.book(Shipment{100000}), "SHIP-17");
}

TEST(BookingTest, CarrierRejectionDoesNotNotify) {
    testing::StrictMock<MockCarrier> carrier;
    testing::StrictMock<MockNotification> notification;
    BookingService service{carrier, notification};
    EXPECT_CALL(carrier, reserve(30000, 1000))
    .WillOnce(testing::Return(""));
    EXPECT_CALL(notification, send(testing::_)).Times(0);
    EXPECT_THROW(service.book(Shipment{100000}), BookingRejected);
}

//ДЗ

TEST(RegularCustomerTest, RegularLocalThresholdIsFree) {
    DeliveryPolicy policy;
    Shipment shipmment{300000, 1000, Zone::Local, Customer::Regular};
    EXPECT_EQ(policy.quote(shipmment), 0);
}

TEST(RegularCustomerTest, RegularLocalHasBaseFee) {
    DeliveryPolicy policy;
    Shipment shipmment{299999, 1000, Zone::Local, Customer::Regular};
    EXPECT_EQ(policy.quote(shipmment), 30000);
}

TEST(RegularCustomerTest, RegularRemoteHasReducedFee) {
    DeliveryPolicy policy;
    Shipment shipmment{1000000, 1000, Zone::Remote, Customer::Regular};
    EXPECT_EQ(policy.quote(shipmment), 50000);
}