#include "DistanceSensors.hpp"

unsigned char DistanceSensors::getDistFrontLeft() const
{
    return distFrontLeft;
}

unsigned char DistanceSensors::getDistFrontCenter() const
{
    return distFrontCenter;
}

unsigned char DistanceSensors::getDistFrontRight() const
{
    return distFrontRight;
}

unsigned char DistanceSensors::getDistRearRight() const
{
    return distRearRight;
}

unsigned char DistanceSensors::getDistRearLeft() const
{
    return distRearLeft;
}

nlohmann::json DistanceSensors::serialize_json() const
{
    nlohmann::json j;
    j["distFrontLeft"] = distFrontLeft;
    j["distFrontCenter"] = distFrontCenter;
    j["distFrontRight"] = distFrontRight;
    j["distRearLeft"] = distRearLeft;
    j["distRearRight"] = distRearRight;
    return j;
}

std::vector<uint8_t> DistanceSensors::serialize_bytes() const
{
    std::vector<uint8_t> bytes;
    bytes.resize(sizeof(DistanceSensors));
    std::memcpy(bytes.data(), this, sizeof(DistanceSensors));
    return bytes;
}

DistanceSensors DistanceSensors::deserialize_bytes(const std::vector<uint8_t> &bytes)
{
    DistanceSensors sensors;
    if (bytes.size() == sizeof(DistanceSensors))
    {
        std::memcpy(&sensors, bytes.data(), sizeof(DistanceSensors));
    }
    return sensors;
}

DistanceSensors DistanceSensors::deserialize_json(const nlohmann::json &j)
{
    DistanceSensors sensors;
    if (j.contains("distFrontLeft"))
    {
        sensors.distFrontLeft = j["distFrontLeft"];
    }
    if (j.contains("distFrontCenter"))
    {
        sensors.distFrontCenter = j["distFrontCenter"];
    }
    if (j.contains("distFrontRight"))
    {
        sensors.distFrontRight = j["distFrontRight"];
    }
    if (j.contains("distRearLeft"))
    {
        sensors.distRearLeft = j["distRearLeft"];
    }
    if (j.contains("distRearRight"))
    {
        sensors.distRearRight = j["distRearRight"];
    }
    return sensors;
}

void DistanceSensors::setDistanceSensor(int pos, unsigned char value)
{
    std::cout << "Set DD " << std::hex << pos << " with val " << value << " #" << std::endl;
    switch (pos)
    {
    case 0:
        std::cout << "Set FL" << std::endl;
        distFrontLeft = value;
        break;
    case 1:
        std::cout << "Set FC" << std::endl;
        distFrontCenter = value;
        break;
    case 2:
        std::cout << "Set FR" << std::endl;
        distFrontRight = value;
        break;
    case 3:
        std::cout << "Set RL" << std::endl;
        distRearLeft = value;
        break;
    case 4:
        std::cout << "Set RR" << std::endl;
        distRearRight = value;
        break;
    default:
        break;
    }
}