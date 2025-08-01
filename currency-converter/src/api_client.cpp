#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <curl/curl.h>

#include "api_client.h"

string fetch_currency_data(){
    // curl stores the curl handle, result stores the return value after calling
    // the curl_easy_perform() function
    CURL *curl;
    CURLcode result;

    // Initialise the curl easy interface session, output an error message and 
    // exit the program with an error status if the initialisation fails.
    curl = curl_easy_init();
    if(curl == NULL){
        std::cerr << "HTTP request failed\n";
        exit(1);
    }

    // Declaration and initialisation of Response struct.  The member string points
    // to a block of memory 1 byte in size, realloc() is used to enlarge the 
    // block of memory so that it's large enough to store the response string.
    Response response;
    response.string = (char*)malloc(1);
    response.size = 0;

    // Set option to have request made to Fawaz Ahmed's Currency Exchange Rates API
    curl_easy_setopt(curl, CURLOPT_URL, "https://cdn.jsdelivr.net/npm/@fawazahmed0/currency-api@latest/v1/currencies/ttd.json");

    // Set option to have the function write_chunk called repeatedly by 
    // curl_easy_perform() for each chunk of the string.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_chunk);

    // Set option to have the memory address of the Response struct response 
    // passed to the write_chunk function (as the 4th argument) each time it is
    // called by curl_easy_perform().
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &response);

    // Perform the HTTP request, curl_easy_perform() will repeatedly call the 
    // write_chunk function with a chunk of the response string.
    result = curl_easy_perform(curl);

    // If the request failed exit with an error message and status.
    if(result != CURLE_OK){
        // curl_easy_strerror() will return a string with the error message
        std::cerr << "Error: " << curl_easy_strerror(result) << std::endl;
        exit(1);
    }

    // Store the response string that the string member will point to
    string result_str = response.string;

    // Finish the curl easy interface session
    curl_easy_cleanup(curl);

    // Free the dynamically allocated memory that stores the response string
    free(response.string);

    // Return the response string that the string member will point to
    return result_str;
}

size_t write_chunk(void *data, size_t size, size_t nmemb, void *userData){
    // Though the official libcurl documentation tells us size will always be 1, 
    // the idea is that nmemb is the amount of 'something' and size is the size 
    // of that 'something' in bytes.  So we multiply size by nmemb to get the 
    // total real size of the chunk, but practically real_size == nmemb.
    size_t real_size = size * nmemb;


    // The function prototype requires the 4th parameter to be a void pointer, but
    // WE know it's really a pointer to a Response struct so we type cast it here.
    Response *response = (Response *) userData;


    // Attempt to reallocate space for a larger block of memory for the Response 
    // struct string member to point to... we increase the size of the block of 
    // memory by the existing size PLUS the size of the chunk and 1 more byte to
    // store the null terminator.
    char *ptr = (char*)realloc(response->string, response->size + real_size + 1);


    // If re-allocation fails realloc() will return NULL, in this case we can 
    // return either 0 or CURL_WRITE_FUNCTION_ERROR to stop the transfer.
    if(ptr == NULL){
        // return 0;
        return CURL_WRITEFUNC_ERROR;
    }


    // If re-allocation was successful, set the string member of the Response 
    // struct to point to the enlarged block of memory.
    response->string = ptr;

    // Append the new chunk of char data to the existing string using memcpy.  The
    // source is set to the memory address of the last index in the existing 
    // string so that we begin copying the new chunk here.  This last index will 
    // be the null terminator of the existing string (unless it is the first time
    // that write_chunk is called, in which case we have no string data stored
    // yet).  We copy to this "source address" from the destination address "data"
    // where the chunk is stored, copying the size of the chunk (real_size).
    memcpy(&(response->string[response->size]), data, real_size);


    // Add the size of the chunk to the size member to keep track of the size of
    // the string received.
    response->size += real_size;


    // Set the last character of the block of memory for the string to the null 
    // terminator to complete the string.
    response->string[response->size] = 0;


    // Return the size of the chunk in bytes as required by libcurl
    return real_size;
}

// References:
// https://github.com/portfoliocourses/c-example-code/blob/main/libcurl_examples/store_http_response_into_string.c - Used for setting up basic libcurl HTTP requests
// https://github.com/fawazahmed0/exchange-api - API for currency conversion
