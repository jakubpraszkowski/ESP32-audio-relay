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


/**
 * @brief      The function then checks the event base and event ID to determine which event occurred. 
 *
 * @param      arg         Not used
 * @param[in]  event_base  The event base is a unique identifier for a specific event category (WIFI_EVENT or IP_EVENT)
 * @param[in]  event_id    This parameter represents the specific event that occurred within the given event base
 * @param      event_data  This is a generic pointer to event-specific data associated with the event. In this function, vent_data is expected to be a pointer to the ip_event_got_ip_t structure, which contains information about the obtained IP address.
 */
void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data);

/**
 * @brief      Function initializes wifi module in station mode and power save mode.
 */
void wifi_power_save(void);

/**
 * @brief      Function sets gpio (LED) and sets it to 1 when the connection to wifi is valid.
 */
void wifi_status(void);