//----------------------------------------------------------------------
// Normal Mapping vertex shader.
// Copyright (C) 2007  Gorka Su�rez Garc�a.
//----------------------------------------------------------------------
varying vec3 LightVec, EyeVec, SpotDir;
varying float Distance;

attribute vec3 Tangent;

//----------------------------------------------------------------------
// Funci�n main del vertex shader.
//----------------------------------------------------------------------
void main()
{
	//------------------------------------------------------------------
	// Primero tomamos la tangente y comprobamos que no invada en
	// cierto modo el espacio de la normal.
	//------------------------------------------------------------------
	vec3 ftang =  normalize(Tangent - (gl_Normal * dot(gl_Normal, Tangent)));
	
	//------------------------------------------------------------------
	// Entonces construimos la matriz formada por la normal, la
	// tangente y la binormal o bitangente.
	//------------------------------------------------------------------
	vec3 n = normalize(gl_NormalMatrix * gl_Normal);
	vec3 t = normalize(gl_NormalMatrix * ftang);
	vec3 b = cross(n, t);
	
	//------------------------------------------------------------------
	// Teniendo dicha matriz calculamos cual es la direcci�n de la luz.
	//------------------------------------------------------------------
	vec3 vertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 tmpvec = gl_LightSource[0].position.xyz - vertex *
				  gl_LightSource[0].position.w;
				  
	Distance = length(tmpvec);
	
	//------------------------------------------------------------------
	// Multiplicamos dicho vector por la matriz de transformaci�n al
	// espacio tangente, para poder usar el mapa de normales.
	//------------------------------------------------------------------
	LightVec.x = dot(tmpvec, t);
	LightVec.y = dot(tmpvec, b);
	LightVec.z = dot(tmpvec, n);
	
	//------------------------------------------------------------------
	// Y calculamos el vector que va del v�rtice, al ojo de la c�mara,
	// con tan solo invertir sus valores. Para luego multiplicarlos por
	// la matriz de transformaci�n al espacio tangente.
	//------------------------------------------------------------------
	tmpvec = -vertex;
	
	EyeVec.x = dot(tmpvec, t);
	EyeVec.y = dot(tmpvec, b);
	EyeVec.z = dot(tmpvec, n);

	//------------------------------------------------------------------
	// Tambien hemos de transformar al espacio tangente la direcci�n
	// del foco de luz, para hacer los c�lculos correctamente.
	//------------------------------------------------------------------
	SpotDir.x = dot(gl_LightSource[0].spotDirection, t);
	SpotDir.y = dot(gl_LightSource[0].spotDirection, b);
	SpotDir.z = dot(gl_LightSource[0].spotDirection, n);

	//------------------------------------------------------------------
	// Y finalmente indicamos las coordenadas de textura y la posici�n
	// final del v�rtice despu�s de ser transformado.
	//------------------------------------------------------------------
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
}
