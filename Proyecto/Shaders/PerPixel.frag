//----------------------------------------------------------------------
// Per-pixel Lighting fragment shader.
// Copyright (C) 2007  Gorka Suárez García.
//----------------------------------------------------------------------
varying vec3 Normal, LightDir, HalfVector;
varying float Distance;

uniform sampler2D Texture;

//----------------------------------------------------------------------
// Variables globales.
//----------------------------------------------------------------------
vec4 Specular, Diffuse, Ambient, AmbientLM;
vec4 Texel;

//----------------------------------------------------------------------
// Función para calcular la iluminación de una luz direccional.
//----------------------------------------------------------------------
void CalcDirLight()
{
	//------------------------------------------------------------------
	// Lo primero es calcular la luz ambiental para el pixel.
	//------------------------------------------------------------------
	vec4 color = (Ambient + AmbientLM) * Texel;
	
	//------------------------------------------------------------------
	// Después necesitamos con el producto escalar entre la normal y
	// la dirección de la luz, obtener la intensidad con la que la luz
	// incide en el pixel actual.
	//------------------------------------------------------------------
	vec3 n = normalize(Normal);	
	float NdotL = max(dot(n, normalize(LightDir)), 0.0);

	//------------------------------------------------------------------
	// Siempre que la intensidad sea mayor que cero, el pixel en
	// cuestión estará de cara a la luz, así que echaremos las cuentas
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
		// Después calculamos la luz especular, usando el modelo de
		// Blinn-Phong, que es una forma simplificada del de Phong.
		//--------------------------------------------------------------
		float NdotHV = max(dot(n, normalize(HalfVector)), 0.0);
		color += Specular * pow(NdotHV, gl_FrontMaterial.shininess);
	}

	//------------------------------------------------------------------
	// Por último tomanos el color resultante y le sumamos el
	// componente de emisión del material.
	//------------------------------------------------------------------
	gl_FragColor = color + gl_FrontMaterial.emission;
}

//----------------------------------------------------------------------
// Función para calcular la iluminación de una luz posicional.
//----------------------------------------------------------------------
void CalcPosLight()
{
	//------------------------------------------------------------------
	// Lo primero es calcular la luz ambiental global para el pixel.
	//------------------------------------------------------------------
	vec4 color = AmbientLM * Texel;
	
	//------------------------------------------------------------------
	// Después necesitamos con el producto escalar entre la normal y
	// la dirección de la luz, obtener la intensidad con la que la luz
	// incide en el pixel actual.
	//------------------------------------------------------------------
	vec3 n = normalize(Normal);
	float NdotL = max(dot(n, normalize(LightDir)), 0.0);

	//------------------------------------------------------------------
	// Siempre que la intensidad sea mayor que cero, el pixel en
	// cuestión estará de cara a la luz, así que echaremos las cuentas
	// para la luz difusa y la especular.
	//------------------------------------------------------------------
	if (NdotL > 0.0)
	{
		//--------------------------------------------------------------
		// Calculamos la atenuación en base a la distancia.
		//--------------------------------------------------------------
		float att = 1.0 / (gl_LightSource[0].constantAttenuation +
			gl_LightSource[0].linearAttenuation * Distance +
			gl_LightSource[0].quadraticAttenuation * Distance * Distance);
			
		//--------------------------------------------------------------
		// Con la atenuación podemos calcular, tanto la luz ambiental,
		// como la difusa, para el pixel actual.
		//--------------------------------------------------------------
		color += att * (Diffuse * NdotL + Ambient) * Texel;
	
		//--------------------------------------------------------------
		// Después calculamos la luz especular, usando el modelo de
		// Blinn-Phong, que es una forma simplificada del de Phong,
		// teniendo en cuenta ahora también la atenuación.
		//--------------------------------------------------------------
		float NdotHV = max(dot(n, normalize(HalfVector)), 0.0);
		color += att * Specular * pow(NdotHV, gl_FrontMaterial.shininess);
	}

	//------------------------------------------------------------------
	// Por último tomanos el color resultante y le sumamos el
	// componente de emisión del material.
	//------------------------------------------------------------------
	gl_FragColor = color + gl_FrontMaterial.emission;
}

//----------------------------------------------------------------------
// Función para calcular la iluminación de una luz focal.
//----------------------------------------------------------------------
void CalcSpotLight()
{
	//------------------------------------------------------------------
	// Lo primero es calcular la luz ambiental global para el pixel.
	//------------------------------------------------------------------
	vec4 color = AmbientLM * Texel;
	
	//------------------------------------------------------------------
	// Después necesitamos con el producto escalar entre la normal y
	// la dirección de la luz, obtener la intensidad con la que la luz
	// incide en el pixel actual.
	//------------------------------------------------------------------
	vec3 n = normalize(Normal);	
	float NdotL = max(dot(n, normalize(LightDir)), 0.0);

	//------------------------------------------------------------------
	// Siempre que la intensidad sea mayor que cero, el pixel en
	// cuestión estará de cara a la luz, así que echaremos las cuentas
	// para la luz difusa y la especular.
	//------------------------------------------------------------------
	if(NdotL > 0.0)
	{
		//--------------------------------------------------------------
		// Calculamos el coseno del ángulo entre el vector de la
		// dirección de la luz, y el de la dirección del foco.
		//--------------------------------------------------------------
		float spotEffect = dot(normalize(gl_LightSource[0].spotDirection),
							   normalize(-LightDir));
		
		//--------------------------------------------------------------
		// Si no nos hemos salido del angulo del foco, calculamos la
		// iluminación para el pixel actual.
		//--------------------------------------------------------------
		if(spotEffect > gl_LightSource[0].spotCosCutoff)
		{
			//----------------------------------------------------------
			// Una vez estamos dentro del foco, hemos de indicarle, que
			// cuanto más cerca del "centro", más intensamente estará
			// iluminado, dato que está recogido en el exponente.
			//----------------------------------------------------------
			spotEffect = pow(spotEffect, gl_LightSource[0].spotExponent);
			
			//----------------------------------------------------------
			// Calculamos la atenuación en base a la distancia.
			//----------------------------------------------------------
			float att = spotEffect / (gl_LightSource[0].constantAttenuation +
				gl_LightSource[0].linearAttenuation * Distance +
				gl_LightSource[0].quadraticAttenuation * Distance * Distance);
				
			//----------------------------------------------------------
			// Con la atenuación podemos calcular, tanto la luz
			// ambiental, como la difusa, para el pixel actual.
			//----------------------------------------------------------
			color += att * (Diffuse * NdotL + Ambient) * Texel;
		
			//----------------------------------------------------------
			// Después calculamos la luz especular, usando el modelo de
			// Blinn-Phong, que es una forma simplificada del de Phong,
			// teniendo en cuenta ahora también la atenuación.
			//----------------------------------------------------------
			float NdotHV = max(dot(n, normalize(HalfVector)), 0.0);
			color += att * Specular * pow(NdotHV, gl_FrontMaterial.shininess);
		}
	}

	//------------------------------------------------------------------
	// Por último tomanos el color resultante y le sumamos el
	// componente de emisión del material.
	//------------------------------------------------------------------
	gl_FragColor = color + gl_FrontMaterial.emission;
}

//----------------------------------------------------------------------
// Función main del fragment shader.
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
	// Obtenemos el pixel correspondiente al fragmento.
	//------------------------------------------------------------------
	Texel = texture2D(Texture, gl_TexCoord[0].st);
	
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
