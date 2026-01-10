# Convert your wired Keyboard --> Wireless using (ESP32-S3 WROOM N8R8)

## In this project i have shown how you can convert any wire keyboard into wireless using the esp32 s3.

## What This Does

```
┌─────────────┐     USB-C OTG     ┌────────────┐     Bluetooth     ┌──────────────┐
│ USB Keyboard│ ◄──────────────►  │ ESP32-S3   │ ◄───────────────► │ PC / Phone   │
└─────────────┘                   └────────────┘                   └──────────────┘
```

![WhatsApp Image 2026-01-10 at 8 26 04 PM](https://github.com/user-attachments/assets/3bad7aa6-a436-4116-8579-6e609e32ee42)


## Features

- **Native USB Host** - Uses ESP32-S3's hardware USB-OTG (no software emulation)
- **Multi-Device Support** - Switch between 3 paired devices with a key combo
- **Low Latency** - Direct HID report forwarding
- **Universal Compatibility** - Works with Windows, macOS, Linux, iOS, Android, Smart TVs

## Multi-Device Switching

You can pair with up to **3 different devices** (e.g., PC, Laptop, Tablet) and switch between them using your keyboard.

|      Key Combo      |      Action        |    Device Name   |
|---------------------|--------------------|------------------|
| **Scroll Lock + 1** | Switch to Device 1 | `BLE-Keyboard 1` |
| **Scroll Lock + 2** | Switch to Device 2 | `BLE-Keyboard 2` |
| **Scroll Lock + 3** | Switch to Device 3 | `BLE-Keyboard 3` |

**How it works:**
1. Press `Scroll Lock + 1`. Pair "USB-BLE Dev 1" with your first computer.
2. Press `Scroll Lock + 2`. The connection drops. Pair "USB-BLE Dev 2" with your second device.
3. Switch back and forth instantly using the key combos!
4. The active slot is **saved** and restored on reboot.
5. The **LED** on GPIO 2 blinks to indicate the current slot (1, 2, or 3 blinks).

## USB Keyboard Power

**The USB-C port on most ESP32-S3 boards does NOT output 5V!**

Even if you power the ESP32-S3 from the 5V pin, that power is NOT routed to the USB-C VBUS line.

### Making

#### Option 1: External Power to Keyboard (This is what I did, best for making it portable 💯)

Power the keyboard from external 5V into keyboard's + - and connect the same 5v/gnd and the D + - to the otg's (+ - D+ D-) wires and insert the typc-C port in the esp32 s3's usb/otg port.

```
                      ┌──────────────┐
  (EXTERNAL)  5V ─────┤   USB OTG    ├──── + USB Keyboard
              GND ────┤USB A to USB C|──── - USB Keyboard
                      └──────┬───────┘
                             │ D+/D- and 5V/gnd (We have to give 5V into the usb port too, then the esp32 s3 will identify it as a device)
                      ┌──────┴───────┐
                      │   ESP32-S3   │
                      │USB-C OTG port│
                      └──────────────┘
```

#### Option 2: Powered USB Hub 

Use a powered USB hub between ESP32-S3 and keyboard:

```
ESP32-S3 USB-C ──► [Powered USB Hub] ──► USB Keyboard
                         ▲
                    External 5V
```

## Software Part

### 1. Clone and Build

```bash
Make a folder and open it in vs code

Do this in the terminal:- git clone https://github.com/surajmaru/BLE-Keyboard-Conversion-ESP32-S3

Go into that folder

# Download and setup PlatformIO (VS Code Extension)

# IMPORTANT!!:-
You have to make changes in the "platormio.ini" file depending on your esp32s3 model, mine is ESP32-S3 WROOM N8R8 so if this is your chip than you dont have to make any changes in the code and if you have some other than you have to update according to your model otherwise it wont work.

# Then connect the s3 to PC and run this:-
pio run

# Upload to ESP32-S3
pio run -t upload
```

## Conclusion

Now just plug the keyboard into the OTG and power the esp32 and then just connect it to your preferred device and enjoy!
