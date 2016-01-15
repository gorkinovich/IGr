//----------------------------------------------------------------------
// Parallax Mapping vertex shader.
// Copyright (C) 2007  Gorka Su�rez Garc�a.
//----------------------------------------------------------------------
varying vec3 LightVec, EyeVec, SpotDir;
varying float Distance;

uniform float ScaleBiasFactor[2];
uniform sampler2D colorMap, normalMap, heightMap;

//----------------------------------------------------------------------
// Variables globales.
//----------------------------------------------------------------------
vec4 Specular, Diffuse, Ambient, AmbientLM;
vec4 Texel;
vec3 lVec, vVec, Normal;

//----------------------------------------------------------------------
// Funci�n para calcular la iluminaci�n de una luz direccional.
//----------------------------------------------------------------------
void CalcDirLight()
{
	//------------------------------------------------------------------
	// Lo primero es calcular la luz ambiental para el pixel.
	//------------------------------------------------------------------
	vec4 color = (Ambient + AmbientLM) * Texel;
	
	//------------------------------------------------------------------
	// Despu�s necesitamos con el producto escalar entre la normal y
	// la direcci�n de la luz, obtener la intensidad con la que la luz
	// incide en el pixel actual.
	//------------------------------------------------------------------
	float NdotL = max(dot(Normal, lVec), 0.0);

	//------------------------------------------------------------------
	// Siempre que la intensidad sea mayor que cero, el pixel en
	// cuesti�n estar� de cara a la luz, as� que echaremos las cuentas
	// para la luz difusa y la especular.
	//------------------------------------------------------------------
	if (NdotL > 0.0)
	{
		//--------------------------------------------------------------
		// Para obtener la intensidad de la luz, cogemos la intensidad
		// plena para la difusa, la multiplicamos por la incidencia de
		// la luz, y por el valor del pixel.
		//--------------------------------------------------------------
		color += Diffuse * NdotL * Texel;
		
		//--------------------------------------------------------------
		// Despu�s calculamos la luz especular.
		//--------------------------------------------------------------
		color += Specular * pow(max(dot(reflect(-lVec, Normal), vVec),
									0.0), gl_FrontMaterial.shininess);
	}

	//------------------------------------------------------------------
	// Por �ltimo tomanos el color resultante y le sumamos el
	// componente de emisi�n del material.
	//------------------------------------------------------------------
	gl_FragColor = color + gl_FrontMaterial.emission;
}

//----------------------------------------------------------------------
// Funci�n para calcular la iluminaci�n de una luz posicional.
//----------------------------------------------------------------------
void CalcPosLight()
{
	//------------------------------------------------------------------
	// Lo primero es calcular la luz ambiental global para el pixel.
	//------------------------------------------------------------------
	vec4 color = AmbientLM * Texel;
	
	//------------------------------------------------------------------
	// Despu�s necesitamos con el producto escalar entre la normal y
	// la direcci�n de la luz, obtener la intensidad con la que la luz
	// incide en el pixel actual.
	//------------------------------------------------------------------
	float NdotL = max(dot(Normal, lVec), 0.0);

	//------------------------------------------------------------------
	// Siempre que la intensidad sea mayor que cero, el pixel en
	// cuesti�n estar� de cara a la luz, as� que echaremos las cuentas
	// para la luz difusa y la especular.
	//------------------------------------------------------------------
	if (NdotL > 0.0)
	{
		//--------------------------------------------------------------
		// Calculamos la atenuaci�n en base a la distancia.
		//--------------------------------------------------------------
		float att = 1.0 / (gl_LightSource[0].constantAttenuation +
			gl_LightSource[0].linearAttenuation * Distance +
			gl_LightSource[0].quadraticAttenuation * Distance * Distance);
			
		//--------------------------------------------------------------
		// Con la atenuaci�n podemos calcular, tanto la luz ambiental,
		// como la difusa, para el pixel actual.
		//--------------------------------------------------------------
		color += att * (Diffuse * NdotL + Ambient) * Texel;
	
		//--------------------------------------------------------------
		// Despu�s calculamos la luz especular, teniendo en cuenta
		// ahora tambi�n la atenuaci�n.
		//--------------------------------------------------------------
		color += att * Specular * pow(max(dot(reflect(-lVec, Normal),
									vVec), 0.0), gl_FrontMaterial.shininess);
	}

	//------------------------------------------------------------------
	// Por �ltimo tomanos el color resultante y le sumamos el
	// componente de emisi�n del material.
	//------------------------------------------------------------------
	gl_FragColor = color + gl_FrontMaterial.emission;
}

//----------------------------------------------------------------------
// Funci�n para calcular la iluminaci�n de una luz focal.
//----------------------------------------------------------------------
void CalcSpotLight()
{
	//------------------------------------------------------------------
	// Lo primero es calcular la luz ambiental global para el pixel.
	//------------------------------------------------------------------
	vec4 color = AmbientLM * Texel;
	
	//------------------------------------------------------------------
	// Despu�s necesitamos con el producto escalar entre la normal y
	// la direcci�n de la luz, obtener la intensidad con la que la luz
	// incide en el pixel actual.
	//------------------------------------------------------------------
	float NdotL = max(dot(Normal, lVec), 0.0);

	//------------------------------------------------------------------
	// Siempre que la intensidad sea mayor que cero, el pixel en
	// cuesti�n estar� de cara a la luz, as� que echaremos las cuentas
	// para la luz difusa y la especular.
	//------------------------------------------------------------------
	if(NdotL > 0.0)
	{
		//--------------------------------------------------------------
		// Calculamos el coseno del �ngulo entre el vector de la
		// direcci�n de la luz, y el de la direcci�n del foco.
		//--------------------------------------------------------------
		float spotEffect = dot(normalize(SpotDir), normalize(-lVec));
		
		//--------------------------------------------------------------
		// Si no nos hemos salido del angulo del foco, calculamos la
		// iluminaci�n para el pixel actual.
		//--------------------------------------------------------------
		if(spotEffect > gl_LightSource[0].spotCosCutoff)
		{
			//----------------------------------------------------------
			// Una vez estamos dentro del foco, hemos de indicarle, que
			// cuanto m�s cerca del "centro", m�s intensamente estar�
			// iluminado, dato que est� recogido en el exponente.
			//----------------------------------------------------------
			spotEffect = pow(spotEffect, gl_LightSource[0].spotExponent);
			
			//----------------------------------------------------------
			// Calculamos la atenuaci�n en base a la distancia.
			//----------------------------------------------------------
			float att = spotEffect / (gl_LightSource[0].constantAttenuation +
				gl_LightSource[0].linearAttenuation * Distance +
				gl_LightSource[0].quadraticAttenuation * Distance * Distance);
				
			//----------------------------------------------------------
			// Con la atenuaci�n podemos calcular, tanto la luz
			// ambiental, como la difusa, para el pixel actual.
			//----------------------------------------------------------
			color += att * (Diffuse * NdotL + Ambient) * Texel;
		
			//----------------------------------------------------------
			// Despu�s calculamos la luz especular, teniendo en cuenta
			// ahora tambi�n la atenuaci�n.
			//----------------------------------------------------------
			color += att * Specular * pow(max(dot(reflect(-lVec, Normal),
										vVec), 0.0), gl_FrontMaterial.shininess);
		}
	}

	//------------------------------------------------------------------
	// Por �ltimo tomanos el color resultante y le sumamos el
	// componente de emisi�n del material.
	//------------------------------------------------------------------
	gl_FragColor = color + gl_FrontMaterial.emission;
}

//----------------------------------------------------------------------
// Funci�n main del fragment shader.
//----------------------------------------------------------------------
void main()
{
	//------------------------------------------------------------------
	// Calculamos para cada tipo de luz su intensidad plena.
	//------------------------------------------------------------------
	Specular  = gl_FrontMaterial.specular * gl_LightSource[0].specular;
	Diffuse   = gl_FrontMaterial.diffuse  * gl_LightSource[0].diffuse;
	Ambient   = gl_FrontMaterial.ambient  * gl_LightSource[0].ambient;
	AmbientLM = gl_LightModel.ambient     * gl_FrontMaterial.ambient;

	//------------------------------------------------------------------
	// Normalizamos el vector direcci�n y el vector al ojo.
	//------------------------------------------------------------------
	lVec = normalize(LightVec);
	vVec = normalize(EyeVec);

	//------------------------------------------------------------------
	// Calculamos las nuevas coordenadas de textura.
	//------------------------------------------------------------------
	vec2 offsetCoord = gl_TexCoord[0].st + (texture2D(heightMap,
					   gl_TexCoord[0].st).x * ScaleBiasFactor[0] -
					   ScaleBiasFactor[1]) * vec2(vVec.xy);
	
	//------------------------------------------------------------------
	// Obtenemos el pixel correspondiente al fragmento.
	//------------------------------------------------------------------
	Texel  = texture2D(colorMap, offsetCoord);
	Normal = normalize(texture2D(normalMap, offsetCoord).xyz * 2.0 - 1.0);

	//------------------------------------------------------------------
	// Y dependiendo del tipo de luz calculamos la intensidad final.
	//------------------------------------------------------------------
	if(gl_LightSource[0].position.w == 0.0)
	{
		CalcDirLight();
	}
	else if(gl_LightSource[0].spotCutoff == 180.0)
	{
		CalcPosLight();
	}
	else
	{
		CalcSpotLight();
	}
}
