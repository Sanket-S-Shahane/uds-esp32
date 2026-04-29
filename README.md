# uds-esp32

A clean-room implementation of UDS (ISO 14229) services and ISO-TP (ISO 15765-2)
transport layer on ESP32 with SN65HVD230 CAN transceiver.

Built using **ESP-IDF v5.5** from publicly available specifications.
Personal learning project.

## Status

In active development.

## Hardware

- ESP32 DevKit V1 (DOIT)
- SN65HVD230 CAN transceiver module
- Standard jumper wires

## Toolchain

- ESP-IDF v5.5.4
- VS Code with Espressif IDF extension
- TWAI driver (ESP32's native CAN 2.0B controller)

## Goals

- Implement UDS services from scratch: 0x10, 0x22, 0x2F, 0x19, 0x27
- Implement ISO-TP transport layer for multi-frame CAN messages
- Document the protocol clearly so others can learn from it

## License

MIT - see LICENSE file.

## Author

Sanket Shahane | [LinkedIn](https://www.linkedin.com/in/sanket-s-shahane)
