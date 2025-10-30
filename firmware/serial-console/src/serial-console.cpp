/*
 * Project: Serial Console Basics
 * Repo: blueprint-beginner-serial-console
 * Author: Particle
 * Date: 2025-05-04
 *
 * Description:
 *  This beginner blueprint introduces the USB Serial terminal on Particle devices.
 *  It shows how to:
 *   - Initialize and use the Serial port over USB
 *   - Open a serial terminal from the Particle CLI
 *   - Register a cloud function that, when called, prints a message to Serial
 *
 * Quickstart:
 *   1) Flash this firmware to your device.
 *   2) Open a terminal: particle serial monitor --follow
 *   3) In the Console, call the function 'printMsg' (optionally pass text).
 *   4) Observe the message printed in your serial terminal.
 *
 * Docs:
 *   - Firmware template & best practices:
 *     https://docs.particle.io/firmware/best-practices/firmware-template/
 *   - Serial reference:
 *     https://docs.particle.io/reference/device-os/firmware/#serial
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently (keeps OTA responsive)
SYSTEM_THREAD(ENABLED);

// Show logs over USB (view with: particle serial monitor --follow)
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// -------------------------------------------------------------------
// Configuration
// -------------------------------------------------------------------

// Choose your serial baud. 9600 is common and beginner-friendly.
constexpr uint32_t SERIAL_BAUD = 9600;

// Forward declaration for the cloud function
int printMsgHandler(String command);

// -------------------------------------------------------------------
// setup() — runs once on boot
// -------------------------------------------------------------------
void setup() {
    // Start the USB serial port.
    // Note: Serial is available over the same USB cable used for power/flash.
    Serial.begin(SERIAL_BAUD);

    // (Optional) Wait briefly for a terminal to attach so the first lines are visible.
    // Do not block forever — keep OTA available.
    unsigned long start = millis();
    while (!Serial.isConnected() && (millis() - start < 3000)) {
        // Give the host time to open the USB CDC interface (up to ~3s)
        delay(50);
    }

    // Register a cloud function named "printMsg".
    // Calling this from the Console or REST API will invoke printMsgHandler(),
    // which writes a message to the Serial terminal.
    Particle.function("printMsg", printMsgHandler);

    // Friendly boot banner for the serial terminal
    Serial.println();
    Serial.println("=== Particle Serial Console Basics ===");
    Serial.println("Baud: 9600  |  Data: 8N1");
    Serial.println("Use 'particle serial monitor --follow' to view output.");
    Serial.println("Cloud function available: printMsg(<optional text>)");
    Serial.println("--------------------------------------");
    Serial.println();

    Log.info("Setup complete. Cloud function 'printMsg' is ready.");
}

// -------------------------------------------------------------------
// loop() — runs repeatedly
// -------------------------------------------------------------------
void loop() {
    // No continuous work is required; we respond to cloud function calls.
    // Keep the loop light to preserve OTA responsiveness.
    delay(50);
}

// -------------------------------------------------------------------
// printMsgHandler() — Cloud Function
// -------------------------------------------------------------------
// Usage examples (from Console → Functions):
//   - Name: printMsg, Argument: <empty>        → prints a default greeting
//   - Name: printMsg, Argument: Hello Tachyon  → prints the text you provide
//
// Return values:
//    1  Success
//   -1  Failure (e.g., Serial not available)
int printMsgHandler(String command) {
    // If Serial isn't ready (very rare after setup), return an error.
    if (!Serial) {
        Log.warn("Serial not available; message not printed.");
        return -1;
    }

    // Prepare the message to print
    String msg;
    if (command.length() == 0) {
        msg = "Hello from Particle! (default message)";
    } else {
        msg = "Cloud says: " + command;
    }

    // Print a timestamped line to the serial terminal
    Serial.printlnf("[%lu ms] %s", millis(), msg.c_str());

    // Also log over the USB logging channel for visibility in CLI
    Log.info("Printed to Serial: %s", msg.c_str());

    return 1;
}
