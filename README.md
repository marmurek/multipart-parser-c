## Multipart form data parser

### Features
* No dependencies
* Works with chunks of a data - no need to buffer the whole request
* Almost no internal buffering. Buffer size doesn't exceed the size of the boundary (~60-70 bytes)

Tested as part of [Cosmonaut](https://github.com/iafonov/cosmonaut) HTTP server.

Implementation based on [node-formidable](https://github.com/felixge/node-formidable)

Inspired by [http-parser](https://github.com/nodejs/http-parser)

### Usage (C)
This parser library works with several callbacks, which the user may set up at application initialization time.

```c
multipart_parser_settings settings;

memset(&settings, 0, sizeof(multipart_parser_settings));

settings.on_header_field = read_header_name;
settings.on_header_value = read_header_value;
settings.boundary_length = 38;
std::memcpy(settings.boundary, "--------------------------boundary1234", 38);
```

These functions must match the signatures defined in the multipart-parser header file.  For this simple example, we'll just use two of the available callbacks to print all headers the library finds in multipart messages.

Returning a value other than 0 from the callbacks will abort message processing.

```c
int read_header_name(multipart_parser* p, const char *at, size_t length)
{
   printf("%.*s: ", length, at);
   return 0;
}

int read_header_value(multipart_parser* p, const char *at, size_t length)
{
   printf("%.*s\n", length, at);
   return 0;
}
```

When a message arrives, callers must parse the multipart boundary from the **Content-Type** header (see the [RFC](http://tools.ietf.org/html/rfc2387#section-5.1) for more information and examples), and then execute the parser.

```c
multipart_parser parser;
multipart_parser_init(&parser, &settings);
multipart_parser_execute(&parser, &settings, body, length);
```

### Usage (C++)
In C++, when the callbacks are static member functions it may be helpful to pass the instantiated multipart consumer along as context.  The following (abbreviated) class called `MultipartConsumer` shows how to pass `this` to callback functions in order to access non-static member data.

```cpp
class MultipartConsumer
{
public:
    MultipartConsumer(const std::string& boundary)
    {
        memset(&m_settings, 0, sizeof(multipart_parser_settings));
        m_settings.on_header_field = ReadHeaderName;
        m_settings.on_header_value = ReadHeaderValue;
		std::memcpy(m_settings.boundary, boundary.c_str(), boundary.length())
        multipart_parser_init(&m_parser, &m_settings);
        m_parser->data = this;
    }

    int CountHeaders(const std::string& body)
    {
        multipart_parser_execute(&m_parser, &m_settings, body.c_str(), body.size());
        return m_headers;
    }

private:
    static int ReadHeaderName(multipart_parser* p, const char *at, size_t length)
    {
        MultipartConsumer* me = (MultipartConsumer*)p->data;
        me->m_headers++;
    }

    multipart_parser m_parser;
    multipart_parser_settings m_settings;
    int m_headers;
};
```

### Contributors
* [Daniel T. Wagner](http://www.danieltwagner.de/)
* [James McLaughlin](http://udp.github.com/)
* [Jay Miller](http://www.cryptofreak.org)

© 2012 [Igor Afonov](http://iafonov.github.com)
@ 2017 [Terry Wu](http://blog.terrywh.net)
