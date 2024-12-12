#ifndef _SOUNDS_H
#define _SOUNDS_H

#include "_Common.h"
#include<SNDS/irrKlang.h>

using namespace irrklang;

class _Sounds
{
	public:
		_Sounds();
		virtual ~_Sounds();

		ISoundEngine *engine = createIrrKlangDevice();

		void playMusic(char *);
		void playSound(char *);
		void pauseSound(char *);
		int initSounds();
		void stopSounds();

	protected:

	private:
};

#endif // _SOUNDS_H
