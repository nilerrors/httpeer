#include "httpeer.h"


Httpeer::Httpeer(String server_url) {
    _server_url = server_url;
}

/***
**
*
GET
*
**
***/
void Httpeer::get(String path = "/", String content = "") {
    get(path, content, nullptr);
}

void Httpeer::get(ResponseHandler handler) {
    get("/", "", handler);
}

void Httpeer::get(String path, ResponseHandler handler) {
    get(path, "", handler);
}

void Httpeer::get(String path, String content, ResponseHandler handler) {
    _send("GET", path, content, handler);
}

/***
**
*
POST
*
**
***/
void Httpeer::post(String path = "/", String content = "") {
    post(path, content, nullptr);
}

void Httpeer::post(ResponseHandler handler) {
    post("/", "", handler);
}

void Httpeer::post(String path, ResponseHandler handler) {
    post(path, "", handler);
}

void Httpeer::post(String path, String content, ResponseHandler handler) {
    _send("POST", path, content, handler);
}


/***
**
*
General
*
**
***/
void Httpeer::_send(t_http_methods method, String path, String content, ResponseHandler handler) {
    _http.begin(_server_url + path);

    _res_code = _http.sendRequest(method, content.c_str(), content.length());
    String payload = _http.getString()

    if (handler == nullptr) {
        bool response_handler_found = false;
        for (auto const& x: _response_handlers) {
            if (x.first == _res_code) {
                x.second(payload);
                response_handler_found = true;
            }
        }
        if (response_handler_found && _other_response_handler != nullptr) {
            _other_response_handler(payload);
        }
    } else {
        handler(payload);
    }
}


/***
**
*
Handler setters
*
**
***/
void Httpeer::on(t_http_codes res_code, ResponseHandler fn) {
    _response_handlers[res_code] = fn;
}

void Httpeer::onOther(ResponseHandler fn) {
    _other_response_handler = fn;
}
