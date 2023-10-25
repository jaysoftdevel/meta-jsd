#include "DistanceSensors.hpp"

unsigned char DistanceSensors::getDistFrontLeft() const {
    return distFrontLeft;
}

unsigned char DistanceSensors::getDistFrontCenter() const {
    return distFrontCenter;
}

unsigned char DistanceSensors::getDistFrontRight() const {
    return distFrontRight;
}

unsigned char DistanceSensors::getDistRearRight() const {
    return distRearRight;
}

unsigned char DistanceSensors::getDistRearLeft() const {
    return distRearLeft;
}

nlohmann::json DistanceSensors::serialize_json() const {
    nlohmann::json j;
    j["distFrontLeft"] = distFrontLeft;
    j["distFrontCenter"] = distFrontCenter;
    j["distFrontRight"] = distFrontRight;
    j["distRearLeft"] = distRearLeft;
    j["distRearRight"] = distRearRight;
    return j;
}

std::vector<uint8_t> DistanceSensors::serialize_bytes() const {
    std::vector<uint8_t> bytes;
    bytes.resize(sizeof(DistanceSensors));
    std::memcpy(bytes.data(), this, sizeof(DistanceSensors));
    return bytes;
}

DistanceSensors DistanceSensors::deserialize_bytes(const std::vector<uint8_t>& bytes) {
    DistanceSensors sensors;
    if (bytes.size() == sizeof(DistanceSensors)) {
        std::memcpy(&sensors, bytes.data(), sizeof(DistanceSensors));
    }
    return sensors;
}

DistanceSensors DistanceSensors::deserialize_json(const nlohmann::json& j) {
    DistanceSensors sensors;
    if (j.contains("distFrontLeft")) {
        sensors.distFrontLeft = j["distFrontLeft"];
    }
    if (j.contains("distFrontCenter")) {
        sensors.distFrontCenter = j["distFrontCenter"];
    }
    if (j.contains("distFrontRight")) {
        sensors.distFrontRight = j["distFrontRight"];
    }
    if (j.contains("distRearLeft")) {
        sensors.distRearLeft = j["distRearLeft"];
    }
    if (j.contains("distRearRight")) {
        sensors.distRearRight = j["distRearRight"];
    }
    return sensors;
}