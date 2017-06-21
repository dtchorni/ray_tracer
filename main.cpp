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
#include <math.h>

#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Source.h"
#include "Intersection.h"

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
		if(object_intersections.at(0).distance >0){
			return 0;
		}else{
			return -1;
		}
	}
	
	else{
		
		for(int i =0; i < object_intersections.size(); ++i){
			if(m < object_intersections.at(i).distance) m = object_intersections.at(i).distance;
		}
	}

	if(m > 0){
		for(int index =0; index < object_intersections.size(); index++){
			if(object_intersections.at(index).distance > 0 && object_intersections.at(index).distance <= m){
				m = object_intersections.at(index).distance;
				index_of_minimum_value=index;
			}
		}
		return index_of_minimum_value;
	}else{
		return -1;
	}
}


Color getColorAt(Vect intersection_position, Vect intersection_ray_direction, vector<Object*>scene_objects,int index_of_winning_object,vector<Source*> light_sources, double accuracy, double ambientlight){
	
	Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();
	Vect winning_object_normal = scene_objects.at(index_of_winning_object)->getNormal();

	Color final_color = winning_object_color.colorScalar(ambientlight);

	for(int light_index =0; light_index < light_sources.size(); light_index++){
		Vect light_direction = (light_sources.at(light_index)->getPosition() + intersection_position.negative()).normalize() ;

		float cosine_angle = winning_object_normal.dot(light_direction);

		if(cosine_angle>0){
			//test for shadows
			bool shadow = false;
			Vect distance_to_light = (light_sources.at(light_index)->getPosition() + intersection_position.negative()).normalize();
			float distance_to_light_magnitude = distance_to_light.magnitude();

			Ray shadow_ray (intersection_position, (light_sources.at(light_index)->getPosition() + intersection_position.negative()).normalize());

			vector<double> secondary_intersections;
			for(int object_index =0; object_index < scene_objects.size() && shadow==false; object_index++){
				secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_ray));

			}
			for(int c =0; c<secondary_intersections.size(); ++c){
				if(secondary_intersections.at(c) > accuracy){
					if(secondary_intersections.at(c)<=distance_to_light_magnitude){
						shadow =true;
					}

				}
				break;
			}
			if(shadow==false){
				//Color temp =((light_sources.at(light_index)->getColor()).colorScalar(cosine_angle));
				final_color =final_color + (winning_object_color * ((light_sources.at(light_index)->getColor()).colorScalar(cosine_angle)));
				
				if(winning_object_color.getSpecial() > 0 && winning_object_color.getSpecial()<=1){
					//special [0-1]shine
					double dot1 = winning_object_normal.dot(intersection_ray_direction.negative());
					Vect scalar1 = winning_object_normal * dot1;
					Vect add1 = scalar1 + intersection_ray_direction;
					Vect scalar2 = add1 * 2;
					Vect add2 = intersection_ray_direction.negative() + scalar2;
					Vect reflection_direction = add2.normalize();

					double specular = reflection_direction.dot(light_direction);
					if(specular > 0){
						specular = pow(specular,10);
						final_color = final_color + light_sources.at(light_index)->getColor().colorScalar(specular*winning_object_color.getSpecial());
					}
				}
			}
		}

	}

	return final_color;
}


int thisone;

int main(int argc, char *argv[]){
		//cout<<"rendering ..." <<endl;

		int dpi =72;
		int width =200;
		int height =200;

		double aspectratio = (double)width/(double)height;
		double ambientlight =0.2;
		double accuracy =0.000001;

		int n = width*height;

		RGBType *pixels = new RGBType[n];

		Vect X(1,0,0);
		Vect Y(0,1,0);
		Vect Z(0,0,1);
		Vect O(0,0,0);


		/*cam1
		Vect campos(3,1.5,-4);

		Vect lookAt(0,0,0);
		Vect diff_btw(campos.getX() - lookAt.getX(),campos.getY() - lookAt.getY(),campos.getZ() - lookAt.getZ());

		Vect camDir = diff_btw.negative().normalize();
		Vect camRight=Y.cross(camDir).normalize();
		Vect camDown = camRight.cross(camDir).negative();
		Camera scene_cam (campos,camDir,camRight,camDown);
		*/

		
		//cam2

		Vect campos(0,0,1);

		Vect lookAt(0,0,0); 
		Vect diff_btw(campos.getX() -
		lookAt.getX(),campos.getY() - lookAt.getY(),campos.getZ() -
		lookAt.getZ());
		
		Vect camDir = (diff_btw.negative()).normalize(); //Z.negative();
		Vect camRight = Y.cross(camDir).normalize(); //X;
		Vect camDown = Y.negative();//camRight.cross(camDir);
		camDir.print();
		camRight.print();
		camDown.print();
		Camera scene_cam(campos,camDir,camRight,camDown);


		Color white_light (1.0,1.0,1.0,0);
		Color pretty_green(0.5,1.0,0.5,0.3);
		Color maroon(0.5,0.25,0.25,0);
		Color gray(0.5,0.5,0.5,0);
		Color black(0,0,0,0);

		Vect light_position(0,0,1); //Vect light_position(-7,10,-10);

		Light scene_light(light_position,white_light);
		vector<Source*> light_sources;
		light_sources.push_back(dynamic_cast<Source*>(&scene_light));

		
		//scene objects
		Vect s = Vect(0,0,0);
		
		//for cam1
		Sphere scene_sphere(O,0.25,pretty_green);
		Plane scene_plane(Y,-1, maroon);
/*
		//for cam2
		Sphere scene_sphere(s,,pretty_green);
		Plane scene_plane(X,-1,maroon);
*/
		vector<Object*> scene_objects;
				
		//cout<<"sphere is first, plane is second"<<endl;
		scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
		//scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

		double xamnt, yamnt;


		for( int x =0; x< width; x++){
			for(int y =0; y < height; y++){
				thisone = y*width +x;
				
				
				//for cam1
				if(width > height){
					xamnt= ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
					yamnt= ((height -y)+ 0.5)/height;
				}else if(height >width){
						xamnt = (x + 0.5)/width;
						yamnt = (((height - y)+ 0.5)/height)/aspectratio - (((height - width)/(double)width/2));
				}else{
						xamnt = (x + 0.5)/width;
						yamnt = ((height-y)+0.5)/height;
				}


/*						
				//for cam2 assume its square
				double xNDC, yNDC,screenX,screenY,camX,camY;
				xNDC = (x+0.5)/width;
				yNDC = (y+0.5)/height;
				screenX = 2*xNDC-1;
				screenY = 1- 2*yNDC;
				camX = (2*screenX-1)*aspectratio*tan(M_PI/4);
				camY=(1-2*screenY)*tan(M_PI/4);
*/
				

				Vect cam_ray_origin = scene_cam.getCampos();
				Vect cam_ray_direction(camDir + (camRight *(xamnt-0.5))+ (camDown * (yamnt-0.5)));//(camX,camY, -1); // cam2
				cam_ray_direction.normalize();

				////cout<<"origin vector: ";
				//cam_ray_origin.print();
				////cout<<"direction vector: ";
				//cam_ray_direction.print();

				Ray cam_ray (cam_ray_origin, cam_ray_direction);

				vector<Intersection> intersections;
				//cout<<"\nintersections at: "<<x<<" "<<y<<endl;
				for(int index =0; index<scene_objects.size(); ++index){
						Intersection h =scene_objects.at(index)->findIntersection(cam_ray);
						intersections.push_back(h);
						//cout<<"\t"<<h<<" "<<endl;
				}
				//cout<<"end of intersections"<<endl;

				int index_of_winning_object = winningObjectIndex(intersections);

				//cout<<index_of_winning_object;



				if(index_of_winning_object==-1){//background
					pixels[thisone].r=0;
					pixels[thisone].g = 0;
					pixels[thisone].b = 0;
					////cout<<" ";
				}else{//object
					if(intersections.at(index_of_winning_object)>accuracy){
						//determine the position and dircetion at the POI

						Vect intersection_position = cam_ray_origin + (cam_ray_direction * intersections.at(index_of_winning_object));
						Vect intersection_ray_direction = cam_ray_direction;


						Color intersection_color = getColorAt(intersection_position, intersection_ray_direction, scene_objects,index_of_winning_object,light_sources, accuracy,ambientlight);

						pixels[thisone].r=intersection_color.getRed();
						pixels[thisone].g = intersection_color.getGreen();
						pixels[thisone].b = intersection_color.getBlue();

						/*Color this_color = scene_objects.at(index_of_winning_object)->getColor();	//no shading		
						////cout<<"x";

						pixels[thisone].r=this_color.getRed();
						pixels[thisone].g = this_color.getGreen();
						pixels[thisone].b = this_color.getBlue();*/
					}

				}

				
			}
			//cout<<endl;
		}


		savebmp("scene.bmp",width,height,dpi,pixels);

		return 0;
}



