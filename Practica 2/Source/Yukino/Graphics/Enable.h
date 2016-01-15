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
#ifndef _YUKINO_GRAPHICS_ENABLE_H_
#define _YUKINO_GRAPHICS_ENABLE_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase Enable
//******************************************************************************************
namespace Yukino
{
	class DLLAPI EnableManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		EnableManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~EnableManager ();

		//----------------------------------------------------------------------------------
		// Funciones para activar parametros de OpenGL.
		//----------------------------------------------------------------------------------
		inline void PointSmooth        (void) { glEnable(GL_POINT_SMOOTH);         }
		inline void LineSmooth         (void) { glEnable(GL_LINE_SMOOTH);          }
		inline void PolygonSmooth      (void) { glEnable(GL_POLYGON_SMOOTH);       }

		inline void LineStipple        (void) { glEnable(GL_LINE_STIPPLE);         }
		inline void PolygonStipple     (void) { glEnable(GL_POLYGON_STIPPLE);      }

		inline void AutoNormal         (void) { glEnable(GL_AUTO_NORMAL);          }
		inline void Normalize          (void) { glEnable(GL_NORMALIZE);            }

		inline void CullFace           (void) { glEnable(GL_CULL_FACE);            }

		inline void Blend              (void) { glEnable(GL_BLEND);                }
		inline void Fog                (void) { glEnable(GL_FOG);                  }
		inline void Dither             (void) { glEnable(GL_DITHER);               }

		inline void ColorLogicOp       (void) { glEnable(GL_COLOR_LOGIC_OP);       }
		inline void IndexLogicOp       (void) { glEnable(GL_INDEX_LOGIC_OP);       }
		inline void LogicOp            (void) { glEnable(GL_LOGIC_OP);             }

		inline void DepthTest          (void) { glEnable(GL_DEPTH_TEST);           }
		inline void StencilTest        (void) { glEnable(GL_STENCIL_TEST);         }
		inline void AlphaTest          (void) { glEnable(GL_ALPHA_TEST);           }
		inline void ScissorTest        (void) { glEnable(GL_SCISSOR_TEST);         }

		inline void ColorArray         (void) { glEnable(GL_COLOR_ARRAY);          }
		inline void IndexArray         (void) { glEnable(GL_INDEX_ARRAY);          }
		inline void NormalArray        (void) { glEnable(GL_NORMAL_ARRAY);         }
		inline void TextureCoordArray  (void) { glEnable(GL_TEXTURE_COORD_ARRAY);  }
		inline void VertexArray        (void) { glEnable(GL_VERTEX_ARRAY);         }

		inline void Light0             (void) { glEnable(GL_LIGHT0);               }
		inline void Light1             (void) { glEnable(GL_LIGHT1);               }
		inline void Light2             (void) { glEnable(GL_LIGHT2);               }
		inline void Light3             (void) { glEnable(GL_LIGHT3);               }
		inline void Light4             (void) { glEnable(GL_LIGHT4);               }
		inline void Light5             (void) { glEnable(GL_LIGHT5);               }
		inline void Light6             (void) { glEnable(GL_LIGHT6);               }
		inline void Light7             (void) { glEnable(GL_LIGHT7);               }
		inline void Lighting           (void) { glEnable(GL_LIGHTING);             }

		inline void ColorMaterial      (void) { glEnable(GL_COLOR_MATERIAL);       }

		inline void Map1Color4         (void) { glEnable(GL_MAP1_COLOR_4);         }
		inline void Map1Index          (void) { glEnable(GL_MAP1_INDEX);           }
		inline void Map1Normal         (void) { glEnable(GL_MAP1_NORMAL);          }
		inline void Map1TextureCoord1  (void) { glEnable(GL_MAP1_TEXTURE_COORD_1); }
		inline void Map1TextureCoord2  (void) { glEnable(GL_MAP1_TEXTURE_COORD_2); }
		inline void Map1TextureCoord3  (void) { glEnable(GL_MAP1_TEXTURE_COORD_3); }
		inline void Map1TextureCoord4  (void) { glEnable(GL_MAP1_TEXTURE_COORD_4); }
		inline void Map1Vertex3        (void) { glEnable(GL_MAP1_VERTEX_3);        }
		inline void Map1Vertex4        (void) { glEnable(GL_MAP1_VERTEX_4);        }

		inline void Map2Color4         (void) { glEnable(GL_MAP2_COLOR_4);         }
		inline void Map2Index          (void) { glEnable(GL_MAP2_INDEX);           }
		inline void Map2Normal         (void) { glEnable(GL_MAP2_NORMAL);          }
		inline void Map2TextureCoord1  (void) { glEnable(GL_MAP2_TEXTURE_COORD_1); }
		inline void Map2TextureCoord2  (void) { glEnable(GL_MAP2_TEXTURE_COORD_2); }
		inline void Map2TextureCoord3  (void) { glEnable(GL_MAP2_TEXTURE_COORD_3); }
		inline void Map2TextureCoord4  (void) { glEnable(GL_MAP2_TEXTURE_COORD_4); }
		inline void Map2Vertex3        (void) { glEnable(GL_MAP2_VERTEX_3);        }
		inline void Map2Vertex4        (void) { glEnable(GL_MAP2_VERTEX_4);        }

		inline void PolygonOffsetFill  (void) { glEnable(GL_POLYGON_OFFSET_FILL);  }
		inline void PolygonOffsetLine  (void) { glEnable(GL_POLYGON_OFFSET_LINE);  }
		inline void PolygonOffsetPoint (void) { glEnable(GL_POLYGON_OFFSET_POINT); }

		inline void Texture1D          (void) { glEnable(GL_TEXTURE_1D);           }
		inline void Texture2D          (void) { glEnable(GL_TEXTURE_2D);           }
		inline void TextureGenQ        (void) { glEnable(GL_TEXTURE_GEN_Q);        }
		inline void TextureGenR        (void) { glEnable(GL_TEXTURE_GEN_R);        }
		inline void TextureGenS        (void) { glEnable(GL_TEXTURE_GEN_S);        }
		inline void TextureGenT        (void) { glEnable(GL_TEXTURE_GEN_T);        }

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Enable.h
//******************************************************************************************