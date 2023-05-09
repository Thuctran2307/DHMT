#include <iostream>

#include <stdlib.h>

#include<iomanip>

#include <stdlib.h>

#include <windows.h>

#include <GL/glut.h>

#include<math.h> 

using namespace std;

 

const int VERTEX = 8;

GLfloat left_val,right_val,top_val,bottom_val,zNear,zFar;
const float _angle = 13.0f;

GLfloat V[VERTEX][3];
GLfloat LookAt[3][3] = {
							{1,1,5},
							{0,0,0},
							{0,1,0}
						};

//Initializes 3D rendering

void initRendering()

{
    glEnable(GL_DEPTH_TEST);

}

 

 

void Square(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]){

    glBegin(GL_POLYGON);

    glVertex3fv(A);

    glVertex3fv(B);

    glVertex3fv(C);

    glVertex3fv(D);

    glEnd();

}

 

void Cube(GLfloat V0[],GLfloat V1[],GLfloat V2[],GLfloat V3[],GLfloat V4[],GLfloat V5[],GLfloat V6[],GLfloat V7[]) {

    //front

    glColor3f(1,0,0);

    Square(V0,V1,V2,V3);

   

    //back

    glColor3f(0,1,1);

    Square(V4,V5,V6,V7);

   

    //left_val

    glColor3f(0,1,0);

    Square(V0,V4,V7,V3);

   

    //right_val

    glColor3f(0,0,1);

    Square(V1,V5,V6,V2);

   

    //down

    glColor3f(1,1,0);

    Square(V3,V2,V7,V6);

   

    //top_val

    glColor3f(1,1,1);

    Square(V0,V1,V5,V4);

}

 

//print coordinate of vertexs of cube

void printVertexCoodinates (GLfloat V[][3]) {

    for (int i = 0; i <VERTEX ; i++){

          cout<<"Vertex "<<i+1<<": ";

          for (int j = 0; j <3; j ++){

                cout<<setprecision(2)<<setw(10)<<V[i][j] ;

          }

          cout<<endl;

    }

    cout<<endl;

}

 

//void printTransformMatrix

void printTransferMatrix(GLfloat matrix[4][4]) {

    cout<<"Transfer matrix:"<<endl;

    for (int i = 0; i <4 ; i++){

    cout<<"|";

    for (int j = 0; j <4; j ++){

          cout<<setprecision(2)<<setw(5)<<matrix[i][j] ;

    }

    cout<<"|"<<endl;

    }

}

 

// multiply transfer matrix with vecto

void matrixMultiply(GLfloat mat1[4][4], GLfloat input[3], GLfloat res[3])

{

    GLfloat prepareMatrix[4] = {input[0],input[1],input[2],1}; 

    GLfloat resultMatrix[4];

    GLfloat sum = 0;

    for (int row = 0 ; row < 4; row++) {

          for (int col = 0 ; col <4 ; col++) {

                sum += mat1[row][col] * prepareMatrix[col];

          }

          resultMatrix[row] = sum;

          sum =0;

    }

   

    for (int i = 0; i< 3; i ++){

          res[i] = resultMatrix[i]/resultMatrix[3];

    }

}
	GLfloat AbsVector(GLfloat a[3]){
    	return sqrtf(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
	}

 	void multiplyMatrix(GLfloat A[][4], GLfloat B[][4], GLfloat C[][4]) {
    	for (int i = 0; i < 4; i++) {
        	for (int j = 0; j < 4; j++) {
            	for (int k = 0; k < 4; k++) {
                	C[i][j] += A[i][k] * B[k][j];
            	}	
        	}
    	}
	}
void orthoTransferMatrix(GLfloat left_val, GLfloat right_val, GLfloat bottom_val, GLfloat top_val, GLfloat zNear, GLfloat zFar, GLfloat V[][3]) {

    GLfloat tx = - (right_val+left_val)/(right_val -left_val);

    GLfloat ty = - (top_val+bottom_val)/(top_val-bottom_val);

    GLfloat tz = - (zFar+zNear)/(zFar-zNear);

    GLfloat transferMatrix[4][4] = {

                                                    {2/(right_val-left_val), 0,0,tx},

                                                    {0, 2/(top_val-bottom_val),0,ty},

                                                    {0, 0,-2/(zFar-zNear),tz},

                                                    {0, 0,0,1},

                                                    };

 

    //print transfer matrix

    printTransferMatrix(transferMatrix);


    // Declare matrix to save all vertex after handle
	GLfloat vertex[VERTEX][3];
     
     //multiply all coodinates of vertex of cube with transferMatrix

     for(int row =0 ;row < VERTEX ; row ++) {

          matrixMultiply(transferMatrix, V[row],vertex[row]);

     }

     // draw cube after handle projection

     Cube(vertex[0],vertex[1],vertex[2],vertex[3],vertex[4],vertex[5],vertex[6], vertex[7]);

}

// change camera
void gluLookat(){
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable(GL_DEPTH_TEST);
		

		GLfloat rs[4][4];
	    GLfloat M[4][4];
	    GLfloat N[3];
	    GLfloat U[3];
	    GLfloat V[3];
	    GLfloat I[4][4];
	    GLfloat scale[4][4];
	    
	    for(int i =0; i < 4 ; i++){
	    	for(int j =0; j < 4 ; j++){
	    		scale[i][j] = (i==j);
	    	}
	    }
	    
	    
	    // bien doi ty le
	    GLfloat V1[VERTEX][3];
	    GLfloat sx,sy,sz;
	    cout<<"Nhap he so ty le theo x y z: ";
	    cin>>sx>>sy>>sz;
	    scale[0][0] = sx;

    	scale[1][1] = sy;

    	scale[2][2] = sz;
    	for(int row =0 ;row < VERTEX ; row ++) {	
	          matrixMultiply(scale, ::V[row],V1[row]);
	
	     }
    	
    	
    	
	    //------------------------------------------
	    
	    
	    cout<<"Nhap thong so bien doi vi tri quan sat & diem nhin (toa do cam | diem nhin): "<<endl;
	    for(int i = 0; i < 2; i++){
	    	for(int j = 0; j <3; j++){
	    		cin >> LookAt[i][j];
	    	}
	    }
	    //Vecto N
	    for(int i = 0; i < 3 ; i++){
	    	N[i] = LookAt[0][i] - LookAt[1][i];
	    }
	    GLfloat a = AbsVector(N);
	    for(int i = 0; i < 3 ; i++){
	    	N[i] /= a;
	    }
	    //Vecto U
	    U[0] = LookAt[2][1]*N[2] - N[1]*LookAt[2][2];
	    U[1] = LookAt[2][2]*N[0] - N[2]*LookAt[2][0];
	    U[2] = LookAt[2][0]*N[1] - N[0]*LookAt[2][1];
	    a = AbsVector(U);
	    for(int i = 0; i < 3 ; i++){
	    	U[i] /= a;
	    }
	    //Vecto V
		V[0] = N[1]*U[2] - U[1]*N[2];
	    V[1] = N[2]*U[0] - U[2]*N[0];
	    V[2] = N[0]*U[1] - U[0]*N[1];
	    a = AbsVector(V);
	    for(int i = 0; i < 3 ; i++){
	    	V[i] /= a;
	    }
	    
	    // thiet lap ma tran M
	    for(int i =0; i<4; i++){
	    	for(int j =0; j<4;j++){
	    		M[i][j] = 0;
	    	}
	    }
	    for(int i = 0; i < 3; i++){
	    	M[0][i] = U[i];
	    }
	    for(int i = 0; i < 3; i++){
	    	M[1][i] = V[i];
	    }
	    for(int i = 0; i < 3; i++){
	    	M[2][i] = N[i];
	    }
	    M[3][3]=1;
	    
	    
	    
	    // ma tran don vi
	    for(int i = 0; i<4; i++){
	    	for(int j = 0;j<4; j++) I[i][j] = (i==j);
	    }
	    for(int i = 0; i<3; i++){
	    	I[i][3] = -LookAt[0][i];
	    }
	    // tinh ma tran bien doi
	    for(int i =0; i<4; i++){
	    	for(int j =0; j<4;j++){
	    		rs[i][j] = 0;
	    	}
		}
	    multiplyMatrix(M,I,rs);	
	    cout<<"Ma tran bien doi cam: "<<endl;
	    printTransferMatrix(rs);

     	GLfloat vertex[VERTEX][3];
     	
		GLfloat V2[VERTEX][3];
	     //multiply all coodinates of vertex of cube with transferMatrix
	     for(int row =0 ;row < VERTEX ; row ++) {	
	          matrixMultiply(rs, V1[row],V2[row]);
	
	     }
	     //--------------
	     
	    GLfloat tx = - (right_val+left_val)/(right_val -left_val);

	    GLfloat ty = - (top_val+bottom_val)/(top_val-bottom_val);
	
	    GLfloat tz = - (zFar+zNear)/(zFar-zNear);
	
	    GLfloat transferMatrix[4][4] = {
	
	                                                    {2/(right_val-left_val), 0,0,tx},
	
	                                                    {0, 2/(top_val-bottom_val),0,ty},
	
	                                                    {0, 0,-2/(zFar-zNear),tz},
	
	                                                    {0, 0,0,1},
	
	                                                    };

	    // Declare matrix to save all vertex after handle
		GLfloat V3[VERTEX][3];
		cout<<"Ma tran chieu song song : "<<endl;
     	printTransferMatrix(transferMatrix);
	     //multiply all coodinates of vertex of cube with transferMatrix
	
	     for(int row =0 ;row < VERTEX ; row ++) {
	
	          matrixMultiply(transferMatrix, V2[row],V3[row]);
	
	     }
	     Cube(V3[0],V3[1],V3[2],V3[3],V3[4],V3[5],V3[6], V3[7]);
	     glutSwapBuffers();
}
float cot( float alpha) {

    return cos(alpha)/sin(alpha);

}

// change angle
void changeViewAngle(){
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable(GL_DEPTH_TEST);

		GLfloat rs[4][4];
	    GLfloat M[4][4];
	    GLfloat N[3];
	    GLfloat U[3];
	    GLfloat V[3];
	    GLfloat I[4][4];
	    cout<<"Nhap vecto huong len):"<<endl;
	    
	    for(int j = 0; j <3; j++){
	    		cin >> LookAt[2][j];
	    	}

	    
	    //Vecto N
	    for(int i = 0; i < 3 ; i++){
	    	N[i] = LookAt[0][i] - LookAt[1][i];
	    }
	    GLfloat a = AbsVector(N);
	    for(int i = 0; i < 3 ; i++){
	    	N[i] /= a;
	    }
	    //Vecto U
	    U[0] = LookAt[2][1]*N[2] - N[1]*LookAt[2][2];
	    U[1] = LookAt[2][2]*N[0] - N[2]*LookAt[2][0];
	    U[2] = LookAt[2][0]*N[1] - N[0]*LookAt[2][1];
	    a = AbsVector(U);
	    for(int i = 0; i < 3 ; i++){
	    	U[i] /= a;
	    }
	    //Vecto V
		V[0] = N[1]*U[2] - U[1]*N[2];
	    V[1] = N[2]*U[0] - U[2]*N[0];
	    V[2] = N[0]*U[1] - U[0]*N[1];
	    a = AbsVector(V);
	    for(int i = 0; i < 3 ; i++){
	    	V[i] /= a;
	    }
	    
	    // thiet lap ma tran M
	    for(int i =0; i<4; i++){
	    	for(int j =0; j<4;j++){
	    		M[i][j] = 0;
	    	}
	    }
	    for(int i = 0; i < 3; i++){
	    	M[0][i] = U[i];
	    }
	    for(int i = 0; i < 3; i++){
	    	M[1][i] = V[i];
	    }
	    for(int i = 0; i < 3; i++){
	    	M[2][i] = N[i];
	    }
	    M[3][3]=1;
	    
	    
	    
	    // ma tran don vi
	    for(int i = 0; i<4; i++){
	    	for(int j = 0;j<4; j++) I[i][j] = (i==j);
	    }
	    for(int i = 0; i<3; i++){
	    	I[i][3] = -LookAt[0][i];
	    }
	    // tinh ma tran bien doi
	    for(int i =0; i<4; i++){
	    	for(int j =0; j<4;j++){
	    		rs[i][j] = 0;
	    	}
		}
	    multiplyMatrix(M,I,rs);
	    cout<<"Ma tran bien doi camera: "<<endl;
	    printTransferMatrix(rs);

     	GLfloat vertex[VERTEX][3];

	     //multiply all coodinates of vertex of cube with transferMatrix
	     for(int row =0 ;row < VERTEX ; row ++) {	
	          matrixMultiply(rs, ::V[row],vertex[row]);
	
	     }
	     //--------------
	     
	     
	    GLfloat tx = - (right_val+left_val)/(right_val -left_val);

	    GLfloat ty = - (top_val+bottom_val)/(top_val-bottom_val);
	
	    GLfloat tz = - (zFar+zNear)/(zFar-zNear);
	
	    GLfloat transferMatrix[4][4] = {
	
	                                                    {2/(right_val-left_val), 0,0,tx},
	
	                                                    {0, 2/(top_val-bottom_val),0,ty},
	
	                                                    {0, 0,-2/(zFar-zNear),tz},
	
	                                                    {0, 0,0,1},
	
	                                                    };
		
	    // Declare matrix to save all vertex after handle
	    cout<<"Ma tran chieu song song: "<<endl;
	    printTransferMatrix(transferMatrix);
		GLfloat kq[VERTEX][3];
	     //multiply all coodinates of vertex of cube with transferMatrix
	
	     for(int row =0 ;row < VERTEX ; row ++) {
	
	          matrixMultiply(transferMatrix, vertex[row],kq[row]);
	
	     }
	     
	     
	     Cube(kq[0],kq[1],kq[2],kq[3],kq[4],kq[5],kq[6], kq[7]);
	     glutSwapBuffers();
}


// calculate cotan


void drawOrthoGraphic(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode(GL_MODELVIEW);

    cout<<"left_val !=right_val, bottom_val !=top_val, zNear!= zFar"<<endl;

    cout<<"left_val: "; cin>>left_val;

    cout<<"right_val: "; cin>>right_val;

    cout<<"bottom_val: "; cin>>bottom_val;

    cout<<"top_val: "; cin>>top_val;

    cout<<"zNear: "; cin>>zNear;

    cout<<"zFar: "; cin>>zFar;

    orthoTransferMatrix(left_val,right_val,bottom_val,top_val,zNear,zFar,V);

    glutSwapBuffers();

}

 

void setCubeCoodinate( GLfloat V[VERTEX][3]){

    GLfloat a;

    cout<<"Nhap do dai canh hinh lap phuong:";

    cin>>a;

 

    V[0][0] = -a/2; V[0][1] = a/2; V[0][2] = a/2;

    V[1][0] = a/2; V[1][1] = a/2; V[1][2] = a/2;

    V[2][0] = a/2; V[2][1] = -a/2; V[2][2] = a/2;

    V[3][0] = -a/2; V[3][1] = -a/2; V[3][2] = a/2;

    V[4][0] = -a/2; V[4][1] = a/2; V[4][2] = -a/2;

    V[5][0] = a/2; V[5][1] = a/2; V[5][2] = -a/2;

    V[6][0] = a/2; V[6][1] = -a/2; V[6][2] = -a/2;

    V[7][0] = -a/2; V[7][1] = -a/2; V[7][2] = -a/2;

   

    cout<<"Coodinate of cube:"<<endl;

    printVertexCoodinates(V);

}

void DrawCube(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode(GL_MODELVIEW);
     Cube(V[0],V[1],V[2],V[3],V[4],V[5],V[6], V[7]);
    glutSwapBuffers();
}

void displayAll() {
	
	DrawCube();
	cout<<"Chieu song song:"<<endl;
    drawOrthoGraphic(); // v? h?nh ?ng v?i l?nh 1
    cout<<"Thay doi goc quan sat:"<<endl;
    changeViewAngle(); // v? h?nh ?ng v?i l?nh 2
    cout<<"Thay doi vi tri quan sat va diem nhin:"<<endl;
    gluLookat(); // v? h?nh ?ng v?i l?nh 3
}


 
int main(int argc, char **argv)

{

    //Initialize GLUT

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowSize(800, 800);
	glutInitWindowPosition(300,200);
 

 
	setCubeCoodinate(V);
    //Create the window

    glutCreateWindow("Cube");

    initRendering();
	glutDisplayFunc(displayAll);
	glutMainLoop();
    

	

    return 0;

}

 
