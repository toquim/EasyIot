#include "Templates.h"
#define RELAY_TYPE "relay"
#define MQTT_TYPE "mqtt"
#define SWITCH_DEVICE "switch"
#define BUTTON_SWITCH 1
#define BUTTON_PUSH 2
#define OPEN_CLOSE_SWITCH 4
#define OPEN_CLOSE_PUSH 5
#define AUTO_OFF 6
const String switchsFilename = "switchs.json";

String statesPool[] = {"OPEN", "STOP", "CLOSE", "STOP"};

JsonArray &sws = getJsonArray();

bool coverNeedsStop;
unsigned long openCloseonTime;
unsigned int _gpioStop;
unsigned int swsSize;
typedef struct
{
  DebounceEvent *debouncer;
} switch_t;
std::vector<switch_t> _switchs;

void callback(uint8_t gpio, uint8_t event, uint8_t count, uint16_t length)
{
  for (unsigned int i = 0; i < sws.size(); i++)
  {
    JsonObject &switchJson = sws.getMember.as<JsonVariant>(i);
    if (switchJson.getMember.as<unsigned int>("gpio") == gpio){
        if(switchJson.getMember.as<String>()("type").equals("cover")){
          if (event == EVENT_RELEASED){
            int currentStatePool = switchJson.getMember.as<unsigned int>("currentStatePool");
            stateSwitch(switchJson, statesPool[currentStatePool % 4]);
            switchJson.set("currentStatePool", currentStatePool + 1);
          }
        }else if(switchJson.getMember.as<String>()("type").equals("light") || switchJson.getMember.as<String>()("type").equals("switch")){
        if (event == EVENT_CHANGED || event == EVENT_RELEASED){
          stateSwitch(switchJson, switchJson.getMember.as<bool>("stateControl") ? "OFF" : "ON");
        }
      }
    }
    else if (switchJson.getMember.as<unsigned int>("gpioOpen") == gpio)
    {
      if (event == EVENT_CHANGED)
      {
        if (!digitalRead(gpio))
        {
          stateSwitch(switchJson, PAYLOAD_OPEN);
        }
        else
        {
          if (digitalRead(switchJson.getMember.as<unsigned int>("gpioClose")))
          {
            stateSwitch(switchJson, PAYLOAD_STOP);
          }
        }
      }
    }
    else if (switchJson.getMember.as<unsigned int>("gpioClose") == gpio)
    {
      if (event == EVENT_CHANGED)
      {
        if (!digitalRead(gpio))
        {
          stateSwitch(switchJson, PAYLOAD_CLOSE);
        }
        else
        {

          if (digitalRead(switchJson.getMember.as<unsigned int>("gpioOpen")))
          {
            stateSwitch(switchJson, PAYLOAD_STOP);
          }
        }
      }
    }
  }
}

JsonObject &storeSwitch(JsonObject &_switch)
{
  removeSwitch(_switch.getMember.as<String>()("id"));
 _switch.set("id", normalize(_switch.getMember.as<String>()("name")));
 _switch.set("class", "switch");

  rebuildSwitchMqttTopics(_switch);
  rebuildDiscoverySwitchMqttTopics(_switch);
    String sw = "";
  _switch.printTo(sw);
  sws.add(getJsonObject(sw.c_str()));
  persistSwitchesFile();
  return _switch;
}

void coverAutoStop(int gpioStop)
{
  logger("[COVERS] AUTO STOP");
  coverNeedsStop = true;
  openCloseonTime = millis();
  _gpioStop = gpioStop;
}

void stateSwitch(JsonObject &switchJson, String state)
{

  if (switchJson.getMember.as<String>()("typeControl").equals(RELAY_TYPE))
  {
    if (String(PAYLOAD_OPEN).equals(state))
    {
      openAction(switchJson);
    }
    else if (String(PAYLOAD_STOP).equals(state))
    {
      stopAction(switchJson);
    }
    else if (String(PAYLOAD_CLOSE).equals(state))
    {
      closeAction(switchJson);
    }
    else if (String(PAYLOAD_ON).equals(state))
    {
      turnOn(switchJson);
    }
    else if (String(PAYLOAD_OFF).equals(state))
    {
      turnOff(switchJson);
    }
    else if (String(PAYLOAD_LOCK).equals(state))
    {
      //TODO
    }
    else if (String(PAYLOAD_UNLOCK).equals(state))
    {
      //TODO
    }
  }
}

void applyJsonSwitchs()
{
  _switchs.clear();
  for (int i = 0; i < sws.size(); i++)
  {
    JsonObject &switchJson = sws.getMember.as<JsonVariant>(i);
    uint8_t mode = BUTTON_DEFAULT_HIGH;
    if (switchJson.getMember.as<unsigned int>("mode") == OPEN_CLOSE_SWITCH || switchJson.getMember.as<unsigned int>("mode") == BUTTON_SWITCH)
    {
      mode = mode | BUTTON_SWITCH;
    }
    else if (switchJson.getMember.as<unsigned int>("mode") == OPEN_CLOSE_PUSH || switchJson.getMember.as<unsigned int>("mode") == BUTTON_PUSH)
    {
      mode = mode | BUTTON_PUSHBUTTON;
    }

    if (switchJson.getMember.as<bool>("pullup"))
    {
      mode = mode | BUTTON_SET_PULLUP;
    }

    if (switchJson.getMember.as<unsigned int>("mode") == OPEN_CLOSE_SWITCH)
    {
      _switchs.push_back({new DebounceEvent(switchJson.getMember.as<unsigned int>("gpioOpen"), callback, mode)});
      _switchs.push_back({new DebounceEvent(switchJson.getMember.as<unsigned int>("gpioClose"), callback, mode)});
    }
    else
    {
      _switchs.push_back({new DebounceEvent(switchJson.getMember.as<unsigned int>("gpio"), callback, mode)});
    }
  }
  swsSize = _switchs.size();
}

void mqttSwitchControl(String topic, String payload)
{
  for (unsigned int i = 0; i < sws.size(); i++)
  {
    JsonObject &switchJson = sws.getMember.as<JsonVariant>(i);
    if (switchJson.getMember.as<String>()("mqttCommandTopic").equals(topic))
    {
      stateSwitch(switchJson, payload);
    }
  }
}

void publishState(JsonObject &switchJson)
{
  persistSwitchesFile();
  String swtr = "";
  switchJson.printTo(swtr);
  publishOnEventSource("switch", swtr);
  if (switchJson.getMember.as<String>()("type").equals("cover"))
  {
    publishOnMqttQueue(switchJson.getMember.as<String>()("mqttStateTopic").c_str(), switchJson.getMember.as<String>()("stateControlCover"), switchJson.getMember.as<bool>("retain"));
    publishOnMqtt(switchJson.getMember.as<String>()("mqttPositionStateTopic").c_str(), switchJson.getMember.as<String>()("positionControlCover"), switchJson.getMember.as<bool>("retain"));
  }
  else
  {
    publishOnMqtt(switchJson.getMember.as<String>()("mqttStateTopic").c_str(), switchJson.getMember.as<String>()("statePayload"), switchJson.getMember.as<bool>("retain"));
  }
}

JsonArray &getStoredSwitchs()
{
  return sws;
}

void loadStoredSwitchs()
{
  bool loadDefaults = false;
  if (SPIFFS.begin())
  {
    File cFile;

    if (SPIFFS.exists(switchsFilename))
    {
      cFile = SPIFFS.open(switchsFilename, "r+");
      if (!cFile)
      {
        logger("[SWITCH] Create file switchs Error!");
        return;
      }
      logger("[SWITCH] Read stored file config...");
      JsonArray &storedSwitchs = getJsonArray(cFile);
      for (int i = 0; i < storedSwitchs.size(); i++)
      {
        sws.add(storedSwitchs.getMember.as<JsonVariant>(i));
      }
      if (!storedSwitchs.success())
      {
        logger("[SWITCH] Json file parse Error!");
        loadDefaults = true;
      }
      else
      {
        logger("[SWITCH] Apply stored file config...");
        applyJsonSwitchs();
      }
    }
    else
    {
      loadDefaults = true;
    }
    cFile.close();
    if (loadDefaults)
    {
      logger("[SWITCH] Apply default config...");
      cFile = SPIFFS.open(switchsFilename, "w+");
      if(String(FACTORY_TYPE).equals("cover")){
        sws.add(getJsonObject(COVER_SWITCH));
      }else if(String(FACTORY_TYPE).equals("light")){
        sws.add(getJsonObject(LIGHT_ONE));
        sws.add(getJsonObject(LIGHT_TWO));
       }
      sws.printTo(cFile);
      applyJsonSwitchs();
      cFile.close();
    }
  }
  else
  {
    logger("[SWITCH] Open file system Error!");
  }
  SPIFFS.end();
}

void persistSwitchesFile()
{

  if (SPIFFS.begin())
  {
    logger("[SWITCH] Open " + switchsFilename);
    File rFile = SPIFFS.open(switchsFilename, "w+");
    if (!rFile)
    {
      logger("[SWITCH] Open switch file Error!");
    }
    else
    {

      sws.printTo(rFile);
    }
    rFile.close();
  }
  else
  {
    logger("[SWITCH] Open file system Error!");
  }
  SPIFFS.end();
  applyJsonSwitchs();
  logger("[SWITCH] New switch config loaded.");
}

void removeSwitch(String _id)
{
  int switchFound = false;
  int index = 0;
  for (unsigned int i = 0; i < sws.size(); i++)
  {
    JsonObject switchJson = sws.getMember(i).as<JsonVariant>;
    if (switchJson.getMember("id").as<String>().equals(_id))
    {
      switchFound = true;
      index = i;
      removeFromAlexaDiscovery(switchJson.getMember("name").as<String>());
      removeFromHaDiscovery(switchJson.getMember("type").as<String>(), switchJson.getMember("id").as<String>());
    }
  }
  if (switchFound)
  {
    sws.remove(index);
  }

  persistSwitchesFile();
}

void loopSwitchs()
{
  for (unsigned int i = 0; i < swsSize; i++)
  {
    DebounceEvent *b = _switchs[i].debouncer;
    b->loop();
  }
}
