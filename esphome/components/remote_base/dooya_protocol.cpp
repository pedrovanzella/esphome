#include "dooya_protocol.h"
#include "esphome/core/log.h"

namespace esphome {
namespace remote_base {
static const char *const TAG = "remote.dooya";

bool DooyaData::operator==(const DooyaData &other) const {
  return this->address == other.address && this->multi == other.multi && this->channel == other.channel &&
         this->action == other.action;
}

void DooyaProtocol::encode(RemoteTransmitData *dst, const DooyaData &data) {}

optional<DooyaData> DooyaProtocol::decode(RemoteReceiveData data) {
  const auto size = data.size();
  /* if (size != 40) {
    ESP_LOGW(TAG, "Invalid Dooya frame size: %d", size);
    return {};
  } */
  DooyaData result;

  for (int i = 0; i < 24; i++) {
    result.address = (result.address << 1) | data[i];
  }
  for (int i = 24; i < 28; i++) {
    result.multi = (result.multi << 1) | data[i];
  }
  result.multi = result.multi == 1;
  for (int i = 28; i < 32; i++) {
    result.channel = (result.channel << 1) | data[i];
  }
  for (int i = 32; i < 40; i++) {
    result.action = (result.action << 1) | data[i];
  }

  return result;
}

void DooyaProtocol::dump(const DooyaData &data) {
  ESP_LOGI(TAG, "Received Dooya: address=%" PRIu32 ", multi=%" PRIu8 ", channel=%" PRIu8 ", action=%" PRIu8,
           data.address, data.multi, data.channel, data.action);
}

}  // namespace remote_base
}  // namespace esphome
