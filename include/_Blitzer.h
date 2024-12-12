#ifndef _BLITZER_H
#define _BLITZER_H

#include <_Enemy.h>


class _Blitzer : public _Enemy
{
	public:
		_Blitzer();
		virtual ~_Blitzer();

		void init(char*,char*,vec3);
		void Actions(int* plHealth);

	protected:

	private:
};

#endif // _BLITZER_H
