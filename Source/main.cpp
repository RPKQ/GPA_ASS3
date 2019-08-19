#include "Program.h"
#include "AssimpModel.h"
#include "Camera.h"
#include "FBO.h"
#include "WindowModel.h"
#include "ComparisonBar.h"
#include "../Source/GLIncludes.h"

using namespace glm;
using namespace std;

enum { MENU_TIMER_START, MENU_TIMER_STOP, MENU_EXIT, 
	MENU_SHADER_LAPLACIAN, MENU_SHADER_REDBLUE, MENU_SHADER_SINWAVE,
	MENU_SHADER_MAGNIFIER, MENU_SHADER_BLOOMING, MENU_SHADER_BLURQUANDOG,
	MENU_SHADER_WHIRL, MENU_SHADER_FROSTED, MENU_SHADER_CROSSHATCH,
	MENU_SCENE_SPONZA, MENU_SCENE_EMPIRE};

// uniforms
int windowW = 1024, windowH = 768;
float magCenterX = 200.0f, magCenterY = 500.0f;
glm::mat4 modelMat;
glm::mat4 perspectMat;

// first program
Program* programOrigin;

// post processing
WindowModel *winModel, *winModel2;
Program *programFilter, *programComparison;
FBO *FBOOrigin, *FBOFiltered;

Program *redBlue, *sinWave, *laplacian;
Program *magnifier, *blooming, *blurQuanDOG;
Program *whirl, *frosted, *crossHatch;

// assimp models
AssimpModel* model;
AssimpModel* model_sponza;
AssimpModel* model_lostEmpire;

// Others
ComparisonBar *comparisonBar;
Camera* cam;

// timer function??
GLubyte timer_cnt = 0;
bool timer_enabled = true;
unsigned int timer_speed = 16;


void DisplayFunc()
{
	// Draw a texture to FBOOrigin
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBOOrigin->getID());
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static const GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, white);
	glClearBufferfv(GL_DEPTH, 0, &one);
	
	programOrigin->use();
	programOrigin->setMat4("pvMat", perspectMat * cam->getViewMat());
	programOrigin->setMat4("modelMat", glm::mat4(1.0));
	programOrigin->setVec3("lightPos", glm::vec3(100000.0, 100000.0, 200000.0));
	programOrigin->setBool("useTex", true);

	model->draw();


	// Filter
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBOFiltered->getID());
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, white);
	glClearBufferfv(GL_DEPTH, 0, &one);

	programFilter->use();
	programFilter->setFloat("time", glutGet(GLUT_ELAPSED_TIME));
	programFilter->setFloat("windowW", (float)windowW);
	programFilter->setFloat("windowH", (float)windowH);
	programFilter->setVec2("center", (float)magCenterX, (float)(windowH - magCenterY));
	programFilter->setTexture("tex", FBOOrigin->getOuputTex(), (GLint)1);
	winModel->draw();


	// Comparison
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	programComparison->use();
	programComparison->setTexture("texOrigin", FBOOrigin->getOuputTex(), (GLint)1);
	programComparison->setTexture("texFiltered", FBOFiltered->getOuputTex(), (GLint)0);
	programComparison->setFloat("splitPoint", (float)comparisonBar->getSplitPos());
	winModel->draw();

	glutSwapBuffers();
	glGetError();
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
	case 'm':
		magCenterX = (float)x;
		magCenterY = (float)y;
		break;
	default:
		break;
	}
}

void MotionFunc(int x, int y)
{
	cam->rotateWithMouse(x, y);
}

void MouseFunc(int button, int state, int x, int y) {
	if (state == GLUT_UP) 
	{
		if(button == GLUT_LEFT_BUTTON) cam->endOfRotate();
	}
	else if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON) cam->startOfRotate();
		else if (button == GLUT_MIDDLE_BUTTON) comparisonBar->setSplitPos((float)x);
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

	FBOOrigin->reshape(width, height);
	FBOFiltered->reshape(width, height);
	comparisonBar->reshape(width);

	windowH = height;
	windowW = width;
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
	case MENU_SCENE_SPONZA:
		model = model_sponza;
		cam->setMoveSpeed(5.0);
		break;
	case MENU_SCENE_EMPIRE:
		model = model_lostEmpire;
		cam->setMoveSpeed(1.0);
		break;
	case MENU_SHADER_LAPLACIAN:
		programFilter = laplacian;
		break;
	case MENU_SHADER_REDBLUE:
		programFilter = redBlue;
		break;
	case MENU_SHADER_SINWAVE:
		programFilter = sinWave;
		break;
	case MENU_SHADER_MAGNIFIER:
		programFilter = magnifier;
		break;
	case MENU_SHADER_BLOOMING:
		programFilter = blooming;
		break;
	case MENU_SHADER_BLURQUANDOG:
		programFilter = blurQuanDOG;
		break;
	case MENU_SHADER_FROSTED:
		programFilter = frosted;
		break;
	case MENU_SHADER_WHIRL:
		programFilter = whirl;
		break;
	case MENU_SHADER_CROSSHATCH:
		programFilter = crossHatch;
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
	glutAddMenuEntry("laplacian", MENU_SHADER_LAPLACIAN);
	glutAddMenuEntry("red-blue", MENU_SHADER_REDBLUE);
	glutAddMenuEntry("sin wave", MENU_SHADER_SINWAVE);
	glutAddMenuEntry("magnifier", MENU_SHADER_MAGNIFIER);
	glutAddMenuEntry("blooming", MENU_SHADER_BLOOMING);
	glutAddMenuEntry("abstraction", MENU_SHADER_BLURQUANDOG);
	glutAddMenuEntry("frosted", MENU_SHADER_FROSTED);
	glutAddMenuEntry("whirl", MENU_SHADER_WHIRL);
	glutAddMenuEntry("cross-hatching", MENU_SHADER_CROSSHATCH);

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
	programOrigin = new Program("Shaders/model.vs.glsl", "Shaders/textured.fs.glsl");

	// post processing
	winModel = new WindowModel();
	//// Filter
	redBlue = new Program("Shaders/window.vs.glsl", "Shaders/redBlue.fs2.glsl");
	sinWave = new Program("Shaders/window.vs.glsl", "Shaders/sinWave.fs2.glsl");
	laplacian = new Program("Shaders/window.vs.glsl", "Shaders/laplacian.fs2.glsl");
	magnifier = new Program("Shaders/window.vs.glsl", "Shaders/magnifier.fs2.glsl");
	blooming = new Program("Shaders/window.vs.glsl", "Shaders/blooming.fs2.glsl");
	blurQuanDOG = new Program("Shaders/window.vs.glsl", "Shaders/blurQuanDOG.fs2.glsl");
	whirl = new Program("Shaders/window.vs.glsl", "Shaders/whirl.fs2.glsl");
	frosted = new Program("Shaders/window.vs.glsl", "Shaders/frosted.fs2.glsl");
	crossHatch = new Program("Shaders/window.vs.glsl", "Shaders/crossHatch.fs2.glsl");
	FBOOrigin = new FBO();
	//// Comparison
	programComparison = new Program("Shaders/window.vs.glsl", "Shaders/comparison.fs3.glsl");
	FBOFiltered = new FBO();
	comparisonBar = new ComparisonBar();


	// load models
	model_sponza = new AssimpModel("Models/sponza.obj");
	model_lostEmpire = new AssimpModel("Models/lost_empire.obj");

	programFilter = redBlue;
	model = model_lostEmpire;

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