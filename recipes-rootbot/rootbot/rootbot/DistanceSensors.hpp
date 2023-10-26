#ifndef DISTANCESENSORS_HPP
#define DISTANCESENSORS_HPP

#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>

class DistanceSensors {
// make privte later!
public:
    unsigned char distFrontLeft = 0x12u;
    unsigned char distFrontCenter = 0x34u;
    unsigned char distFrontRight = 0x56u;
    unsigned char distRearLeft = 0x78u;
    unsigned char distRearRight = 0x90u;

public:
    unsigned char getDistFrontLeft() const;
    unsigned char getDistFrontCenter() const;
    unsigned char getDistFrontRight() const;
    unsigned char getDistRearRight() const;
    unsigned char getDistRearLeft() const;
    void setDistanceSensor(int pos, unsigned char value);

    nlohmann::json serialize_json() const;
    std::vector<uint8_t> serialize_bytes() const;
    static DistanceSensors deserialize_bytes(const std::vector<uint8_t>& bytes);
    static DistanceSensors deserialize_json(const nlohmann::json& j);
};

#endif // DISTANCESENSORS_HPP