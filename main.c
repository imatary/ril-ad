#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define RIL_SHLIB

#include <telephony/ril.h>

#include <stdbool.h>
#include <zconf.h>

#include "adapter.h"

#define CFG_PATH "/data/local/tmp/adapter.cfg"

#define CFG_MAX 512

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "RILH"
#else
#define LOG_TAG "RILH"
#endif

/*

static MESSAGE_ITEM message_items[] =
        {{RIL_REQUEST_GET_SIM_STATUS,                           "GET_SIM_STATUS"},
         {RIL_REQUEST_ENTER_SIM_PIN,                            "ENTER_SIM_PIN"},
         {RIL_REQUEST_ENTER_SIM_PUK,                            "ENTER_SIM_PUK"},
         {RIL_REQUEST_ENTER_SIM_PIN2,                           "ENTER_SIM_PIN2"},
         {RIL_REQUEST_ENTER_SIM_PUK2,                           "ENTER_SIM_PUK2"},
         {RIL_REQUEST_CHANGE_SIM_PIN,                           "CHANGE_SIM_PIN"},
         {RIL_REQUEST_CHANGE_SIM_PIN2,                          "CHANGE_SIM_PIN2"},
         {RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION,          "ENTER_NETWORK_DEPERSONALIZATION"},
         {RIL_REQUEST_GET_CURRENT_CALLS,                        "GET_CURRENT_CALLS"},
         {RIL_REQUEST_DIAL,                                     "DIAL"},
         {RIL_REQUEST_GET_IMSI,                                 "GET_IMSI"},
         {RIL_REQUEST_HANGUP,                                   "HANGUP"},
         {RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND,             "HANGUP_WAITING_OR_BACKGROUND"},
         {RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND,      "HANGUP_FOREGROUND_RESUME_BACKGROUND"},
         {RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE,     "SWITCH_WAITING_OR_HOLDING_AND_ACTIVE"},
         {RIL_REQUEST_CONFERENCE,                               "CONFERENCE"},
         {RIL_REQUEST_UDUB,                                     "UDUB"},
         {RIL_REQUEST_LAST_CALL_FAIL_CAUSE,                     "LAST_CALL_FAIL_CAUSE"},
         {RIL_REQUEST_SIGNAL_STRENGTH,                          "SIGNAL_STRENGTH"},
         {RIL_REQUEST_VOICE_REGISTRATION_STATE,                 "VOICE_REGISTRATION_STATE"},
         {RIL_REQUEST_DATA_REGISTRATION_STATE,                  "DATA_REGISTRATION_STATE"},
         {RIL_REQUEST_OPERATOR,                                 "OPERATOR"},
         {RIL_REQUEST_RADIO_POWER,                              "RADIO_POWER"},
         {RIL_REQUEST_DTMF,                                     "DTMF"},
         {RIL_REQUEST_SEND_SMS,                                 "SEND_SMS"},
         {RIL_REQUEST_SEND_SMS_EXPECT_MORE,                     "SEND_SMS_EXPECT_MORE"},
         {RIL_REQUEST_SETUP_DATA_CALL,                          "SETUP_DATA_CALL"},
         {RIL_REQUEST_SIM_IO,                                   "SIM_IO"},
         {RIL_REQUEST_SEND_USSD,                                "SEND_USSD"},
         {RIL_REQUEST_CANCEL_USSD,                              "CANCEL_USSD"},
         {RIL_REQUEST_GET_CLIR,                                 "GET_CLIR"},
         {RIL_REQUEST_SET_CLIR,                                 "SET_CLIR"},
         {RIL_REQUEST_QUERY_CALL_FORWARD_STATUS,                "QUERY_CALL_FORWARD_STATUS"},
         {RIL_REQUEST_SET_CALL_FORWARD,                         "SET_CALL_FORWARD"},
         {RIL_REQUEST_QUERY_CALL_WAITING,                       "QUERY_CALL_WAITING"},
         {RIL_REQUEST_SET_CALL_WAITING,                         "SET_CALL_WAITING"},
         {RIL_REQUEST_SMS_ACKNOWLEDGE,                          "SMS_ACKNOWLEDGE"},
         {RIL_REQUEST_GET_IMEI,                                 "GET_IMEI"},
         {RIL_REQUEST_GET_IMEISV,                               "GET_IMEISV"},
         {RIL_REQUEST_ANSWER,                                   "ANSWER"},
         {RIL_REQUEST_DEACTIVATE_DATA_CALL,                     "DEACTIVATE_DATA_CALL"},
         {RIL_REQUEST_QUERY_FACILITY_LOCK,                      "QUERY_FACILITY_LOCK"},
         {RIL_REQUEST_SET_FACILITY_LOCK,                        "SET_FACILITY_LOCK"},
         {RIL_REQUEST_CHANGE_BARRING_PASSWORD,                  "CHANGE_BARRING_PASSWORD"},
         {RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE,             "QUERY_NETWORK_SELECTION_MODE"},
         {RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC,          "SET_NETWORK_SELECTION_AUTOMATIC"},
         {RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL,             "SET_NETWORK_SELECTION_MANUAL"},
         {RIL_REQUEST_QUERY_AVAILABLE_NETWORKS,                 "QUERY_AVAILABLE_NETWORKS "},
         {RIL_REQUEST_DTMF_START,                               "DTMF_START"},
         {RIL_REQUEST_DTMF_STOP,                                "DTMF_STOP"},
         {RIL_REQUEST_BASEBAND_VERSION,                         "BASEBAND_VERSION"},
         {RIL_REQUEST_SEPARATE_CONNECTION,                      "SEPARATE_CONNECTION"},
         {RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE,               "SET_PREFERRED_NETWORK_TYPE"},
         {RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE,               "GET_PREFERRED_NETWORK_TYPE"},
         {RIL_REQUEST_GET_NEIGHBORING_CELL_IDS,                 "GET_NEIGHBORING_CELL_IDS"},
         {RIL_REQUEST_SET_MUTE,                                 "SET_MUTE"},
         {RIL_REQUEST_GET_MUTE,                                 "GET_MUTE"},
         {RIL_REQUEST_QUERY_CLIP,                               "QUERY_CLIP"},
         {RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE,                "LAST_DATA_CALL_FAIL_CAUSE"},
         {RIL_REQUEST_DATA_CALL_LIST,                           "DATA_CALL_LIST"},
         {RIL_REQUEST_RESET_RADIO,                              "RESET_RADIO"},
         {RIL_REQUEST_OEM_HOOK_RAW,                             "OEM_HOOK_RAW"},
         {RIL_REQUEST_OEM_HOOK_STRINGS,                         "OEM_HOOK_STRINGS"},
         {RIL_REQUEST_SET_BAND_MODE,                            "SET_BAND_MODE"},
         {RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE,                "QUERY_AVAILABLE_BAND_MODE"},
         {RIL_REQUEST_STK_GET_PROFILE,                          "STK_GET_PROFILE"},
         {RIL_REQUEST_STK_SET_PROFILE,                          "STK_SET_PROFILE"},
         {RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND,                "STK_SEND_ENVELOPE_COMMAND"},
         {RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE,               "STK_SEND_TERMINAL_RESPONSE"},
         {RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM, "STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM"},
         {RIL_REQUEST_SCREEN_STATE,                             "SCREEN_STATE"},
         {RIL_REQUEST_EXPLICIT_CALL_TRANSFER,                   "EXPLICIT_CALL_TRANSFER"},
         {RIL_REQUEST_SET_LOCATION_UPDATES,                     "SET_LOCATION_UPDATES"},
         {RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE,             "CDMA_SET_SUBSCRIPTION_SOURCE"},
         {RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE,              "CDMA_SET_ROAMING_PREFERENCE"},
         {RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE,            "CDMA_QUERY_ROAMING_PREFERENCE"},
         {RIL_REQUEST_SET_TTY_MODE,                             "SET_TTY_MODE"},
         {RIL_REQUEST_QUERY_TTY_MODE,                           "QUERY_TTY_MODE"},
         {RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE,    "CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE"},
         {RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE,  "CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE"},
         {RIL_REQUEST_CDMA_FLASH,                               "CDMA_FLASH"},
         {RIL_REQUEST_CDMA_BURST_DTMF,                          "CDMA_BURST_DTMF"},
         {RIL_REQUEST_CDMA_SEND_SMS,                            "CDMA_SEND_SMS"},
         {RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE,                     "CDMA_SMS_ACKNOWLEDGE"},
         {RIL_REQUEST_GSM_GET_BROADCAST_SMS_CONFIG,             "GSM_GET_BROADCAST_SMS_CONFIG"},
         {RIL_REQUEST_GSM_SET_BROADCAST_SMS_CONFIG,             "GSM_SET_BROADCAST_SMS_CONFIG"},
         {RIL_REQUEST_CDMA_GET_BROADCAST_SMS_CONFIG,            "CDMA_GET_BROADCAST_SMS_CONFIG"},
         {RIL_REQUEST_CDMA_SET_BROADCAST_SMS_CONFIG,            "CDMA_SET_BROADCAST_SMS_CONFIG"},
         {RIL_REQUEST_CDMA_SMS_BROADCAST_ACTIVATION,            "CDMA_SMS_BROADCAST_ACTIVATION"},
         {RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY,             "CDMA_VALIDATE_AND_WRITE_AKEY"},
         {RIL_REQUEST_CDMA_SUBSCRIPTION,                        "CDMA_SUBSCRIPTION"},
         {RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM,                   "CDMA_WRITE_SMS_TO_RUIM"},
         {RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM,                  "CDMA_DELETE_SMS_ON_RUIM"},
         {RIL_REQUEST_DEVICE_IDENTITY,                          "DEVICE_IDENTITY"},
         {RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE,             "EXIT_EMERGENCY_CALLBACK_MODE"},
         {RIL_REQUEST_GET_SMSC_ADDRESS,                         "GET_SMSC_ADDRESS"},
         {RIL_REQUEST_SET_SMSC_ADDRESS,                         "SET_SMSC_ADDRESS"},
         {RIL_REQUEST_REPORT_SMS_MEMORY_STATUS,                 "REPORT_SMS_MEMORY_STATUS"},
         {RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING,            "REPORT_STK_SERVICE_IS_RUNNING"},
         {RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE,             "CDMA_GET_SUBSCRIPTION_SOURCE"},
         {RIL_REQUEST_ISIM_AUTHENTICATION,                      "ISIM_AUTHENTICATION"},
         {RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU,    "RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU"},
         {RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS,            "RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS"},
         {RIL_REQUEST_VOICE_RADIO_TECH,                         "VOICE_RADIO_TECH"},
         {RIL_REQUEST_GET_CELL_INFO_LIST,                       "GET_CELL_INFO_LIST"},
         {RIL_REQUEST_SET_UNSOL_CELL_INFO_LIST_RATE,            "SET_UNSOL_CELL_INFO_LIST_RATE"},
         {RIL_REQUEST_SET_INITIAL_ATTACH_APN,                   "RIL_REQUEST_SET_INITIAL_ATTACH_APN"},
         {RIL_REQUEST_IMS_REGISTRATION_STATE,                   "IMS_REGISTRATION_STATE"},
         {RIL_REQUEST_IMS_SEND_SMS,                             "IMS_SEND_SMS"},
         {RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED,               "UNSOL_RESPONSE_RADIO_STATE_CHANGED"},
         {RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED,                "UNSOL_RESPONSE_CALL_STATE_CHANGED"},
         {RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED,       "UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED"},
         {RIL_UNSOL_RESPONSE_NEW_SMS,                           "UNSOL_RESPONSE_NEW_SMS"},
         {RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT,             "UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT"},
         {RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM,                    "UNSOL_RESPONSE_NEW_SMS_ON_SIM"},
         {RIL_UNSOL_ON_USSD,                                    "UNSOL_ON_USSD"},
         {RIL_UNSOL_ON_USSD_REQUEST,                            "UNSOL_ON_USSD_REQUEST(obsolete)"},
         {RIL_UNSOL_NITZ_TIME_RECEIVED,                         "UNSOL_NITZ_TIME_RECEIVED"},
         {RIL_UNSOL_SIGNAL_STRENGTH,                            "UNSOL_SIGNAL_STRENGTH"},
         {RIL_UNSOL_STK_SESSION_END,                            "UNSOL_STK_SESSION_END"},
         {RIL_UNSOL_STK_PROACTIVE_COMMAND,                      "UNSOL_STK_PROACTIVE_COMMAND"},
         {RIL_UNSOL_STK_EVENT_NOTIFY,                           "UNSOL_STK_EVENT_NOTIFY"},
         {RIL_UNSOL_STK_CALL_SETUP,                             "UNSOL_STK_CALL_SETUP"},
         {RIL_UNSOL_SIM_SMS_STORAGE_FULL,                       "UNSOL_SIM_SMS_STORAGE_FUL"},
         {RIL_UNSOL_SIM_REFRESH,                                "UNSOL_SIM_REFRESH"},
         {RIL_UNSOL_DATA_CALL_LIST_CHANGED,                     "UNSOL_DATA_CALL_LIST_CHANGED"},
         {RIL_UNSOL_CALL_RING,                                  "UNSOL_CALL_RING"},
         {RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED,                "UNSOL_RESPONSE_SIM_STATUS_CHANGED"},
         {RIL_UNSOL_RESPONSE_CDMA_NEW_SMS,                      "UNSOL_NEW_CDMA_SMS"},
         {RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS,                 "UNSOL_NEW_BROADCAST_SMS"},
         {RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL,                 "UNSOL_CDMA_RUIM_SMS_STORAGE_FULL"},
         {RIL_UNSOL_RESTRICTED_STATE_CHANGED,                   "UNSOL_RESTRICTED_STATE_CHANGED"},
         {RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE,              "UNSOL_ENTER_EMERGENCY_CALLBACK_MODE"},
         {RIL_UNSOL_CDMA_CALL_WAITING,                          "UNSOL_CDMA_CALL_WAITING"},
         {RIL_UNSOL_CDMA_OTA_PROVISION_STATUS,                  "UNSOL_CDMA_OTA_PROVISION_STATUS"},
         {RIL_UNSOL_CDMA_INFO_REC,                              "UNSOL_CDMA_INFO_REC"},
         {RIL_UNSOL_OEM_HOOK_RAW,                               "UNSOL_OEM_HOOK_RAW"},
         {RIL_UNSOL_RINGBACK_TONE,                              "UNSOL_RINGBACK_TONE"},
         {RIL_UNSOL_RESEND_INCALL_MUTE,                         "UNSOL_RESEND_INCALL_MUTE"},
         {RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED,           "UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED"},
         {RIL_UNSOL_CDMA_PRL_CHANGED,                           "UNSOL_CDMA_PRL_CHANGED"},
         {RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE,               "UNSOL_EXIT_EMERGENCY_CALLBACK_MODE"},
         {RIL_UNSOL_RIL_CONNECTED,                              "UNSOL_RIL_CONNECTED"},
         {RIL_UNSOL_VOICE_RADIO_TECH_CHANGED,                   "UNSOL_VOICE_RADIO_TECH_CHANGED"},
         {RIL_UNSOL_CELL_INFO_LIST,                             "UNSOL_CELL_INFO_LIST"},
         {RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED,         "RESPONSE_IMS_NETWORK_STATE_CHANGED"},
         {0,                                                    "\0"}
        };

*/

extern const char *requestToString(int request);

extern const char *failCauseToString(RIL_Errno);

extern const char *callStateToString(RIL_CallState);

extern const char *radioStateToString(RIL_RadioState);

static struct RIL_Env original_environment;

static RIL_RadioFunctions original_functions;

static KEY_VALUE_PAIR properties_arraylist[CFG_MAX] = {0};
static bool properties_loaded = false;

void attach_environment(struct RIL_Env *environment);

RIL_RadioFunctions *attach_functions(const RIL_RadioFunctions *functions);

static void initialize_properties();

static void load_properties(const char *path);

static bool is_enable(const char *key);

static bool is_item_enable(const char *key);

static void print_request_buffer(void *buffer, int buffer_length);

static void OnRequestComplete(RIL_Token t, RIL_Errno e, void *response, size_t responselen);

static void OnUnsolicitedResponse(int unsolResponse, const void *data, size_t datalen);

static void RequestTimedCallback(RIL_TimedCallback callback, void *param, const struct timeval *relativeTime);


// OnRequestComplete
static void OnRequestComplete(RIL_Token t, RIL_Errno e, void *response, size_t responselen) {

    bool root = is_enable("OnRequestComplete");

    if (root) {
        RLOGD("adapter begin OnRequestComplete\n");
    }

    original_environment.OnRequestComplete(t, e, response, responselen);

    if (root) {
        RLOGD("adapter end OnRequestComplete\n");
    }
}

// OnUnsolicitedResponse
static void OnUnsolicitedResponse(int unsolResponse, const void *data, size_t datalen) {
   /* switch (unsolResponse) { */
   /*     case RIL_UNSOL_SIGNAL_STRENGTH: */
   /*         original_environment.OnUnsolicitedResponse(unsolResponse, data, datalen); */
   /*         return; */
   /*     default: */
   /*         break; */
   /* } */

   RIL_Data_Call_Response_v6 *r, *mydata;
   int i,j;

   mydata = data;

   bool root = is_enable("OnUnsolicitedResponse");
   if (root) {
       RLOGD("adapter begin OnUnsolicitedResponse\n");
   }

   /* if (unsolResponse == RIL_UNSOL_DATA_CALL_LIST_CHANGED) { */
   /*     RLOGD("Hook: DATA_CALL_LIST_CHANGED, datalen = %d", datalen); */
   /*     if (datalen > sizeof(RIL_Data_Call_Response_v6)) { */
   /*         i = datalen / sizeof(RIL_Data_Call_Response_v6); */
   /*         for (j = 0; j < i; j++) { */
   /*             r = &((RIL_Data_Call_Response_v6*)data)[j]; */
   /*             if (strcmp(r->ifname, "rmnet1") == 0) { */
   /*                 mydata = (RIL_Data_Call_Response_v6*)malloc(sizeof(RIL_Data_Call_Response_v6)); */
   /*                 memcpy(mydata, r, sizeof(RIL_Data_Call_Response_v6)); */
   /*                 mydata->cid = 0; */
   /*                 break; */
   /*             } */
                   
   /*         } */
               
   /*         RLOGD("Hook replace RESPONSE!!!"); */
   /*         datalen = sizeof(RIL_Data_Call_Response_v6); */
   /*     } */
   /* } */

   if (root) {
       RLOGD("adapter response is [%s] \n", requestToString(unsolResponse));
   }
   /* switch (unsolResponse) { */
   /*     case RIL_UNSOL_RESPONSE_NEW_SMS: { */

   /*     } */
   /*         break; */
   /*     default: */
   /*         break; */
   /* } */

    original_environment.OnUnsolicitedResponse(unsolResponse, mydata, datalen);

   if (root) {
       RLOGD("adapter end OnUnsolicitedResponse\n");
   }
}

// RequestTimedCallback
static void RequestTimedCallback(RIL_TimedCallback callback, void *param, const struct timeval *relativeTime) {
    bool root = is_enable("RequestTimedCallback");
    if (root) {
        RLOGD("adapter begin RequestTimedCallback\n");
    }
    original_environment.RequestTimedCallback(callback, param, relativeTime);
    if (root) {
        RLOGD("adapter end RequestTimedCallback\n");
    }
}

void attach_environment(struct RIL_Env *environment) {
    initialize_properties();

    memcpy(&original_environment, environment, sizeof(struct RIL_Env));
    environment->OnRequestComplete = OnRequestComplete;
    environment->OnUnsolicitedResponse = OnUnsolicitedResponse;
    environment->RequestTimedCallback = RequestTimedCallback;
}

static void onRequest(int request, void *data, size_t datalen, RIL_Token t);

static RIL_RadioState currentState();

static int onSupports(int requestCode);

static void onCancel(RIL_Token t);

static const char *getVersion();

static RIL_RadioFunctions adapter_functions = {
        RIL_VERSION,
        onRequest,
        currentState,
        onSupports,
        onCancel,
        getVersion
};

RIL_RadioFunctions *attach_functions(const RIL_RadioFunctions *functions) {

    initialize_properties();

    memcpy(&original_functions, functions, sizeof(RIL_RadioFunctions));
    return &adapter_functions;
}


// onRequest;
static void onRequest(int request, void *data, size_t datalen, RIL_Token t) {

    bool root = is_enable("onRequest");
    const char *message = requestToString(request);
    bool item = is_item_enable(message);
    LOGT("adapter switch %s root is %d, item is %d \n", message, root, item);
    if (!root || !item) {
        original_functions.onRequest(request, data, datalen, t);
        return;
    }
    RLOGD("adapter begin onRequest\n");

    RLOGD("adapter request is [%s] \n", message);

    switch (request) {
        case RIL_REQUEST_SEND_SMS: {
            const char *smsc;
            const char *pdu;
            char *command;
            smsc = ((const char **) data)[0];
            pdu = ((const char **) data)[1];
            // "NULL for default SMSC"
            if (smsc == NULL) {
                smsc = "00";
            }
            asprintf(&command, "%s%s", smsc, pdu);
            RLOGD("adapter pdu is { %s } \n", command);
        }
            break;
        case RIL_REQUEST_SET_INITIAL_ATTACH_APN: {
            RLOGD("adapter apn \n");
            RIL_InitialAttachApn *apn = (RIL_InitialAttachApn *) data;
            RLOGD("adapter apn %s %s %d %s %s \n", apn->apn, apn->protocol, apn->authtype, apn->username,
                  apn->password);
        }
            break;
        case RIL_REQUEST_GET_IMEI:
        case RIL_REQUEST_GET_IMEISV:
            RLOGD("adapter imei length %d \n", datalen);
            RLOGD("adapter imei %s \n", (char *) data);
            break;
        default:
            break;
    }

    original_functions.onRequest(request, data, datalen, t);
    RLOGD("adapter end onRequest\n");
}

// onStateRequest;
static RIL_RadioState currentState() {
    bool root = is_enable("onStateRequest");
    if (root) {
        RLOGD("adapter begin currentState\n");
    }

    RIL_RadioState state = original_functions.onStateRequest();

    if (root) {
        RLOGD("adapter current state is [%s] \n", radioStateToString(state));
        RLOGD("adapter end currentState\n");
    }
    return state;
}

// supports;
static int onSupports(int requestCode) {
    bool root = is_enable("supports");
    if (root) {
        RLOGD("adapter begin onSupports\n");
        RLOGD("adapter supports is [%s] \n", requestToString(requestCode));
    }
    int support = original_functions.supports(requestCode);

    if (root) {
        RLOGD("adapter end onSupports\n");
    }
    return support;
}

// onCancel;
static void onCancel(RIL_Token t) {
    bool root = is_enable("onCancel");
    if (root) {
        RLOGD("adapter begin onCancel\n");
    }

    original_functions.onCancel(t);

    if (root) {
        RLOGD("adapter end onCancel\n");
    }
}

// getVersion;
static const char *getVersion() {
    bool root = is_enable("getVersion");
    if (root) {
        RLOGD("adapter begin getVersion\n");
    }
    const char *version = original_functions.getVersion();
    if (root) {
        RLOGD("adapter end getVersion\n");
    }
    return version;
}


static void initialize_properties() {
    if (properties_loaded) {
        return;
    }
    load_properties(CFG_PATH);
    properties_loaded = true;
}

static bool is_item_enable(const char *key) {
    if (!properties_loaded) {
        return false;
    }
    int length = CFG_MAX;
    bool enable = false;
    for (int i = 0; i < length; ++i) {
        KEY_VALUE_PAIR pair = properties_arraylist[i];
        if (strcasecmp(key, pair.key) == 0) {
            int v = atoi(pair.value);
            if (v == 1) {
                enable = true;
            }
            break;
        }
    }
    LOGT("adapter  %s is enable  %s \n", key, enable ? "true" : "false");
    return enable;

}

static bool is_enable(const char *key) {
    if (!properties_loaded) {
        return true;
    }
    int length = CFG_MAX;
    bool enable = true;
    for (int i = 0; i < length; ++i) {
        KEY_VALUE_PAIR pair = properties_arraylist[i];
        LOGT("key = %s, value = %s", pair.key, pair.value);
        if (strcasecmp(key, pair.key) == 0) {
            int v = atoi(pair.value);
            if (v == 0) {
                enable = false;
            }
            break;
        }
    }
    LOGT("adapter  %s is enable  %s \n", key, enable ? "true" : "false");
    return enable;
}

static void load_properties(const char *path) {
    if (access(path, 00) == -1) {
        return;
    }

    LOGT("adapter begin load_properties \n");

    FILE *file;

    file = fopen(path, "r");
    char line[CHAR_MAX] = {0};

    int index = 0;
    while (fgets(line, CHAR_MAX, file) != NULL) {

        KEY_VALUE_PAIR pair = {0};

        LOGT("adapter load_properties line : %s \n", line);

        char key[CHAR_MAX] = {0};
        char value[CHAR_MAX] = {0};
        sscanf(line, "%s = %s", key, value);

        int length = strlen(value);
        if (value[length] == '\n') {
            value[length] = 0;
        }

        LOGT("adapter sscanf %s : %s \n", key, value);

        if (strlen(key) == 0 | strlen(value) == 0) {
            continue;
        }

        strcpy(pair.key, key);
        strcpy(pair.value, value);
        properties_arraylist[index] = pair;
        index++;
        if (index >= CFG_MAX) {
            break;
        }
    }

    fclose(file);

#ifdef LOCAL_TRACE
    for (int i = 0; i < CHAR_MAX; ++i) {
        KEY_VALUE_PAIR pair = properties_arraylist[i];
        if (strlen(pair.key) == 0) {
            break;
        }
        LOGT("adapter index %d,  key : %s, value : %s \n", i, pair.key, pair.value);
    }
#endif
    LOGT("adapter end load_properties \n");
}


