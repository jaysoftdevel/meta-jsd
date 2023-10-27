// MotorStatus.hpp
#ifndef MOTORSTATUS_HPP
#define MOTORSTATUS_HPP

#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>

class MotorStatus {
// make private in future!
public:
    unsigned short positionLeft = 0;
    unsigned short positionRight = 0;

public:
    unsigned short getPositionLeft() const;
    unsigned short getPositionRight() const;
    void setMotorStatus(unsigned short ML, unsigned short MR);

    nlohmann::json serialize_json() const;
    std::vector<uint8_t> serialize_bytes() const;
    static MotorStatus deserialize_bytes(const std::vector<uint8_t>& bytes);
    static MotorStatus deserialize_json(const nlohmann::json& j);
};

#endif // MOTORSTATUS_HPP