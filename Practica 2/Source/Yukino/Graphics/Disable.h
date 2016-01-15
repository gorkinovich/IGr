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
#ifndef _YUKINO_GRAPHICS_DISABLE_H_
#define _YUKINO_GRAPHICS_DISABLE_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase Disable
//******************************************************************************************
namespace Yukino
{
	class DLLAPI DisableManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		DisableManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~DisableManager ();

		//----------------------------------------------------------------------------------
		// Funciones para desactivar parametros de OpenGL.
		//----------------------------------------------------------------------------------		
		inline void PointSmooth        (void) { glDisable(GL_POINT_SMOOTH);         }
		inline void LineSmooth         (void) { glDisable(GL_LINE_SMOOTH);          }
		inline void PolygonSmooth      (void) { glDisable(GL_POLYGON_SMOOTH);       }

		inline void LineStipple        (void) { glDisable(GL_LINE_STIPPLE);         }
		inline void PolygonStipple     (void) { glDisable(GL_POLYGON_STIPPLE);      }

		inline void AutoNormal         (void) { glDisable(GL_AUTO_NORMAL);          }
		inline void Normalize          (void) { glDisable(GL_NORMALIZE);            }

		inline void CullFace           (void) { glDisable(GL_CULL_FACE);            }

		inline void Blend              (void) { glDisable(GL_BLEND);                }
		inline void Fog                (void) { glDisable(GL_FOG);                  }
		inline void Dither             (void) { glDisable(GL_DITHER);               }

		inline void ColorLogicOp       (void) { glDisable(GL_COLOR_LOGIC_OP);       }
		inline void IndexLogicOp       (void) { glDisable(GL_INDEX_LOGIC_OP);       }
		inline void LogicOp            (void) { glDisable(GL_LOGIC_OP);             }

		inline void DepthTest          (void) { glDisable(GL_DEPTH_TEST);           }
		inline void StencilTest        (void) { glDisable(GL_STENCIL_TEST);         }
		inline void AlphaTest          (void) { glDisable(GL_ALPHA_TEST);           }
		inline void ScissorTest        (void) { glDisable(GL_SCISSOR_TEST);         }

		inline void ColorArray         (void) { glDisable(GL_COLOR_ARRAY);          }
		inline void IndexArray         (void) { glDisable(GL_INDEX_ARRAY);          }
		inline void NormalArray        (void) { glDisable(GL_NORMAL_ARRAY);         }
		inline void TextureCoordArray  (void) { glDisable(GL_TEXTURE_COORD_ARRAY);  }
		inline void VertexArray        (void) { glDisable(GL_VERTEX_ARRAY);         }

		inline void Light0             (void) { glDisable(GL_LIGHT0);               }
		inline void Light1             (void) { glDisable(GL_LIGHT1);               }
		inline void Light2             (void) { glDisable(GL_LIGHT2);               }
		inline void Light3             (void) { glDisable(GL_LIGHT3);               }
		inline void Light4             (void) { glDisable(GL_LIGHT4);               }
		inline void Light5             (void) { glDisable(GL_LIGHT5);               }
		inline void Light6             (void) { glDisable(GL_LIGHT6);               }
		inline void Light7             (void) { glDisable(GL_LIGHT7);               }
		inline void Lighting           (void) { glDisable(GL_LIGHTING);             }

		inline void ColorMaterial      (void) { glDisable(GL_COLOR_MATERIAL);       }

		inline void Map1Color4         (void) { glDisable(GL_MAP1_COLOR_4);         }
		inline void Map1Index          (void) { glDisable(GL_MAP1_INDEX);           }
		inline void Map1Normal         (void) { glDisable(GL_MAP1_NORMAL);          }
		inline void Map1TextureCoord1  (void) { glDisable(GL_MAP1_TEXTURE_COORD_1); }
		inline void Map1TextureCoord2  (void) { glDisable(GL_MAP1_TEXTURE_COORD_2); }
		inline void Map1TextureCoord3  (void) { glDisable(GL_MAP1_TEXTURE_COORD_3); }
		inline void Map1TextureCoord4  (void) { glDisable(GL_MAP1_TEXTURE_COORD_4); }
		inline void Map1Vertex3        (void) { glDisable(GL_MAP1_VERTEX_3);        }
		inline void Map1Vertex4        (void) { glDisable(GL_MAP1_VERTEX_4);        }

		inline void Map2Color4         (void) { glDisable(GL_MAP2_COLOR_4);         }
		inline void Map2Index          (void) { glDisable(GL_MAP2_INDEX);           }
		inline void Map2Normal         (void) { glDisable(GL_MAP2_NORMAL);          }
		inline void Map2TextureCoord1  (void) { glDisable(GL_MAP2_TEXTURE_COORD_1); }
		inline void Map2TextureCoord2  (void) { glDisable(GL_MAP2_TEXTURE_COORD_2); }
		inline void Map2TextureCoord3  (void) { glDisable(GL_MAP2_TEXTURE_COORD_3); }
		inline void Map2TextureCoord4  (void) { glDisable(GL_MAP2_TEXTURE_COORD_4); }
		inline void Map2Vertex3        (void) { glDisable(GL_MAP2_VERTEX_3);        }
		inline void Map2Vertex4        (void) { glDisable(GL_MAP2_VERTEX_4);        }

		inline void PolygonOffsetFill  (void) { glDisable(GL_POLYGON_OFFSET_FILL);  }
		inline void PolygonOffsetLine  (void) { glDisable(GL_POLYGON_OFFSET_LINE);  }
		inline void PolygonOffsetPoint (void) { glDisable(GL_POLYGON_OFFSET_POINT); }

		inline void Texture1D          (void) { glDisable(GL_TEXTURE_1D);           }
		inline void Texture2D          (void) { glDisable(GL_TEXTURE_2D);           }
		inline void TextureGenQ        (void) { glDisable(GL_TEXTURE_GEN_Q);        }
		inline void TextureGenR        (void) { glDisable(GL_TEXTURE_GEN_R);        }
		inline void TextureGenS        (void) { glDisable(GL_TEXTURE_GEN_S);        }
		inline void TextureGenT        (void) { glDisable(GL_TEXTURE_GEN_T);        }

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Disable.h
//******************************************************************************************