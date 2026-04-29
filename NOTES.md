# Notes - uds-esp32

## Day 3 - Wed Apr 29, 2026

### ESP-IDF setup
- Version: v5.5.4 (current stable)
- Path: C:\esp\v5.5.4\esp-idf
- v6.0.1 install kept failing — switched to v5.5.4 via Expert Install, succeeded
- Lesson: stick to current stable, not latest. Latest is for trailblazers.

### VS Code workflow (no F1 menu needed)
- Bottom status bar has all the controls: target, port, flame icon (Build/Flash/Monitor)
- Exit serial monitor: Ctrl+]
- First build takes 3-6 min (compiles FreeRTOS + drivers from scratch). Subsequent builds are seconds.

### Phase 1 verification: blink example
- Built and flashed successfully on COM9
- Serial output confirms firmware running and toggling GPIO every 1s
- Onboard LED on DOIT DevKit V1 is GPIO 2, not GPIO 5 (board variant difference)
- This is expected — we're using GPIO 5 for CAN TX anyway

### TWAI vs CAN
- ESP32 calls its CAN peripheral "TWAI" (Two-Wire Automotive Interface) for trademark reasons
- Functionally identical to CAN 2.0B
- Driver header: driver/twai.h

### Hardware wiring (Phase 3)
- 3V3 → VCC (NOT 5V — SN65HVD230 is a 3.3V transceiver, 5V will damage it)
- GND → GND
- GPIO 5 (D5) → CTX/TXD (MCU TX → transceiver TX-input)
- GPIO 4 (D4) → CRX/RXD (MCU RX ← transceiver RX-output)
- CANH/CANL: not connected (loopback test tomorrow doesn't need physical bus)
- Always wire with power off

### Repo structure decisions
- Repo on E:\Sanket_code_backups\GitHub\uds-esp32 (E: drive — more space)
- ESP-IDF projects can be huge (~200-500MB build folder). Added build/ to .gitignore.
- LICENSE: MIT
- README + NOTES + .gitignore committed in first push

### Things I almost messed up
- [Add anything that confused you, you almost wired wrong, or learned the hard way]