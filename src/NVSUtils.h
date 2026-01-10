/**
 * @file NVSUtils.h
 * @brief Utilities for Non-Volatile Storage (NVS) management, specifically BLE
 * bonds.
 */

#ifndef NVS_UTILS_H
#define NVS_UTILS_H

#include <stdint.h>

class NVSUtils {
public:
  /**
   * @brief Copies all keys from one NVS namespace to another.
   * @param src_ns Source namespace name.
   * @param dst_ns Destination namespace name.
   */
  static void copyNamespace(const char *src_ns, const char *dst_ns);

  /**
   * @brief Loads stored BLE bonds for a specific slot into the active BLE
   * namespace.
   * @param slot Slot index (0-based).
   */
  static void loadSlotBonds(uint8_t slot);

  /**
   * @brief Saves current active BLE bonds into the storage for a specific slot.
   * @param slot Slot index (0-based).
   */
  static void saveSlotBonds(uint8_t slot);
};

#endif // NVS_UTILS_H
