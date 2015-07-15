#include "CubeTexture.h"
using namespace BasicEngine::Rendering;

#define PI 3.14159265

CubeTexture::CubeTexture()
{
}


CubeTexture::~CubeTexture()
{
}

void CubeTexture::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	time(&timer);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices; 
	std::vector<unsigned int>  indices = { 0,  1,  2,  0,  2,  3,   //front
										   4,  5,  6,  4,  6,  7,   //right
								           8,  9,  10, 8,  10, 11 ,  //back
										   12, 13, 14, 12, 14, 15,  //left
										   16, 17, 18, 16, 18, 19,  //upper
										   20, 21, 22, 20, 22, 23}; //bottom
	//front
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3( 1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3( 1.0,  1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0,  1.0, 1.0), glm::vec2(0, 1)));
			
	//right
	vertices.push_back(VertexFormat(glm::vec3(1.0,  1.0,  1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0,  1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0,  1.0), glm::vec2(0, 1)));

	//back
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),  glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0,  -1.0, -1.0),  glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0,   1.0, -1.0),  glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0,  1.0, -1.0),  glm::vec2(0, 1)));

	//left
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0,  1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0,  1.0,  1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0,  1.0, -1.0), glm::vec2(0, 1)));

	//upper
	vertices.push_back(VertexFormat(glm::vec3( 1.0, 1.0,  1.0),  glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0,  1.0),  glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0),  glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3( 1.0, 1.0, -1.0),  glm::vec2(0, 1)));
	

	////bottom
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3( 1.0, -1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3( 1.0, -1.0,  1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0,  1.0), glm::vec2(0, 1)));
	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,   vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	rotation_speed = glm::vec3(90.0, 90.0, 90.0);
	rotation = glm::vec3(0.0, 0.0, 0.0);

}

void CubeTexture::Update()
{
	rotation = 0.01f * rotation_speed + rotation;
	rotation_sin = glm::vec3(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);
}

void CubeTexture::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("Create"));
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	glUniform3f(glGetUniformLocation(program, "rotation"), rotation_sin.x, rotation_sin.y, rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
