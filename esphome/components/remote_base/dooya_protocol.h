#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "remote_base.h"

#include <cinttypes>

namespace esphome {
namespace remote_base {

struct DooyaData {
  DooyaData() {}
  bool operator==(const DooyaData &other) const;
  uint32_t action;
  uint32_t address;
  uint8_t single_multi;
  uint8_t channel;
  uint8_t key;
};

class DooyaProtocol : public RemoteProtocol<DooyaData> {
 public:
  void encode(RemoteTransmitData *dst, const DooyaData &data) override;
  optional<DooyaData> decode(RemoteReceiveData data) override;
  void dump(const DooyaData &data) override;
};

DECLARE_REMOTE_PROTOCOL(Dooya)

template<typename... Ts> class DooyaAction : public RemoteTransmitterActionBase<Ts...> {
  TEMPLATABLE_VALUE(uint32_t, action)
  TEMPLATABLE_VALUE(uint32_t, address)
  TEMPLATABLE_VALUE(uint8_t, single_multi)
  TEMPLATABLE_VALUE(uint8_t, channel)
  TEMPLATABLE_VALUE(uint8_t, key)
  void encode(RemoteTransmitData *dst, Ts... x) {
    DooyaProtocol().encode(dst, {this->action_.value(x...), this->address.value(x...), this->single_multi_.value(x...),
                                 this->channel_.value(x...), this->key_.value(x...)});
  }
};
}  // namespace remote_base
}  // namespace esphome
