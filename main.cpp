#include "../include/mod_interface.hpp"

#include <unordered_set>

#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "../extern/beatsaber-hook/shared/utils/utils.h"
MAKE_HOOK_OFFSETLESS(FlickeringNeonSign_Start, void, Il2CppObject* self) {

  il2cpp_utils::SetFieldValue(self, "_minOffDelay", 999999999999.0f);
  il2cpp_utils::SetFieldValue(self, "_maxOffDelay", 999999999999.0f);
  il2cpp_utils::SetFieldValue(self, "_minOnDelay", 0.0f);
  il2cpp_utils::SetFieldValue(self, "_maxOnDelay", 0.0f);
  
  FlickeringNeonSign_Start(self);

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
