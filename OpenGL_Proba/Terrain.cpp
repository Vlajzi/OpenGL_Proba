#include "pch.h"
#include"Terrain.h"


void Terrain::LoadData(char* path)
{

}


void Terrain::SaveData(char* path)
{

}

std::vector<Point3f> Terrain::genPoints()
{
	std::vector<Point3f> data(0);

	float x, z;
	x = 0;
	z = 0;
	int tes;
	float scale = map_size/size;
	for (int i = 0; i <  size-1; i++)
	{
		int poz = i * size;
		for (int j = 0; j < size; j++)
		{
			
			data.push_back({ x,points[poz + j],z });
			data.push_back({ x,points[poz + size + j],z + scale });
			tes = poz + size + j;
			x += scale;
		}
		z += scale;
		x = 0;
	}

	return data;
}

std::vector<point3f> Terrain::genColor()
{
	std::vector<point3f> data(0);
	for (int i = 0; i < size-1; i++)
	{
		int poz = i * size;
		for (int j = 0; j < size; j++)
		{
			data.push_back(GetColor(points[poz + j]));
			data.push_back(GetColor(points[poz + size + j]));
			
		}
	}
	return data;
}




	point3f Terrain::GetColor(float data)
	{
		if (data < -0.5)
		{
			return{ 1.0f,1.0f,0.7f };
		}
		else
		{
			if (data < 0.0f)
			{
				return { 0.2f, 1.0f, 0.2f };
			}
			else if (data < 0.5f)
			{
				return { 0.0,0.7,0.0 };
			}
			else if (data < 0.7f)
			{
				return{ 0.7,0.3,0.0 };
			}
		}

		return{ 0.7,0.3,0.0 };
	}