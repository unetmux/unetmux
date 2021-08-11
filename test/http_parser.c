#include <llhttp.h>
#include <stdio.h>
#include <string.h>

int main()
{
    llhttp_t parser;
    llhttp_settings_t settings;

    llhttp_settings_init(&settings);
    llhttp_init(&parser, HTTP_REQUEST, &settings);

    const char * request = "POST / HTTP/1.1\r\n\r\n";

    int request_length = strlen(request);

    enum llhttp_errno error = llhttp_execute(&parser, request, request_length);

    if (error == HPE_OK)
    {
        printf("%d(Http data conetnet length) %d(http request method)", (int)parser.content_length, (int)parser.method);
    }

    else
    {
        fprintf(stderr, "Could not parse the http content");   
    }


    return 0;
}