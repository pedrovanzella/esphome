#include "dooya_protocol.h"
#include "esphome/core/log.h"

namespace esphome {
namespace remote_base {
static const char *const TAG = "remote.dooya";

static const uint32_t BIT_ONE_HIGH_US = 700;
static const uint32_t BIT_ONE_LOW_US = 300;
static const uint32_t BIT_ZERO_HIGH_US = 300;
static const uint32_t BIT_ZERO_LOW_US = 700;
static const uint32_t HEADER_HIGH_US = 4500;
static const uint32_t HEADER_LOW_US = 1400;

bool DooyaData::operator==(const DooyaData &other) const {
  return this->address == other.address && this->multi == other.multi && this->channel == other.channel &&
         this->action == other.action;
}

void DooyaProtocol::encode(RemoteTransmitData *dst, const DooyaData &data) {}

static boolean get_bit(RemoteReceiveData data) {
  if (data.peek_mark(BIT_ONE_HIGH_US) && data.peek_space(BIT_ONE_LOW_US)) {
    data.advance(2);
    return true;
  }
  if (data.peek_mark(BIT_ZERO_HIGH_US) && data.peek_space(BIT_ZERO_LOW_US)) {
    data.advance(2);
    return false;
  }
  return false;
}

optional<DooyaData> DooyaProtocol::decode(RemoteReceiveData data) {
  DooyaData out;

  // Sync pulse
  if (!data.expect_pulse_with_gap(HEADER_HIGH_US, HEADER_LOW_US)) {
    return {};
  }

  // address
  for (int i = 0; i < 24; i++) {
    out.address <<= 1UL;
    out.address |= get_bit(data);
  }

  // multi
  for (int i = 0; i < 4; i++) {
    out.multi <<= 1UL;
    out.multi |= get_bit(data);
  }

  // channel
  for (int i = 0; i < 4; i++) {
    out.channel <<= 1UL;
    out.channel |= get_bit(data);
  }

  // action
  for (int i = 0; i < 8; i++) {
    out.action <<= 1UL;
    out.action |= get_bit(data);
  }

  return out;
}

void DooyaProtocol::dump(const DooyaData &data) {
  ESP_LOGI(TAG, "Received Dooya: address=%" PRIu32 ", multi=%" PRIu8 ", channel=%" PRIu8 ", action=%" PRIu8,
           data.address, data.multi, data.channel, data.action);
}

}  // namespace remote_base
}  // namespace esphome
