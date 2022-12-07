#include "Application.h"

int x, y;

Application::Application(const unsigned width, const unsigned height)
{
	Application::width = width;
	Application::height = height;

	init();
	gameLoop();
	destroy();
}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double cx, double cy)
{
	//printf("cursor_callback \n");
	x = cx;
	y = cy;
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);

	if (action == GLFW_PRESS) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		GLbyte color[4];
		GLfloat depth;
		GLuint index; // identifikace tìlesa
		int newy = height - y;
		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
	}
}

void Application::set_error_callback()
{
	glfwSetErrorCallback(error_callback);
}

void Application::set_callbacks()
{
	// Sets the key callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
}

void Application::init()
{
	set_error_callback();
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	set_callbacks();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::init(int major, int minor)
{
	//window;
	//set_error_callback();
	//if (!glfwInit()) {
	//	fprintf(stderr, "ERROR: could not start GLFW3\n");
	//	exit(EXIT_FAILURE);
	//}

	////inicializace konkretni verze
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
	//if (!window) {
	//	glfwTerminate();
	//	exit(EXIT_FAILURE);
	//}

	//glfwMakeContextCurrent(window);
	//glfwSwapInterval(1);

	//// start GLEW extension handler
	//glewExperimental = GL_TRUE;
	//glewInit();

	//set_callbacks();

	//// get version info
	//printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	//printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	//printf("Vendor %s\n", glGetString(GL_VENDOR));
	//printf("Renderer %s\n", glGetString(GL_RENDERER));
	//printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//int revision;
	//glfwGetVersion(&major, &minor, &revision);
	//printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	//int width, height;
	//glfwGetFramebufferSize(window, &width, &height);
	////float ratio = width / (float)height;
	//glViewport(0, 0, width, height);


	////glMatrixMode(GL_PROJECTION);
	////glLoadIdentity();
	////glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void Application::gameLoop()
{
	// Ball scene to test phong shader
	Scene ballScene(width, height);

	Model ballModel;
	ballModel.generate_VBO(sphere, sizeof(sphere), sizeof(sphere) / 6);
	ballModel.generate_VAO6();

	ShaderProgram ballPhongShaderProgram;
	ballPhongShaderProgram.AttachShaders("phong.vert", "phong.frag");
	ballPhongShaderProgram.LinkProgram();
	ballPhongShaderProgram.CheckLinkStatus();

	DrawableObject drawableBallLeft = DrawableObject(&ballModel);
	drawableBallLeft.Translate(glm::vec3(-3.0f, .0f, 0.0f));
	DrawableObject drawableBallRight = DrawableObject(&ballModel);
	drawableBallRight.Translate(glm::vec3(3.0f, .0f, 0.0f));
	DrawableObject drawableBallDown = DrawableObject(&ballModel);
	drawableBallDown.Translate(glm::vec3(0.0f, .0f, 3.0f));
	DrawableObject drawableBallUp = DrawableObject(&ballModel);
	drawableBallUp.Translate(glm::vec3(0.0f, .0f, -3.0f));


	ballScene.AddToVectorModelsShaders(&drawableBallLeft, &ballPhongShaderProgram);
	ballScene.AddToVectorModelsShaders(&drawableBallRight, &ballPhongShaderProgram);
	ballScene.AddToVectorModelsShaders(&drawableBallDown, &ballPhongShaderProgram);
	ballScene.AddToVectorModelsShaders(&drawableBallUp, &ballPhongShaderProgram);



	// Main Scene

	Scene scene(width, height);

	Model houseModel;
	houseModel.generate_VBO("Models/house.obj");
	houseModel.generate_VAO8();

	Model zombieModel;
	zombieModel.generate_VBO("Models/zombie.obj");
	zombieModel.generate_VAO8();

	Model terrainModel;
	terrainModel.generate_VBO("Models/teren.obj");
	terrainModel.generate_VAO8();

	Model treeModel;
	treeModel.generate_VBO("Models/tree.obj");
	treeModel.generate_VAO8();

	DrawableObject drawableHouse = DrawableObject(&houseModel);
	drawableHouse.Translate(glm::vec3(0.0f, 0.0f, -15.0f));

	DrawableObject drawableZombie1 = DrawableObject(&zombieModel);
	drawableZombie1.Translate(glm::vec3(0.0f, 0.0f, 15.0f));

	DrawableObject drawableTerrain = DrawableObject(&terrainModel);
	drawableTerrain.Scale(glm::vec3 (2.0f));

	DrawableObject drawableTree1 = DrawableObject(&treeModel);
	drawableTree1.Translate(glm::vec3(12.0f, 0.0f, 15.0f));
	drawableTree1.Scale(glm::vec3(0.2f));

	DrawableObject drawableTree2 = DrawableObject(&treeModel);
	drawableTree2.Translate(glm::vec3(15.0f, 0.0f, 12.0f));
	drawableTree2.Scale(glm::vec3(0.1f));

	Model skycubeModel;
	DrawableObject drawableOSkycube = DrawableObject(&skycubeModel);
	drawableOSkycube.model->generate_VBO(skycube, sizeof(skycube), sizeof(skycube) / 3);
	drawableOSkycube.model->generate_skybox_VAO();


	ShaderProgram shader_program;
	shader_program.AttachShaders("default.vert", "default.frag");
	shader_program.LinkProgram();
	shader_program.CheckLinkStatus();

	ShaderProgram shader_program2;
	shader_program2.AttachShaders("phong.vert", "phong.frag");
	shader_program2.LinkProgram();
	shader_program2.CheckLinkStatus();

	ShaderProgram textureShader;
	textureShader.AttachShaders("texture.vert", "texture.frag");
	textureShader.LinkProgram();
	textureShader.CheckLinkStatus();

	ShaderProgram skyboxShader;
	skyboxShader.AttachShaders("skybox.vert", "skybox.frag");
	skyboxShader.LinkProgram();
	skyboxShader.CheckLinkStatus();






	Skybox skybox(99);
	skybox.LoadCubemap();
	skybox.BindTexture();



	Texture treeTexture(5);
	treeTexture.LoadTexture("Textures/tree.png");
	treeTexture.BindTexture();
	Texture grassTexture(6);
	grassTexture.LoadTexture("Textures/grass.png");
	grassTexture.BindTexture();
	grassTexture.Parameters();
	Texture houseTexture(7);
	houseTexture.LoadTexture("Textures/house.png");
	houseTexture.BindTexture();
	Texture zombieTexture(8);
	zombieTexture.LoadTexture("Textures/zombie.png");
	zombieTexture.BindTexture();
	

	scene.AddSkybox(&drawableOSkycube, &skyboxShader, &skybox);
	scene.AddToVectorModelsShadersTextures(&drawableHouse, &textureShader, &houseTexture);
	scene.AddToVectorModelsShadersTextures(&drawableZombie1, &textureShader, &zombieTexture);
	scene.AddToVectorModelsShadersTextures(&drawableTerrain, &textureShader, &grassTexture);
	scene.AddToVectorModelsShadersTextures(&drawableTree1, &textureShader, &treeTexture);
	scene.AddToVectorModelsShadersTextures(&drawableTree2, &textureShader, &treeTexture);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		// draw all objects


		ballScene.camera->UpdateWorldWidthAndHeight(Application::width, Application::height);
		ballScene.camera->UpdateCamera(window);
		ballScene.DrawAllBalls();




		//scene.camera->UpdateWorldWidthAndHeight(Application::width, Application::height);
		//scene.camera->UpdateCamera(window);
		//scene.DrawAllObjectsWithSkybox();

		// update other events like input handling
		glfwPollEvents();
		// put the stuff weve been drawing onto the display
		glfwSwapBuffers(window);
	}
}

void Application::destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


