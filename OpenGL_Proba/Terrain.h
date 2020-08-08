#pragma once
#include <vector>

typedef struct point3f
{
	float x;
	float y;
	float z;
}Point3f;

class Terrain
{
private:
	
	int size;
	float map_size;
public:
	float* points; // tmp
	Terrain(int size, float scale)
	{
		this->size = size;
		this->map_size = scale;
		points = (float*)malloc(sizeof(float) * (size * size + size));
	}

	void LoadData(char* path);
	void SaveData(char* path);
	std::vector<Point3f> genPoints();
	std::vector<point3f> genColor();

	 point3f GetColor(float data);



};