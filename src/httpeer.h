#include <functional>
#include <map>
#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>


#ifndef HTTPEER_H
#define HTTPEER_H


typedef std::function<void(String payload)> ResponseHandler;


class Httpeer {
private:
    std::map<t_http_codes, ResponseHandler> _response_handlers;
    ResponseHandler _other_response_handler = nullptr;

    int _res_code = 0;

    String _server_url;

    HTTPClient _http;

    void _send(const char *method, String path, String content, ResponseHandler handler);

public:
    Httpeer(String server_url);

    void get(String path, String content);
    void get(ResponseHandler handler);
    void get(String path, ResponseHandler handler);
    void get(String path, String content, ResponseHandler handler);

    void post(String path, String content);
    void post(ResponseHandler handler);
    void post(String path, ResponseHandler handler);
    void post(String path, String content, ResponseHandler handler);

    void on(t_http_codes res_code, ResponseHandler fn);
    void onOther(ResponseHandler fn);
};


#endif
