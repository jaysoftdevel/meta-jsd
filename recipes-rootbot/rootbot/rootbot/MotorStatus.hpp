// MotorStatus.hpp
#ifndef MOTORSTATUS_HPP
#define MOTORSTATUS_HPP

#include <vector>
#include <nlohmann/json.hpp>

class MotorStatus {
private:
    unsigned short positionLeft = 0xABu;
    unsigned short positionRight = 0xCDu;

public:
    unsigned short getPositionLeft() const;
    unsigned short getPositionRight() const;

    nlohmann::json serialize_json() const;
    std::vector<uint8_t> serialize_bytes() const;
    static MotorStatus deserialize_bytes(const std::vector<uint8_t>& bytes);
    static MotorStatus deserialize_json(const nlohmann::json& j);
};

#endif // MOTORSTATUS_HPP