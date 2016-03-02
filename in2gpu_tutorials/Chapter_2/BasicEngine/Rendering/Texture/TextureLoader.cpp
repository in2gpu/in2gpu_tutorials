#include "TextureLoader.h"
using namespace BasicEngine::Rendering;

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{

}

unsigned int TextureLoader::LoadTexture(const std::string& filename, unsigned int width, unsigned int height)
{
	
	unsigned char* data;
	LoadBMPFile(filename, width, height, data);

	//create the OpenGL texture
	unsigned int gl_texture_object;
	glGenTextures(1, &gl_texture_object);
	glBindTexture(GL_TEXTURE_2D, gl_texture_object);

	//filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Following commented two lines are deprecated in OpenGL 3.1 and above.
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	float maxAnisotropy = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	//cand lucram cu texturi cu dimensiuni non multiple de 4 trebuie sa facem cititorul de randuri
	//ce incarca texturile in OpenGL sa lucreze cu memorie aliniata la 1 (default este la 4)
	//when we work with textures of sizes not divisible by 4 we have to use the line reader
	//which loads the textures in OpenGL so as it can work with a 1 alligned memory (default is 4)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Generates texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//eliminates the array from the RAM
	delete data;

	//creates the mipmap hierarchy
	glGenerateMipmap(GL_TEXTURE_2D);

	//returns the texture object
	return gl_texture_object;
}

void TextureLoader::LoadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data)
{
	//read the file
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good()){
		std::cout << "Texture Loader: Cannot open texture file ";
		width = 0;
		height = 0;
		return;
	}


	//reads the headers
	Texture::BMP_Header h; Texture::BMP_Header_Info h_info;
	file.read((char*)&(h.type[0]), sizeof(char));
	file.read((char*)&(h.type[1]), sizeof(char));
	file.read((char*)&(h.f_lenght), sizeof(int));
	file.read((char*)&(h.rezerved1), sizeof(short));
	file.read((char*)&(h.rezerved2), sizeof(short));
	file.read((char*)&(h.offBits), sizeof(int));
	file.read((char*)&(h_info), sizeof(Texture::BMP_Header_Info));

	//assigning memory (a pixel has 3 components, R, G, B)
	data = new unsigned char[h_info.width*h_info.height * 3];

	// check if the line contains 4 byte groups
	long padd = 0;
	if ((h_info.width * 3) % 4 != 0) padd = 4 - (h_info.width * 3) % 4;

	//save height &width
	width = h_info.width;
	height = h_info.height;

	long pointer;
	unsigned char r, g, b;
	//reading the matrix
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			file.read((char*)&b, 1);	//in bmp, the component order in the pixel is b,g,r (in Windows)
			file.read((char*)&g, 1);
			file.read((char*)&r, 1);

			pointer = (i*width + j) * 3;
			data[pointer] = r;
			data[pointer + 1] = g;
			data[pointer + 2] = b;
		}

		file.seekg(padd, std::ios_base::cur);
	}
	file.close();
}