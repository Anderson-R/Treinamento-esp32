/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
#define CHIP_NAME "ESP32-S2 Beta"
#endif

char* TAG = "Threads";

void thread1(void* arg);
void thread2(void* arg);
void thread3(void* arg);


void thread1(void* arg)
{
    ESP_LOGI(TAG, "Entered thread1");
    
    // Block for 500ms.
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
    
    while (true)
    {
        // task code here
        ESP_LOGI(TAG, "Inside thread1"); // ler_sinal();
        vTaskDelay( xDelay );
    }
    
}

void thread2(void* arg)
{
    ESP_LOGI(TAG, "Entered thread2");
    
    // Block for 500ms.
    const TickType_t xDelay = 2500 / portTICK_PERIOD_MS;
    
    while (true)
    {
        // task code here
        ESP_LOGI(TAG, "Inside thread2");

        vTaskDelay( xDelay );
    }
    
}

void thread3(void* arg)
{
    ESP_LOGI(TAG, "Entered thread3");
    
    // Block for 500ms.
    const TickType_t xDelay = 5000 / portTICK_PERIOD_MS;
    
    while (true)
    {
        // task code here
        ESP_LOGI("thread3", "Inside thread3");
        vTaskDelay( xDelay );
    }
    
}

void app_main(void)
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU cores, WiFi%s%s, ",
            CHIP_NAME,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    TaskHandle_t xHandleThread1 = NULL;
    int var = 10;
    xTaskCreatePinnedToCore(thread1, "thread1", 4096, (void*) &var, 0, &xHandleThread1, 0);

    TaskHandle_t xHandleThread2 = NULL;
    xTaskCreatePinnedToCore(thread2, "thread2", 4096, NULL, 0, &xHandleThread2, 1);

    TaskHandle_t xHandleThread3 = NULL;
    xTaskCreate(thread3, "thread3", 4096, NULL, 0, &xHandleThread3);

    // for (int i = 10; i >= 0; i--) {
    //     printf("Restarting in %d seconds...\n", i);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
    // printf("Restarting now.\n");
    // fflush(stdout);
    // esp_restart();
}
