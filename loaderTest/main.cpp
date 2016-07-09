#include <iostream>
#include "ImageFile.h"

using namespace std;
using namespace Pix;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <out filename>" << endl;
		return -1;
	}

	Image image(18, 18);
	ImageFile::Read("/home/ben/code/ledBoard/images/gradient.pix", image);

	ImageFile::Write(image, "out.pix");

	return 0;
}
