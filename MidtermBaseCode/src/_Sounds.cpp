#include "_Sounds.h"

_Sounds::_Sounds()
{
	//ctor
}

_Sounds::~_Sounds()
{
	//dtor
	engine->drop();
}

void _Sounds::playMusic(char* File)
{
	engine->play2D(File,true);
}

void _Sounds::playSound(char* File)
{
	if(!engine->isCurrentlyPlaying(File))
		engine->play2D(File,false,false);
}

void _Sounds::pauseSound(char* File)
{
	engine->play2D(File,true,false);
}

int _Sounds::initSounds()
{
	if(!engine)
	{
		cout << "ERROR: sound engine failed to initialize" << endl;
		return 0;
	}
	return 1;
}

void _Sounds::stopSounds()
{
	engine->stopAllSounds();
}
