#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Level.h"

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

	static Level* GetLevelData()
	{
		sf::Image* image = GetImageAtlas(LEVEL_ONE_DATA);
		unsigned int imageWidth = image->getSize().x;
		unsigned int imageHeight = image->getSize().y;

		int** lvlData = new int*[imageHeight];
		for (unsigned int j = 0; j < imageHeight; j++)
		{
			lvlData[j] = new int[imageWidth];
			for (unsigned int i = 0; i < imageWidth; i++)
			{
				sf::Color* color = new sf::Color(image->getPixel(i, j));
				int value = color->r;
				if (value >= 48) value = 0;
				lvlData[j][i] = value;
			}
		}

		Level* level = new Level(lvlData, imageWidth, imageHeight);

		return level;
	}
};