/********************************************
** \file http_op.c
** \brief
** \author lihaicg
** \date 2016年03月23日 星期三 15时53分05秒
** Mail:  lihaicg@126.com
**********************************************/

#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>
#include <string.h>
#include "libcurl_http_op.h"
//#include "log.h"

#define http_request_comm_opt(parm) { \
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt"); \
	/* ask libcurl to show us the verbose output */ \
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);\
	/*pass headers to the data stream */ \
	curl_easy_setopt(curl, CURLOPT_HEADER, 1L); \
	curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 60 * 60 * 72); \
	curl_easy_setopt(curl, CURLOPT_URL, parm->host_url); \
	curl_easy_setopt(curl, CURLOPT_PORT, parm->port); \
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &process_data);\
	if (parm->is_https == 1) {  \
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);\
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);\
	}\
}

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
	//size_t return_size = fwrite(buffer, size, nmemb, fp);
	char *user_buf = (char *)user_p;
	int data_size = size * nmemb;
	if (data_size < MAX_LENGTH_HTTP_RESPONSE) {
		strncpy(user_buf, (char *)buffer, data_size);
		user_buf[data_size] = '\0';
	} else {
		ERROR_OVER_LENGTH_HTTP_RESPONSE();
		user_buf[0] = '\0';
	}
	return data_size;
}

int http_get(char *https_response_buf, CURL * curl, http_request_parms_t * parm)
{
	// CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	curl = curl_easy_init();	// 初始化
	if (curl) {
		headers = curl_slist_append(headers, "Accept: Agent-007");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);	// 改协议头

		http_request_comm_opt(parm);
		//curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");// 代理
		curl_easy_setopt(curl, CURLOPT_HTTPGET, parm->parms_str);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA,
				 (void *)https_response_buf);

		res = curl_easy_perform(curl);	// 执行
		if (res != 0) {

			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);
		}
	}
	return 0;
}

int http_post_with_json(char *https_response_buf, CURL * curl,
			http_request_parms_t * post_parm)
{
	CURLcode res;
	//CURL *curl = curl_easy_init();
	struct curl_slist *headers = NULL;
	if (curl) {
		headers = curl_slist_append(headers,
			"Content-Type:application/json;charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		http_request_comm_opt(post_parm);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA,
				 (void *)https_response_buf);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_parm->parms_str);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
			return -1;
		}
	}
	return 0;
}
