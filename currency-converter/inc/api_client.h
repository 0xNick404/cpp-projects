#ifndef _APICLIENT_H
#define _APICLIENT_H

#include <string>
using std::string;

// Struct for storing the response string, where the member string points 
// to the string, and the member size stores the size of the string.
struct Response{
    char *string;
    size_t size;
};

// Function using the libcurl library in C++ to make an HTTP request and store the response into a string.
string fetch_currency_data();

// Writes each chunk of the response string received to dynamically allocated 
// memory, called repeatedly by curl_easy_perform() until the entire response
// string is created.  The function prototype is required by libcurl.
//
// Parameters:
//
// - data is a pointer to the chunk of the response
// - size will always be 1
// - nmemb is the number of chars/bytes received, the "number of elements"
// - user data will be a pointer to the Response struct in main BECAUSE we 
//   set it to be so using CURLOPT_WRITEDATA.
//
// The return value is expected to be the number of bytes in the chunk otherwise
// the libcurl library will stop the transfer.
size_t write_chunk(void *data, size_t size, size_t nmemb, void *userData);

#endif

// References:
// https://github.com/portfoliocourses/c-example-code/blob/main/libcurl_examples/store_http_response_into_string.c
