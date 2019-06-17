#define HARDWARE "onofre"
#define FACTORY_TYPE "light"  //suported types cover light
#define FIRMWARE_VERSION 6.12
#define FIRMWARE_VERSION_X "6x12"
const String DEFAULT_NODE_ID = String(HARDWARE) +"-"+String(FACTORY_TYPE)+"-"+String(ESP.getChipId())+"-"+String(FIRMWARE_VERSION_X);

#define CONFIG_FILENAME  "/config_bh"+String(HARDWARE)+".json"
#define CONFIG_BUFFER_SIZE 1024

//AP PASSWORD  
#define AP_SECRET "EasyIot@"

#define PAYLOAD_ON "ON"
#define PAYLOAD_OFF "OFF"
#define PAYLOAD_CLOSE "CLOSE"
#define PAYLOAD_OPEN "OPEN"
#define PAYLOAD_STOP "STOP"
#define PAYLOAD_LOCK "LOCK"
#define PAYLOAD_UNLOCK "UNLOCK"



//CONTROL FLAGS
bool REBOOT = false;
bool LOAD_DEFAULTS = false;
bool AUTO_UPDATE = false;
bool STORE_CONFIG = false;
bool WIFI_SCAN = false;

void requestConfigStorage(){
  STORE_CONFIG = true;
}
void requestReboot(){
  REBOOT = true;
}
void requestAutoUpdate(){
  AUTO_UPDATE = true;
}
void requestLoadDefaults(){
  AUTO_UPDATE = true;
}
void requestWifiScan(){
  WIFI_SCAN = true;
}

DynamicJsonDocument jsonBuffer(CONFIG_BUFFER_SIZE);

JsonArray getJsonArray() {
    return jsonBuffer.to<JsonArray>();
}

JsonArray getJsonArray(File file) {
  auto error = deserializeJson(jsonBuffer, file);
if (error) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
}
    return jsonBuffer.as<JsonArray>();
}

JsonObject getJsonObject() {
    return jsonBuffer.to<JsonObject>();
}



JsonObject getJsonObject(const char *data) {
     auto error = deserializeJson(jsonBuffer, data);
if (error) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());

}
    return jsonBuffer.as<JsonObject>();
}
