#include "Application.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Scene.h"
#include "Skybox.h"

#include "Models/sphere.h"
#include "Models/plain.h"
#include "Models/plain_uv.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/gift.h"
#include "Models/bushes.h"
#include "Models/skycube.h"


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

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{
	//printf("cursor_callback \n");
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
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
	Scene scene(width, height);

	Model houseModel;
	houseModel.generate_VBO("Models/house.obj");
	houseModel.generate_VAO8();
	DrawableObject drawableHouse = DrawableObject(&houseModel);

	Model zombieModel;
	zombieModel.generate_VBO("Models/zombie.obj");
	zombieModel.generate_VAO8();
	DrawableObject drawableZombie1 = DrawableObject(&zombieModel);


	Model model2;
	model2.generate_VBO(suziSmooth, sizeof(suziSmooth), sizeof(suziSmooth) / 6);
	model2.generate_VAO6();
	DrawableObject drawableObject3 = DrawableObject(&model2);
	//drawableObject3.model->generate_VBO(suziSmooth, sizeof(suziSmooth), sizeof(suziSmooth) / 6);
	//drawableObject3.model->generate_VAO6();
	drawableObject3.Translate(glm::vec3(0.0f, 0.0f, -1.2f));
	//drawableObject3.Scale(glm::vec3(0.7f));
	//drawableObject3.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));

	Model model3;
	DrawableObject drawableObject4 = DrawableObject(&model3);
	drawableObject4.model->generate_VBO(plain, sizeof(plain), sizeof(plain) / 6);
	drawableObject4.model->generate_VAO6();
	drawableObject4.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
	//drawableObject4.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));
	drawableObject4.Scale(glm::vec3(10.0f));
	//drawableObject4.Rotate(45.f, glm::vec3(1.0f, 0.0f, 0.0f));

	Model model4;
	DrawableObject drawableObject5 = DrawableObject(&model4);
	drawableObject5.model->generate_VBO(plain_uv, sizeof(plain_uv), sizeof(plain_uv) / 8);
	drawableObject5.model->generate_VAO8();
	drawableObject5.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
	//drawableObject5.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));
	//drawableObject5.Scale(glm::vec3(10.0f));
	drawableObject5.Rotate(45.f, glm::vec3(1.0f, 0.0f, 0.0f));

	DrawableObject drawableObject6 = DrawableObject(&model4);
	drawableObject6.model->generate_VBO(plain_uv, sizeof(plain_uv), sizeof(plain_uv) / 8);
	drawableObject6.model->generate_VAO8();
	drawableObject6.Translate(glm::vec3(0.0f, -1.0f, -3.0f));
	//drawableObject5.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));
	//drawableObject5.Scale(glm::vec3(10.0f));
	drawableObject6.Rotate(45.f, glm::vec3(1.0f, 0.0f, 0.0f));


	ShaderProgram shader_program;
	shader_program.AttachShaders("default.vert", "default.frag");
	shader_program.LinkProgram();
	shader_program.CheckLinkStatus();

	ShaderProgram shader_program2;
	shader_program2.AttachShaders("phong.vert", "phong.frag");
	shader_program2.LinkProgram();
	shader_program2.CheckLinkStatus();

	ShaderProgram shader_program3;
	shader_program3.AttachShaders("texture.vert", "texture.frag");
	shader_program3.LinkProgram();
	shader_program3.CheckLinkStatus();

	ShaderProgram shader_program4;
	shader_program4.AttachShaders("skybox.vert", "skybox.frag");
	shader_program4.LinkProgram();
	shader_program4.CheckLinkStatus();


	Model model7;
	DrawableObject drawableObject7 = DrawableObject(&model7);
	drawableObject7.model->generate_VBO(skycube, sizeof(skycube), sizeof(skycube) / 3);
	drawableObject7.model->generate_skybox_VAO();
	drawableObject7.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
	//drawableObject7.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));
	drawableObject7.Scale(glm::vec3(90.0f));
	//drawableObject7.Rotate(45.f, glm::vec3(1.0f, 0.0f, 0.0f));


	Skybox skybox(99);
	skybox.LoadCubemap();
	skybox.BindTexture();



	Texture texture5(5);
	texture5.LoadTexture("Textures/test.png");
	texture5.BindTexture();
	Texture texture6(6);
	texture6.LoadTexture("Textures/grass.png");
	texture6.BindTexture();
	Texture houseTexture(7);
	houseTexture.LoadTexture("Textures/house.png");
	houseTexture.BindTexture();
	Texture zombieTexture(8);
	zombieTexture.LoadTexture("Textures/zombie.png");
	zombieTexture.BindTexture();
	

	scene.AddSkybox(&drawableObject7, &shader_program4, &skybox);

	scene.AddToVectorModelsShaders(&drawableObject3, &shader_program2);
	scene.AddToVectorModelsShaders(&drawableObject4, &shader_program2);
	scene.AddToVectorModelsShadersTextures(&drawableObject5, &shader_program3, &texture5);
	scene.AddToVectorModelsShadersTextures(&drawableObject6, &shader_program3, &texture6);
	scene.AddToVectorModelsShadersTextures(&drawableHouse, &shader_program3, &houseTexture);
	scene.AddToVectorModelsShadersTextures(&drawableZombie1, &shader_program3, &zombieTexture);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		// draw all objects



		scene.camera->UpdateWorldWidthAndHeight(Application::width, Application::height);
		scene.camera->UpdateCamera(window);
		scene.DrawAllObjectsWithSkybox();
		//scene.DrawAllObjects();

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


