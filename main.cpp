#include "../include/mod_interface.hpp"

#include <unordered_set>

#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include "../extern/beatsaber-hook/include/modloader.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp" 
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "../extern/beatsaber-hook/shared/utils/typedefs.h"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"

static ModInfo modInfo;

static Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

static const Logger& getLogger() {
    static const Logger logger(modInfo);
    return logger;
}

MAKE_HOOK_OFFSETLESS(NoteCut, void, Il2CppObject* self) {

    getLogger().debug("Level Started!");

    Il2CppObject* empty = CRASH_UNLESS(il2cpp_utils::New("UnityEngine", "GameObject"));

    Il2CppObject* component = CRASH_UNLESS(il2cpp_utils::RunMethod(empty, "AddComponent", il2cpp_utils::GetSystemType("UnityEngine", "ParticleSystem")));
    Il2CppObject* transform = CRASH_UNLESS(il2cpp_utils::RunMethod(empty, "GetComponent", il2cpp_utils::GetSystemType("UnityEngine", "Transform")));

    CRASH_UNLESS(il2cpp_utils::SetPropertyValue(transform, "position", Vector3{0,0,-5}));
    
    NoteCut(self);
}

extern "C" void setup(ModInfo& info) {
    info.id = "tutorial";
    info.version = "0.1.0";
    modInfo = info;
    getLogger().info("Modloader name: %s", Modloader::getInfo().name.c_str());
    getConfig().Load();
    getLogger().info("Completed setup!");
}


extern "C" void load() {
    getLogger().debug("Hello from il2cpp_init!");
    getLogger().debug("Installing hooks...");
    il2cpp_functions::Init();

    INSTALL_HOOK_OFFSETLESS(NoteCut, il2cpp_utils::FindMethodUnsafe("", "NoteController", "SendNoteWasMissedEvent", 0));    
    
    getLogger().debug("Installed all hooks!");
    
}

enum class Space {
    World,
    Self
};

DEFINE_IL2CPP_ARG_TYPE(Space, "UnityEngine", "Space");
