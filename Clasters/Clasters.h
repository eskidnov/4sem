#pragma once
#include <vector>

/*
Просто для общего сведение:
в винде можно писать как такие слеши / , так и \.
в линуксе только /.
Поэтому по-моему лучше писать всегда /, в случае необходимости собирать код под разные платформы.
*/
#include <SFML\Graphics.hpp>

using Centroids = std::vector<sf::Color>;
using ClosestCentroidIndices = std::vector<int>;

Centroids initializeCentroids(const sf::Image&, const int);
ClosestCentroidIndices findClosestCentroids(const sf::Image&, Centroids);
Centroids computeMeans(const sf::Image&, const ClosestCentroidIndices, const int);
void changeColors(sf::Image&, const Centroids);
