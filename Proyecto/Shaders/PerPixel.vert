//----------------------------------------------------------------------
// Per-pixel Lighting vertex shader.
// Copyright (C) 2007  Gorka Su�rez Garc�a.
//----------------------------------------------------------------------
varying vec3 Normal, LightDir, HalfVector;
varying float Distance;

//----------------------------------------------------------------------
// Funci�n main del vertex shader.
//----------------------------------------------------------------------
void main()
{
	//------------------------------------------------------------------
	// Existe dos posibilidades para la luz al procesar los v�rtices,
	// la primera que sea una luz direccional, y la segunda, que sea
	// una luz posicional. Para ello hay que mirar la componente w.
	//------------------------------------------------------------------
	if(gl_LightSource[0].position.w == 0.0)
	{
		//--------------------------------------------------------------
		// En el caso de que sea una luz direccional, tan solo
		// tendremos que coger su direcci�n para interpolarla. Sin
		// embargo no nos har� falta interpolar la distancia.
		//--------------------------------------------------------------
		LightDir = normalize(gl_LightSource[0].position.xyz);
		Distance = 1.0;
	}
	else
	{
		//--------------------------------------------------------------
		// Para una luz posicional calcularemos la posici�n final del
		// v�rtice en el espacio, y se la restaremos a la posici�n de
		// la luz. Obteniendo el vector que va del v�rtice a la luz.
		//--------------------------------------------------------------
		vec4 vpos = gl_ModelViewMatrix * gl_Vertex;
		vec3 auxld = vec3(gl_LightSource[0].position - vpos);
		
		//--------------------------------------------------------------
		// Ese vector ser� la direcci�n reflejada de la luz sobre el
		// v�rtice, y tambi�n nos dar� la distancia con la luz.
		//--------------------------------------------------------------
		LightDir = normalize(auxld);
		Distance = length(auxld);
	}

	//------------------------------------------------------------------
	// Preparamos la normal y el vector medio para que sean
	// interpolados al calcular la iluminaci�n de cada pixel.
	//------------------------------------------------------------------
	Normal     = normalize(gl_NormalMatrix * gl_Normal);
	HalfVector = normalize(gl_LightSource[0].halfVector.xyz);

	//------------------------------------------------------------------
	// Y finalmente indicamos las coordenadas de textura y la posici�n
	// final del v�rtice despu�s de ser transformado.
	//------------------------------------------------------------------
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
}
