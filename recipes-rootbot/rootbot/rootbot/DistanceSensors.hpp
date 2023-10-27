#ifndef DISTANCESENSORS_HPP
#define DISTANCESENSORS_HPP

#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>

class DistanceSensors {
// make privte later!
public:
    unsigned char distFrontLeft = 0;
    unsigned char distFrontCenter = 0;
    unsigned char distFrontRight = 0;
    unsigned char distRearLeft = 0;
    unsigned char distRearRight = 0;

public:
    unsigned char getDistFrontLeft() const;
    unsigned char getDistFrontCenter() const;
    unsigned char getDistFrontRight() const;
    unsigned char getDistRearRight() const;
    unsigned char getDistRearLeft() const;
    void setDistanceSensors(unsigned char FL, unsigned char FC, unsigned char FR, unsigned char RL, unsigned char RR);

    nlohmann::json serialize_json() const;
    std::vector<uint8_t> serialize_bytes() const;
    static DistanceSensors deserialize_bytes(const std::vector<uint8_t>& bytes);
    static DistanceSensors deserialize_json(const nlohmann::json& j);
};

#endif // DISTANCESENSORS_HPP