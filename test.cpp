#include "cfgparser.h"

using namespace std;

int main()
{
	CfgParser cfg;
	cfg.setStandart(map<wstring, wstring> { 
		{L"name", L"olaf"},
		{L"age", L"20"}
	});
	cout << cfg.create();

	cin.get();
    return 0;
}

