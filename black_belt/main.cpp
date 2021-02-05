#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <vector>
#include <iostream>

using namespace std;

int main() {
	int* n = DBG_NEW int[5];
	_CrtDumpMemoryLeaks();
	return 0;
}