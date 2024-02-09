#pragma once

#ifdef YT_PLAT_WINDOWS

extern Yor::Application* Yor::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Yor::CreateApplication();
	app->run();
	delete app;
}

#endif