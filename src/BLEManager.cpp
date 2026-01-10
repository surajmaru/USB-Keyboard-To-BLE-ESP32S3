#include "BLEManager.h"
#include "Config.h"

BLEManager::BLEManager() : _bleCombo(nullptr) {}

void BLEManager::begin(uint8_t /*slot*/, const char *deviceName) {

  Serial.printf("[BLE] Initializing: '%s'\n", deviceName);

  _bleCombo = new BleCombo(deviceName, DEVICE_MANUFACTURER, BATTERY_LEVEL);
  _bleCombo->begin();

  Serial.printf("[BLE] Advertising as '%s'\n", deviceName);
}

bool BLEManager::isConnected() {
  return (_bleCombo != nullptr && _bleCombo->isConnected());
}

void BLEManager::sendKeyboardReport(const uint8_t *keys, uint8_t modifiers) {
  if (!isConnected()) return;

  KeyReport report{};
  report.modifiers = modifiers;
  memcpy(report.keys, keys, 6);
  _bleCombo->sendReport(&report);
}
