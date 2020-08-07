#include"pch.h"


void Terrain::LoadData(char* path)
{

}


void Terrain::SaveData(char* path)
{

}

std::vector<Point3f> Terrain::genPoints(char* path)
{
	std::vector<Point3f> data(size*size);

	float x, z;
	x = 0;
	z = 0;
	float scale = size / 1.0f;
	//int sizr_d = size*size;
	for (int i = 0; i < size; i++)
	{
		int poz = i*size;
		for (int j = 0; j < size; j++)
		{
			data.push_back({ x,points[poz+j],z });
			data.push_back({ x,points[poz + size + j],z + scale });
			x += scale;
		}
		z += scale;
		x = 0;
	}

	return data;
}

/*std::vector<point3f> Terrain::genColor(char* path)
{
	std::vector<point3f> data(size*size);

	float x, z;
	x = 0;
	z = 0;
	float scale = size / 1.0f;
	//int sizr_d = size*size;
	for (int i = 0; i < size; i++)
	{
		int poz = i*size;
		for (int j = 0; j < size; j++)
		{
			if (points[poz + j] < 0.5)
			{
				data.push_back({ 1.0f,1.0f,0.2f });

				data.push_back({ x,points[poz + j],z });
				data.push_back({ x,points[poz + size + j],z + scale });
				x += scale;
			}
			z += scale;
			x = 0;
		}
	}
		return data;
}*/


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
			else if (data < 0.7f);
			{
				return{ 0.7,0.3,0.0 };
			}
		}

		return{ 0.7,0.3,0.0 };
	}