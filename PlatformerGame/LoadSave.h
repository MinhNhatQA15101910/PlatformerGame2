#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"

#include <iostream>

class LoadSave
{
public:
	static sf::Image* GetImageAtlas(std::string fileName)
	{
		sf::Image* image = new sf::Image();
		std::string filePath = RES_FOLDER + '\\' + fileName;

		if (!image->loadFromFile(filePath))
		{
			std::cout << "[ERROR] : Cannot load file " + fileName + "\n";
		}

		return image;
	}

	static sf::Texture* GetTextureAtlas(std::string fileName)
	{
		sf::Texture* texture = new sf::Texture();
		std::string filePath = RES_FOLDER + '\\' + fileName;

		if (!texture->loadFromFile(filePath))
		{
			std::cout << "[ERROR] : Cannot load file " + fileName + "\n";
		}

		return texture;
	}

	static int** GetLevelData()
	{
		sf::Image* image = GetImageAtlas(LEVEL_ONE_DATA);

		int** lvlData = new int*[TILES_IN_HEIGHT];
		for (unsigned int j = 0; j < image->getSize().y; j++)
		{
			lvlData[j] = new int[TILES_IN_WIDTH];
			for (unsigned int i = 0; i < image->getSize().x; i++)
			{
				sf::Color* color = new sf::Color(image->getPixel(i, j));
				int value = color->r;
				if (value >= 48) value = 0;
				lvlData[j][i] = value;
			}
		}

		return lvlData;
	}
};