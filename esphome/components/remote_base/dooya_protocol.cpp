#include "dooya_protocol.h"
#include "esphome/core/log.h"

namespace esphome {
namespace remote_base {
static const char *const TAG = "remote.dooya";

bool DooyaData::operator==(const DooyaData &other) const {
  return this->address == other.address && this->single == other.single && this->channel == other.channel &&
         this->action == other.action;
}

void DooyaProtocol::encode(RemoteTransmitData *dst, const DooyaData &data) {}

optional<DooyaData> DooyaProtocol::decode(RemoteReceiveData data) {
  DooyaData result;
  const auto size = data.size();
  // here we should return if the size is wrong, but I'm not sure about the size just yet, so I'm just going to log it.
  ESP_LOGW(TAG, "Received Dooya with size: %d", size);

  return result;
}

void DooyaProtocol::dump(const DooyaData &data) {
  ESP_LOGI(TAG, "Received Dooya: address=%" PRIu32 ", single=%" PRIu8 ", channel=%" PRIu8 ", action=%" PRIu8,
           data.address, data.single, data.channel, data.action);
}

}  // namespace remote_base
}  // namespace esphome
