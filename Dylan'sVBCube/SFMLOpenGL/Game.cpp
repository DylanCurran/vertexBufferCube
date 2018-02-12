#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertexchips;

Vertexchips vertex1[6];
GLubyte triangles[6];
MyMatrix3 matrix[6];
/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	/* Vertices counter-clockwise winding */

	vertex1[0].coordinate[0] = -0.5f;
	vertex1[0].coordinate[1] = -0.5f;
	vertex1[0].coordinate[2] = 0.0f;

	vertex1[1].coordinate[0] = -0.5f;
	vertex1[1].coordinate[1] = 0.5f;
	vertex1[1].coordinate[2] = 0.0f;

	vertex1[2].coordinate[0] = 0.5f;
	vertex1[2].coordinate[1] = 0.5f;
	vertex1[2].coordinate[2] = 0.0f;

	vertex1[3].coordinate[0] = 0.5f; 
	vertex1[3].coordinate[1] = 0.5f;  
	vertex1[3].coordinate[2] = 0.0f;

	vertex1[4].coordinate[0] = 0.5f; 
	vertex1[4].coordinate[1] = -0.5f;  
	vertex1[4].coordinate[2] = 0.0f;

	vertex1[5].coordinate[0] = -0.5f; 
	vertex1[5].coordinate[1] = -0.5f;  
	vertex1[5].coordinate[2] = 0.0f;

	vertex1[0].color[0] = 0.1f;
	vertex1[0].color[1] = 1.0f;
	vertex1[0].color[2] = 0.0f;

	vertex1[1].color[0] = 0.2f;
	vertex1[1].color[1] = 1.0f;
	vertex1[1].color[2] = 0.0f;

	vertex1[2].color[0] = 0.3f;
	vertex1[2].color[1] = 1.0f;
	vertex1[2].color[2] = 0.0f;

	vertex1[3].color[0] = 0.4f;
	vertex1[3].color[1] = 1.0f;
	vertex1[3].color[2] = 1.0f;

	vertex1[4].color[0] = 0.5f;
	vertex1[4].color[1] = 1.0f;
	vertex1[4].color[2] = 1.0f;

	vertex1[5].color[0] = 0.6f;
	vertex1[5].color[1] = 1.0f;
	vertex1[5].color[2] = 1.0f;


	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;

	matrix[0] = { vertex1[0].coordinate[0],vertex1[0].coordinate[1],vertex1[0].coordinate[2],
				vertex1[1].coordinate[0], vertex1[1].coordinate[1],vertex1[1].coordinate[2],
				vertex1[2].coordinate[0],vertex1[2].coordinate[1],vertex1[2].coordinate[2] };
	matrix[1] = { vertex1[3].coordinate[0],vertex1[3].coordinate[1],vertex1[3].coordinate[2],
		vertex1[4].coordinate[0], vertex1[4].coordinate[1],vertex1[4].coordinate[2],
		vertex1[5].coordinate[0],vertex1[5].coordinate[1],vertex1[5].coordinate[2] };
	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexchips) * 6, vertex1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	//Change vertex data
	vertex1[0].coordinate[0] += -0.0001f;
	vertex1[0].coordinate[1] += -0.0001f;
	vertex1[0].coordinate[2] += -0.0001f;
	

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexchips) * 6, vertex1, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertexchips), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertexchips), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

