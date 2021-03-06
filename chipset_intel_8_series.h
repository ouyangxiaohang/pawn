// Copyright 2014-2018 Google LLC. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SECURITY_ZYNAMICS_PAWN_CHIPSET_INTEL_8_SERIES_H_
#define SECURITY_ZYNAMICS_PAWN_CHIPSET_INTEL_8_SERIES_H_

#include "third_party/zynamics/pawn/chipset_intel_7_series.h"
#include "third_party/zynamics/pawn/pci.h"

namespace security {
namespace zynamics {

// All page references mentioned in this header and its implementation refer to
// the Intel 8 Series/C220 Series Chipset Datasheet, May 2014 (document number
// 328904-003). References to the mobile variants refer to the Mobile 4th
// Generation Intel Core Processor Familiy I/O Datasheet, June 2013 (document
// number 329003).
class Intel8SeriesChipset : public Intel7SeriesChipset {
 public:
  static constexpr bool IsIntegratedIo(uint16 device) {
    // Device ids were taken from the mobile datasheet, page 63.
    return (device == 0x9C41 /* Engineering Sample */ ||
            device == 0x9C43 /* QM87 Premium (i.e. HP EliteBook 840 G1) */ ||
            device == 0x9C45 /* Base SKU */);
  }

  static constexpr bool SupportsDevice(const Chipset::HardwareId& id) {
    // Device ids were taken directly from the datasheet, page 59.
    return id.vendor == 0x8086 &&
           (IsIntegratedIo(id.device) ||
            id.device == 0x8C41 /* Mobile Engineering Sample */ ||
            id.device == 0x8C42 /* Desktop Engineering Sample */ ||
            id.device == 0x8C44 /* Z87 */ || id.device == 0x8C46 /* Z85 */ ||
            id.device == 0x8C49 /* HM86 */ || id.device == 0x8C4A /* H87 */ ||
            id.device == 0x8C4B /* HM87 */ || id.device == 0x8C4C /* Q85 */ ||
            id.device == 0x8C4E /* Q87 */ || id.device == 0x8C4F /* QM87 */ ||
            id.device == 0x8C50 /* B85 */ || id.device == 0x8C52 /* C222 */ ||
            id.device == 0x8C54 /* C224 */ || id.device == 0x8C56 /* C226 */ ||
            id.device == 0x8C5C /* H81 */);
  }

  Chipset::Gcs ReadGcsRegister() override;

 protected:
  friend class Chipset;
  Intel8SeriesChipset(const Chipset::HardwareId& probed_id, Pci* pci);

  virtual bool IsIntegratedIo() { return IsIntegratedIo(hardware_id().device); }
};

}  // namespace zynamics
}  // namespace security

#endif  // SECURITY_ZYNAMICS_PAWN_CHIPSET_INTEL_8_SERIES_H_
