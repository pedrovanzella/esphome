#include "dooya_protocol.h"
#include "esphome/core/log.h"

namespace esphome {
namespace remote_base {
static const char *const TAG = "remote.dooya";

bool DooyaData::operator==(const DooyaData &other) const {
  return this->action == other.action && this->address == other.address && this->single_multi == other.single_multi &&
         this->channel == other.channel && this->key == other.key;
}

void DooyaProtocol::encode(RemoteTransmitData *dst, const DooyaData &data) {}

optional<DooyaData> DooyaProtocol::decode(RemoteReceiveData data) { return {}; }

void DooyaProtocol::dump(const DooyaData &data) {
  ESP_LOGI(TAG,
           "Received Dooya: action=%" PRIu32 ", address=%" PRIu32 ", single_multi=%" PRIu8 ", channel=%" PRIu8
           ", key=%" PRIu8,
           data.action, data.address, data.single_multi, data.channel, data.key);
}

}  // namespace remote_base
}  // namespace esphome
