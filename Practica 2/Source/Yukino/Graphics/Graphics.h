//******************************************************************************************
// Yukino 2.0 - A 3D game library.
// Copyright (C) 2006  Gorka Suárez García
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//******************************************************************************************
#ifndef _YUKINO_GRAPHICS_GRAPHICS_H_
#define _YUKINO_GRAPHICS_GRAPHICS_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include "../Util/Matrix.h"
#include "../Util/Point2D.h"
#include "../Util/Point3D.h"
#include "../Util/Vector2D.h"
#include "../Util/Vector3D.h"
//------------------------------------------------------------------------------------------
#include "Enable.h"
#include "Disable.h"
#include "Render.h"
#include "Point.h"
#include "Line.h"
#include "Polygon.h"
#include "Camera.h"
#include "Buffer.h"
#include "LightModel.h"
#include "World.h"
//------------------------------------------------------------------------------------------
#include "Light.h"
#include "Material.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase GraphicsManager
//******************************************************************************************
namespace Yukino
{
	class DLLAPI GraphicsManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		GraphicsManager ();
		
		static GraphicsManager * Instance;

	//--------------------------------------------------------------------------------------
	// Miembros protegidos.
	//--------------------------------------------------------------------------------------
	protected:
		//...
		
	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~GraphicsManager ();

		EnableManager     Enable;
		DisableManager    Disable;
		RenderManager     Render;
		PointManager      Point;
		LineManager       Line;
		PolygonManager    Polygon;
		CameraManager     Camera;
		BufferManager     Buffer;
		LightModelManager LightModel;
		WorldManager      World;

		//----------------------------------------------------------------------------------
		// Funciones para controlar la lógica.
		//----------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------
		// Sets.
		//----------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------
		// Funciones estáticas.
		//----------------------------------------------------------------------------------
		static GraphicsManager * GetInstance (void);
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Graphics.h
//******************************************************************************************