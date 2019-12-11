#include "json.h"
#include "resources.h"
#include "scenario.h"

int main(int argc, char** argv)
{
	scenario::Mesh m;
	m.addPoint(0, 0);
	m.addPoint(5, 10);
	m.addPoint(10, 5);

	resource::Maps.extractAndWrite(m, "test.mesh");

	return 0;
}
