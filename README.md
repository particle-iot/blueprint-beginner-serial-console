# Blueprint – Beginner – Serial Console Basics

**Difficulty:** Beginner  
**Estimated Time:** 15–25 minutes  
**Hardware Needed:** None  
**Particle Features:** `Serial`, `Particle.function()`, `Console`

---

## Overview
This blueprint introduces the USB Serial terminal on Particle devices. You’ll open a serial terminal over USB and use a cloud function to print a message to the terminal. It’s a fast way to learn basic debugging and device interaction.

---

## Tools & Materials
- Any Particle device (Photon 2, Boron, etc.)  
- USB cable  
- [Particle Workbench](https://docs.particle.io/workbench/) or [Particle CLI](https://docs.particle.io/tutorials/developer-tools/cli/)  
- A Particle account with a claimed device  

---

## Steps
1. **Clone this repository:**
   ```bash
   git clone https://github.com/particle-iot/blueprint-beginner-serial-console.git
   cd blueprint-beginner-serial-console
   ```
2. **Open the project** in Particle Workbench or your preferred editor.  
3. **Flash the firmware** to your device:
   ```bash
   particle flash <device-name>
   ```
4. **Open a serial terminal** at 9600 baud (8N1):
   ```bash
   particle serial monitor --follow
   ```
5. **Call the cloud function** from the Particle Console:
   - Go to **Functions** → select `printMsg`  
   - Optional argument: any text to echo (e.g., `Hello Tachyon`)  
6. **Observe output** in your terminal. You’ll see a timestamped line like:
   ```
   [12345 ms] Cloud says: Hello Tachyon
   ```

---

## How It Works
- `Serial.begin(9600)` starts the USB CDC serial interface.  
- The firmware registers a cloud function named `printMsg`.  
- When called, the handler prints a line to the Serial terminal (and logs via `Log.info`).  
- The loop stays light to keep OTA responsive.

---

## Source Code
Main firmware: [`/src/serial-console.cpp`](src/serial-console.cpp)  
It’s generously commented so this repo can serve as standalone documentation.

---

## Expected Output
**Serial terminal (from `particle serial monitor --follow`):**
```
=== Particle Serial Console Basics ===
Baud: 9600  |  Data: 8N1
Use 'particle serial monitor --follow' to view output.
Cloud function available: printMsg(<optional text>)
--------------------------------------

[12345 ms] Cloud says: Hello Tachyon
```

---

## Extensions
- Change the baud rate or print a formatted table of sensor values.  
- Add another function (e.g., `clear`) to print separators or reset counters.  
- Combine with `Particle.publish()` to log to the cloud and to Serial.

---

## Assets
| File | Purpose |
|------|---------|
| `images/hero.jpg` | Optional hero image (16:9) |
| `images/console.png` | Screenshot of terminal output |

---

## License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
