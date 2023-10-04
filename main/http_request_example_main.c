/* HTTP GET Example using plain POSIX sockets

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "sdkconfig.h"
#include "../litechain/MODULE/MODULE_CFG.h"
#include <stdio.h>
#include "cJSON.h"
static const char *TAG = "example";


char* get_json(char* str)
{
    char *start, *end;

    // 寻找开始和结束的指针
    start = strchr(str, '{');
    end = strrchr(str, '}');

    // 如果没有找到，返回NULL
    if (!start || !end)
    {
        return NULL;
    }

    end[1] = '\0';
    return start;
}

void app_main(void)
{

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(example_connect());
#if 1
	LLM *llm;
	llm = Openai_init("gpt-3.5-turbo-16k-0613",0.1,16*1024,"sk-q6iEheCNMGxHlhQd04702713Ba7143A28997D1C2F9A32a27","api1.t-chat.cn");
	char *chat_data =llm->run("/v1/chat/completions","Introduction to Wuhan?");
	ESP_LOGI(TAG,"return data:%s",chat_data);
#endif
	char* json = get_json(chat_data);

	if(json != NULL)
	{
		ESP_LOGI(TAG,"json data:%s",json);
	}
	else
	{
		ESP_LOGI(TAG,"json data Incomplete");
	}

#if 1
	cJSON_InitHooks(0);
    cJSON* root = cJSON_Parse(json);
    if (root == NULL)
    {
    	ESP_LOGI(TAG,"Failed to parse JSON\n");
    }

    cJSON* choices_array = cJSON_GetObjectItem(root, "choices");
    if (choices_array == NULL || !cJSON_IsArray(choices_array))
    {
    	ESP_LOGI(TAG,"Invalid JSON format\n");
        cJSON_Delete(root);
    }

    cJSON* choice_object = cJSON_GetArrayItem(choices_array, 0);
    if (choice_object == NULL || !cJSON_IsObject(choice_object))
    {
    	ESP_LOGI(TAG,"Invalid JSON format\n");
        cJSON_Delete(root);
    }

    cJSON* message_object = cJSON_GetObjectItem(choice_object, "message");
    if (message_object == NULL || !cJSON_IsObject(message_object))
    {
    	ESP_LOGI(TAG,"Invalid JSON format\n");
        cJSON_Delete(root);
    }

    cJSON* content_string = cJSON_GetObjectItem(message_object, "content");
    if (content_string == NULL || !cJSON_IsString(content_string))
    {
    	ESP_LOGI(TAG,"Invalid JSON format\n");
        cJSON_Delete(root);
    }

    ESP_LOGI(TAG,"Content: %s\n", content_string->valuestring);

    cJSON_Delete(root);
#endif
}
