/* Based on node-formidable by Felix Geisendörfer
 * Igor Afonov - afonov@gmail.com - 2012
 * terry wu - terry.wuhao@gmail.com - 2017
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
typedef struct multipart_parser_settings multipart_parser_settings;
typedef struct {
  void*  data;
  size_t        index;
  unsigned char state;

  char* lookbehind;
} multipart_parser;
typedef struct multipart_parser_state multipart_parser_state;

typedef int (*multipart_data_cb) (multipart_parser*, const char *at, size_t length);
typedef int (*multipart_notify_cb) (multipart_parser*);

struct multipart_parser_settings {
  multipart_data_cb on_header_field;
  multipart_data_cb on_header_value;
  multipart_data_cb on_part_data;

  multipart_notify_cb on_part_data_begin;
  multipart_notify_cb on_headers_complete;
  multipart_notify_cb on_part_data_end;
  multipart_notify_cb on_body_end;
  size_t boundary_length;
  char   boundary[128]; /* place at rear for larger boundaries: at least 2 * boundary_length */
};

void multipart_parser_init(multipart_parser* parser, const multipart_parser_settings* settings);
#define multipart_parser_free(p) (void)

size_t multipart_parser_execute(multipart_parser* p, const multipart_parser_settings* settings, const char *buf, size_t len);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
