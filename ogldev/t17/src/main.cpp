
#include "GlfwSupport.h"
#include "AmbientLight.h"
#include "Config.h"

int main(int argc, char** argv)
{
	std::shared_ptr<AmbientLight> pApp(new AmbientLight());

	GlfwSupport::GlfwBackendInit(argc, argv, true, true);

	GlfwSupport::GlfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AmbientLight");
	
	gl3wInit();

	GlfwSupport::SetEnvironment(pApp);

	pApp->Init();

	pApp->FrameSetting(GlfwSupport::isWithDepth(), GlfwSupport::isWithStencil());

	GlfwSupport::Display();

	GlfwSupport::GlfwDestroyWindow();

	GlfwSupport::GlfwTerminate();

}