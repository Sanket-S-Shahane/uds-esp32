/*
 * uds-esp32 - Day 15 :Minimum viable TWAI driver
 * 
 * Goal : install and start the TWAIdriver, log success.
 * No transmit, no receive yet. Just confirm driver loads cleanly
 * 
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/twai.h"
#include "esp_log.h"

static const char *TAG = "uds_esp32";

static void can_init(void)
{
    //----Stage 1: Configs ----
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT
    (
        GPIO_NUM_5,          // CAN TX pin ( to SN65HVD230 CTX)
        GPIO_NUM_4,          // CAN RX pin ( from SN65HVD230 CRX)
        TWAI_MODE_NO_ACK
    );
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // ---- Stage 2: Install ----
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to install TWAI driver");
        return;
    }
    ESP_LOGI(TAG, "TWAI driver installed");

    // ---- Stage 4: Start ----
    if (twai_start() != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start TWAI driver");
        return;
    }
    ESP_LOGI(TAG, "TWAI driver started");
}

static void can_transmit_test(uint32_t counter)
{
    twai_message_t message = {
        .identifier = 0x123,
        .data_length_code = 8,
        .data = {
            (uint8_t)(counter & 0xFF),
            0xAA,
            0xBB,
            0xCC,
            0xDD,
            0xEE,
            0xFF,
            0X00
        }
    };

    esp_err_t result = twai_transmit(&message, pdMS_TO_TICKS(1000));

    if (result == ESP_OK) {
        ESP_LOGI(TAG, "TX ok: ID=0x%lx DLC=%d data[0]=0x%02x",
                 message.identifier,
                 message.data_length_code,
                 message.data[0]);
    }
    else {
        ESP_LOGE(TAG, "TX failed: esp_err = %d", result);
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "uds-esp32 starting up");

    can_init();

    // Hearbeat loop -prove the program keep running
    int counter = 0;
    while(1)
    {
        ESP_LOGI(TAG, "alive, counter = %d", counter);
        can_transmit_test(counter);
        counter++;
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}