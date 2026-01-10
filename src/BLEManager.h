/**
 * @file BLEManager.h
 * @brief Manages Bluetooth Low Energy (BLE) HID functionality.
 */

#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <Arduino.h>
#include <BleCombo.h>

class BLEManager {
public:
  BLEManager();

  /**
   * @brief Initializes BLE with a specific slot name and a unique MAC.
   * @param slot Slot index (0-based) used to derivate the MAC.
   * @param deviceName Bluetooth display name.
   */
  void begin(uint8_t slot, const char *deviceName);

  /**
   * @brief Checks if a BLE host is currently connected.
   * @return true if connected.
   */
  bool isConnected();

  /**
   * @brief Sends a raw HID keyboard report.
   * @param keys Array of 6 key codes.
   * @param modifiers Modifier byte.
   */
  void sendKeyboardReport(const uint8_t *keys, uint8_t modifiers);

private:
  BleCombo *_bleCombo;

  /**
   * @brief Sets a unique MAC address derived from the base MAC and slot index.
   * This ensures different slots appear as different devices to the host.
   */
  void setUniqueMac(uint8_t slot);
};

#endif // BLE_MANAGER_H
