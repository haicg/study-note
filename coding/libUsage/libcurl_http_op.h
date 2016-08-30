#ifndef __HTTP_OP_H__
#define __HTTP_OP_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LENGTH_HTTP_RESPONSE 2048
#define MAX_LENGTH_HTTP_PARM 512

#define ERROR_OVER_LENGTH_HTTP_PARM() \
{\
	fprintf(stderr,"the parm is over length. \n \
	you can change the macro MAX_LENGTH_HTTP_PARM ,\n \
	at the same time you should promise the buf is enough for parms.\n"); \
}

#define ERROR_OVER_LENGTH_HTTP_RESPONSE() \
{\
	fprintf(stderr,"the parm is over length. \n \
	you can change the macro MAX_LENGTH_HTTP_RESPONSE ,\n \
	at the same time you should promise the buf is enough to store.\n"); \
}

	typedef struct http_post_parms_s {
		char *host;
		char *host_url;
		char *parms_str;
		int port;
		int is_https;
	} http_request_parms_t;

	typedef enum {
		REQ_OPT_HTTPS,
		REQ_OPT_PORT
	} request_opt_type_t;

	extern int http_post_with_json(
		char *https_response_buf,
		CURL * curl,
		http_request_parms_t * post_parm);

#ifdef __cplusplus
}
#endif				//end __cplusplus
#endif
