#include <Arduino.h>

// -------------------- Data Structure --------------------
typedef struct {
  uint8_t dataID;
  int32_t DataValue;
} Data_t;

// -------------------- Global Variables --------------------
uint8_t G_DataID = 1;
int32_t G_DataValue = 0;

bool priorityIncreased = false;
UBaseType_t initialPriority = 1;

// -------------------- Handles --------------------
QueueHandle_t Queue1;
TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

// -------------------- Task 1: Sender --------------------
void ExampleTask1(void *pv) {
  Data_t data;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xDelay = pdMS_TO_TICKS(500);

  while (1) {
    data.dataID = G_DataID;
    data.DataValue = G_DataValue;

    xQueueSend(Queue1, &data, portMAX_DELAY);
    vTaskDelayUntil(&xLastWakeTime, xDelay);
  }
}

// -------------------- Task 2: Receiver --------------------
void ExampleTask2(void *pv) {
  Data_t rxData;

  while (1) {
    if (xQueueReceive(Queue1, &rxData, portMAX_DELAY) == pdPASS) {
      Serial.printf("Received -> ID: %d, Value: %ld\n", rxData.dataID, rxData.DataValue);

      if (rxData.dataID == 0) {
        Serial.println("Task2: Deleting itself (dataID == 0)");
        vTaskDelete(NULL);
      } 
      else if (rxData.dataID == 1) {
        if (rxData.DataValue == 0 && !priorityIncreased) {
          Serial.println("Increasing priority...");
          UBaseType_t newPriority = uxTaskPriorityGet(NULL) + 2;
          vTaskPrioritySet(NULL, newPriority);
          priorityIncreased = true;
          Serial.printf("Task2: Priority increased to %d\n", newPriority);
        } 
        else if (rxData.DataValue == 1 && priorityIncreased) {
          vTaskPrioritySet(NULL, initialPriority);
          priorityIncreased = false;
          Serial.printf("Task2: Priority decreased to %d\n", initialPriority);
        } 
        else if (rxData.DataValue == 2) {
          Serial.println("Task2: Deleting itself (dataValue == 2)");
          vTaskDelete(NULL);
        }
      }
    }
  }
}

// -------------------- Arduino Setup --------------------
void setup() {
  Serial.begin(115200);
  delay(1000); // Let serial settle

  // Create the queue
  Queue1 = xQueueCreate(5, sizeof(Data_t));
  if (Queue1 == NULL) {
    Serial.println("Error creating the queue");
    while (1);
  }

  // Create Task1
  xTaskCreatePinnedToCore(ExampleTask1, "Task1", 2048, NULL, 1, &TaskHandle_1, 0);

  // Create Task2
  xTaskCreatePinnedToCore(ExampleTask2, "Task2", 2048, NULL, initialPriority, &TaskHandle_2, 1);
}

// -------------------- Arduino Loop (Simulating Data Changes) --------------------
void loop() {
  delay(10000);  // Wait 10 seconds before each change

  static int state = 0;

  switch (state) {
    case 0:
      Serial.println("Sending: dataID = 1, dataValue = 0 → Increase priority");
      G_DataID = 1;
      G_DataValue = 0;
      break;
    case 1:
      Serial.println("Sending: dataID = 1, dataValue = 1 → Decrease priority");
      G_DataID = 1;
      G_DataValue = 1;
      break;
    case 2:
      Serial.println("Sending: dataID = 1, dataValue = 2 → Delete Task 2");
      G_DataID = 1;
      G_DataValue = 2;
      break;
    case 3:
      Serial.println("Sending: dataID = 0 → Delete Task 2");
      G_DataID = 0;
      G_DataValue = 99;
      break;
  }

  state = (state + 1) % 4;
}
