// ConnectionStatus.hpp
#ifndef CONNECTIONSTATUS_HPP
#define CONNECTIONSTATUS_HPP

#include <vector>
#include <nlohmann/json.hpp>

class ConnectionStatus {
private:
    unsigned int ping = 0x123456u;
    bool connectionStatus = false;

public:
    unsigned int getPing() const;
    void setPing(unsigned int value);
    bool getConnectionStatus() const;
    void setConnectionStatus(bool value);

    nlohmann::json serialize_json() const;
    std::vector<uint8_t> serialize_bytes() const;
    static ConnectionStatus deserialize_bytes(const std::vector<uint8_t>& bytes);
    static ConnectionStatus deserialize_json(const nlohmann::json& j);
};

#endif // CONNECTIONSTATUS_HPP