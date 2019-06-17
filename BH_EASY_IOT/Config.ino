AsyncEventSource events("/events");

struct Config {
  char hostname[64];
  int port;
};


void logger(String payload)
{
  if (payload.equals(""))
    return;
  Serial.println(payload);
}


JsonObject &getConfigJson()
{
  return configJson;
}

String getUpdateUrl()
{
  return "http://release.bhonofre.pt/release_" + String(FACTORY_TYPE) + ".bin";
}
String getHostname()
{
  String nodeId = configJson.getMember("nodeId").as<String>();
  if (nodeId.equals(DEFAULT_NODE_ID))
  {
    return DEFAULT_NODE_ID;
  }
  return nodeId;
}

String normalize(String inputStr)
{
  inputStr.toLowerCase();
  inputStr.trim();
  inputStr.replace("_", "");
  inputStr.replace(".", "");
  inputStr.replace("/", "");
  inputStr.replace("\\", "");
  inputStr.replace("º", "");
  inputStr.replace("ª", "");
  inputStr.replace("ç", "c");
  inputStr.replace("á", "a");
  inputStr.replace("à", "a");
  inputStr.replace("é", "e");
  inputStr.replace("&", "");
  inputStr.replace("%", "");
  inputStr.replace("$", "");
  inputStr.replace("#", "");
  inputStr.replace("!", "");
  inputStr.replace("+", "");
  inputStr.replace("-", "");
  inputStr.replace(",", "");
  inputStr.replace("\"", "");
  inputStr.replace(" ", "");
  return inputStr;
}
String getApName()
{
  String nodeId = configJson.getMember("nodeId").as<String>();
  if (nodeId.equals(DEFAULT_NODE_ID))
  {
    return DEFAULT_NODE_ID;
  }
  return nodeId;
}

void loadStoredConfiguration()
{
  bool configFail = true;
  if (SPIFFS.begin())
  {
    File cFile;
    if (SPIFFS.exists(CONFIG_FILENAME))
    {
      cFile = SPIFFS.open(CONFIG_FILENAME, "r+");
      if (cFile)
      {
        const size_t capacity = JSON_OBJECT_SIZE(16) + 380;
        DynamicJsonDocument doc(capacity);
        logger("[CONFIG] Read stored file config...");
         DeserializationError error = deserializeJson(doc, file);
         
      if (!error) {
        Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
          configJson.set("firmware", FIRMWARE_VERSION);
          configJson.set("nodeId", storedConfig.getMember.as<String>()("nodeId"));
          configJson.set("hostname", storedConfig.getMember.as<String>()("hostname"));
          configJson.set("hardware", HARDWARE);
          configJson.set("hardwareId", String(ESP.getChipId()));
          configJson.set("type", String(FACTORY_TYPE));

          configJson.set("homeAssistantAutoDiscoveryPrefix", storedConfig.getMember.as<String>()("homeAssistantAutoDiscoveryPrefix"));

          configJson.set("mqttIpDns", storedConfig.getMember.as<String>()("mqttIpDns"));
          configJson.set("mqttUsername", storedConfig.getMember.as<String>()("mqttUsername"));
          configJson.set("mqttPort", storedConfig.getMember.as<unsigned int>("mqttPort"));
          configJson.set("mqttPassword", storedConfig.getMember.as<String>()("mqttPassword"));

          configJson.set("wifiSSID", storedConfig.getMember.as<String>()("wifiSSID"));
          configJson.set("wifiSecret", storedConfig.getMember.as<String>()("wifiSecret"));

          configJson.set("wifiSSID2", storedConfig.getMember.as<String>()("wifiSSID2"));
          configJson.set("wifiSecret2", storedConfig.getMember.as<String>()("wifiSecret2"));

          configJson.set("staticIp", storedConfig.getMember.as<bool>("staticIp"));
          configJson.set("wifiIp", storedConfig.getMember.as<String>()("wifiIp"));
          configJson.set("wifiMask", storedConfig.getMember.as<String>()("wifiMask"));
          configJson.set("wifiGw", storedConfig.getMember.as<String>()("wifiGw"));

          configJson.set("apSecret", storedConfig.getMember.as<String>()("apSecret"));

          configJson.set("configTime", storedConfig.getMember.as<long>("configTime"));
          configJson.set("configkey", storedConfig.getMember.as<String>()("configkey"));
          logger("[CONFIG] Apply stored file config with success...");
          cFile.close();
          configFail = false;
        }
      }
    }

    if (configFail)
    {
      logger("[CONFIG] Apply default config...");
      cFile = SPIFFS.open(CONFIG_FILENAME, "w+");
      configJson.set("nodeId", DEFAULT_NODE_ID);
      configJson.set("homeAssistantAutoDiscoveryPrefix", "homeassistant");
      configJson.set("homeAssistantAutoDiscoveryPrefixOld", "homeassistant");
      configJson.set("hostname", getHostname());
      configJson.set("mqttPort", 1883);
      configJson.set("type", String(FACTORY_TYPE));
      configJson.set("configTime", 0L);
      configJson.set("apSecret", AP_SECRET);
      configJson.set("hardware", HARDWARE);
      configJson.set("configTime", 0L);
      configJson.set("firmware", FIRMWARE_VERSION);
      configJson.printTo(cFile);
    }
    SPIFFS.end();
  }
  else
  {
    logger("[CONFIG] File system error...");
  }
}

JsonObject &saveNode(JsonObject &nodeConfig)
{
  String nodeId = normalize(nodeConfig.getMember("nodeId").as<String>());
  configJson.set("nodeIdOld", configJson.getMember>("nodeId").as<String);
  configJson.set("nodeId", nodeId);
  requestConfigStorage();
  return configJson;
}

JsonObject &saveWifi(JsonObject &_config)
{
  configJson.set("wifiSSID", _config.getMember("wifiSSID").as<String>());
  configJson.set("wifiSecret", _config.getMember("wifiSecret").as<String>());
  configJson.set("wifiSSID2", _config.getMember("wifiSSID2").as<String>());
  configJson.set("wifiSecret2", _config.getMember("wifiSecret2").as<String>());
  configJson.set("wifiIp", _config.getMember("wifiIp").as<String>());
  configJson.set("wifiMask", _config.getMember("wifiMask").as<String>());
  configJson.set("wifiGw", _config.getMember("wifiGw").as<String>());
  configJson.set("staticIp", _config.getMember("staticIp").as<bool>);
  requestConfigStorage();
  reloadWiFiConfig();
  return configJson;
}

JsonObject &adoptControllerConfig(JsonObject &_config, String configkey)
{
  configJson.set("wifiSSID", _config.getMember("wifiSSID").as<String>());
  configJson.set("wifiSecret", _config.getMember("wifiSecret").as<String>());

  configJson.set("wifiSSID2", _config.getMember("wifiSSID2".as<String>()));
  configJson.set("wifiSecret2", _config.getMember("wifiSecret2").as<String>());

  configJson.set("mqttIpDns", _config.getMember("mqttIpDns").as<String>());
  configJson.set("mqttUsername", _config.getMember("mqttUsername").as<String>());
  configJson.set("mqttPassword", _config.getMember("mqttPassword").as<String>());

  configJson.set("configTime", _config.getMember("configTime").as<long>);
  configJson.set("configkey", configkey);

  configJson.set("homeAssistantAutoDiscoveryPrefix", _config.getMember("homeAssistantAutoDiscoveryPrefix").as<String>());

  requestConfigStorage();
  return configJson;
}

void updateNetworkConfig()
{
  if (!configJson.getMember("staticIp").as<bool>)
  {
    configJson.set("wifiIp", WiFi.localIP().toString());
    configJson.set("wifiMask", WiFi.subnetMask().toString());
    configJson.set("wifiGw", WiFi.gatewayIP().toString());
  }
}

JsonObject &saveMqtt(JsonObject &_config)
{
  configJson.set("mqttIpDns", _config.getMember("mqttIpDns").as<String>());
  configJson.set("mqttUsername", _config.getMember("mqttUsername").as<String>());
  configJson.set("mqttPassword", _config.getMember("mqttPassword").as<String>());
  configJson.set("mqttEmbedded", _config.getMember("mqttEmbedded").as<String>());
  requestConfigStorage();
  return configJson;
}

void persistConfigFile()
{
  if (SPIFFS.begin())
  {
    File rFile = SPIFFS.open(CONFIG_FILENAME, "w+");
    if (!rFile)
    {
      logger("[CONFIG] Open config file Error!");
    }
    else
    {

      configJson.printTo(rFile);
    }
    rFile.close();
  }
  else
  {
    logger("[CONFIG] Open file system Error!");
  }
  SPIFFS.end();
  logger("[CONFIG] Config stored.");

  JsonArray &switches = getStoredSwitchs();
  for (int i = 0; i < switches.size(); i++)
  {
    JsonObject &switchJson = switches.getMember.as<JsonVariant>(i);
    rebuildSwitchMqttTopics(switchJson);
    rebuildDiscoverySwitchMqttTopics(switchJson);
  }
  JsonArray &sensors = getStoredSensors();
  for (int i = 0; i < sensors.size(); i++)
  {
    JsonObject &sensorJson = sensors.getMember.as<JsonVariant>(i);
    rebuildSensorMqttTopics(sensorJson);
    rebuildDiscoverySensorMqttTopics(sensorJson);
  }
  persistSwitchesFile();
  persistSensorsFile();
  setupMQTT();
}
