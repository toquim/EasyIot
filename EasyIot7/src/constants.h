#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace constantsMqtt
{
    constexpr const char *mqttCloudURL{"mqtt.bhonofre.pt"};
    constexpr const char *availablePayload{"online"};
    constexpr const char *homeAssistantAutoDiscoveryPrefix{"homeassistant"};
    constexpr const char *unavailablePayload{"offline"};
    constexpr const int defaultPort{1883};
    constexpr const char *homeassistantOnlineTopic{"hass/status"};
} // namespace constantsMqtt
namespace constantsSensor
{
    constexpr const char *noneClass{"none"};
    constexpr const char *powerMeterClass{"power_meter"};
    constexpr const char *familySensor{"sensor"};
    constexpr const char *binarySensorFamily{"binary_sensor"};
} // namespace constantsSensor
namespace tags
{
    constexpr const char *system{"[SYSTEM]"};
    constexpr const char *config{"[CONFIG]"};
    constexpr const char *mqtt{"[MQTT]"};
    constexpr const char *wifi{"[WIFI]"};
    constexpr const char *discovery{"[DISCOVERY]"};
    constexpr const char *sensors{"[SENSORS]"};
    constexpr const char *switches{"[SWITCHES]"};
    constexpr const char *alexa{"[ALEXA]"};
    constexpr const char *webserver{"[WEBSERVER]"};
    constexpr const char *emoncms{"[EMONCMS]"};
    constexpr const char *cloudIO{"[CLOUDIO]"};
} // namespace tags
namespace configFilenames
{
    auto constexpr config = "/config/config.bin";
    auto constexpr sensors = "/config/sensors.bin";
    auto constexpr switches = "/config/switches.bin";

} // namespace configFilenames
namespace constantsConfig
{
#if NO_FEATURES
    constexpr const char *firmwareMode{"NO_FEATURES"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=NO_FEATURES"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=NO_FEATURES"};
#endif
#if SINGLE_SWITCH
    constexpr const char *firmwareMode{"SINGLE_SWITCH"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=SINGLE_SWITCH"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=SINGLE_SWITCH"};
#endif
#if DUAL_LIGHT
    constexpr const char *firmwareMode{"DUAL_LIGHT"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=DUAL_LIGHT"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=DUAL_LIGHT"};
#endif
#if VMC
    constexpr const char *firmwareMode{"VMC"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=VMC"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=VMC"};
#endif
#if COVER
    constexpr const char *firmwareMode{"COVER"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=COVER"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=COVER"};
#endif
#if COVER_V3
    constexpr const char *firmwareMode{"COVER_V3"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=COVER_V3"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=COVER_V3"};
#endif
#if LOCK
    constexpr const char *firmwareMode{"LOCK"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=LOCK"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=LOCK"};
#endif
#if FOUR_LOCK
    constexpr const char *firmwareMode{"FOUR_LOCK"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=FOUR_LOCK"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=FOUR_LOCK"};
#endif
#if BHPZEM_004T
    constexpr const char *firmwareMode{"BHPZEM_004T"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=BHPZEM_004T"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=BHPZEM_004T"};
#endif
#if BHPZEM_004T_2_0
    constexpr const char *firmwareMode{"BHPZEM_004T_2_0"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=BHPZEM_004T_2_0"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=BHPZEM_004T_2_0"};
#endif
#if BHPZEM_004T_V03
    constexpr const char *firmwareMode{"BHPZEM_004T_V03"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=BHPZEM_004T_V03"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=BHPZEM_004T_V03"};
#endif

#if BHPZEM_004T_V03_2_0
    constexpr const char *firmwareMode{"BHPZEM_004T_V03_2_0"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=BHPZEM_004T_V03_2_0"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=BHPZEM_004T_V03_2_0"};
#endif
#if GATE
    constexpr const char *firmwareMode{"GATE"};
    constexpr const char *updateURL{"http://update.bhonofre.pt/firmware/latest-binary?firmwareMode=GATE"};
    constexpr const char *lastVersionURL{"http://update.bhonofre.pt/firmware/latest-version?firmwareMode=GATE"};
#endif

    constexpr const char *newID{"NEW"};
    constexpr unsigned int noGPIO{99u};
    constexpr unsigned long storeConfigDelay{5000ul};

    constexpr const char *apSecret{"bhonofre"}; //AP PASSWORD
    constexpr const char *apiUser{"admin"};     //API USER
    constexpr const char *apiPassword{"xpto"};  //API PASSWORD
} // namespace constantsConfig

namespace constanstsCloudIO
{
    constexpr const char *mqttDns{"mqtt.bhonofre.pt"};

    constexpr int mqttPort{1883};
} // namespace constanstsCloudIO

namespace constanstsSwitch
{

    constexpr const unsigned long delayDebounce{25ul};              //25 milliseconds
    constexpr const unsigned long delayCoverProtection{50ul};       //50 milliseconds
    constexpr const unsigned long coverAutoStopProtection{90000ul}; // after 90 seconds turn off all relay to enhance the lifecycle
    constexpr const char *payloadOn{"ON"};
    constexpr const char *payloadOff{"OFF"};
    constexpr const char *payloadClose{"CLOSE"};
    constexpr const char *payloadStateClose{"closed"};
    constexpr const char *payloadOpen{"OPEN"};
    constexpr const char *payloadStateOpen{"open"};
    constexpr const char *payloadStop{"STOP"};
    constexpr const char *payloadStateStop{""};
    constexpr const char *payloadLock{"LOCK"};
    constexpr const char *payloasStateLock{"LOCK"};
    constexpr const char *payloadUnlock{"UNLOCK"};
    constexpr const char *payloadStateUnlock{"UNLOCK"};
    constexpr const char *payloadReleased{"RELEASED"};

    constexpr const char *familyLight{"light"};
    constexpr const char *familySwitch{"switch"};
    constexpr const char *familyCover{"cover"};
    constexpr const char *familyLock{"lock"};

    constexpr const int offIdx{0};
    constexpr const int onIdx{1};
    constexpr const int firtStopIdx{2};
    constexpr const int openIdx{3};
    constexpr const int secondStopIdx{4};
    constexpr const int closeIdx{5};
    constexpr const int lockIdx{6};
    constexpr const int unlockIdx{7};
    constexpr const int coverStartIdx{2};
    constexpr const int converEndIdx{5};
    constexpr const int switchStartIdx{0};
    constexpr const int switchEndIdx{1};
    constexpr const int lockStartIdx{6};
    constexpr const int lockEndIdx{7};
} // namespace constanstsSwitch
#endif
