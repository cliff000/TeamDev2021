#pragma once
#include <map>
#include <string>

class Image
{
protected:
	static std::map<std::string, int> imgMap;
	int img;

public:
	Image(){}
	Image(const char* imgPass);
	~Image();

	virtual void draw(int x, int y, double ExtRate, double Angle, int TransFlag, int TurnFlag);

	static void read(const char* imgPass);
	static void clear();
};

