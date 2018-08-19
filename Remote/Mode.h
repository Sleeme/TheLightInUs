#ifndef MODE_H
#define MODE_H
#include "WString.h"

using namespace std;
class Mode {
private:
	String mName;
public:
	Mode(String name) {
		mName = name;
	}
	void onModeSelected() {};
	String getName() {
		return mName;
	}
};
#endif
