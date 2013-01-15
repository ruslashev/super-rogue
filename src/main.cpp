#include "engine.hpp"
#include "main.hpp"

GLuint textureID;
// Exported from GIMP
unsigned char tile[16 * 16 * 3 + 1] = "\370R\37\370R\37\370o\34\370\273\23\370\303\22\370\246\25\363R\37\367R\37\370\222\30\370\301\22\370\277\23\370\211\31\370R\37\370R\37\370R\37\370i\34\370R\37\370R\37\370W\36\370\264\24\370\304\22\370\270\23\316Z\37\342g/\367\251\25\367\302\22\370\273\23\370o\34\370R\37\370`\35\370\216\30\370\273\23\370R\37\370R\37\370R\37\367\224\27\350\266\22\302\234!\232\243Q\254\237U\275\232,\276\242#\336\253&\365\\\35\370v\33\370\257\24\370\301\22\370\304\22\370\216\30\370`\35\365Q\37\271\211/\236\265Ry~Jam7\204\263b\236\275~y\220@\233\2036\322\243&\364\274\23\370\302\22\370\300\22\370\267\24\370\301\22\365\256\24\315z\33~\252S\204\256_y\216Ur\216L\213\270g\230\274x~\231Uik-\231\257A\330\302.\367\274\23\370\226\27\370`\35\370\300\22\347\270\27\245\226(r\245Un\242Um\246Wr\261]\202\263ra~Bs\252Q\210\272m\224\300{\303\302\\\360u\35\370X\36\370R\37\370\226\27\335\256\33\227\216-r\234[n\231]n\246`s\262e\243\315\255u\235mb\233F\213\274\202\242\312\235\262\247Y\350U#\370R\37\370R\37\370X\36\335k\37\227v*p\204Nn\215Tf\222No\246Xy\256de\222LZ\2137j\241L\204\260a\247\226K\351R\40\370R\37\370R\37\370o\34\352\212\30\262\206\30rj8ri9l|@p\223Kv\240Ue\204<c\215;n\227Dy\244O\252\220@\360Q\37\370R\37\370R\37\370\273\23\361\275\22\343\263\21tg3wi7r{@n|>z\224Nni0j~3m\216>w\240H\260\264<\362\237\26\370m\34\370R\37\370\303\22\366\276\22\366\266\23\201W)zi9sf6ps:w\211Gli1j\204:p\224Ew\243K\255\270=\361\277\22\370\271\23\370i\34\370\253\25\370\213\30\370`\35\230@\36w_6me5pw=r|?mW+ju5o\226Fw\244I\264\2647\364\301\22\370\303\22\370\273\23\370X\36\370R\37\370R\37\274Y\27wT1nc4s\203Duy>k<\"lJ$o\206:\210\226@\325j\37\370\247\25\370\300\23\370\304\22\370R\37\370R\37\370`\35\357\250\23\204R\36wL+tU.~X-i+\20q6\25\217L\37\323Q\40\367R\37\370X\36\370{\32\370\273\23\370R\37\370W\36\370\226\27\370\300\22\347\262\21\302r\23\305G\32\336\224\23\361\276\22\363\267\23\367o\34\370R\37\370R\37\370R\37\370R\37\370i\34\370R\37\370v\33\370\275\23\370\302\22\370\256\25\370`\35\361R\37\366\214\30\370\301\22\370\301\22\370\215\30\370R\37\370R\37\370R\37\370R\37\370R\37";

GLint posAttrib, texAttrib;
GLuint vbo_vertices, vbo_texcoords;
std::vector<glm::vec2> vertices;
std::vector<glm::vec2> texCoords;

int main()
{
	renderer drawman(800, 600, "pew pew pew");

	drawman.projection = glm::ortho(0.f, (float)800, (float)600, 0.f);
	drawman.mvpUniform = glGetUniformLocation(drawman.shaderProgram, "mvp");
	
	vbo_vertices = 0;
	vbo_texcoords = 0;

	int tileSize = 16;
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			vertices.push_back(glm::vec2(x*1.1*tileSize, 			y*1.1*tileSize));
			vertices.push_back(glm::vec2(x*1.1*tileSize, 			y*1.1*tileSize+tileSize));
			vertices.push_back(glm::vec2(x*1.1*tileSize+tileSize, 	y*1.1*tileSize+tileSize));
			vertices.push_back(glm::vec2(x*1.1*tileSize+tileSize, 	y*1.1*tileSize));
			
			texCoords.push_back(glm::vec2(0.0, 0.0));
			texCoords.push_back(glm::vec2(0.0, 1.0));
			texCoords.push_back(glm::vec2(1.0, 1.0));
			texCoords.push_back(glm::vec2(1.0, 0.0));
		}
	}
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &vbo_texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size()*sizeof(texCoords[0]), texCoords.data(), GL_STATIC_DRAW);


	glUniform1i(glGetUniformLocation(drawman.shaderProgram, "tile"), 0);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, tile);
	

	const double constdt = 0.01;
	drawman.oldTime = glfwGetTime();
	while (drawman.running)
	{
		drawman.updateTime();
		
		while (drawman.dt >= constdt)
		{
			drawman.update();
			drawman.draw();
	
			drawman.time += constdt;
			drawman.dt -= constdt;
		}
	}

	return 0;
}

void renderer::update()
{
	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(projection));
}
void renderer::draw()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// for (std::vector<mesh>::iterator i = meshes.begin(); i != meshes.end(); i++)
	// {
	// 	i->draw(GL_QUADS);
	// }

	glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(texAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_QUADS, 0, vertices.size());

	glfwSwapBuffers();
}

void renderer::cleanup()
{
	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &vbo_texcoords);
	glDeleteTextures(1, &textureID);
}