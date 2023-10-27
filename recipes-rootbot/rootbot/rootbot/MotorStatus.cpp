// MotorStatus.cpp
#include "MotorStatus.hpp"

unsigned short MotorStatus::getPositionLeft() const {
    return positionLeft;
}

unsigned short MotorStatus::getPositionRight() const {
    return positionRight;
}

nlohmann::json MotorStatus::serialize_json() const {
    nlohmann::json j;
    j["positionLeft"] = positionLeft;
    j["positionRight"] = positionRight;
    return j;
}

std::vector<uint8_t> MotorStatus::serialize_bytes() const {
    std::vector<uint8_t> bytes;
    bytes.resize(sizeof(MotorStatus));
    std::memcpy(bytes.data(), this, sizeof(MotorStatus));
    return bytes;
}

MotorStatus MotorStatus::deserialize_bytes(const std::vector<uint8_t>& bytes) {
    MotorStatus status;
    if (bytes.size() == sizeof(MotorStatus)) {
        std::memcpy(&status, bytes.data(), sizeof(MotorStatus));
    }
    return status;
}

MotorStatus MotorStatus::deserialize_json(const nlohmann::json& j) {
    MotorStatus status;
    if (j.contains("positionLeft")) {
        status.positionLeft = j["positionLeft"];
    }
    if (j.contains("positionRight")) {
        status.positionRight = j["positionRight"];
    }
    return status;
}

void MotorStatus::setMotorStatus(unsigned short ML, unsigned short MR){
    std::cout << "set motor status ML: " << std::hex << ML << " MR: " << MR << std::endl;
    positionLeft = ML;
    positionRight = MR;
    return;
}