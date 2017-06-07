#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"

using namespace std;

struct RGBType{ double r; double g; double b; };

void savebmp(const char *filename, int w, int h, int dpi, RGBType *data){
	FILE *f;
	int k = w*h;
	int s =4*k;
	int filesize =54+s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14]={'B','M',0,0,0,0, 0,0,0,0, 54 ,0,0,0};
	unsigned char bmpinfoheader[40]={40,0,0,0,  0,0,0,0,  0,0,0,0 ,1,0,24,0};

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize>>8);
	bmpfileheader[4] = (unsigned char)(filesize>>16);
	bmpfileheader[5] = (unsigned char)(filesize>>24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w>>8);
	bmpinfoheader[6] = (unsigned char)(w>>16);
	bmpinfoheader[7] = (unsigned char)(w>>24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);

	f = fopen(filename,"wb");

	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);

	for(int i =0; i< k; i++){
			RGBType rgb = data[i];
			double red = (data[i].r)*255;
			double green = (data[i].g)*255;
			double blue = (data[i].b)*255;

			unsigned char color[3] = {(int)floor(red),(int)floor(green), (int)floor(blue)};

			fwrite(color,1,3,f);
	}
	fclose(f);


}

int winningObjectIndex(vector<double> object_intersections){
	//return the index of teh winning intersection
	int index_of_minimum_value;
double m = 0;
	//prevent unnecessary calculations
	if(object_intersections.size()==0){ return -1;}
	else if(object_intersections.size()==1) {
		if(object_intersections.at(0)>0){
			return 0;
		}else{
			return -1;
		}
	}
	
	else{
		
		for(int i =0; i < object_intersections.size(); ++i){
			if(m < object_intersections.at(i)) m = object_intersections.at(i);
		}
	}

	if(m > 0){
		for(int index =0; index < object_intersections.size(); index++){
			if(object_intersections.at(index) > 0 && object_intersections.at(index)<= m){
				m = object_intersections.at(index);
				index_of_minimum_value=index;
			}
		}
		return index_of_minimum_value;
	}else{
		return -1;
	}
}

int thisone;

int main(int argc, char *argv[]){
		cout<<"rendering ..." <<endl;

		int dpi =72;
		int width =640;
		int height =480;

		double aspectratio = (double)width/(double)height;

		int n = width*height;

		RGBType *pixels = new RGBType[n];

		Vect X(1,0,0);
		Vect Y(0,1,0);
		Vect Z(0,0,1);
		Vect O(0,0,0);

		Vect campos(3,1.5,-4);

		Vect lookAt(0,0,0);
		Vect diff_btw(campos.getX() - lookAt.getX(),campos.getY() - lookAt.getY(),campos.getZ() - lookAt.getZ());
		
		Vect camDir = (diff_btw.negative()).normalize();
		Vect camRight = Y.cross(camDir).normalize();
		Vect camDown = camRight.cross(camDir);
		Camera scene_cam(campos,camDir,camRight,camDown);

		Color white_light (1.0,1.0,1.0,0);
		Color pretty_green(0.5,1.0,0.5,0.3);
		Color maroon(0.5,0.25,0.25,0);
		Color gray(0.5,0.5,0.5,0);
		Color black(0,0,0,0);

		Vect light_position(-7,10,-10);

		Light scene_light(light_position,white_light);
		
		//scene objects

		//Sphere scene_sphere(O,1,pretty_green);
		Plane scene_plane(Y,-1, maroon);

		vector<Object*> scene_objects;
		//scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
		scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

		double xamnt, yamnt;
		//double scale = tan(deg2rad())


		for( int x =0; x< width; x++){
			for(int y =0; y < height; y++){
				thisone = y*width +x;
				
				//start with no anti-aliasing
				//if(width > height){
					xamnt = (2*((x+0.5)/width)-1)*aspectratio ;
					yamnt = (1 - 2*((y+0.5)/height));
					//xamnt= ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
					//yamnt= ((height -y)+ 0.5)/height;
				/*}else if(height >width){
					xamnt = (x + 0.5)/width;
					yamnt = (((height - y)+ 0.5)/height)/aspectratio - (((height - width)/(double)width/2));
				}else{
					xamnt = (x + 0.5)/width;
					yamnt = ((height-y)+0.5)/height;
				}*/

				Vect cam_ray_origin = scene_cam.getCampos();
				Vect cam_ray_direction = camDir + (camRight *(xamnt-0.5)+ (camDown * (yamnt-0.5))).normalize();

				Ray cam_ray (cam_ray_origin, cam_ray_direction);

				vector<double> intersections;

				for(int index =0; index<scene_objects.size(); ++index){
						intersections.push_back(scene_objects.at(index)->findIntersection(cam_ray));
				}

				int index_of_winning_object = winningObjectIndex(intersections);

				cout<<index_of_winning_object;

				if(index_of_winning_object==-1){//background
					pixels[thisone].r=0;
					pixels[thisone].g = 0;
					pixels[thisone].b = 0;
				}else{//object
					Color this_color = scene_objects.at(index_of_winning_object)->getColor();			

					pixels[thisone].r=this_color.getRed();
					pixels[thisone].g = this_color.getGreen();
					pixels[thisone].b = this_color.getBlue();
				}

				
			}
		}


		savebmp("scene.bmp",width,height,dpi,pixels);

		return 0;
}