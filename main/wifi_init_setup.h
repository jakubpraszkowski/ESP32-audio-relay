#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_pm.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include <stdio.h>

#define DEFAULT_SSID "24link24"
#define DEFAULT_PWD "Link_gr3g_wifi"

#define DEFAULT_LISTEN_INTERVAL 1000
#define DEFAULT_BEACON_TIMEOUT  10000

#if CONFIG_EXAMPLE_POWER_SAVE_MIN_MODEM
#define DEFAULT_PS_MODE WIFI_PS_MIN_MODEM
#elif CONFIG_EXAMPLE_POWER_SAVE_NONE
#define DEFAULT_PS_MODE WIFI_PS_NONE
#else
#define DEFAULT_PS_MODE WIFI_PS_NONE
#endif /*CONFIG_POWER_SAVE_MODEM*/

void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data);
void wifi_power_save(void);

void wifi_status();