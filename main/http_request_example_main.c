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
#include "litechain_cfg.h"
#include <stdio.h>

char *api_key = API_KEY;
char *api_base = API_BASE;

void llm_simple_test(void)
{
	LLM *llm;
	llm = Openai_init("gpt-3.5-turbo-16k-0613",0.1,16*1024,api_key,api_base);
	if(llm == 0)
	{
		printf("llm init fail");
	}

	char *prompt = "Introduction to Beijing?(Answers are all in English)";

	char *chat_data =llm->run("/v1/chat/completions",prompt);

	printf("http read data:%s\n",chat_data);

	printf("ai:%s\n",OutputParserJson(chat_data,"choices","0","message","content",NULL));
}

void prompt_simple_test(void)
{
	LLM *llm;
	llm = Openai_init("gpt-3.5-turbo-16k-0613",0.1,16*1024,api_key,api_base);
	if(llm == 0)
	{
		printf("llm init fail");
	}

	const char* tour_introduction = "%s's tour introduction, recommend the corresponding %s";

	char *prompt = prompt_format(tour_introduction,"wuhan","Famous person of history");

	char *chat_data =llm->run("/v1/chat/completions",prompt);

	printf("http read data:%s\n",chat_data);

	printf("ai:%s\n",OutputParserJson(chat_data,"choices","0","message","content",NULL));
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(example_connect());
	//llm_simple_test();
	prompt_simple_test();
}
