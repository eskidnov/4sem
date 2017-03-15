#include "SFML\Graphics.hpp"
#include "Clasters.h"
#include <iostream>

Centroids initializeCentroids(const sf::Image& image, const int K) {
	Centroids centroids(K);
	sf::Color pixel;

	for (int i = 0; i < K; ++i) {
		pixel = image.getPixel(rand() % image.getSize().x, rand() % image.getSize().y);
		centroids[i] = pixel;
	}
	for (int i = 0; i < K; ++i) {
		for (int j = i + 1; j < K; ++j) {
			if (centroids[i] == centroids[j] && i != j) std::cout << "win";
		}
	}

	return centroids;
}

ClosestCentroidIndices findClosestCentroids(const sf::Image& image, Centroids centroids) {
	sf::Color pixel;
	std::vector<float> distance(centroids.size());
	ClosestCentroidIndices ids(image.getSize().x * image.getSize().y);
	float min = 500000;
	unsigned int number;

	for (auto i = 0; i < image.getSize().x; ++i) {
		for (auto j = 0; j < image.getSize().y; ++j) {
			pixel = image.getPixel(i, j);
			for (auto k = 0; k < centroids.size(); ++k) {
				distance[k] = sqrt((pixel.r - centroids[k].r) * (pixel.r - centroids[k].r) +
									(pixel.g - centroids[k].g) * (pixel.g - centroids[k].g) +
									(pixel.r - centroids[k].b) * (pixel.r - centroids[k].b));
				if (min > distance[k]) {
					min = distance[k];
					number = k;
				}
			}
			ids[i + j * image.getSize().x] = number;
			min = 500000;
		}
	}

	return ids;
}

Centroids computeMeans(const sf::Image& image, const ClosestCentroidIndices ids, const int K) {
	unsigned int x = 0, y = 0;
	unsigned int r = 0, g = 0, b = 0;
	unsigned int number = 0;
	Centroids centroids(K);
	sf::Color pixel;

	for (auto k = 0; k < K; ++k) {
		for (auto i = 0; i < ids.size(); ++i) {
			if (ids[i] == k) {
				y = i / image.getSize().x;
				x = i - y * image.getSize().x;
				pixel = image.getPixel(x, y);
				r += pixel.r;
				g += pixel.g;
				b += pixel.b;
				number++;
			}
		}
		if (number != 0) {
			r /= number;
			g /= number;
			b /= number;
			pixel.r = r;
		//std::cout << pixel.r << " " << r << "\n";
			pixel.g = g;
			pixel.b = b;
			centroids[k] = pixel;
			r = 0;
			g = 0;
			b = 0;
			number = 0;
		}
		//else std::cout << ids.size() << " " << image.getSize().x * image.getSize().y << "\n";
	}


	return centroids;
}

void changeColors(sf::Image& image, const Centroids centroids) {
	sf::Color pixel;
	float min = 500000;
	unsigned int number;
	std::vector<float> distance(centroids.size());

	for (auto i = 0; i < image.getSize().x; ++i) {
		for (auto j = 0; j < image.getSize().y; ++j) {
			pixel = image.getPixel(i, j);
			for (auto k = 0; k < centroids.size(); ++k) {
				distance[k] = sqrt((pixel.r - centroids[k].r) * (pixel.r - centroids[k].r) +
									(pixel.g - centroids[k].g) * (pixel.g - centroids[k].g) +
									(pixel.r - centroids[k].b) * (pixel.r - centroids[k].b));
				if (min > distance[k]) {
					min = distance[k];
					number = k;
				}
			}
			image.setPixel(i, j, centroids[number]);
			min = 500000;
		}
	}
}