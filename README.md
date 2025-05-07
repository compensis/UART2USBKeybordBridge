# ⌨️ Arduino UART to USB HID Keyboard Bridge

This is a [PlatformIO](https://platformio.org/) based Arduino project that turns a supported microcontroller into a **UART to USB HID Keyboard Bridge**. When connected to a PC, the device identifies itself as a USB HID keyboard. Every character received via the hardware UART interface (Serial1) is immediately sent to the PC as a corresponding keyboard keystroke.

## 🚀 Features

- Emulates a USB HID keyboard
- Listens for characters on the hardware UART interface
- Sends received characters as individual keypresses

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

3. Connect your Arduino board and upload the firmware:
    ```bash
    pio run --environment micro --target upload
    ```

    **Note:** Replace `micro` with the appropriate environment name from the [platformio.ini](platformio.ini) file if you are using a different board. For example, use `leonardo` for an Arduino Leonardo or another environment defined in the configuration.

## 🔌 How It Works

- The board uses the [Arduino HID Project](https://github.com/NicoHood/HID) library to emulate a USB [Boot Keyboard](https://github.com/NicoHood/HID/wiki/Keyboard-API#boot-keyboard).
- It listens on `Serial1` (hardware UART) for incoming characters.
- Each character is sent to the PC as a keyboard keypress using `Keyboard.write()`.
