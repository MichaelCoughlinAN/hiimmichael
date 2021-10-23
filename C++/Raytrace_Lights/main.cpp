#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "vec3.h"
#include "object.h"
#include "light.h"
#include "matrix.h"
#include <algorithm>
#include <cstdlib>
#include <stack>
using namespace std;

// #define HEIGHT 480
// #define WIDTH 640
// #define RECURSION_DEPTH 5
// #define TOTAL_SAMPLE 16

struct Camera {
	Vec3 pos;
	Vec3 lookAt;
	Vec3 up;
	double fov;
	int width;
	int height;
	int total_samples;
	int recursion_depth;
};

Camera camera;

/* function for recursive raytracer*/
Vec3 sendRay(Vec3 rayOrigin, Vec3 rayDirection, int level, vector<Object*> objects, vector<Light> lights){
	double intersectPoint = INFINITY;
	bool doesIntersect = false;
	Object* intersectObject = NULL;
	/*checking for nearest intersection*/
	for(vector<Object*>::iterator it = objects.begin() ; it != objects.end(); ++it) {
		double point = (*it)->intersectionPoints(rayOrigin, rayDirection);
		if(point<0) continue;
		else {
			doesIntersect = true;
			if(intersectPoint > point){
				intersectPoint = point;
				intersectObject = (*it);
			}
		}
	}
	/*no intersection => background color*/
	if(!doesIntersect) return Vec3(2);

	/*if there is intersection*/
	Vec3 point = rayOrigin + rayDirection * intersectPoint;
	Vec3 normal = intersectObject->getNormal(point);
	Vec3 finalColor(0);

	bool isIn = false;
	if(normal.dot(rayDirection)>0) {
		/* ray is inside of the object not valide for triangles - for them one side is in*/
		normal = normal * -1;
		isIn = true;
	}

	/*case if specular object and not reached depth of recursion*/
	if(intersectObject->objectType == SPECULAR && level < camera.recursion_depth) {

		Vec3 reflectionDir = rayDirection - (normal * 2 * rayDirection.dot(normal));
		reflectionDir.normalize();
		/*coloring the specular object accoring to direction of ray with respect to normal*/
		double facingratio = -1 * rayDirection.dot(normal);
		double fresneleffect = 0.1 + pow(1 - facingratio, 3) * 0.9;

		/*recursion call for reflected ray*/
		Vec3 reflectionColor = sendRay(point + reflectionDir * 0.01 , reflectionDir, level + 1, objects, lights);

		Vec3 refractionColor(0);
		/*checking for refracting object if yes than recursion call for refraction*/
		if(intersectObject->transparency > 0){
			double n1 = 1;
			double n2 = intersectObject->transparency;
			double n = isIn ? n2/n1 : n1/n2;
			double c1 = -rayDirection.dot(normal);
			double c2 = 1 - (n*n * (1 - c1*c1));

			if(c2 > 0){
				Vec3 refractionDir = (rayDirection * n) +  (normal * (n*c1 - sqrt(c2)));

				refractionDir.normalize();
				refractionColor = sendRay(point + refractionDir * 0.01, refractionDir, level + 1, objects, lights); 
			}
		}
		/*final color -> linear combination of refracted and reflected ray * surface color */
		finalColor += (reflectionColor * fresneleffect + refractionColor * (1- fresneleffect)) * intersectObject->surfaceColor;

	}
	else{
		/*case if diffused object or recursion depth reached*/
		for(vector<Light>::iterator light = lights.begin() ; light != lights.end(); ++light) {
			/*checking if ray from light to object is intervened then shadow else light*/
			Vec3 pos = light->position;
			Vec3 lightDir = point - pos;
			lightDir.normalize();
			bool shadow = false;
			intersectPoint = INFINITY;
			for(vector<Object*>::iterator it = objects.begin() ; it != objects.end(); ++it){
				double point = (*it)->intersectionPoints(pos, lightDir);
				if(point<0) continue;
				else {
					shadow = true;
					if(intersectPoint > point){
						intersectPoint = point;
						intersectObject = (*it);
					}
				}
			}
			if(point == (pos + lightDir * intersectPoint)) shadow = false;
			if(!shadow) {
				lightDir = lightDir * -1;
				double colorFactor = normal.dot(lightDir);
				if(colorFactor > 0){
					/*if diffused object only then phong model for adding up diffused component*/
					finalColor += intersectObject->surfaceColor * light->colors * colorFactor * intersectObject->phongCoeffs.x * (1/(point - pos).length2());
				}
				/*if specular object then specular light is added it shows glossiness*/
				if(intersectObject->objectType == SPECULAR){
					Vec3 V = rayOrigin - point;
					V.normalize();
					double shine = normal.dot((V + lightDir).normalize());
					if(shine > 0){
						shine = pow(shine, 50) * intersectObject->phongCoeffs.y * (1/(point - pos).length2());
						finalColor += intersectObject->surfaceColor * light->colors * shine;
					}
				}
			}
		}
	}
	return finalColor;
}

void init(vector<Object*> objects, vector<Light> lights){
	/*Making view transformation matrix using eye, up vector, look at vector*/
	Vec3 n = (camera.pos - camera.lookAt).normalize();
	Vec3 u = camera.up.cross(n).normalize();
	Vec3 v = n.cross(u);

	Vec3 e;
	e.x = u.dot(camera.pos)*-1;
	e.y = v.dot(camera.pos)*-1;
	e.z = n.dot(camera.pos)*-1;

	/*
	Avw = 
		[u.x, u.y, u.z, e.x]
		[v.x, v.y, v.z, e.y]
		[n.x, n.y, n.z, e.z]
		[ 0,   0, 	0,   1 ]	
	*/
	double V[16] = {u.x, u.y, u.z, e.x, v.x, v.y, v.z, e.y, n.x, n.y, n.z, e.z, 0, 0, 0, 1};
	Matrix viewingTransform(V);

	double aspectRatio = camera.width/(double) camera.height;
	double angle = tan((M_PI/2)*camera.fov/180);

	vector<vector<Vec3> > image(camera.width, vector<Vec3>(camera.height, Vec3()));
	for(int j=0;j<camera.height;++j){
		for(int i=0;i<camera.width;++i){
			image[i][j] = Vec3(0);
			for(int sample = 0; sample<camera.total_samples; sample++){
				/*Random number between pixels for super sampling*/

				double ii = i + rand()/(double)RAND_MAX;
				double jj = j + rand()/(double)RAND_MAX;
				double xx = (2 * ((ii + 0.5) / camera.width) - 1) * angle * aspectRatio;
				double yy = (1 - 2 * ((jj + 0.5) / camera.height)) * angle;
				Vec3 rayDirection(xx, yy, -1);

				/*ray transformation to world coordinate system*/
				rayDirection = viewingTransform.transform(rayDirection, 0);
				rayDirection.normalize();

				/*starting of ray tracer*/
				image[i][j]+= sendRay(Vec3(0), rayDirection, 0, objects, lights);
			}
			image[i][j] = image[i][j] * (1/(double)camera.total_samples);
		}
	}

	/*writing into file image.ppm*/
	ofstream ofs("./image.ppm", ios::out);
	ofs << "P3\n" << camera.width << " " << camera.height << "\n255\n";
	for(int j=0;j<camera.height;j++) {
		for(int i=0;i<camera.width;i++){
			ofs<<int(min(1., image[i][j].x)*255)<<" ";
			ofs<<int(min(1., image[i][j].y)*255)<<" ";
			ofs<<int(min(1., image[i][j].z)*255)<<" ";
		}
		ofs<<endl;
	}
	ofs.close();
}
int main(int argc, char** argv){
	if(argc!=2){
		cout<<"Usage: "<<argv[0]<<" scene_description_file"<<endl;
		return -1;
	}
	/*Opening and parsing of scene description file*/
	ifstream ifs;
	ifs.open(argv[1], ios::in);
	if(!ifs.is_open()) {
		cout<<"Error opening file"<<endl;
		return -1;
	}

	stack <Matrix> transform_stack;
	Matrix current_transform;


	vector<Object*> objects;
	vector<Light> lights;

	while(ifs.good()){
		string type;
		ifs>>type;
		if(type == "LIGHTS") {
			while(ifs.good()){
				ifs>>type;
				if(type=="LIGHT"){
					Vec3 pos;
					Vec3 color;
					ifs>>pos.x>>pos.y>>pos.z>>color.x>>color.y>>color.z;
					lights.push_back(Light(pos,color));
				}
				else{
					break;
				}

			}
		}
		if(type=="CAMERA"){
			while(ifs.good()){
				ifs>>type;
				if(type == "POS"){
					ifs>>camera.pos.x>>camera.pos.y>>camera.pos.z;
				}
				else if(type == "LOOKAT") {
					ifs>>camera.lookAt.x>>camera.lookAt.y>>camera.lookAt.z;
				}
				else if(type == "UP") {
					ifs>>camera.up.x>>camera.up.y>>camera.up.z;
				}
				else if(type == "DIMENSION") {
					ifs>>camera.width>>camera.height;
				}
				else if(type == "FOV") {
					ifs>>camera.fov;
				}
				else if(type == "TOTAL_SAMPLES") {
					ifs>>camera.total_samples;
				}
				else if(type == "RECURSION_DEPTH") {
					ifs>>camera.recursion_depth;
				}
				else{
					break;
				}
			}
		}
		if(type == "ACTION") {
			while(ifs.good()){
				ifs>>type;
				if(type == "LOAD_IDENTITY"){
					while(!transform_stack.empty())
						transform_stack.pop();
					current_transform = Matrix();
				}
				else if(type == "BEGIN"){
					transform_stack.push(current_transform);
				}
				else if(type == "END"){
					current_transform = transform_stack.top();
					transform_stack.pop();
				}
				else if(type == "SCALE"){
					Vec3 val;
					ifs>>val.x>>val.y>>val.z;
					Matrix temp(SCALE, val);
					current_transform = current_transform * temp;
				}
				else if(type == "TRANSLATE"){
					Vec3 val;
					ifs>>val.x>>val.y>>val.z;
					Matrix temp(TRANSLATE, val);
					current_transform = current_transform * temp;
				}
				else if(type == "ROTATEX"){
					double angle;
					ifs>>angle;
					Matrix temp(ROTATEX, angle);
					current_transform = current_transform * temp;
				}
				else if(type == "ROTATEY"){
					double angle;
					ifs>>angle;
					Matrix temp(ROTATEY, angle);
					current_transform = current_transform * temp;
				}
				else if(type == "ROTATEZ"){
					double angle;
					ifs>>angle;
					Matrix temp(ROTATEZ, angle);
					current_transform = current_transform * temp;
				}
				else if(type == "SHEAR"){
					Vec3 val1, val2;
					ifs>>val1.x>>val1.y>>val1.z;
					ifs>>val2.x>>val2.y>>val2.z;
					Matrix temp(SHEAR, val1, val2);
					current_transform = current_transform * temp;
				}
				else if(type == "SPHERE"){
					Vec3 center;
					double radius;
					Vec3 color;
					double transparency;
					Type surface;
					Vec3 phong;
					ifs>>center.x>>center.y>>center.z>>radius>>color.x>>color.y>>color.z>>transparency>>type>>phong.x>>phong.y>>phong.z;
					if(type == "SPECULAR"){
						Sphere* temp = new Sphere(center,radius,color,transparency,SPECULAR,current_transform,phong);
						objects.push_back(temp);
					}
					else{
						Sphere* temp = new Sphere(center,radius,color,transparency,DIFFUSED,current_transform,phong);
						objects.push_back(temp);
					}
				}
				else if(type == "CYLINDER"){
					Vec3 center,upVector;
					double radius,height;
					Vec3 color;
					double transparency;
					Type surface;
					Vec3 phong;
					ifs>>center.x>>center.y>>center.z>>upVector.x>>upVector.y>>upVector.z>>radius>>height>>color.x>>color.y>>color.z>>transparency>>type>>phong.x>>phong.y>>phong.z;
					if(type == "SPECULAR"){
						Cylinder* temp = new Cylinder(center,upVector,radius,height,color,transparency,SPECULAR,current_transform,phong);
						objects.push_back(temp);
					}
					else{
						Cylinder* temp = new Cylinder(center,upVector,radius,height,color,transparency,DIFFUSED,current_transform,phong);
						objects.push_back(temp);
					}
				}
				else if(type == "CONE"){
					Vec3 center,upVector;
					double alpha,height;
					Vec3 color;
					double transparency;
					Type surface;
					Vec3 phong;
					ifs>>center.x>>center.y>>center.z>>upVector.x>>upVector.y>>upVector.z>>alpha>>height>>color.x>>color.y>>color.z>>transparency>>type>>phong.x>>phong.y>>phong.z;
					if(type == "SPECULAR"){
						Cone* temp = new Cone(center,upVector,alpha,height,color,transparency,SPECULAR,current_transform,phong);
						objects.push_back(temp);
					}
					else{
						Cone* temp = new Cone(center,upVector,alpha,height,color,transparency,DIFFUSED,current_transform,phong);
						objects.push_back(temp);
					}
				}
				else if(type == "TRIANGLE"){
					Vec3 p1,p2,p3;
					Vec3 color;
					double transparency;
					Type surface;
					Vec3 phong;
					ifs>>p1.x>>p1.y>>p1.z>>p2.x>>p2.y>>p2.z>>p3.x>>p3.y>>p3.z>>color.x>>color.y>>color.z>>transparency>>type>>phong.x>>phong.y>>phong.z;
					if(type == "SPECULAR"){
						Triangle* temp = new Triangle(p1,p2,p3,color,transparency,SPECULAR,current_transform,phong);
						objects.push_back(temp);
					}
					else{
						Triangle* temp = new Triangle(p1,p2,p3,color,transparency,DIFFUSED,current_transform,phong);
						objects.push_back(temp);
					}
				}
				else {
					break;
				}
			}
		}
		if(type == "CUT"){
			break;
		}
	}
	init(objects, lights);
}