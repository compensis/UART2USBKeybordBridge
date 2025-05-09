# ⌨️ Arduino UART to USB HID Keyboard Bridge

This is a [PlatformIO](https://platformio.org/) based Arduino project that turns a supported microcontroller into a **UART to USB HID Keyboard Bridge**. When connected to a PC, the device identifies itself as a USB HID keyboard. Every character received via the hardware UART interface (Serial1) is immediately sent to the PC as a corresponding keyboard keystroke.

## 🚀 Features

- Emulates a USB HID keyboard
- Listens for characters on the hardware UART interface
- Sends received characters as individual keypresses

## ❓ Why This Project Was Created

I am using a [JetKVM](https://jetkvm.com/) connected to a Mac mini from 2012. Unfortunately, during the boot process of the Mac mini, the virtual USB keyboard provided by the JetKVM is not recognized when entering the FileVault password. 

To work around this issue, I use a SparkFun Pro Micro with the code from this repository. It is connected to the [extension port](https://jetkvm.com/docs/peripheral-devices/extension-port) of the JetKVM and is recognized by the Mac mini as a USB keyboard. Through the Serial Console Extension in the JetKVM web interface, I can then input the FileVault password successfully.

## 🛠 Requirements

- A microcontroller board with native USB support, such as:
  - Arduino Leonardo
  - Arduino Micro
  - SparkFun Pro Micro
- PlatformIO installed (via VS Code extension or CLI)
- USB cable for connection to your PC

## 📦 Installation

1. Clone this repository:
    ```bash
    git clone https://github.com/compensis/UART2USBKeybordBridge.git
    cd UART2USBKeybordBridge
    ```

2. Open the project in PlatformIO (VS Code):
    ```bash
    code .
    ```

3. (Optional) Adjust the keyboard layout:\
    Open the [platformio.ini](platformio.ini) file and modify the `build_flags` section to set your desired keyboard layout. For example:
    ```ini
    build_flags =
        -D HID_CUSTOM_LAYOUT
        -D LAYOUT_GERMAN_MAC
    ```
    Replace `LAYOUT_GERMAN_MAC` with the desired layout from the [HID-Project library](https://github.com/NicoHood/HID/blob/master/src/KeyboardLayouts/ImprovedKeylayouts.h).

4. Connect your Arduino board and upload the firmware:
    ```bash
    pio run --environment micro --target upload
    ```

    **Note:** Replace `micro` with the appropriate environment name from the [platformio.ini](platformio.ini) file if you are using a different board. For example, use `leonardo` for an Arduino Leonardo or another environment defined in the configuration.

## 🔌 How It Works

- The board uses the [Arduino HID Project](https://github.com/NicoHood/HID) library to emulate a USB [Boot Keyboard](https://github.com/NicoHood/HID/wiki/Keyboard-API#boot-keyboard).
- It listens on `Serial1` (hardware UART) for incoming characters.
- Each character is sent to the PC as a keyboard keypress using `Keyboard.write()`.
