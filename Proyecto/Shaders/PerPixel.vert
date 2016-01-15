//----------------------------------------------------------------------
// Per-pixel Lighting vertex shader.
// Copyright (C) 2007  Gorka Suárez García.
//----------------------------------------------------------------------
varying vec3 Normal, LightDir, HalfVector;
varying float Distance;

//----------------------------------------------------------------------
// Función main del vertex shader.
//----------------------------------------------------------------------
void main()
{
	//------------------------------------------------------------------
	// Existe dos posibilidades para la luz al procesar los vértices,
	// la primera que sea una luz direccional, y la segunda, que sea
	// una luz posicional. Para ello hay que mirar la componente w.
	//------------------------------------------------------------------
	if(gl_LightSource[0].position.w == 0.0)
	{
		//--------------------------------------------------------------
		// En el caso de que sea una luz direccional, tan solo
		// tendremos que coger su dirección para interpolarla. Sin
		// embargo no nos hará falta interpolar la distancia.
		//--------------------------------------------------------------
		LightDir = normalize(gl_LightSource[0].position.xyz);
		Distance = 1.0;
	}
	else
	{
		//--------------------------------------------------------------
		// Para una luz posicional calcularemos la posición final del
		// vértice en el espacio, y se la restaremos a la posición de
		// la luz. Obteniendo el vector que va del vértice a la luz.
		//--------------------------------------------------------------
		vec4 vpos = gl_ModelViewMatrix * gl_Vertex;
		vec3 auxld = vec3(gl_LightSource[0].position - vpos);
		
		//--------------------------------------------------------------
		// Ese vector será la dirección reflejada de la luz sobre el
		// vértice, y también nos dará la distancia con la luz.
		//--------------------------------------------------------------
		LightDir = normalize(auxld);
		Distance = length(auxld);
	}

	//------------------------------------------------------------------
	// Preparamos la normal y el vector medio para que sean
	// interpolados al calcular la iluminación de cada pixel.
	//------------------------------------------------------------------
	Normal     = normalize(gl_NormalMatrix * gl_Normal);
	HalfVector = normalize(gl_LightSource[0].halfVector.xyz);

	//------------------------------------------------------------------
	// Y finalmente indicamos las coordenadas de textura y la posición
	// final del vértice después de ser transformado.
	//------------------------------------------------------------------
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
}
