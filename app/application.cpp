#include "application.h"

namespace dia {

Application::Application(int& argc, char** argv)
	: QApplication(argc, argv)
{  }
Application::~Application() = default;

} // namespace dia
