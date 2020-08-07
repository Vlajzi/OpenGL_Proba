#pragma once


typedef struct point3f
{
	float x;
	float y;
	float z;
}Point3f;

class Terrain
{
private:
	float* points;
	int size;
	float scale;
public:
	
	void LoadData(char* path);
	void SaveData(char* path);
	std::vector<Point3f> genPoints();
	std::vector<point3f> genColor();

	 point3f GetColor(float data);
};