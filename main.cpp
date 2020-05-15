#include "../include/mod_interface.hpp"

#include <unordered_set>

#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "../extern/beatsaber-hook/shared/utils/utils.h"
MAKE_HOOK_OFFSETLESS(FlickeringNeonSign_Start, void, Il2CppObject* self) {

    float _minOffDelay = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(self, "_minOffDelay"));
    float _maxOnDelay = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(self, "_maxOnDelay"));
    _minOffDelay = 99999999999999;
    _maxOnDelay = 0;
}

__attribute__((constructor)) void lib_main() {
    log(INFO, "Hello from the first time this mod is loaded!");
}

extern "C" void load() {
    log(INFO, "Hello from il2cpp_init!");
    log(INFO, "Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(FlickeringNeonSign_Start, il2cpp_utils::FindMethod("", "FlickeringNeonSign", "Start"));
    log(INFO, "Installed all hooks!");
}

enum class Space {
    World,
    Self
};

DEFINE_IL2CPP_ARG_TYPE(Space, "UnityEngine", "Space");
