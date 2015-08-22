#include "Multitexturing.h"

using namespace BasicEngine::Rendering;

const float PI = 3.1415927;

int indicesSize;

std::chrono::time_point<std::chrono::system_clock> startTime;

Multitexturing::Multitexturing()
{

}


Multitexturing::~Multitexturing()
{

}

void Multitexturing::CreateSphere(float radius, unsigned int rings, unsigned int sectors) {

	// Generate a sphere
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;

	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	vertices.resize(rings * sectors * 3);
	//normals.resize(rings * sectors * 3);
	texcoords.resize(rings * sectors * 2);

	std::vector<GLfloat>::iterator v = vertices.begin();
	//std::vector<GLfloat>::iterator n = normals.begin();
	std::vector<GLfloat>::iterator t = texcoords.begin();

	// Calculate vertices' position and their respective texture coordinates 
	for (r = 0; r < rings; r++) {
		for (s = 0; s < sectors; s++) {
			float const y = sin(-PI/2 + PI * r * R);
			float const x = cos(2 * PI * s * S) * sin(PI * r * R);
			float const z = sin(2 * PI * s * S) * sin(PI * r * R);

			*t++ = s*S;
			*t++ = r*R;

			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			//*n++ = -x;
			//*n++ = -y;
			//*n++ = -z;
		}
	}

	// Calculate indices 
	indices.resize(rings * sectors * 4);
	std::vector<GLushort>::iterator i = indices.begin();
	for (r = 0; r < rings - 1; r++) {
		for (s = 0; s < sectors - 1; s++) {
			
			*i++ = r * sectors + s;
			*i++ = r * sectors + (s+1);
			*i++ = (r+1) * sectors + (s+1);
			*i++ = (r+1) * sectors + s;
		}
	}

	// Use Sergiu's & Vlad's approach for storing everything in a VertexFormat(vec3 vertices, vex2 texCoords) & binding everything
	GLuint vao, vbo, ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertexData;
	
	int count = 0;
	for (int verts = 0; verts < vertices.size(); verts += 3) {
		for (int j = count; j < texcoords.size(); j += 2) {
			vertexData.push_back(VertexFormat(glm::vec3(vertices[verts], vertices[verts + 1], vertices[verts + 2]), glm::vec2(texcoords[j], texcoords[j + 1])));
			count += 2;
			break;
		}
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(VertexFormat), &vertexData[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	m_RotationSpeed = glm::vec3(90.0, 90.0, 90.0);
	m_Rotation = glm::vec3(0.0, 0.0, 0.0);
	indicesSize = indices.size();

	startTime = HiResTime::now();
}

void Multitexturing::Update()
{
	m_Rotation = 0.01f * m_RotationSpeed + m_Rotation;
	m_RotationSin = glm::vec3(m_Rotation.x * PI / 180, m_Rotation.y * PI / 180, m_Rotation.z * PI / 180);
}

void Multitexturing::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("BaseTexture"));
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("SecondTexture"));
	unsigned int secondTextureLocation = glGetUniformLocation(program, "texture2");
	glUniform1i(secondTextureLocation, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("ThirdTexture"));
	unsigned int thirdTextureLocation = glGetUniformLocation(program, "texture3");
	glUniform1i(thirdTextureLocation, 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("AlphaChanTexture"));
	unsigned int alphaChanTextureLocation = glGetUniformLocation(program, "texture4");
	glUniform1i(alphaChanTextureLocation, 3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("RampTexture"));
	unsigned int rampTextureLocation = glGetUniformLocation(program, "texture5");
	glUniform1i(rampTextureLocation, 4);
	
	auto      endTime = HiResTime::now();
	DeltaTime dt      = endTime - startTime; //in seconds
	MiliSec   dtMS = std::chrono::duration_cast<MiliSec>(dt); //in ms
	glUniform1f(glGetUniformLocation(program, "Timer"), dtMS.count());

	glUniform3f(glGetUniformLocation(program, "rotation"), m_RotationSin.x, m_RotationSin.y, m_RotationSin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	
	// Need to draw twice since the textures are scrolling and we do not wish for the back of the texture to be drawn over the front (depth!!!)
	glCullFace(GL_BACK); // draw back face 
	glDrawElements(GL_QUADS, indicesSize, GL_UNSIGNED_SHORT, 0);

	glCullFace(GL_FRONT); // draw front face
	glDrawElements(GL_QUADS, indicesSize, GL_UNSIGNED_SHORT, 0);
}
