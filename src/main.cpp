#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

static void applyFps() {
    auto fps = Mod::get()->getSettingValue<int64_t>("target-fps");
    if (fps < 1) fps = 60;
    CCApplication::sharedApplication()->setAnimationInterval(1.0 / static_cast<double>(fps));
}

// Aplica el FPS cuando el juego ya cargó el menú principal
class $modify(UnlockFpsMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        applyFps();
        return true;
    }
};

// Reaplica cuando cambias el valor en los ajustes del mod
$on_mod(Loaded) {
    listenForSettingChanges<int64_t>("target-fps", [](int64_t) {
        applyFps();
    });
}
