# Problem Statement 1 – RTOS Task and Queue Handling

This code demonstrates an ESP32 FreeRTOS-based embedded application with two tasks communicating via a queue. It is implemented in Arduino IDE using ESP32 board support.

## 📌 Features Implemented

- **Task1 (ExampleTask1)**:
  - Sends a custom structure to a queue every **500 ms** using `vTaskDelayUntil()` to ensure exact timing.
  - The structure contains two fields: `dataID` and `DataValue`, controlled by global variables `G_DataID` and `G_DataValue`.

- **Task2 (ExampleTask2)**:
  - Continuously waits to receive data from the queue.
  - Applies logic based on the received `dataID` and `DataValue`:
    - `dataID == 0`: Deletes itself.
    - `dataID == 1`:
      - `DataValue == 0`: Increases priority by 2 (once).
      - `DataValue == 1`: Decreases priority back to original (if previously increased).
      - `DataValue == 2`: Deletes itself.
  - Prints the received values and status messages to the Serial Monitor.

## 🧪 Test Simulation

In the `loop()` function, `G_DataID` and `G_DataValue` are changed every 10 seconds to simulate different inputs:

```cpp
Sending: dataID = 1, dataValue = 0 → Increase priority
Sending: dataID = 1, dataValue = 1 → Decrease priority
Sending: dataID = 1, dataValue = 2 → Delete Task 2
Sending: dataID = 0 → Delete Task 2
