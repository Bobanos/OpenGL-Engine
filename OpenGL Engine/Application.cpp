#include "Application.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Scene.h"

static float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

static const float pointsWithColors[] = {
   -.5f, -.5f, .5f, 1.f, 1.f, 1.f, 0.f, 1.f,
   -.5f, .5f, .5f, 1.f, 1.f, 0.f, 0.f, 1.f,
   .5f, .5f, .5f, 1.f, 0.f, 0.f, 0.f, 1.f,
   .5f, -.5f, .5f, 1.f, 0.f, 1.f, 0.f, 1.f,
};

static const float pointsWithColors2[] = {
   1.f, 1.f, 1.f, .5f, 1.f, 1.f, 1.f, 1.f,
   -1.f, -1.f, 1.f, .5f, 0.f, 1.f, 0.f, 1.f,
   -1.f, 1.f, 1.f, .5f, 1.f, 0.f, 0.f, 1.f,
   1.f, -1.f, 1.f, .5f, 0.f, 0.f, 1.f, 1.f,
};


const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

const char* vertex_shader2 =
"#version 330\n"
"layout(location=0) in vec4 vp;"
"layout(location=1) in vec4 vo;"
"out vec4 colour;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"	  colour = vo;"
"}";

const char* fragment_shader2 =
"#version 330\n"
"in vec4 colour"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = colour;"
"}";

Application::Application(const unsigned width, const unsigned height)
{
	Application::width = width;
	Application::height = height;

	set_camera();
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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
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
	printf("cursor_callback \n");
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

void Application::set_camera()
{
	//GLM test

// Projection matrix : 45 degree Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
}

void Application::init()
{
	window;
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


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void Application::init(int major, int minor)
{
	window;
	set_error_callback();
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	//inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	int revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void Application::gameLoop()
{
	Scene scene;
	Model model;
	DrawableObject drawableObject1 = DrawableObject(&model);
	drawableObject1.model->generate_VBO(pointsWithColors, sizeof(pointsWithColors));
	drawableObject1.model->generate_VAO();

	ShaderProgram shader_program;
	shader_program.AttachShaders(vertex_shader, fragment_shader);
	shader_program.LinkProgram();
	shader_program.CheckLinkStatus();

	scene.AddToVector(&drawableObject1, &shader_program);

	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//shader_program.UseProgram();
		//drawableObject1.model->bind_VAO();
		// draw triangles
		//glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
		scene.DrawAllObjects();
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


