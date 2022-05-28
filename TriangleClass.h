#pragma once

#include <iostream>

namespace CAP {
	// This is a custom vector , that I use the most in my apps . Easy to use
	struct Vector3D {

		float x, y, z;
		Vector3D()
		{
			x = 0, y = 0, z = 0;
		}
		Vector3D(float X, float Y, float Z)
		{
			x = X; y = Y; z = Z;
		}

		// Find distance between positions
		float Distanceto(Vector3D vec) { return sqrtf((x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y) + (z - vec.z) * (z - vec.z)); }

		void operator *=(float a) { x = x * a; y = y * a; z = z * a; }
		void operator +=(Vector3D vec) { x = vec.x + x; y = vec.y + y; z = vec.z + z; }

		Vector3D operator +(Vector3D vec) { return Vector3D(vec.x + x, vec.y + y, vec.z + z); }
		Vector3D operator *(float a) { return Vector3D(x * a, y * a, z * a); }
		Vector3D operator - (Vector3D vec) { return Vector3D(x - vec.x, y - vec.y, z - vec.z); }
	};

	class Triangle
	{


		void rotateX(float angle)
		{
			float sinF = sin(angle);  // Find the sin value of rotation
			float cosF = cos(angle);  // Find the cos value of rotation 
			for (int i = 0; i < 3; i++)
			{
				float y = Translation[i].y;
				float z = Translation[i].z;

				Translation[i].y = y * cosF - z * sinF; // Save the change in y value 
				Translation[i].z = z * cosF + y * sinF; // Save the change in z value 
			}

		} // Rotate on the X plane

		void rotateY(float angle)
		{
			float sinF = sin(angle); // Find the sin value of rotation
			float cosF = cos(angle); // Find the cos value of rotation 
			for (int i = 0; i < 3; i++)
			{
				float x = Translation[i].x;
				float z = Translation[i].z;

				Translation[i].x = x * cosF + z * sinF; // Save the change in x value 
				Translation[i].z = z * cosF - x * sinF; // Save the change in z value 
			}

		} // Rotate on the Y plane

		void rotateZ(float angle)
		{
			float sinF = sin(angle); // Find the sin value of rotation
			float cosF = cos(angle); // Find the cos value of rotation 
			for (int i = 0; i < 3; i++)
			{
				float x = Translation[i].x;
				float y = Translation[i].y;
				Translation[i].x = x * cosF - y * sinF; // Save the change in x value 
				Translation[i].y = y * cosF + x * sinF; // Save the change in y value 
			}

		} // Rotate on the Z plane

		void Transform()
		{
			for (int i = 0; i < 3; i++)
				corners[i] = center + Translation[i];
		} // The Transform function will set the position of all corners based on the center of the triangle
			  // and also based on the distance from the center to the corner. 
			  // Adding this together will conclude on the actual position of the vertex

	public:
		Vector3D origin;  // The origin of the triangle
		Vector3D center;  // The center of the Triangle
		Vector3D corners[3];     // Corners
		Vector3D Translation[3]; // Distance from the center to all corners
		void update()
		{
			center = Vector3D((corners[0].x + corners[1].x + corners[2].x) / 3,
				(corners[0].y + corners[1].y + corners[2].y) / 3,
				(corners[0].z + corners[1].z + corners[2].z) / 3);  // Find the center of the triangle

			FindTranslation();
		}

		void FindTranslation()
		{
			for (int i = 0; i < 3; i++)
				Translation[i] = corners[i] - center;   // Find the new translations
		}

		void move(float x, float y, float z)
		{
			center += Vector3D(x, y, z); // Move the center of the triangle by x,y,z
			Transform(); // Save the changes made
		}
		void resize(float Alfa)
		{
			for (int i = 0; i < 3; i++) Translation[i] *= Alfa;
			Transform();  // Save the changes made to the triangle
		}                     // Resize the triangle by a specific ratio

		void rotate(float AlfaX, float AlfaY, float AlfaZ)
		{
			rotateX(AlfaX); // Rotate on the X plane
			rotateY(AlfaY); // Rotate on the Y plane
			rotateZ(AlfaZ); // Rotate on the Z plane
			Transform();    // Save the changes
		}

	};



	class RenderMap
	{


	public:
		Triangle* triangles;
		int vertices = 10;
		int gap = 25;
		int _sizeX = 2;
		int _sizeY = 2;


		RenderMap(int SizeX, int SizeY)
		{
			_sizeX = SizeX * 2;
			_sizeY = SizeY;
			vertices = _sizeX * SizeY;
			triangles = new Triangle[vertices];

			for (int i = 0; i < SizeY; i++)
				for (int j = 0; j < SizeX; j++)
				{
					int index = i * _sizeX + j * 2;
					triangles[index].corners[0] = Vector3D(j * gap, i * gap, 0);
					triangles[index].corners[1] = Vector3D((j + 1) * gap, i * gap, 0);
					triangles[index].corners[2] = Vector3D((j + 1) * gap, (i + 1) * gap, 0);

					triangles[index + 1].corners[0] = Vector3D(j * gap, i * gap, 0);
					triangles[index + 1].corners[1] = Vector3D(j * gap, (i + 1) * gap, 0);
					triangles[index + 1].corners[2] = Vector3D((j + 1) * gap, (i + 1) * gap, 0);

				}

			float distanceX = (triangles[vertices - 2].corners[1].x - triangles[0].corners[0].x) / 2;
			float distanceY = (triangles[vertices - 2].corners[2].x - triangles[0].corners[0].y) / 2;

			for (int i = 0; i < vertices; i++)
			{
				triangles[i].update();
				triangles[i].center = Vector3D(distanceX, distanceY, 0);
				triangles[i].FindTranslation();

			}

		}

		void Rotate(float AlfaX, float AlfaY, float AlfaZ)
		{
			for (int i = 0; i < vertices; i++)
			{
				triangles[i].rotate(AlfaX, AlfaY, AlfaZ);

			}

		}

		void MoveBy(float x, float y, float z)
		{
			for (int i = 0; i < vertices; i++)
			{
				triangles[i].move(x, y, z);

			}
		}


	};


	
}
