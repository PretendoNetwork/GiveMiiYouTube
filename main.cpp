#include <wups.h>
#include <string.h>

WUPS_PLUGIN_NAME("GiveMiiYouTube");
WUPS_PLUGIN_DESCRIPTION("Allows the YouTube app to continue functioning after its discontinuation");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("GaryOderNichts");
WUPS_PLUGIN_LICENSE("MIT");

#define CLIENT_ID_YT "e921a604fce89365498613fdf001b492"

DECL_FUNCTION(int, AcquireIndependentServiceToken__Q2_2nn3actFPcPCc, uint8_t* token, const char* client_id)
{
    if (strcmp(client_id, CLIENT_ID_YT) == 0) {
        return 0;
    }

    return real_AcquireIndependentServiceToken__Q2_2nn3actFPcPCc(token, client_id);
}

WUPS_MUST_REPLACE(AcquireIndependentServiceToken__Q2_2nn3actFPcPCc, WUPS_LOADER_LIBRARY_NN_ACT, AcquireIndependentServiceToken__Q2_2nn3actFPcPCc);
