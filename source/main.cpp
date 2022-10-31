#include <wups.h>
#include <whb/log.h>
#include <whb/log_module.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>
#include <string.h>

#include <coreinit/title.h>

#include <patcher/rplinfo.h>
#include <patcher/patcher.h>

WUPS_PLUGIN_NAME("GiveMiiYouTube");
WUPS_PLUGIN_DESCRIPTION("Allows the YouTube app to continue functioning after its discontinuation");
WUPS_PLUGIN_VERSION("v2.0");
WUPS_PLUGIN_AUTHOR("GaryOderNichts");
WUPS_PLUGIN_LICENSE("MIT");

#define YOUTUBE_CLIENT_ID "e921a604fce89365498613fdf001b492"
#define YOUTUBE_TITLE_ID 0x0005000010105700llu
#define YOUTUBE_USERAGENT_PLATFORM "WiiU; "
#define YOUTUBE_USERAGENT_PLATFORM_REPLACEMENT "NoU; "

ON_APPLICATION_START()
{
    // If this is not the YouTube app no need to do anything
    if (OSGetTitleID() != YOUTUBE_TITLE_ID) {
        return;
    }

    // Init logging
    if (!WHBLogModuleInit()) {
        WHBLogCafeInit();
        WHBLogUdpInit();
    }

    WHBLogPrintf("GiveMiiYouTube: applying patches...");

    // Patch the dynload functions so GetRPLInfo works
    if (!PatchDynLoadFunctions()) {
        WHBLogPrintf("GiveMiiYouTube: Failed to patch dynload functions");
        return;
    }

    // Get the RPLInfo
    auto rpl_info = TryGetRPLInfo();
    if (!rpl_info) {
        WHBLogPrintf("GiveMiiYouTube: Failed to get RPL info");
        return;
    }

    // Find the rpx
    rplinfo rpls = *rpl_info;
    auto lb_shell_rpx = FindRPL(rpls, "lb_shell.rpx");
    if (!lb_shell_rpx) {
        WHBLogPrintf("GiveMiiYouTube: Failed to find lb_shell.rpx");
        return;
    }

    // Patch the useragent platform
    OSDynLoad_NotifyData rpx_data = *lb_shell_rpx;
    if (!replace_string(rpx_data.dataAddr, rpx_data.dataSize, 
        YOUTUBE_USERAGENT_PLATFORM, sizeof(YOUTUBE_USERAGENT_PLATFORM),
        YOUTUBE_USERAGENT_PLATFORM_REPLACEMENT, sizeof(YOUTUBE_USERAGENT_PLATFORM_REPLACEMENT))) {
        WHBLogPrintf("GiveMiiYouTube: Failed to replace useragent platform");
        return;
    }
}

DECL_FUNCTION(int, AcquireIndependentServiceToken__Q2_2nn3actFPcPCc, uint8_t* token, const char* client_id)
{
    // If this is the YouTube client, return sucess
    if (client_id && strcmp(client_id, YOUTUBE_CLIENT_ID) == 0) {
        WHBLogPrintf("GiveMiiYouTube: Faking service sucess for '%s'", client_id);
        return 0;
    }

    return real_AcquireIndependentServiceToken__Q2_2nn3actFPcPCc(token, client_id);
}

WUPS_MUST_REPLACE(AcquireIndependentServiceToken__Q2_2nn3actFPcPCc, WUPS_LOADER_LIBRARY_NN_ACT, AcquireIndependentServiceToken__Q2_2nn3actFPcPCc);
