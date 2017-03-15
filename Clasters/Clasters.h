#pragma once
// May be neede libraries ...

using Centroids = std::vector<sf::Color>;
using ClosestCentroidIndices = std::vector<int>;

Centroids initializeCentroids(const sf::Image&, const int);
ClosestCentroidIndices findClosestCentroids(const sf::Image&, Centroids);
Centroids computeMeans(const sf::Image&, const ClosestCentroidIndices, const int);
void changeColors(sf::Image&, const Centroids);