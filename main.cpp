#include <GL/glut.h>
#include "game/game.h"
//#include "pluginManager/plugin_manager.h"
//#include "libManager/library_manager.h"
//#include <format>
//
//constexpr std::string dlExt = ".so";
//constexpr std::string searchDir = "dynamiclib";

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    Game::setupEngine();
//
//    LibraryManager libManager;
//    libManager.scan(searchDir, dlExt);
//
//    PluginManager& plugManager = PluginManager::getInstance();
//
//    for(const auto& pluginInfo : plugManager.getPlugins()) {
//        const Enemy& plugin = pluginInfo.second;
//        std::cout << std::format("loaded plugin \"{}\"", plugin.get_entity_name())  << std::endl;
//    }
//
//    for(const auto& pluginInfo : plugManager.getPlugins()) {
//        const Enemy& plugin = pluginInfo.second;
//        std::cout << plugin.get_entity_name() << std::endl;
//    }

    glutMainLoop();
}
