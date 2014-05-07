#include "model_tests.hpp"
#include "point_tests.hpp"
#include "line_tests.hpp"
#include "shell_tests.hpp"
#include "text_tests.hpp"

int main(int argc, char const *argv[]){
	RunModelTests();
	RunPointTests();
	RunLineTests();
	RunShellTests();
	RunTextTests();
	return 0;
}