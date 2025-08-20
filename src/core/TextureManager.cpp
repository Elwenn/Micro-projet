#include "TextureManager.h"

std::map<std::string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::getTexture(const std::string& path) {
    auto it = textures.find(path);
    if (it == textures.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            // Fallback texture
            sf::Image fallback({50, 50}, sf::Color::Magenta);
            texture.loadFromImage(fallback);
        }
        textures[path] = texture;
        return textures[path];
    }
    return it->second;
}
