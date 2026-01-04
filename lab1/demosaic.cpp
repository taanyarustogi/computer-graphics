#include "demosaic.h"

// information on how to from the slides on the github

inline unsigned char avg(unsigned char a, unsigned char b) {
	return static_cast<unsigned char>((a + b) / 2);
}

inline unsigned char avg(unsigned char a, unsigned char b, unsigned char c) {
	return static_cast<unsigned char>((a + b + c) / 3);
}

inline unsigned char avg(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
	return static_cast<unsigned char>((a + b + c + d) / 4);
}

void demosaic(
	const std::vector<unsigned char>& bayer,
	const int& width,
	const int& height,
	std::vector<unsigned char>& rgb)
{
	rgb.resize(width * height * 3);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (j % 2 == 0 && i % 2 == 0) {
				rgb[3 * (j * width + i) + 1] = bayer[j * width + i];
				if (i == 0) {
					rgb[3 * (j * width + i) + 2] = bayer[j * width + i + 1];
				}
				else if (i == (width - 1)) {
					rgb[3 * (j * width + i) + 2] = bayer[j * width + i - 1];
				}
				else {
					rgb[3 * (j * width + i) + 2] = avg(bayer[j * width + i + 1], bayer[j * width + i - 1]);
				}
				if (j == 0) {
					rgb[3 * (j * width + i)] = bayer[(j + 1) * width + i];
				}
				else if (j == (height - 1)) {
					rgb[3 * (j * width + i)] = bayer[(j - 1) * width + i];
				}
				else {
					rgb[3 * (j * width + i)] = avg(bayer[(j - 1) * width + i], bayer[(j + 1) * width + i]);
				}
			}
			if (j % 2 == 0 && i % 2 == 1) {
				rgb[3 * (j * width + i) + 2] = bayer[j * width + i];
				if ((i == (width - 1)) && (j == 0)) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j + 1) * width + i], bayer[j * width + i - 1]);
				}
				else if (j == 0) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j + 1) * width + i], bayer[j * width + i - 1], bayer[j * width + i + 1]);
				}
				else if ((i == (width - 1)) && (j == (height - 1))) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[j * width + i - 1]);
				}
				else if (j == (height - 1)) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[j * width + i - 1], bayer[j * width + i + 1]);
				}
				else if (i == (width - 1)) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[(j + 1) * width + i], bayer[j * width + i - 1]);
				}
				else {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[(j + 1) * width + i], bayer[j * width + i - 1], bayer[j * width + i + 1]);
				}
				if ((i == (width - 1)) && (j == 0)) {
					rgb[3 * (j * width + i)] = bayer[(j + 1) * width + i - 1];
				}
				else if (j == 0) {
					rgb[3 * (j * width + i)] = avg(bayer[(j + 1) * width + i + 1], bayer[(j + 1) * width + i - 1]);
				}
				else if ((i == (width - 1)) && (j == (height - 1))) {
					rgb[3 * (j * width + i)] = bayer[(j - 1) * width + i - 1];
				}
				else if (j == (height - 1)) {
					rgb[3 * (j * width + i)] = avg(bayer[(j - 1) * width + i + 1], bayer[(j - 1) * width + i - 1]);
				}
				else if (i == (width - 1)) {
					rgb[3 * (j * width + i)] = avg(bayer[(j + 1) * width + i - 1], bayer[(j - 1) * width + i - 1]);
				}
				else {
					rgb[3 * (j * width + i)] = avg(bayer[(j + 1) * width + i + 1], bayer[(j + 1) * width + i - 1], bayer[(j - 1) * width + i + 1], bayer[(j - 1) * width + i - 1]);
				}
			}
			if (j % 2 == 1 && i % 2 == 0) {
				rgb[3 * (j * width + i)] = bayer[j * width + i];
				if ((i == (width - 1)) && (j == (height - 1))) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[j * width + i - 1]);
				}
				else if ((i == 0) && (j == (height - 1))) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[j * width + i + 1]);
				}
				else if (j == (height - 1)) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[j * width + i - 1], bayer[j * width + i + 1]);
				}
				else if (i == (width - 1)) {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[(j + 1) * width + i], bayer[j * width + i - 1]);
				}
				else {
					rgb[3 * (j * width + i) + 1] = avg(bayer[(j - 1) * width + i], bayer[(j + 1) * width + i], bayer[j * width + i - 1], bayer[j * width + i + 1]);
				}
				if ((i == (width - 1)) && (j == (height - 1))) {
					rgb[3 * (j * width + i) + 2] = bayer[(j - 1) * width + i - 1];
				}
				else if ((i == 0) && (j == (height - 1))) {
					rgb[3 * (j * width + i) + 2] = bayer[(j - 1) * width + i + 1];
				}
				else if (j == (height - 1)) {
					rgb[3 * (j * width + i) + 2] = avg(bayer[(j - 1) * width + i + 1], bayer[(j - 1) * width + i - 1]);
				}
				else if (i == (width - 1)) {
					rgb[3 * (j * width + i) + 2] = avg(bayer[(j - 1) * width + i - 1], bayer[(j + 1) * width + i - 1]);
				}
				else {
					rgb[3 * (j * width + i) + 2] = avg(bayer[(j - 1) * width + i + 1], bayer[(j - 1) * width + i - 1], bayer[(j + 1) * width + i + 1], bayer[(j + 1) * width + i - 1]);
				}
			}
			if (j % 2 == 1 && i % 2 == 1) {
				rgb[3 * (j * width + i) + 1] = bayer[j * width + i];
				if (i == (width - 1)) {
					rgb[3 * (j * width + i)] = bayer[j * width + i - 1];
				}
				else {
					rgb[3 * (j * width + i)] = avg(bayer[j * width + i - 1], bayer[j * width + i + 1]);
				}
				if (j == (height - 1)) {
					rgb[3 * (j * width + i) + 2] = bayer[(j - 1) * width + i];
				}
				else {
					rgb[3 * (j * width + i) + 2] = avg(bayer[(j - 1) * width + i], bayer[(j + 1) * width + i]);
				}
			}
		}
	}
}
