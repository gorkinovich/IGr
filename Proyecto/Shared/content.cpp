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
#include "content.h"
//******************************************************************************************
// Miembros de la clase CContentManager.
//******************************************************************************************

	//**************************************************************************************
	// Constructores y destructor.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CContentManager.
	//--------------------------------------------------------------------------------------
	CContentManager::CContentManager ()
	{
		this->Images.clear();
		this->Textures.clear();
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CContentManager.
	//--------------------------------------------------------------------------------------
	CContentManager::~CContentManager ()
	{
		this->Images.clear();
		this->Textures.clear();
	}

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************
	
	//--------------------------------------------------------------------------------------
	// Método para borrar una imagen de la memoria ram.
	//--------------------------------------------------------------------------------------
	void CContentManager::ReleaseImage (const char * name)
	{
		list<CImage *>::iterator i;
		CImage * aux = NULL;

		//----------------------------------------------------------------------------------
		// Para encontrar la imagen que queremos borrar, tenemos que ir una por una,
		// comprobando si tiene el mismo nombre o ruta. Una vez es encontrada borramos el
		// objeto de tipo CImage, eliminamos el nodo de la lista y salimos del bucle.
		//----------------------------------------------------------------------------------
		for(i = this->Images.begin(); i != this->Images.end(); ++i)
		{
			aux = *i;

			if(aux->GetName() == name)
			{
				delete aux;
				this->Images.erase(i);
				break;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para borrar una textura de la memoria de video.
	//--------------------------------------------------------------------------------------
	void CContentManager::ReleaseTexture (const char * name)
	{
		list<CTexture *>::iterator i;
		CTexture * aux = NULL;

		//----------------------------------------------------------------------------------
		// Para encontrar la textura que queremos borrar, tenemos que ir una por una,
		// comprobando si tiene el mismo nombre o ruta. Una vez es encontrada borramos el
		// objeto de tipo CTexture, eliminamos el nodo de la lista y salimos del bucle.
		//----------------------------------------------------------------------------------
		for(i = this->Textures.begin(); i != this->Textures.end(); ++i)
		{
			aux = *i;

			if(aux->GetImage()->GetName() == name)
			{
				delete aux;
				this->Textures.erase(i);
				break;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para borrar todas las imagenes de la memoria ram.
	//--------------------------------------------------------------------------------------
	void CContentManager::ReleaseAllImages (void)
	{
		list<CImage *>::iterator i;
		CImage * aux = NULL;

		//----------------------------------------------------------------------------------
		// Recorremos la lista entera nodo por nodo eliminando cada objeto de tipo CImage.
		//----------------------------------------------------------------------------------
		for(i = this->Images.begin(); i != this->Images.end(); ++i)
		{
			aux = *i;
			delete aux;
		}

		//----------------------------------------------------------------------------------
		// Para finalmente borrar todos los nodos de la lista.
		//----------------------------------------------------------------------------------
		this->Images.clear();
	}

	//--------------------------------------------------------------------------------------
	// Método para borrar todas las texturas de la memoria de video.
	//--------------------------------------------------------------------------------------
	void CContentManager::ReleaseAllTextures (void)
	{
		list<CTexture *>::iterator i;
		CTexture * aux = NULL;

		//----------------------------------------------------------------------------------
		// Recorremos la lista entera nodo por nodo eliminando cada objeto de tipo CTexture.
		//----------------------------------------------------------------------------------
		for(i = this->Textures.begin(); i != this->Textures.end(); ++i)
		{
			aux = *i;
			delete aux;
		}

		//----------------------------------------------------------------------------------
		// Para finalmente borrar todos los nodos de la lista.
		//----------------------------------------------------------------------------------
		this->Textures.clear();
	}

	//--------------------------------------------------------------------------------------
	// Método para borrar todos los contenidos almacenados en la clase.
	//--------------------------------------------------------------------------------------
	void CContentManager::ReleaseAll (void)
	{
		this->ReleaseAllImages();
		this->ReleaseAllTextures();
	}

	//--------------------------------------------------------------------------------------
	// Método para buscar una imagen en la lista.
	//--------------------------------------------------------------------------------------
	CImage * CContentManager::SearchImage (const char * name)
	{
		list<CImage *>::iterator i;
		CImage * aux = NULL;

		//----------------------------------------------------------------------------------
		// Para encontrar la imagen que queremos buscar, tenemos que ir una por una,
		// comprobando si tiene el mismo nombre o ruta. En caso de encontrarla, cogeremos
		// el puntero y lo devolveremos.
		//----------------------------------------------------------------------------------
		for(i = this->Images.begin(); i != this->Images.end(); ++i)
		{
			aux = *i;

			if(aux->GetName() == name)
			{
				return aux;
			}
		}

		//----------------------------------------------------------------------------------
		// Si no hay ninguna imagen con el nombre que queremos, será que no existe.
		//----------------------------------------------------------------------------------
		return NULL;
	}

	//--------------------------------------------------------------------------------------
	// Método para buscar una textura en la lista.
	//--------------------------------------------------------------------------------------
	CTexture * CContentManager::SearchTexture (const char * name)
	{
		list<CTexture *>::iterator i;
		CTexture * aux = NULL;

		//----------------------------------------------------------------------------------
		// Para encontrar la textura que queremos buscar, tenemos que ir una por una,
		// comprobando si tiene el mismo nombre o ruta. En caso de encontrarla, cogeremos
		// el puntero y lo devolveremos.
		//----------------------------------------------------------------------------------
		for(i = this->Textures.begin(); i != this->Textures.end(); ++i)
		{
			aux = *i;

			if(aux->GetImage()->GetName() == name)
			{
				return aux;
			}
		}

		//----------------------------------------------------------------------------------
		// Si no hay ninguna textura con el nombre que queremos, será que no existe.
		//----------------------------------------------------------------------------------
		return NULL;
	}

	//**************************************************************************************
	// Gets.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para comprobar si una imagen está en la lista.
	//--------------------------------------------------------------------------------------
	bool CContentManager::IsImageLoaded (const char * name)
	{
		return (this->SearchImage(name) != NULL);
	}
	
	//--------------------------------------------------------------------------------------
	// Método para comprobar si una textura está en la lista.
	//--------------------------------------------------------------------------------------
	bool CContentManager::IsTextureLoaded (const char * name)
	{
		return (this->SearchTexture(name) != NULL);
	}
	
	//--------------------------------------------------------------------------------------
	// Método para obtener una imagen de la lista o cargarla en ella.
	//--------------------------------------------------------------------------------------
	CImage * CContentManager::GetImage (const char * name)
	{
		appResetLastError();

		//----------------------------------------------------------------------------------
		// Comprobamos primero si la imagen está en la lista.
		//----------------------------------------------------------------------------------
		CImage * aux = this->SearchImage(name);

		//----------------------------------------------------------------------------------
		// Si no está, nos devolverá NULL, por lo que tendremos que cargarla.
		//----------------------------------------------------------------------------------
		if(aux == NULL)
		{
			//------------------------------------------------------------------------------
			// Pedimos memoria para esta nueva imagen, si no lo logra devolveremos NULL.
			//------------------------------------------------------------------------------
			aux = new CImage();

			if(aux == NULL)
			{
				appSetLastError(TEXERR_CNTMNG_GETIMG_NULLNEW);
				return NULL;
			}

			//------------------------------------------------------------------------------
			// Luego mandamos cargar el fichero que estamos pidiendo. Si ocurriera algún
			// error, borraríamos el objeto creado y devolveríamos NULL.
			//------------------------------------------------------------------------------
			if(aux->LoadFile(name) == false)
			{
				delete aux;
				return NULL;
			}
			
			//------------------------------------------------------------------------------
			// Si logra cargar la imagen, añadimos el objeto a la lista de imagenes.
			//------------------------------------------------------------------------------
			this->Images.push_back(aux);
		}

		//----------------------------------------------------------------------------------
		// Y si todo ha ido bien, devolveremos el puntero al objeto pedido.
		//----------------------------------------------------------------------------------
		return aux;
	}

	//--------------------------------------------------------------------------------------
	// Método para obtener una imagen de la lista.
	//--------------------------------------------------------------------------------------
	CImage * CContentManager::GetImage (unsigned int index)
	{
		//----------------------------------------------------------------------------------
		// Comprobamos que el indice pasado está dentro del rango de valores. Si lo está
		// posicionaremos el iterador en el elemento indicado por index y lo devolveremos.
		//----------------------------------------------------------------------------------
		if(index < this->Images.size())
		{
			list<CImage *>::iterator i = this->Images.begin();
			unsigned int j;

			for(j = 0; j < index; ++j) ++i;

			return (*i);
		}

		//----------------------------------------------------------------------------------
		// Y si index está fuera del rango, devolveremos NULL.
		//----------------------------------------------------------------------------------
		return NULL;
	}

	//--------------------------------------------------------------------------------------
	// Método para obtener una textura de la lista o cargarla en ella.
	//--------------------------------------------------------------------------------------
	CTexture * CContentManager::GetTexture (const char * name)
	{
		appResetLastError();

		//----------------------------------------------------------------------------------
		// Comprobamos primero si la textura está en la lista.
		//----------------------------------------------------------------------------------
		CTexture * aux = this->SearchTexture(name);

		//----------------------------------------------------------------------------------
		// Si no está, nos devolverá NULL, por lo que tendremos que cargarla.
		//----------------------------------------------------------------------------------
		if(aux == NULL)
		{
			//------------------------------------------------------------------------------
			// Obtenemos la imagen de la lista.
			//------------------------------------------------------------------------------
			CImage * img = this->GetImage(name);
            if(img == NULL)
            {
                return NULL;
            }
			
			//------------------------------------------------------------------------------
			// Pedimos memoria para esta nueva textura, si no lo logra devolveremos NULL.
			//------------------------------------------------------------------------------
			aux = new CTexture(img);

			if(aux == NULL)
			{
				appSetLastError(TEXERR_CNTMNG_GETTEX_NULLNEW);
				return NULL;
			}

			//------------------------------------------------------------------------------
			// Si logra cargar la textura, añadimos el objeto a la lista de texturas.
			//------------------------------------------------------------------------------
			this->Textures.push_back(aux);
		}

		//----------------------------------------------------------------------------------
		// Y si todo ha ido bien, devolveremos el puntero al objeto pedido.
		//----------------------------------------------------------------------------------
		return aux;
	}

	//--------------------------------------------------------------------------------------
	// Método para obtener una textura de la lista.
	//--------------------------------------------------------------------------------------
	CTexture * CContentManager::GetTexture (unsigned int index)
	{
		//----------------------------------------------------------------------------------
		// Comprobamos que el indice pasado está dentro del rango de valores. Si lo está
		// posicionaremos el iterador en el elemento indicado por index y lo devolveremos.
		//----------------------------------------------------------------------------------
		if(index < this->Textures.size())
		{
			list<CTexture *>::iterator i = this->Textures.begin();
			unsigned int j;

			for(j = 0; j < index; ++j) ++i;

			return (*i);
		}

		//----------------------------------------------------------------------------------
		// Y si index está fuera del rango, devolveremos NULL.
		//----------------------------------------------------------------------------------
		return NULL;
	}

	//--------------------------------------------------------------------------------------
	// Método para obtener el número de imagenes de la lista.
	//--------------------------------------------------------------------------------------
	int CContentManager::GetNumImages (void)
	{
		return this->Images.size();
	}

	//--------------------------------------------------------------------------------------
	// Método para obtener el número de texturas de la lista.
	//--------------------------------------------------------------------------------------
	int CContentManager::GetNumTextures (void)
	{
		return this->Textures.size();
	}

	//**************************************************************************************
	// Miembros estáticos.
	//**************************************************************************************
	CContentManager * CContentManager::Instance = NULL;

	CContentManager * CContentManager::GetInstance (void)
	{
		if(CContentManager::Instance == NULL)
			CContentManager::Instance = new CContentManager();

		return CContentManager::Instance;
	}

//******************************************************************************************
// content.cpp
//******************************************************************************************