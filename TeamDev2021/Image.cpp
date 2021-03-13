#include "Image.h"
#include "Dxlib.h"

std::map<std::string, int> Image::imgMap;

Image::Image(const char* imgPass) {
	read(imgPass);
	img = imgMap[imgPass];
}

Image::~Image() {

}

void Image::draw(int x, int y, double ExtRate, double Angle, int TransFlag, int TurnFlag) {
	DrawRotaGraph(x, y, ExtRate, Angle, img, TransFlag, TurnFlag);
}


void Image::read(const char* imgPass) {
	if (imgMap.find(imgPass) == imgMap.end())
		imgMap[imgPass] = LoadGraph(imgPass);
}

void Image::clear() {
	InitGraph();
	imgMap.clear();
}