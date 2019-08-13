#include "Program.h"
#include "AssimpModel.h"
#include "Camera.h"
#include "../Source/GLIncludes.h"

using namespace glm;
using namespace std;

enum { MENU_TIMER_START, MENU_TIMER_STOP, MENU_EXIT, 
	MENU_SHADER_NORMAL, MENU_SHADER_LIGHTING, MENU_SHADER_TEXTURE,
	MENU_SCENE_SPONZA, MENU_SCENE_EMPIRE};


const int windowW = 1024, windowH = 768;

glm::mat4 modelMat;
glm::mat4 perspectMat;

Program* programNormal;
Program* programTexture;
Program* programLight;
Program* program;

Program* filterProgram;
GLuint FBO;
GLuint FBO_tex;
GLuint RBO;
GLuint window_vao;

AssimpModel* model;
AssimpModel* model_sponza;
AssimpModel* model_lostEmpire;
Camera* cam;

GLubyte timer_cnt = 0;
bool timer_enabled = true;
unsigned int timer_speed = 16;

void DisplayFunc()
{
	// Draw a texture to FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static const GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, white);
	glClearBufferfv(GL_DEPTH, 0, &one);
	
	program->use();
	program->setMat4("pvMat", perspectMat * cam->getViewMat());
	program->setMat4("modelMat", glm::mat4(1.0));
	program->setVec3("lightPos", glm::vec3(100000.0, 100000.0, 200000.0));
	program->setBool("useTex", true);

	model->draw();


	// apply the texture to screen
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	filterProgram->use();
	glBindVertexArray(window_vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, FBO_tex);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	glutSwapBuffers();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		cam->moveLocal(Camera::FRONT);
		break;
	case 's':
		cam->moveLocal(Camera::BACK);
		break;
	case 'a':
		cam->moveLocal(Camera::LEFT);
		break;
	case 'd':
		cam->moveLocal(Camera::RIGHT);
		break;
	case 'z':
		cam->moveLocal(Camera::UP);
		break;
	case 'x':
		cam->moveLocal(Camera::DOWN);
		break;
	default:
		break;
	}
}

void MotionFunc(int moveX, int moveY)
{
	cam->rotateWithMouse(moveX, moveY);
}

void MouseFunc(int button, int state, int x, int y) {
	if (state == GLUT_UP) 
	{
		cam->endOfRotate();
	}
}

void TimerFunc(int val)
{
	timer_cnt++;
	glutPostRedisplay();
	if (timer_enabled)
	{
		glutTimerFunc(timer_speed, TimerFunc, val);
	}
}

void ReshapeFunc(int width, int height)
{
	glViewport(0, 0, width, height);
	float viewportAspect = (float)width / (float)height;
	perspectMat = glm::perspective(glm::radians(60.0f), viewportAspect, 0.1f, 1500.0f);

	// FBO
	glDeleteRenderbuffers(1, &RBO);
	glDeleteTextures(1, &FBO_tex);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);

	glGenTextures(1, &FBO_tex);
	glBindTexture(GL_TEXTURE_2D, FBO_tex);	// bind tex
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);	// bind FBO
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBO_tex, 0);
}

void InitCallbackFuncs() 
{
	glutDisplayFunc(DisplayFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMotionFunc(MotionFunc);
	glutMouseFunc(MouseFunc);
	glutTimerFunc(timer_speed, TimerFunc, 0);
	glutReshapeFunc(ReshapeFunc);
}

void MenuFunc(int id)
{
	switch (id)
	{
	case MENU_TIMER_START:
		if (!timer_enabled)
		{
			timer_enabled = true;
			glutTimerFunc(timer_speed, TimerFunc, 0);
		}
		break;
	case MENU_TIMER_STOP:
		timer_enabled = false;
		break;
	case MENU_EXIT:
		exit(0);
		break;
	case MENU_SHADER_NORMAL:
		program = programNormal;
		break;
	case MENU_SHADER_TEXTURE:
		program = programTexture;
		break;
	case MENU_SHADER_LIGHTING:
		program = programLight;
		break;
	case MENU_SCENE_SPONZA:
		model = model_sponza;
		cam->setMoveSpeed(5.0);
		break;
	case MENU_SCENE_EMPIRE:
		model = model_lostEmpire;
		cam->setMoveSpeed(1.0);
		break;
	default:
		break;
	}
}

void InitMenu()
{
	int menu_main = glutCreateMenu(MenuFunc);
	int menu_timer = glutCreateMenu(MenuFunc);
	int menu_shader = glutCreateMenu(MenuFunc);
	int menu_scene = glutCreateMenu(MenuFunc);

	glutSetMenu(menu_main);
	glutAddSubMenu("Timer", menu_timer);
	glutAddSubMenu("Shader", menu_shader);
	glutAddSubMenu("Scene", menu_scene);
	glutAddMenuEntry("Exit", MENU_EXIT);

	glutSetMenu(menu_timer);
	glutAddMenuEntry("Start", MENU_TIMER_START);
	glutAddMenuEntry("Stop", MENU_TIMER_STOP);

	glutSetMenu(menu_shader);
	glutAddMenuEntry("normal", MENU_SHADER_NORMAL);
	glutAddMenuEntry("texture", MENU_SHADER_TEXTURE);
	glutAddMenuEntry("lighting", MENU_SHADER_LIGHTING);

	glutSetMenu(menu_scene);
	glutAddMenuEntry("lost empire", MENU_SCENE_EMPIRE);
	glutAddMenuEntry("sponza", MENU_SCENE_SPONZA);

	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void InitObjects()
{
	// setup camera
	cam = new Camera(vec3(0.0f, 15.0f, 20.0f), vec3(0.0f, 15.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	// setup program
	programTexture = new Program("vs.vs.glsl", "fs.fs.glsl");
	//programLight = new Program("vs.vs.glsl", "light.fs.glsl");
	//programNormal = new Program("vs.vs.glsl", "normal.fs.glsl");
	program = programTexture;

	// load models
	//model_sponza = new AssimpModel("sponza.obj");
	model_lostEmpire = new AssimpModel("lost_empire.obj");
	model = model_lostEmpire;

}

void initFBO()
{
	static const GLfloat window_positions[] =
	{
		1.0f,-1.0f,1.0f,0.0f,
		-1.0f,-1.0f,0.0f,0.0f,
		-1.0f,1.0f,0.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f
	};

	// others
	filterProgram = new Program("window.vs.glsl", "inverse.fs2.glsl");
	glGenFramebuffers(1, &FBO);

	// window_vao
	glGenVertexArrays(1, &window_vao);
	glBindVertexArray(window_vao);

	GLuint window_buffer;
	glGenBuffers(1, &window_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, window_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(window_positions), window_positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 4, (const GLvoid*)(sizeof(GL_FLOAT) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Init()
{
	// Init Window and GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Window");

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		system("pause");
		exit(1);
	}

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	InitMenu();
	InitObjects();
	InitCallbackFuncs();
	initFBO();

	// init reshape window
	ReshapeFunc(windowW, windowH);
}

int main(int argc, char *argv[]) 
{
	glutInit(&argc, argv);
	Init();
	glutMainLoop();

	return 0;
}