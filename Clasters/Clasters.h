#pragma once
// May be need libraries ...

/*
по-хорошему как раз здесь и надо было написать 

#include <vector>
#include <sfml/ ...>
*/

using Centroids = std::vector<sf::Color>;
using ClosestCentroidIndices = std::vector<int>;

Centroids initializeCentroids(const sf::Image&, const int);
ClosestCentroidIndices findClosestCentroids(const sf::Image&, Centroids);
Centroids computeMeans(const sf::Image&, const ClosestCentroidIndices, const int);
void changeColors(sf::Image&, const Centroids);
