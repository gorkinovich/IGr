//******************************************************************************************
// Anubis Editor 1.0 - A 3D Adventure Game Engine.
// Copyright (C) 2006-2007  Gorka Suárez García
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//******************************************************************************************
#include "textures.h"
//******************************************************************************************
// Tipos estructurados.
//******************************************************************************************
//typedef struct tagBITMAPFILEHEADER
//{
//    WORD  bfType;      // Tipo del fichero, que tiene que ser "BM" (0x4D42).
//    DWORD bfSize;      // = sizeof(BITMAPFILEHEADER);
//    WORD  bfReserved1; // Reservado, vale 0.
//    WORD  bfReserved2; // Reservado, vale 0.
//    DWORD bfOffBits;   // Offset de la imagen desde la cabecera.
//} BITMAPFILEHEADER;
//------------------------------------------------------------------------------------------
//typedef struct tagBITMAPINFOHEADER
//{
//    DWORD biSize;          // = sizeof(BITMAPINFOHEADER);
//    LONG  biWidth;         // Ancho de la imagen en pixels.
//    LONG  biHeight;        // Alto de la imagen en pixels.
//    WORD  biPlanes;        // Número de planos de color (= 1).
//    WORD  biBitCount;      // Bits por pixel (1, 4, 8, 16, 24 o 32).
//    DWORD biCompression;   // Tipo de compresión.
//    DWORD biSizeImage;     // Tamaño de la imagen en bytes.
//    LONG  biXPelsPerMeter; // Número de pixels por metro en el eje X.
//    LONG  biYPelsPerMeter; // Número de pixels por metro en el eje Y.
//    DWORD biClrUsed;       // Número de colores usados en el bitmap.
//    DWORD biClrImportant;  // Número de colores que son importantes.
//} BITMAPINFOHEADER;
//------------------------------------------------------------------------------------------
typedef struct tagTARGAFILEHEADER
{
    BYTE      imageIDLength;     // Nº de caracteres del campo de ID (=0)
    BYTE      colorMapType;      // = 0;
    BYTE      imageTypeCode;     // = 2; (RGB no comprimido)
                                 // = 3; (Escala de grises no comprimida)
    short int colorMapOrigin;    // = 0;
    short int colorMapLength;    // = 0;
    BYTE      colorMapEntrySize; // = 0;
    short int imageXOrigin;      // = 0;
    short int imageYOrigin;      // = 0;
    short int imageWidth;        // Ancho en pixeles de la imagen.
    short int imageHeight;       // Alto en pixeles de la imagen.
    BYTE      bitCount;          // Profundidad de color (16, 24, 32)
    BYTE      imageDescriptor;   // 24bits = 0x00, 32bits = 0x08
} TARGAFILEHEADER;
//******************************************************************************************
// Miembros de la clase CImage.
//******************************************************************************************

	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CImage.
	//--------------------------------------------------------------------------------------
	CImage::CImage ()
	{
		this->Name   = "";
		this->Type   = 0;
		this->Width  = 0;
		this->Height = 0;
		this->Depth  = 0;
		this->Data   = NULL;
	}

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CImage.
	//--------------------------------------------------------------------------------------
	CImage::CImage (const char * path)
	{
		this->Name   = "";
		this->Type   = 0;
		this->Width  = 0;
		this->Height = 0;
		this->Depth  = 0;
		this->Data   = NULL;

		this->LoadFile(path);
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CImage.
	//--------------------------------------------------------------------------------------
	CImage::CImage (const CImage & obj)
	{
		this->CopyFrom(obj);
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CImage.
	//--------------------------------------------------------------------------------------
	CImage::~CImage ()
	{
		this->Release();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CImage & CImage::operator = (const CImage & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CImage::CopyFrom (const CImage & obj)
	{
		if(obj.Data != NULL)
		{
			this->Release();

			unsigned int size = obj.Width * obj.Height * (obj.Depth / 8);

			this->Data = (unsigned char *) malloc(size);

			if(Data != NULL)
			{
				this->Name   = obj.Name;
				this->Type   = obj.Type;
				this->Width  = obj.Width;
				this->Height = obj.Height;
				this->Depth  = obj.Depth;

				memcpy(this->Data, obj.Data, size);
			}
		}
	}

	//**************************************************************************************
	// Funciones para cargar, salvar y liberar la imagen.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Metodo que carga una imagen desde un fichero.
	//--------------------------------------------------------------------------------------
	bool CImage::LoadFile (const char * path)
	{
		appResetLastError();
		char * aux = strlwr(strdup(path));

		if(strstr(aux, ".bmp") != NULL)
		{
			return this->LoadBMPFile(path);
		}
		else if(strstr(aux, ".tga") != NULL)
		{
			return this->LoadTGAFile(path);
		}
		else
		{
			return appSetLastError(TEXERR_UNSUPPORTED_FORMAT);
		}
	}

	//--------------------------------------------------------------------------------------
	// Metodo que salva una imagen a un fichero.
	//--------------------------------------------------------------------------------------
	bool CImage::SaveFile (const char * path)
	{
		appResetLastError();
		char * aux = strlwr(strdup(path));

		if(strstr(aux, ".bmp") != NULL)
		{
			return this->SaveBMPFile(path);
		}
		else if(strstr(aux, ".tga") != NULL)
		{
			return this->SaveTGAFile(path);
		}
		else
		{
			return appSetLastError(TEXERR_UNSUPPORTED_FORMAT);
		}
	}

	//--------------------------------------------------------------------------------------
	// Metodo que libera la imagen de la memoria ram.
	//--------------------------------------------------------------------------------------
	void CImage::Release (void)
	{
		if(this->Data != NULL)
			free(this->Data);

		this->Name   = "";
		this->Type   = 0;
		this->Width  = 0;
		this->Height = 0;
		this->Depth  = 0;
		this->Data   = NULL;
	}

	//**************************************************************************************
	// Funciones para cargar y salvar BMPs y TGAs.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Función para cargar un bmp en memoria.
	//--------------------------------------------------------------------------------------
	bool CImage::LoadBMPFile (const char * name)
	{
		//----------------------------------------------------------------------------------
		// Abrimos el fichero, comprobando que así haya sido.
		//----------------------------------------------------------------------------------
		FILE * file;

		file = fopen(name, "rb");
		if(file == NULL) return appSetLastError(TEXERR_LOADBMP_FOPEN);

		//----------------------------------------------------------------------------------
		// Leemos la cabecera del bmp para comprobar que es ese tipo de fichero.
		//----------------------------------------------------------------------------------	
		BITMAPFILEHEADER header;

		fread(&header, sizeof(BITMAPFILEHEADER), 1, file);

		if(header.bfType != 0x4D42)
		{
			fclose(file);
			return appSetLastError(TEXERR_LOADBMP_BADFORMAT);
		}

		//----------------------------------------------------------------------------------
		// Leemos la cabecera de información para obtener la configuración del bmp.
		//----------------------------------------------------------------------------------
		BITMAPINFOHEADER info;

		fread(&info, sizeof(BITMAPINFOHEADER), 1, file);

		if(info.biCompression != BI_RGB)
		{
			fclose(file);
			return appSetLastError(TEXERR_LOADBMP_BADCOMPRESSION);
		}

		//----------------------------------------------------------------------------------
		// Calculamos el tamaño del buffer donde almacenaremos la imagen y lo pedimos.
		//----------------------------------------------------------------------------------
		fseek(file, header.bfOffBits, SEEK_SET);

		unsigned int size = info.biWidth * info.biHeight * (info.biBitCount / 8);
		this->Data = (unsigned char *) malloc (size);

		if(this->Data == NULL)
		{
			fclose(file);
			return appSetLastError(TEXERR_LOADBMP_NULLMALLOC);
		}

		//----------------------------------------------------------------------------------
		// Leemos todos los pixels de la imagen que hay en el bmp.
		//----------------------------------------------------------------------------------
		fread(this->Data, 1, size, file);

		//----------------------------------------------------------------------------------
		// Invertimos los colores para que pase de BGR a ser RGB.
		//----------------------------------------------------------------------------------
		if((info.biBitCount == 24) || (info.biBitCount == 32))
		{
			DWORD imgidx;
			unsigned char temprgb;
			BYTE imginc = (info.biBitCount / 8);

			for(imgidx = 0; imgidx < size; imgidx += imginc)
			{
				temprgb                = this->Data[imgidx];
				this->Data[imgidx]     = this->Data[imgidx + 2];
				this->Data[imgidx + 2] = temprgb;
			}
		}

		//----------------------------------------------------------------------------------
		// Y finalmente cerramos el fichero y guardamos los últimos datos.
		//----------------------------------------------------------------------------------
		fclose(file);

		this->Name   = name;
		this->Type   = IMAGE_TYPE_RGBA;
		this->Depth  = info.biBitCount;
		this->Width  = info.biWidth;
		this->Height = info.biHeight;

		return true;
	}

	//--------------------------------------------------------------------------------------
	// Función para salvar un bmp en memoria.
	//--------------------------------------------------------------------------------------
	bool CImage::SaveBMPFile (const char * name)
	{
		//----------------------------------------------------------------------------------
		// Configuramos la cabecera del bmp.
		//----------------------------------------------------------------------------------
		BITMAPFILEHEADER header;

		header.bfType      = 0x4D42;
		header.bfSize      = sizeof(BITMAPFILEHEADER);
		header.bfReserved1 = 0;
		header.bfReserved2 = 0;
		header.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		//----------------------------------------------------------------------------------
		// Configuramos la otra cabecera de configuración de la imagen.
		//----------------------------------------------------------------------------------
		BITMAPINFOHEADER info;

		info.biSize          = sizeof(BITMAPINFOHEADER);
		info.biWidth         = this->Width;
		info.biHeight        = this->Height;
		info.biPlanes        = 1;
		info.biBitCount      = this->Depth;
		info.biCompression   = BI_RGB;
		info.biSizeImage     = this->Width * this->Height * (this->Depth / 8);
		info.biXPelsPerMeter = 0;
		info.biYPelsPerMeter = 0;
		info.biClrUsed       = 0;
		info.biClrImportant  = 0;

		//----------------------------------------------------------------------------------
		// Dependiendo de la profundidad crearemos un buffer temporal donde vamos a
		// almacenar la imagen que tenemos dentro del objeto.
		//----------------------------------------------------------------------------------
		unsigned char * data = NULL;

		if((info.biBitCount == 24) || (info.biBitCount == 32))
		{
			data = (unsigned char *) malloc (info.biSizeImage);

			if(data == NULL) return appSetLastError(TEXERR_SAVEBMP_NULLMALLOC);

			//------------------------------------------------------------------------------
			// Esto es para poder invertir el orden de sus colores y salvar el bmp bien.
			//------------------------------------------------------------------------------
			DWORD imgidx;
			BYTE imginc = (info.biBitCount / 8);

			for(imgidx = 0; imgidx < info.biSizeImage; imgidx += imginc)
			{
				data[imgidx]     = this->Data[imgidx + 2];
				data[imgidx + 1] = this->Data[imgidx + 1];
				data[imgidx + 2] = this->Data[imgidx];
			}
		}
		else
		{
			data = this->Data;
		}

		//----------------------------------------------------------------------------------
		// Abrimos el fichero, comprobando que así haya sido.
		//----------------------------------------------------------------------------------
		FILE * file;

		file = fopen(name, "wb");
		if(file == NULL)
		{
			if((info.biBitCount == 24) || (info.biBitCount == 32))
				free(data);

			return appSetLastError(TEXERR_SAVEBMP_FOPEN);
		}

		//----------------------------------------------------------------------------------
		// Mandamos a escribir las cabeceras y la imagen.
		//----------------------------------------------------------------------------------
		fwrite(&header, sizeof(BITMAPFILEHEADER), 1, file);
		fwrite(&info, sizeof(BITMAPINFOHEADER), 1, file);
		fwrite(data, 1, info.biSizeImage, file);

		//----------------------------------------------------------------------------------
		// Y finalmente liberamos el buffer temporal, cerramos el fichero y ya está.
		//----------------------------------------------------------------------------------
		if((info.biBitCount == 24) || (info.biBitCount == 32))
		{
			free(data);
		}

		fclose(file);

		return true;
	}

	//--------------------------------------------------------------------------------------
	// Función para cargar un tga en memoria.
	//--------------------------------------------------------------------------------------
	bool CImage::LoadTGAFile (const char * name)
	{
		//----------------------------------------------------------------------------------
		// Abrimos el fichero, comprobando que así haya sido.
		//----------------------------------------------------------------------------------
		FILE * file;

		file = fopen(name, "rb");
		if(file == NULL) return appSetLastError(TEXERR_LOADTGA_FOPEN);

		//----------------------------------------------------------------------------------
		// Leemos la cabecera, por desgracia no podemos leerla de un golpe, ya que el
		// compilador alinea la memoria de la estructura dandole un byte de más y todo se
		// va a tomar por culo, a la hora de intentar leer el fichero TGA.
		//----------------------------------------------------------------------------------
		TARGAFILEHEADER header;

		fread(&(header.imageIDLength), 1, 1, file);
		fread(&(header.colorMapType),  1, 1, file);
		fread(&(header.imageTypeCode), 1, 1, file);

		if((header.imageTypeCode != 2) && (header.imageTypeCode != 3))
		{
			fclose(file);
			return appSetLastError(TEXERR_LOADTGA_BADFORMAT);
		}

		fread(&(header.colorMapOrigin),    2, 1, file);
		fread(&(header.colorMapLength),    2, 1, file);
		fread(&(header.colorMapEntrySize), 1, 1, file);

		fread(&(header.imageXOrigin),    2, 1, file);
		fread(&(header.imageYOrigin),    2, 1, file);
		fread(&(header.imageWidth),      2, 1, file);
		fread(&(header.imageHeight),     2, 1, file);
		fread(&(header.bitCount),        1, 1, file);
		fread(&(header.imageDescriptor), 1, 1, file);

		//----------------------------------------------------------------------------------
		// Salvamos la información importante en la estructura.
		//----------------------------------------------------------------------------------
		this->Name   = name;
		this->Type   = header.imageTypeCode;
		this->Width  = header.imageWidth;
		this->Height = header.imageHeight;
		this->Depth  = header.bitCount;

		//----------------------------------------------------------------------------------
		// Calculamos el tamaño del buffer donde almacenaremos la imagen y lo pedimos.
		//----------------------------------------------------------------------------------
		DWORD imgidx, imagesize;
		BYTE temprgb, colormode;

		colormode = this->Depth / 8;
		imagesize = this->Width * this->Height * colormode;

		this->Data = (unsigned char *) malloc(imagesize);

		if(this->Data == NULL)
		{
			fclose(file);
			return appSetLastError(TEXERR_LOADTGA_NULLMALLOC);
		}

		//----------------------------------------------------------------------------------
		// Leemos todos los pixels de la imagen que hay en el bmp.
		//----------------------------------------------------------------------------------
		fread(this->Data, sizeof(unsigned char), imagesize, file);

		//----------------------------------------------------------------------------------
		// Invertimos los colores para que pase de BGR a ser RGB.
		//----------------------------------------------------------------------------------
		if((this->Depth == 24) || (this->Depth == 32))
		{
			for(imgidx = 0; imgidx < imagesize; imgidx += colormode)
			{
				temprgb                = this->Data[imgidx];
				this->Data[imgidx]     = this->Data[imgidx + 2];
				this->Data[imgidx + 2] = temprgb;
			}
		}

		//----------------------------------------------------------------------------------
		// Y finalmente cerramos el fichero.
		//----------------------------------------------------------------------------------
		fclose(file);
		return true;
	}

	//--------------------------------------------------------------------------------------
	// Función para salvar un tga en memoria.
	//--------------------------------------------------------------------------------------
	bool CImage::SaveTGAFile (const char * name)
	{
		//----------------------------------------------------------------------------------
		// Configuramos los valores de la cabecera.
		//----------------------------------------------------------------------------------
		TARGAFILEHEADER header;

		header.imageIDLength = 0;
		header.colorMapType  = 0;
		header.imageTypeCode = this->Type;

		header.colorMapOrigin    = 0;
		header.colorMapLength    = 0;
		header.colorMapEntrySize = 0;

		header.imageXOrigin    = 0;
		header.imageYOrigin    = 0;
		header.imageWidth      = this->Width;
		header.imageHeight     = this->Height;
		header.bitCount        = this->Depth;

		if(this->Depth == 32)
			header.imageDescriptor = 0x08;
		else
			header.imageDescriptor = 0x00;

		//----------------------------------------------------------------------------------
		// Calculamos el tamaño en bytes de un pixel y el de la imagen.
		//----------------------------------------------------------------------------------
		BYTE  colormode = this->Depth / 8;
		DWORD imagesize = this->Width * this->Height * colormode;

		//----------------------------------------------------------------------------------
		// Dependiendo de la profundidad crearemos un buffer temporal donde vamos a
		// almacenar la imagen que tenemos dentro del objeto.
		//----------------------------------------------------------------------------------
		unsigned char * data = NULL;

		if((this->Depth == 24) || (this->Depth == 32))
		{
			data = (unsigned char *) malloc (imagesize);

			if(data == NULL) return appSetLastError(TEXERR_SAVETGA_NULLMALLOC);

			//------------------------------------------------------------------------------
			// Esto es para poder invertir el orden de sus colores y salvar el tga bien.
			//------------------------------------------------------------------------------
			DWORD imgidx;

			for(imgidx = 0; imgidx < imagesize; imgidx += colormode)
			{
				data[imgidx]     = this->Data[imgidx + 2];
				data[imgidx + 1] = this->Data[imgidx + 1];
				data[imgidx + 2] = this->Data[imgidx];
			}
		}
		else
		{
			data = this->Data;
		}

		//----------------------------------------------------------------------------------
		// Abrimos el fichero.
		//----------------------------------------------------------------------------------
		FILE * file;

		file = fopen(name, "wb");
		if(file == NULL)
		{
			if((this->Depth == 24) || (this->Depth == 32))
				free(data);

			return appSetLastError(TEXERR_SAVETGA_FOPEN);
		}

		//----------------------------------------------------------------------------------
		// Escribimos la cabecera.
		//----------------------------------------------------------------------------------
		fwrite(&(header.imageIDLength), 1, 1, file);
		fwrite(&(header.colorMapType),  1, 1, file);
		fwrite(&(header.imageTypeCode), 1, 1, file);

		fwrite(&(header.colorMapOrigin),    2, 1, file);
		fwrite(&(header.colorMapLength),    2, 1, file);
		fwrite(&(header.colorMapEntrySize), 1, 1, file);

		fwrite(&(header.imageXOrigin),    2, 1, file);
		fwrite(&(header.imageYOrigin),    2, 1, file);
		fwrite(&(header.imageWidth),      2, 1, file);
		fwrite(&(header.imageHeight),     2, 1, file);
		fwrite(&(header.bitCount),        1, 1, file);
		fwrite(&(header.imageDescriptor), 1, 1, file);

		//----------------------------------------------------------------------------------
		// Escribimos el contenido de la imagen.
		//----------------------------------------------------------------------------------
		fwrite(data, sizeof(unsigned char), imagesize, file);

		//----------------------------------------------------------------------------------
		// Cerramos el fichero y devolvemos que todo ha ido bien.
		//----------------------------------------------------------------------------------
		if((this->Depth == 24) || (this->Depth == 32))
		{
			free(data);
		}

		fclose(file);

		return true;
	}

//******************************************************************************************
// Miembros de la clase CTexture.
//******************************************************************************************

	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CTexture.
	//--------------------------------------------------------------------------------------
	CTexture::CTexture ()
	{
		this->Name      = 0;
		this->Image     = NULL;
		this->MinFilter = GL_LINEAR_MIPMAP_LINEAR;
		this->MagFilter = GL_LINEAR;
		this->WrapS     = GL_REPEAT;
		this->WrapT     = GL_REPEAT;
		this->Mode      = GL_MODULATE;
	}

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CTexture.
	//--------------------------------------------------------------------------------------
	CTexture::CTexture (CImage * image, GLint minfilter, GLint magfilter, GLint wraps,
						GLint wrapt, GLint mode)
	{
		this->Name      = 0;
		this->Image     = NULL;
		this->MinFilter = minfilter;
		this->MagFilter = magfilter;
		this->WrapS     = wraps;
		this->WrapT     = wrapt;
		this->Mode      = mode;
		
		this->Load(image);
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CTexture.
	//--------------------------------------------------------------------------------------
	CTexture::CTexture (const CTexture & obj)
	{
		this->CopyFrom(obj);
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CTexture.
	//--------------------------------------------------------------------------------------
	CTexture::~CTexture ()
	{
		this->Release();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CTexture & CTexture::operator = (const CTexture & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CTexture::CopyFrom (const CTexture & obj)
	{
		this->Name      = obj.Name;
		this->Image     = obj.Image;
		this->MinFilter = obj.MinFilter;
		this->MagFilter = obj.MagFilter;
		this->WrapS     = obj.WrapS;
		this->WrapT     = obj.WrapT;
		this->Mode      = obj.Mode;
	}

	//**************************************************************************************
	// Logica.
	//**************************************************************************************
	
	//--------------------------------------------------------------------------------------
	// Método para cargar una imagen de la memoria ram a la memoria de video.
	//--------------------------------------------------------------------------------------
	bool CTexture::Load (CImage * image)
	{
		appResetLastError();

		//----------------------------------------------------------------------------------
		// Comprobamos que no estamos pasando un puntero nulo.
		//----------------------------------------------------------------------------------
		if(image == NULL) return appSetLastError(TEXERR_TEXTURE_LOAD_NULLIMAGE);

		//----------------------------------------------------------------------------------
		// Luego filtramos cualquier imagen que no sea de 8, 24 o 32 bits de profundidad.
		//----------------------------------------------------------------------------------
		if((image->GetDepth() == 32) || (image->GetDepth() == 24) ||
		   (image->GetDepth() == 8))
		{
			//------------------------------------------------------------------------------
			// Apuntamos desde la textura a la imagen que se nos ha pasado.
			//------------------------------------------------------------------------------
			this->Image = image;

			//------------------------------------------------------------------------------
			// Seleccionamos el formato en base a la profundidad.
			//------------------------------------------------------------------------------
			GLint format;

			if(this->Image->GetDepth() == 32)
			{
				format = GL_RGBA;
			}
			else if (this->Image->GetDepth() == 24)
			{
				format = GL_RGB;
			}
			else
			{
				format = GL_LUMINANCE;
			}

			//------------------------------------------------------------------------------
			// Reservamos un nombre identificador de la textura en la tarjeta, y la
			// mandamos crear, activándola como la textura actual en uso.
			//------------------------------------------------------------------------------
			glGenTextures(1, &(this->Name));
			glBindTexture(GL_TEXTURE_2D, this->Name);

			//------------------------------------------------------------------------------
			// Y finalmente generamos los mipmaps cargando en memoria la textura.
			//------------------------------------------------------------------------------
			gluBuild2DMipmaps(GL_TEXTURE_2D, format, this->Image->GetWidth(),
							  this->Image->GetHeight(), format, GL_UNSIGNED_BYTE,
							  this->Image->GetData());

			return true;
		}
		else
		{
			return appSetLastError(TEXERR_TEXTURE_LOAD_BADDEPTH);
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para recargar una imagen de la memoria ram a la memoria de video.
	//--------------------------------------------------------------------------------------
	bool CTexture::Reload (void)
	{
		appResetLastError();

		//----------------------------------------------------------------------------------
		// Comprobamos que no estamos usando un puntero nulo.
		//----------------------------------------------------------------------------------
		if(this->Image == NULL) return appSetLastError(TEXERR_TEXTURE_RELOAD_NULLIMG);

		//----------------------------------------------------------------------------------
		// Seleccionamos el formato en base a la profundidad.
		//----------------------------------------------------------------------------------
		GLint format;

		if(this->Image->GetDepth() == 32)
		{
			format = GL_RGBA;
		}
		else if (this->Image->GetDepth() == 24)
		{
			format = GL_RGB;
		}
		else
		{
			format = GL_LUMINANCE;
		}

		//----------------------------------------------------------------------------------
		// Indicamos a OpenGL cual es la textura actual en uso.
		//----------------------------------------------------------------------------------
		glBindTexture(GL_TEXTURE_2D, this->Name);

		//----------------------------------------------------------------------------------
		// Y finalmente generamos los mipmaps cargando en memoria la textura.
		//----------------------------------------------------------------------------------
		gluBuild2DMipmaps(GL_TEXTURE_2D, format, this->Image->GetWidth(),
						  this->Image->GetHeight(), format, GL_UNSIGNED_BYTE,
						  this->Image->GetData());

		return true;
	}

	//--------------------------------------------------------------------------------------
	// Método para activar como textura en uso la actual.
	//--------------------------------------------------------------------------------------
	void CTexture::Use (void)
	{
		//----------------------------------------------------------------------------------
		// Activamos el uso de texturas 2D.
		//----------------------------------------------------------------------------------
		glEnable(GL_TEXTURE_2D);

		//----------------------------------------------------------------------------------
		// Activamos esta textura como la actual en uso.
		//----------------------------------------------------------------------------------
		glBindTexture(GL_TEXTURE_2D, this->Name);
		
		//----------------------------------------------------------------------------------
		// Indicamos los parametros de magnificación y minificación.
		//----------------------------------------------------------------------------------
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->MagFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->MinFilter);
		
		//----------------------------------------------------------------------------------
		// Indicamos los parametros de repetición o expansión de la textura.
		//----------------------------------------------------------------------------------
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->WrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->WrapT);

		//----------------------------------------------------------------------------------
		// E indicamos el modo de pintado de la textura sobre los objetos.
		//----------------------------------------------------------------------------------
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, this->Mode);
	}

	//--------------------------------------------------------------------------------------
	// Método para liberar la textura y la imagen de la memoria de video.
	//--------------------------------------------------------------------------------------
	void CTexture::Release (void)
	{
		if(this->Image != NULL)
		{
			glDeleteTextures(1, &(this->Name));
			
			this->Name      = 0;
			this->Image     = NULL;
			this->MinFilter = GL_LINEAR_MIPMAP_LINEAR;
			this->MagFilter = GL_LINEAR;
			this->WrapS     = GL_REPEAT;
			this->WrapT     = GL_REPEAT;
			this->Mode      = GL_MODULATE;
		}
	}

//******************************************************************************************
// textures.cpp
//******************************************************************************************