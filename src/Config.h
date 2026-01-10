/**
 * @file Config.h
 * @brief Global configuration constants for the USB-to-BLE Bridge.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================================
// CONFIGURATION - Edit these to customize behavior
// ============================================================================

/** @brief Device names for each slot (will show up in Bluetooth settings) */
#define DEVICE_NAME_1 "BLE-Keyboard 1"
#define DEVICE_NAME_2 "BLE-Keyboard 2"
#define DEVICE_NAME_3 "BLE-Keyboard 3"

/** @brief Manufacturer name reported over BLE */
#define DEVICE_MANUFACTURER "ESP32-S3"

/** @brief Battery level reported over BLE (0-100) */
#define BATTERY_LEVEL 100

/** @brief Number of available device slots (maximum 3 recommended) */
#define NUM_DEVICE_SLOTS 3

/** @brief Key combo for device switching: Scroll Lock + number key */
#define ENABLE_DEVICE_SWITCHING true

/**
 * @brief LED feedback pin (blinks to show current slot)
 * Set to -1 to disable, or use your board's built-in LED pin
 */
#define LED_FEEDBACK_PIN 2

#endif // CONFIG_H
