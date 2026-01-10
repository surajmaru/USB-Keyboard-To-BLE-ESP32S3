#include "BLEManager.h"
#include "Config.h"
#include <esp_mac.h>

BLEManager::BLEManager() : _bleCombo(nullptr) {}

void BLEManager::begin(uint8_t slot, const char *deviceName) {
  setUniqueMac(slot);

  Serial.printf("[BLE] Initializing slot %d: '%s'\n", slot + 1, deviceName);
  _bleCombo = new BleCombo(deviceName, DEVICE_MANUFACTURER, BATTERY_LEVEL);
  _bleCombo->begin();

  Serial.printf("[BLE] Advertising as '%s'\n", deviceName);
}

bool BLEManager::isConnected() {
  return (_bleCombo != nullptr && _bleCombo->isConnected());
}

void BLEManager::sendKeyboardReport(const uint8_t *keys, uint8_t modifiers) {
  if (!isConnected())
    return;

  KeyReport report;
  report.modifiers = modifiers;
  report.reserved = 0;
  memcpy(report.keys, keys, 6);
  _bleCombo->sendReport(&report);
}

void BLEManager::setUniqueMac(uint8_t slot) {
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);

  // Changing the last byte based on slot ensures each slot is a unique device
  mac[5] = (mac[5] & 0xF0) | (slot & 0x0F);

  esp_err_t err = esp_base_mac_addr_set(mac);
  if (err != ESP_OK) {
    Serial.printf("[BLE] Failed to set MAC address: %s\n",
                  esp_err_to_name(err));
  } else {
    Serial.printf("[BLE] Set MAC address to: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  }
}
