/* Based on node-formidable by Felix Geisendörfer
 * Igor Afonov - afonov@gmail.com - 2012
 * terry wu - terry.wuhao@gmail.com - 2017
 * marmur -  2024
 * MIT License - http://www.opensource.org/licenses/mit-license.php
 */
#ifndef _multipart_parser_h
#define _multipart_parser_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <ctype.h>
typedef struct multipart_parser_callbacks multipart_parser_callbacks;
typedef struct {
  void*  context;
  size_t        index;
  unsigned char state;

  size_t boundary_length;
  char   boundary[128];

  char* lookbehind;
} multipart_parser;

typedef int (*multipart_data_cb) (void*, const char *at, size_t length);
typedef int (*multipart_notify_cb) (multipart_parser*);

struct multipart_parser_callbacks {
  multipart_data_cb on_header_field;
  multipart_data_cb on_header_value;
  multipart_data_cb on_part_data;

  multipart_notify_cb on_body_begin;
  multipart_notify_cb on_part_data_begin;
  multipart_notify_cb on_headers_complete;
  multipart_notify_cb on_part_data_end;
  multipart_notify_cb on_body_end;
};

void multipart_parser_init(multipart_parser* parser, const char* boundary, void* context);
size_t multipart_parser_process(multipart_parser* p, const multipart_parser_callbacks* callbacks, const char *buf, size_t len);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
