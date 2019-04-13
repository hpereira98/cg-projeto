#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <hash.h>
#include <figure.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;



/**
 Função para realizar escritas no ficheiro passado como argumento
 */
int fileWriter(string file, string content) {
	ofstream myfile;
	myfile.open(file);
	myfile << content;
	myfile.close();
	return 0;
}

/**
Função responsável por calcular os pontos dos dois triângulos que compõem
uma figura do tipo 'plane'
*/
void planeHandler(double size, char* destFile){
    double x1 = size/2;
    double x2 = -1*x1;
    double z1 = size/2;
    double z2 = -1*z1;

    string s = "";
    
    string p1 = to_string(x2) + ",0," + to_string(z2) + "\n";
    string p2 = to_string(x2) + ",0," + to_string(z1) + "\n";
    string p3 = to_string(x1) + ",0," + to_string(z1) + "\n";
    string p4 = to_string(x1) + ",0," + to_string(z2) + "\n";
    
    s.append(p1);
    s.append(p2);
    s.append(p3);
    s.append(p1);
    s.append(p3);
    s.append(p4);
    
	fileWriter(destFile, s);
}

/**
 Função responsável por calcular os pontos dos triângulos que compõem
 uma figura do tipo 'box', centrada na origem
 */
void boxHandler(double x, double y, double z, int d, char* destFile){
	string s="";
	double divY = (double) y / d;
    double divZ = (double) z / d;
    double divX = (double) x / d;
    double x1, y1, z1, x2, y2, z2;

    
    //pontos da base e do topo (diferem no valor y) (faces paralelas ao plano xOz)
    x1=x/2;
    y1=y/2;
    z1=z/2;
    for(int i=0; i<d; i++, x1 -= divX){
        x2 = x1-divX;
        for (int j = 0; j < d; j++, z1 -= divZ) {
            z2 = z1-divZ;
            for(int k=0;k<2;k++){
                if(k==1) {
                    y1*=-1; //simetrico de y para desenhar face oposta
                    x1*=-1; //simetrico de x por causa do vetor normal
                    x2*=-1;
                }
                string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n";
                string p2 = to_string(x1) + "," + to_string(y1) + "," + to_string(z2) + "\n";
                string p3 = to_string(x2) + "," + to_string(y1) + "," + to_string(z1) + "\n";
                string p4 = to_string(x2) + "," + to_string(y1) + "," + to_string(z2) + "\n";
                
                s.append(p1);
                s.append(p2);
                s.append(p3);
                s.append(p3);
                s.append(p2);
                s.append(p4);
            }
    
            y1*=-1; //recuperar valores originais
            x1*=-1;
            x2*=-1;
            
        }
        z1 = z/2;
    }

  
    //pontos das faces paralelas ao plano xOy (diferem no valor z)
    x1 = x/2;
    z1 = z/2;
    y1 = -y/2; // vai ser feito desenho bottom up
    for(int i=0; i<d; i++, x1-=divX){
        x2 = x1-divX;
        for (int j = 0; j < d; j++, y1 += divY) {
            y2 = y1+divY;
            for(int k=0; k<2; k++){
                if(k==1) {
                    z1*=-1; //simetrico de z para desenhar face oposta
                    x1*=-1; //simetrico de x por causa do vetor normal
                    x2*=-1;
                }
            
                string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n"; // A
                string p2 = to_string(x2) + "," + to_string(y2) + "," + to_string(z1) + "\n"; // H
                string p3 = to_string(x2) + "," + to_string(y1) + "," + to_string(z1) + "\n"; // D
                string p4 = to_string(x1) + "," + to_string(y2) + "," + to_string(z1) + "\n"; // E
            
                s.append(p1);
                s.append(p4);
                s.append(p3);
                s.append(p4);
                s.append(p2);
                s.append(p3);
            }
            z1*=-1; // recuperar valores originais
            x1*=-1;
            x2*=-1;
        }
        y1 = -y/2; // volta a começar a desenhar por baixo
    }
    
    x1 = x/2;
    z1 = z/2;
    y1 = -y/2;
    // desenhar faces paralelas ao plano yOz (diferem no valor x)
    for(int i = 0; i < d; i++, z1-=divZ){
        z2 = z1-divZ;
        for (int j = 0; j < d; j++, y1 += divY) {
            y2 = y1+divY;
            for(int k=0; k<2; k++){
                if(k==1) {
                    x1*=-1; //simetrico de x para desenhar face oposta
                    z1*=-1; //simetrico de z por causa do vetor normal
                    z2*=-1;
                }
            
                string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n"; // H - C
                string p2 = to_string(x1) + "," + to_string(y1) + "," + to_string(z2) + "\n"; // D - G
                string p3 = to_string(x1) + "," + to_string(y2) + "," + to_string(z1) + "\n"; // E - B
                string p4 = to_string(x1) + "," + to_string(y2) + "," + to_string(z2) + "\n"; // A - F
            
                s.append(p1);
                s.append(p2);
                s.append(p4);
                s.append(p1);
                s.append(p4);
                s.append(p3);
            
            }
            z1*=-1; // recuperar valores originais
            z2*=-1;
            x1*=-1;
        }
        y1 = -y/2;
    }

	fileWriter(destFile, s);
}

/**
 Função responsável por os pontos dos triângulos que compõem uma figura do tipo 'sphere', centrada
 na origem
 */
void sphereHandler(double raio, int slices, int stacks, char* destFile){
	string s = "";
	double a = 0;
	double stepSide = 2 * M_PI / slices;
	double stepUp = M_PI / stacks;
	double b = 0;

	for (int i = 0; i < slices; i++){
		a = i * stepSide;
		for (int j = 0; j < stacks; j++){
			b = j * stepUp;
            
            double x1 = raio*sin(b)*sin(a);
            double x2 = raio*sin(b + stepUp)*sin(a);
            double x3 = raio*sin(b + stepUp)*sin(a + stepSide);
            double x4 = raio*sin(b)*sin(a + stepSide);
            double y1 = raio*cos(b);
            double y2 = raio*cos(b + stepUp);
            double z1 = raio*sin(b)*cos(a);
            double z2 = raio*sin(b + stepUp)*cos(a);
            double z3 = raio*sin(b + stepUp)*cos(a + stepSide);
            double z4 = raio*sin(b)*cos(a + stepSide);
            
            string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n";
            string p2 = to_string(x2) + "," + to_string(y2) + "," + to_string(z2) + "\n";
            string p3 = to_string(x3) + "," + to_string(y2) + "," + to_string(z3) + "\n";
            string p4 = to_string(x4) + "," + to_string(y1) + "," + to_string(z4) + "\n";
		
			s.append(p1);
			s.append(p2);
			s.append(p3);

			s.append(p1);
			s.append(p3);
            s.append(p4);
		}
	}

	fileWriter(destFile, s);
}

/**
 Função auxiliar ao desenho de uma figura do tipo 'cone'. Calcula os pontos
 dos triângulos que compõem uma slice do cone.
 */
string buildSlice(int stacks, double r, double h, string s, double a, double stepSide, double hips) {
	double stepUp = (double)(h / stacks);
	double stepInside = sqrt((hips*hips) - (stepUp*stepUp));
	double height = 0;
    string p1;
    string p2;
    string p3;
    string p4;
    
	for (int i = 0; i < stacks - 1; i++) {
        double x1 = r*cos(a);
        double x2 = (r - stepInside)*cos(a);
        double x3 = (r - stepInside)*cos(a + stepSide);
        double x4 = r*cos(a + stepSide);
        double y1 = height;
        double y2 = height + stepUp;
        double z1 = r*sin(a);
        double z2 = (r - stepInside)*sin(a);
        double z3 = (r - stepInside)*sin(a + stepSide);
        double z4 = r*sin(a + stepSide);
        
        p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n";
        p2 = to_string(x2) + "," + to_string(y2) + "," + to_string(z2) + "\n";
        p3 = to_string(x3) + "," + to_string(y2) + "," + to_string(z3) + "\n";
        p4 = to_string(x4) + "," + to_string(y1) + "," + to_string(z4) + "\n";
        
        s.append(p1);
        s.append(p2);
        s.append(p3);
        
        s.append(p3);
        s.append(p4);
        s.append(p1);
        
		height += stepUp;
		r -= stepInside;

	}

    // "cobertura" do cone
	s.append("0," + to_string(h) + ",0\n");
    s.append(p3);
    s.append(p2);
    
	return s;
}
/**
 Função responsável por calcular os pontos que formam uma figura do tipo 'cone'.
 */
void coneHandler(double raio, double altura, int slices, int stacks, char* destFile){
	string s;
	double a = 0;
	double step = 2 * M_PI / slices;
	double hip = sqrt((raio*raio) + (altura*altura));
    
	for (int i = 0; i < slices; i++) {
		string x1 = to_string(raio*cos(a));
		string x2 = to_string((raio*cos(a + step)));
		string z1 = to_string(raio * sin(a));
		string z2 = to_string(raio * sin(a + step));
        
		a += step;
		s = buildSlice(stacks, raio, altura, s, a, step, hip / stacks);
		
        // desenhar a base do cone
        s.append("0,0,0\n");
		s.append(x1 + ",0," + z1 +"\n");
        s.append(x2 + ",0," + z2 + "\n");
	}	

	fileWriter(destFile, s);
} 


/**
 Função responsável por calcular os pontos que formam uma figura do tipo 'ring'.
 */
void ringHandler(double r, double R, int slices, char* destFile) {
	string s = "";
	double a = 0;
	double step = 2 * M_PI / slices;

	for (int i = 0; i < slices; i++, a+=step) {
		string x1 = to_string(r * cos(a));
		string z1 = to_string(r * sin(a));
		string x2 = to_string((r * cos(a + step)));		
		string z2 = to_string(r * sin(a + step));
		string x3 = to_string(R * cos(a));
		string z3 = to_string(R * sin(a));
		string x4 = to_string((R * cos(a + step)));
		string z4 = to_string(R * sin(a + step));

		// Draw top
		s.append(x2 + ",0," + z2 + "\n");
		s.append(x1 + ",0," + z1 + "\n");
		s.append(x3 + ",0," + z3 + "\n");

		s.append(x3 + ",0," + z3 + "\n");
		s.append(x4 + ",0," + z4 + "\n");
		s.append(x2 + ",0," + z2 + "\n");

		// Draw bottom
		s.append(x1 + ",0," + z1 + "\n");
		s.append(x2 + ",0," + z2 + "\n");
		s.append(x3 + ",0," + z3 + "\n");

		s.append(x3 + ",0," + z3 + "\n");
		s.append(x2 + ",0," + z2 + "\n");
		s.append(x4 + ",0," + z4 + "\n");
	}

	fileWriter(destFile, s);
}




/********************
*					*
*	   BEZIER		*
*					*
********************/

int nr_patches = 0;
int** patch_indices;
int nr_pts_ctrl;
Point* pts_ctrl;

void cross(float *a, float *b, float *res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float *a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}


float length(float *v) {

	float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return res;

}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void multVectorMatrix(float *v, float *m, float *res) {
	for (int i = 0; i < 4; ++i) {
		res[i] = 0;
		for (int j = 0; j < 4; ++j) {
			res[i] += v[j] * m[j * 4 + i];
		}
	}
}

void multMatrixMatrix(float *m1, float *m2, float *res) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[i * 4 + j] = 0.0f;
			for (int k = 0; k < 4; ++k)
				res[i * 4 + j] += m1[i * 4 + k] * m2[k * 4 + j];
		}
	}
}


int bezierPatchParser(char *patch) {
	string line;
	ifstream file(patch);
	float x, y, z;

	if (!file) return -1;

	// Verifica o número de patches
	getline(file, line);
	nr_patches = atoi((char*)line.c_str());
	if (nr_patches < 1) return -1;
	printf("Numero de patches = %d\n", nr_patches);

	// Preenche array dos indices de cada patch
	patch_indices = (int**)malloc(sizeof(int*) * nr_patches);

	for (int i = 0; i < nr_patches; i++) {
		getline(file, line);
		patch_indices[i] = (int*)malloc(sizeof(int) * 16);

		char* token = strtok((char*)line.c_str(), ",");
		for (int j = 0; j < 16 && token != NULL; token = strtok(NULL, ","), j++) {
			patch_indices[i][j] = atoi(token);
		}
	}

	// Verifica o número de pontos de controlo
	getline(file, line);
	nr_pts_ctrl = atoi((char*)line.c_str());
	if (nr_pts_ctrl < 1) return -1;
	printf("Numero de pontos de controlo = %d\n", nr_pts_ctrl);


	// Preenche o array dos pontos de controlo
	pts_ctrl = (Point*)malloc(sizeof(Point) * nr_pts_ctrl);
	for (int i = 0; i < nr_pts_ctrl; i++) {
		getline(file, line);

		x = atof(strtok((char*)line.c_str(), ","));
		y = atof(strtok(NULL, ","));
		z = atof(strtok(NULL, ","));

		pts_ctrl[i] = *new Point(x, y, z);
	}

	return 1;
}


void getBezierPatchPoint(float u, float v, Point *pts, float *res, float *pNormal, float *coor_contexto) {

	float M[4][4] = { {-1.0f,  3.0f, -3.0f, 1.0f},
					{3.0f, -6.0f,  3.0f, 0.0f},
					{-3.0f,  3.0f,  0.0f, 0.0f},
					{ 1.0f,  0.0f,  0.0f, 0.0f} };

	float U[4] = { u*u*u, u*u, u, 1 };
	float der_U[4] = { 3*u*u, 2*u, 1, 0 };
	float V[4] = { v*v*v, v*v, v, 1 };
	float der_V[4] = { 3*v*v, 2*v, 1, 0 };

	// M * V
	float MV[4];
	float Mder_V[4];
	multMatrixVector((float *)M, V, MV);
	multMatrixVector((float *)M, der_V, Mder_V);

	// U * M 
	float UM[4];
	float der_UM[4];
	multVectorMatrix(U, (float *)M, UM);
	multVectorMatrix(der_U, (float *)M, der_UM);

	// x, y, z
	float Px[4][4] = {
		{ pts[0].getX(), pts[1].getX(), pts[2].getX(), pts[3].getX() },
		{ pts[4].getX(), pts[5].getX(), pts[6].getX(), pts[7].getX() },
		{ pts[8].getX(), pts[9].getX(), pts[10].getX(), pts[11].getX() },
		{ pts[12].getX(), pts[13].getX(), pts[14].getX(), pts[15].getX() }
	};

	float Py[4][4] = {
		{ pts[0].getY(), pts[1].getY(), pts[2].getY(), pts[3].getY() },
		{ pts[4].getY(), pts[5].getY(), pts[6].getY(), pts[7].getY() },
		{ pts[8].getY(), pts[9].getY(), pts[10].getY(), pts[11].getY() },
		{ pts[12].getY(), pts[13].getY(), pts[14].getY(), pts[15].getY() }
	};

	float Pz[4][4] = {
		{ pts[0].getZ(), pts[1].getZ(), pts[2].getZ(), pts[3].getZ() },
		{ pts[4].getZ(), pts[5].getZ(), pts[6].getZ(), pts[7].getZ() },
		{ pts[8].getZ(), pts[9].getZ(), pts[10].getZ(), pts[11].getZ() },
		{ pts[12].getZ(), pts[13].getZ(), pts[14].getZ(), pts[15].getZ() }
	};

	// UM * P 
	float UMP[3][4];
	multVectorMatrix(UM, (float *)Px, UMP[0]);
	multVectorMatrix(UM, (float *)Py, UMP[1]);
	multVectorMatrix(UM, (float *)Pz, UMP[2]);

	float der_UMP[3][4];
	multVectorMatrix(der_UM, (float *)Px, der_UMP[0]);
	multVectorMatrix(der_UM, (float *)Py, der_UMP[1]);
	multVectorMatrix(der_UM, (float *)Pz, der_UMP[2]);

	// UMP * MV 
	float dU[3];
	float dV[3];

	for (int j = 0; j < 3; j++) {
		res[j] = 0.0f;
		dU[j] = 0.0f;
		dV[j] = 0.0f;

		for (int i = 0; i < 4; i++) {
			res[j] += MV[i] * UMP[j][i];
			dU[j] += MV[i] * der_UMP[j][i];
			dV[j] += Mder_V[i] * UMP[j][i];
		}
	}

	normalize(dU);
	normalize(dV);
	cross(dV, dU, pNormal);
	normalize(pNormal);

	coor_contexto[0] = u;
	coor_contexto[1] = v;
}

int bezierPatchGenerator(char* patch_file, int tesselationLevel, char *dest_file) {
	bezierPatchParser(patch_file);
	Point pv[16];
	int divs = tesselationLevel; // change this to change the tesselation level
	string points_str, normals_str, coor_contexto_str;
	string output;


	for (int i = 0; i < nr_patches; i++) {
		for (int j = 0; j < 16; j++) {
			pv[j] = pts_ctrl[patch_indices[i][j]];
		}
		for (int u = 0; u < divs; u++) {
			float resP1[3], pNormal1[3], coor_contexto_1[2];
			float resP2[3], pNormal2[3], coor_contexto_2[2];
			float resP3[3], pNormal3[3], coor_contexto_3[2];
			float resP4[3], pNormal4[3], coor_contexto_4[2];

			for (int v = 0; v < divs; v++) {
				getBezierPatchPoint(u / (float)divs, v / (float)divs, pv, resP1, pNormal1, coor_contexto_1);
				getBezierPatchPoint((u + 1) / (float)divs, v / (float)divs, pv, resP2, pNormal2, coor_contexto_2);
				getBezierPatchPoint(u / (float)divs, (v + 1) / (float)divs, pv, resP3, pNormal3, coor_contexto_3);
				getBezierPatchPoint((u + 1) / (float)divs, (v + 1) / (float)divs, pv, resP4, pNormal4, coor_contexto_4);

				points_str.append(to_string(resP1[0]) + ',' + to_string(resP1[1]) + ',' + to_string(resP1[2]) + '\n');
				points_str.append(to_string(resP3[0]) + ',' + to_string(resP3[1]) + ',' + to_string(resP3[2]) + '\n');
				points_str.append(to_string(resP4[0]) + ',' + to_string(resP4[1]) + ',' + to_string(resP4[2]) + '\n');

				points_str.append(to_string(resP2[0]) + ',' + to_string(resP2[1]) + ',' + to_string(resP2[2]) + '\n');
				points_str.append(to_string(resP1[0]) + ',' + to_string(resP1[1]) + ',' + to_string(resP1[2]) + '\n');
				points_str.append(to_string(resP4[0]) + ',' + to_string(resP4[1]) + ',' + to_string(resP4[2]) + '\n');

				normals_str.append(to_string(pNormal1[0]) + ',' + to_string(pNormal1[1]) + ',' + to_string(pNormal1[2]) + '\n');
				normals_str.append(to_string(pNormal3[0]) + ',' + to_string(pNormal3[1]) + ',' + to_string(pNormal3[2]) + '\n');
				normals_str.append(to_string(pNormal4[0]) + ',' + to_string(pNormal4[1]) + ',' + to_string(pNormal4[2]) + '\n');

				normals_str.append(to_string(pNormal2[0]) + ',' + to_string(pNormal2[1]) + ',' + to_string(pNormal2[2]) + '\n');
				normals_str.append(to_string(pNormal1[0]) + ',' + to_string(pNormal1[1]) + ',' + to_string(pNormal1[2]) + '\n');
				normals_str.append(to_string(pNormal4[0]) + ',' + to_string(pNormal4[1]) + ',' + to_string(pNormal4[2]) + '\n');

				coor_contexto_str.append(to_string(coor_contexto_1[0]) + ',' + to_string(coor_contexto_1[1]) + '\n');
				coor_contexto_str.append(to_string(coor_contexto_3[0]) + ',' + to_string(coor_contexto_3[1]) + '\n');
				coor_contexto_str.append(to_string(coor_contexto_4[0]) + ',' + to_string(coor_contexto_4[1]) + '\n');

				coor_contexto_str.append(to_string(coor_contexto_2[0]) + ',' + to_string(coor_contexto_2[1]) + '\n');
				coor_contexto_str.append(to_string(coor_contexto_1[0]) + ',' + to_string(coor_contexto_1[1]) + '\n');
				coor_contexto_str.append(to_string(coor_contexto_4[0]) + ',' + to_string(coor_contexto_4[1]) + '\n');

			}
		}
	}

	output.append(/*to_string(p) + "\n" + */points_str + normals_str + coor_contexto_str);
	fileWriter(dest_file, output);
	return 0;
}




int main(int argc, char** argv){
	int error_flag = 0; 

	if (argc == 1) return -1;

	switch (hashF(argv[1])){
    	case PLANE:
        	if(argc == 4) planeHandler(atof(argv[2]), argv[3]);
        	else error_flag = 1;
        	break;

    	case BOX:
        	if(argc >= 6){
        		int dim = 1;
				char* fdest = argv[5];
				
				if(argc == 7) { 
					dim = atoi(argv[5]); 
					fdest = argv[6];
				}
				boxHandler(atof(argv[2]), atof(argv[3]), atof(argv[4]), dim, fdest);
        	}
        	else error_flag = 1;
        	break;

    	case SPHERE:
       	 	if(argc == 6) sphereHandler(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
       	 	else error_flag = 1;
        	break;

        case CONE:
       	 	if(argc == 7) coneHandler(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
       	 	else error_flag = 1;
        	break;

		case RING:
			if (argc == 6) ringHandler(atof(argv[2]), atof(argv[3]), atoi(argv[4]), argv[5]);
			else error_flag = 1;
			break;

		case PATCH:
			if(argc == 5) bezierPatchGenerator(argv[2], atoi(argv[3]), argv[4]);
			else error_flag = 1;
			break;

    	default:
			error_flag = 1;
        	break;
    }
    

    if(error_flag) printf("Por favor insira todos os parâmetros necessários. \n");
    else printf("Pontos gerados com sucesso\n");

	return 1;

}

