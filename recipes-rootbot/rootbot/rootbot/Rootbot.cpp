// Rootbot.cpp
#include "Rootbot.hpp"

using namespace jsd;

const DistanceSensors& Rootbot::getDistanceSensors() const {
    return distanceSensors;
}

DistanceSensors& Rootbot::getDistanceSensors() {
    return distanceSensors;
}

const ConnectionStatus& Rootbot::getConnectionStatus() const {
    return connectionStatus;
}

ConnectionStatus& Rootbot::getConnectionStatus() {
    return connectionStatus;
}

const MotorStatus& Rootbot::getMotorStatus() const {
    return motorStatus;
}

MotorStatus& Rootbot::getMotorStatus() {
    return motorStatus;
}

unsigned char Rootbot::getCurrentLoad() const {
    return currentLoad;
}

nlohmann::json Rootbot::serialize_json() const {
    nlohmann::json j;
    j["distanceSensors"] = distanceSensors.serialize_json();
    j["connectionStatus"] = connectionStatus.serialize_json();
    j["motorStatus"] = motorStatus.serialize_json();
    j["currentLoad"] = currentLoad;
    return j;
}

std::vector<uint8_t> Rootbot::serialize_bytes() const {
    std::vector<uint8_t> bytes;
    bytes.resize(sizeof(Rootbot));
    std::memcpy(bytes.data(), this, sizeof(Rootbot));
    return bytes;
}

Rootbot Rootbot::deserialize_bytes(const std::vector<uint8_t>& bytes) {
    Rootbot data;
    if (bytes.size() == sizeof(Rootbot)) {
        std::memcpy(&data, bytes.data(), sizeof(Rootbot));
    }
    return data;
}

Rootbot Rootbot::deserialize_json(const nlohmann::json& j) {
    Rootbot data;
    if (j.contains("distanceSensors")) {
        data.distanceSensors = DistanceSensors::deserialize_json(j["distanceSensors"]);
    }
    if (j.contains("connectionStatus")) {
        data.connectionStatus = ConnectionStatus::deserialize_json(j["connectionStatus"]);
    }
    if (j.contains("motorStatus")) {
        data.motorStatus = MotorStatus::deserialize_json(j["motorStatus"]);
    }
    if (j.contains("currentLoad")) {
        data.currentLoad = j["currentLoad"];
    }
    return data;
}