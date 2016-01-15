//----------------------------------------------------------------------
// Normal Mapping vertex shader.
// Copyright (C) 2007  Gorka Suárez García.
//----------------------------------------------------------------------
varying vec3 LightVec, EyeVec, SpotDir;
varying float Distance;

attribute vec3 Tangent;

//----------------------------------------------------------------------
// Función main del vertex shader.
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
	// Teniendo dicha matriz calculamos cual es la dirección de la luz.
	//------------------------------------------------------------------
	vec3 vertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 tmpvec = gl_LightSource[0].position.xyz - vertex *
				  gl_LightSource[0].position.w;
				  
	Distance = length(tmpvec);
	
	//------------------------------------------------------------------
	// Multiplicamos dicho vector por la matriz de transformación al
	// espacio tangente, para poder usar el mapa de normales.
	//------------------------------------------------------------------
	LightVec.x = dot(tmpvec, t);
	LightVec.y = dot(tmpvec, b);
	LightVec.z = dot(tmpvec, n);
	
	//------------------------------------------------------------------
	// Y calculamos el vector que va del vértice, al ojo de la cámara,
	// con tan solo invertir sus valores. Para luego multiplicarlos por
	// la matriz de transformación al espacio tangente.
	//------------------------------------------------------------------
	tmpvec = -vertex;
	
	EyeVec.x = dot(tmpvec, t);
	EyeVec.y = dot(tmpvec, b);
	EyeVec.z = dot(tmpvec, n);

	//------------------------------------------------------------------
	// Tambien hemos de transformar al espacio tangente la dirección
	// del foco de luz, para hacer los cálculos correctamente.
	//------------------------------------------------------------------
	SpotDir.x = dot(gl_LightSource[0].spotDirection, t);
	SpotDir.y = dot(gl_LightSource[0].spotDirection, b);
	SpotDir.z = dot(gl_LightSource[0].spotDirection, n);

	//------------------------------------------------------------------
	// Y finalmente indicamos las coordenadas de textura y la posición
	// final del vértice después de ser transformado.
	//------------------------------------------------------------------
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
}
