
#include <vector>
#include <map> //memoizing in getMidpoint
#include <random> //for Mersenne Twister RNG
#include <cmath> //for calculating distance between two Points
#include <math.h> //for fabs as a workaround for problems with cmath's abs
#include <algorithm> //for iterating

#include "Triangle.struct"

const std::vector<Point> BASE = {{-1, 1, 0}, {-1, -1, 0}, {1, -1, 0}, {1, 1, 0}};
const float MOUNTAIN_HEIGHT = 1.0;
const float SNOW_LEVEL = 0.6;
const float RANDOMNESS_SCALE = 0.085f;//shouldn't be more than 0.2
const int RESOLUTION = 7; //8 is a good max
const int NUM_VERTICES = 262144; //= 4 ^ (RESOLUTION + 2)

std::mt19937 mersenneTwister; //Mersenne Twister PRNG. WAY better randomness!
std::uniform_real_distribution<float> randomFloat(-1, 1);


/* Produces a vector with the coordinates randomized and in the range of (-1, 1) */
Point randVector()
{
	return { //return random coordinates, each in the range of (-1, 1)
		randomFloat(mersenneTwister),
		randomFloat(mersenneTwister),
		randomFloat(mersenneTwister)
	};
}



/* Returns the distance between the two given Points */
float length(const Point& a, const Point& b)
{ //for some reason cmath's abs function rounds floats, idk why
	return sqrt(pow(fabs(a.x - b.x), 2) + pow(fabs(a.y - b.y), 2) + pow(fabs(a.z - b.z), 2));
}



/*	Returns the midpoint between the two points with a randomized offset.
	Uses memoizing to avoid tearing across repeated lookups. */
Point getMidpoint(const Point& a, const Point& b)
{
	static std::map<std::pair<Point, Point>, Point> memo;
	auto AB = std::make_pair(a, b), BA = std::make_pair(b, a);

	auto foundResult = memo.find(AB);
	if (foundResult != memo.end())
		return foundResult->second; //if found in cache, return pre-computed midpoint
	
	auto result = (a + b) / 2; //create midpoint
	result += randVector() * length(a, b) * RANDOMNESS_SCALE; //add random offset

	memo.insert(std::make_pair(AB, result)); //memoize
	memo.insert(std::make_pair(BA, result));

	return result;
}



/* Subdivides the triangle into four separate equilateral triangles and returns the result */
std::vector<Triangle> subdivideTriangle(const Triangle& triangle)
{
	/*	
				  A
				  /\
				 /  \
			  c'/____\b'
			   /\    /\
			  /  \  /  \
			 /____\/____\
			B     a'     C
	*/

	auto aPrime = getMidpoint(triangle.B, triangle.C);
	auto bPrime = getMidpoint(triangle.C, triangle.A);
	auto cPrime = getMidpoint(triangle.A, triangle.B);

	return {
		{ triangle.A, cPrime, bPrime }, //top triangle
		{ cPrime, triangle.B, aPrime }, //bottom left triangle
		{ bPrime, aPrime, triangle.C }, //bottom right triangle
		{ cPrime, aPrime, bPrime }      //center triangle
	};
}



/* Creates a face of the mountain by divide and conquer */
void createFace(std::vector<Triangle>& modelTriangles, const Triangle& baseTriangle, int depthLeft)
{
	if (depthLeft <= 0) //base case
	{
		modelTriangles.push_back(baseTriangle);
		return;
	}
		
	//subdivide and recurse
	auto subTriangles = subdivideTriangle(baseTriangle);
	for_each (subTriangles.begin(), subTriangles.end(), 
		[&](const Triangle& subTri)
		{
			createFace(modelTriangles, subTri, depthLeft - 1);
		});
}



/* Creates all four faces of the 3D mountain and returns the result */
void createMountain(std::vector<Triangle>& modelTriangles)
{
	auto oppositeCorners = std::make_pair(BASE[0], BASE[2]);

	auto topPeak = getMidpoint(oppositeCorners.first, oppositeCorners.second);
	topPeak.z = MOUNTAIN_HEIGHT;

	createFace(modelTriangles, {topPeak, BASE[0], BASE[1]}, RESOLUTION);
	createFace(modelTriangles, {topPeak, BASE[1], BASE[2]}, RESOLUTION);
	createFace(modelTriangles, {topPeak, BASE[2], BASE[3]}, RESOLUTION);
	createFace(modelTriangles, {topPeak, BASE[3], BASE[0]}, RESOLUTION);
}



/* Creates the mountain model using the Sierpinksi Gasket.
	Uses memoizing to create the model only once. */
std::vector<Triangle> getModel()
{
	static std::vector<Triangle> modelTriangles;

	if (modelTriangles.empty())
	{
		createMountain(modelTriangles);
		return modelTriangles;
	}
	else
		return modelTriangles;
}



/* Scales val, which is the range of (0, 1) to the given range and returns the result */
float scale(float val, int begin, int end)
{
	return val * (end - begin) + begin;
}



/* Given the vertices, it return a list of respective colors for those points.
	The returned array will be the same length as the list of vertices. */
std::vector<Point> colorModel(const std::vector<Point>& points)
{
	std::vector<Point> colors;
	const float lowerScale = 1.2f;

	for_each (points.begin(), points.end(), 
		[&](const Point& vertex)
		{
			float height = vertex.z;
			
			if (height > SNOW_LEVEL)
			{
				float topScale = (height - SNOW_LEVEL) / (MOUNTAIN_HEIGHT - SNOW_LEVEL);
				height * 2 - 1;

				colors.push_back({
					scale(topScale, 34, 238) / 255,
					scale(topScale, 139, 233) / 255,
					scale(topScale, 34, 233) / 255
					});
			}
			else
			{
				float topScale = height / SNOW_LEVEL;

				colors.push_back({
					scale(topScale, 160, 34) / 255,
					scale(topScale, 82, 139) / 255,
					scale(topScale, 45, 34) / 255
					});
			}
		});

	return colors;
}



/* Returns the vertices that describe the on-screen shapes */
std::vector<Point> getVertices()
{
	auto model = getModel();
	std::cout << "Triangle count: " << model.size() << std::endl;

	std::vector<Point> vertices;
	for_each (model.begin(), model.end(), //iterate through all the gasket's triangles
		[&](const Triangle& triangle)
		{
			vertices.push_back(triangle.A);
			vertices.push_back(triangle.B);
			vertices.push_back(triangle.C);
		});
	
	std::cout << "Coord count: " << vertices.size() << std::endl;

	return vertices;
}
