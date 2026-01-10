/**
 * @file USBManager.h
 * @brief Manages USB Host and HID Driver functionality.
 */

#ifndef USB_MANAGER_H
#define USB_MANAGER_H

#include "hid_host.h"
#include "usb/usb_host.h"
#include <Arduino.h>

/** @brief Callback type for keyboard reports. */
typedef void (*KeyboardReportCallback)(const uint8_t *data, size_t length);

class USBManager {
public:
  /**
   * @brief Initializes the USB Host library and HID driver.
   * Spawns background tasks for USB event handling.
   */
  static void begin();

  /** @brief Sets the callback for incoming keyboard reports. */
  static void setKeyboardCallback(KeyboardReportCallback cb) {
    _keyboardCb = cb;
  }

private:
  static KeyboardReportCallback _keyboardCb;

  static void usb_lib_task(void *arg);
  static void hid_host_task(void *pvParameters);

  static void
  hid_host_device_callback(hid_host_device_handle_t hid_device_handle,
                           const hid_host_driver_event_t event, void *arg);
  static void hid_host_device_event(hid_host_device_handle_t hid_device_handle,
                                    const hid_host_driver_event_t event,
                                    void *arg);
  static void
  hid_host_interface_callback(hid_host_device_handle_t hid_device_handle,
                              const hid_host_interface_event_t event,
                              void *arg);
};

#endif // USB_MANAGER_H
