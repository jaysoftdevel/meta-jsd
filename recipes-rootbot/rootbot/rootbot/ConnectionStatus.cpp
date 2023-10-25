// ConnectionStatus.cpp
#include "ConnectionStatus.hpp"

nlohmann::json ConnectionStatus::serialize_json() const {
    nlohmann::json j;
    j["ping"] = ping;
    j["connectionStatus"] = connectionStatus;
    return j;
}

std::vector<uint8_t> ConnectionStatus::serialize_bytes() const {
    std::vector<uint8_t> bytes;
    bytes.resize(sizeof(ConnectionStatus));
    std::memcpy(bytes.data(), this, sizeof(ConnectionStatus));
    return bytes;
}

ConnectionStatus ConnectionStatus::deserialize_bytes(const std::vector<uint8_t>& bytes) {
    ConnectionStatus status;
    if (bytes.size() == sizeof(ConnectionStatus)) {
        std::memcpy(&status, bytes.data(), sizeof(ConnectionStatus));
    }
    return status;
}

ConnectionStatus ConnectionStatus::deserialize_json(const nlohmann::json& j) {
    ConnectionStatus status;
    if (j.contains("ping")) {
        status.ping = j["ping"];
    }
    if (j.contains("connectionStatus")) {
        status.connectionStatus = j["connectionStatus"];
    }
    return status;
}