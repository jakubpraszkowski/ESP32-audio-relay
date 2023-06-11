#include "dac_audio_test.h"

bool IRAM_ATTR dac_on_convert_done_callback(dac_continuous_handle_t handle, const dac_event_data_t *event, void *user_data)
{
    QueueHandle_t que = (QueueHandle_t)user_data;
    BaseType_t need_awoke;
    /* When the queue is full, drop the oldest item */
    if (xQueueIsQueueFullFromISR(que)) {
        dac_event_data_t dummy;
        xQueueReceiveFromISR(que, &dummy, &need_awoke);
    }
    /* Send the event from callback */
    xQueueSendFromISR(que, event, &need_awoke);
    return need_awoke;
}

void dac_write_data_asynchronously(dac_continuous_handle_t handle, QueueHandle_t que, uint8_t *data, size_t data_size)
{
    ESP_LOGI("audio", "Audio size %d bytes, played at frequency %d Hz asynchronously", data_size, 48000);
    uint32_t cnt = 1;
    while (1) {
        printf("Play count: %"PRIu32"\n", cnt++);
        dac_event_data_t evt_data;
        size_t byte_written = 0;
        /* Receive the event from callback and load the data into the DMA buffer until the whole audio loaded */
        while (byte_written < data_size) {
            xQueueReceive(que, &evt_data, portMAX_DELAY);
            size_t loaded_bytes = 0;
            ESP_ERROR_CHECK(dac_continuous_write_asynchronously(handle, evt_data.buf, evt_data.buf_size,
                                            data + byte_written, data_size - byte_written, &loaded_bytes));
            byte_written += loaded_bytes;
        }
        /* Clear the legacy data in DMA, clear times equal to the 'dac_continuous_config_t::desc_num' */
        for (int i = 0; i < 4; i++) {
            xQueueReceive(que, &evt_data, portMAX_DELAY);
            memset(evt_data.buf, 0, evt_data.buf_size);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}