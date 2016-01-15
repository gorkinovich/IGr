//******************************************************************************************
// Gorka Suárez García - Ing. Tec. Inf. de Gestión 2º B.
// Práctica 02 - Apartado 03.
//******************************************************************************************
#ifndef _DATA_H_
#define _DATA_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "Yukino/Yukino.h"
using namespace Yukino;
//******************************************************************************************
// Tipo figura
//******************************************************************************************
#define TYPE_CUBE          0 // void auxSolidCube         (GLdouble);
#define TYPE_SPHERE        1 // void auxSolidSphere       (GLdouble);
#define TYPE_BOX           2 // void auxSolidBox          (GLdouble, GLdouble, GLdouble);
#define TYPE_TORUS         3 // void auxSolidTorus        (GLdouble, GLdouble);
#define TYPE_CYLINDER      4 // void auxSolidCylinder     (GLdouble, GLdouble);
#define TYPE_ICOSAHEDRON   5 // void auxSolidIcosahedron  (GLdouble);
#define TYPE_OCTAHEDRON    6 // void auxSolidOctahedron   (GLdouble);
#define TYPE_TETRAHEDRON   7 // void auxSolidTetrahedron  (GLdouble);
#define TYPE_DODECAHEDRON  8 // void auxSolidDodecahedron (GLdouble);
#define TYPE_CONE          9 // void auxSolidCone         (GLdouble, GLdouble);
#define TYPE_TEAPOT       10 // void auxSolidTeapot       (GLdouble);

typedef struct
{
	int Type;
	GLfloat Param1;
	GLfloat Param2;
	GLfloat Param3;
	
	GLfloat X;
	GLfloat Y;
	GLfloat Z;
	
	GLfloat R;
	GLfloat G;
	GLfloat B;
	
	GLfloat Yaw;
} tAuxObject;
//******************************************************************************************
// Clase GameData
//******************************************************************************************
class GameData
{
private:
	GameData ();
	
	
	static GameData * Instance;


	unsigned int Font;
	unsigned int Font3D;

	GLfloat RadarAngle;
	
	GLfloat Yaw;   // Giro sobre el eje y (izquierda-derecha).
	GLfloat Pitch; // Giro sobre el eje x (arriba-abajo).


public:
	~GameData ();


	void Init (void);
	void Release (void);
	void PrintString (GLfloat x, GLfloat y, char * str);
	void PrintString3D (GLfloat x, GLfloat y, char * str);
	void IncRadarAngle (void);

	void IncYaw (void);
	void DecYaw (void);
	
	void IncPitch (void);
	void DecPitch (void);

	void GotoCamera (void);

	void MoveForward (void);
	void MoveBackward (void);
	void StrafeLeft (void);
	void StrafeRight (void);


	Point3D TankPosition;
	Point3D EnemyPosition;

	vector<tAuxObject> Objects;


	void SetRadarAngle (GLfloat val) { RadarAngle = val; }


	GLfloat GetRadarAngle (void) { return RadarAngle; }

	GLfloat GetYaw   (void) { return Yaw;   }
	GLfloat GetPitch (void) { return Pitch; }


	static GameData * GetInstance (void);
};
//******************************************************************************************
#endif
//******************************************************************************************
// Data.h
//******************************************************************************************