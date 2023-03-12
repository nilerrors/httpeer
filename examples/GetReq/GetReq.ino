#include <httpeer.h>


void setup() {
    Serial.begin(112500);

    Httpeer http("http://google.com/");

    http.get([&](String payload) {
        Serial.println(payload);
    });

    delay(5000);
    ESP.reset();
}

void loop() {}
