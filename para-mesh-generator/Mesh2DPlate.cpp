#include "Mesh2DPlate.h"



Mesh2DPlate::Mesh2DPlate(const glm::dvec3& _pos, const glm::dvec2& _length, double _amp, double _freq)
	: Mesh2DRectangle(_pos, _length)
{
	amplitude	= _amp;
	freq		= _freq;
	b			= 2.0*M_PI*freq;
}


Mesh2DPlate::Mesh2DPlate(const glm::dvec3& _pos, const glm::dvec2& _length, double _amp, double _freq, const glm::dvec2& _elsize) 
	: Mesh2DPlate(_pos, _length, _amp, _freq)
{
	elsize = _elsize;
	defineYZvalues();	
}


void Mesh2DPlate::defineYZvalues() {

	double y		= 0.0;
	double yprev	= 0.0;
	ys.push_back(0.0);
	zs.push_back(0.0);

	while (y < length.y) {
		double der	= abs(amplitude * b * glm::cos(b * yprev));
		double dy	= elsize.y / glm::sqrt(1.0 + der);
		y = dy + yprev;
		yprev = y;
		double z = amplitude * glm::sin(b * y);
		ys.push_back(y);
		zs.push_back(z);
	}

	nnodes.x = (int)(length.x / elsize.x) + 1;
	nnodes.y = (int)ys.size();
	elsize.x = length.x / (double)(nnodes.x - 1);
}

/*

segment of a x sin(bx) = (a/b)(cos(bx0) - cos(bx1))

dz/dy = ab cos(by)

*/
glm::dvec3 Mesh2DPlate::getCoords(int ix, int iy) {
	glm::dvec3 coords;
	coords.x = (double)ix * elsize.x;
	coords.y = ys[iy];
	coords.z = zs[iy];
	return coords;
}
void Mesh2DPlate::writeNodes(std::ofstream& file, format_type format) {
	int nodeID = nodeID1;
	for (int ix = 0; ix < nnodes.x; ix++) {
		for (int iy = 0; iy < nnodes.y; iy++) {
			glm::dvec3 c = getCoords(ix, iy);
			writeNode(file, nodeID++, c, format);
		}
	}
}
void Mesh2DPlate::writeElements(std::ofstream& file, format_type format) {
	int n[4];
	int c = nodeID1;
	int elID = elementID1;
	bool stop = false;
	for (int ix = 0; ix < (nnodes.x - 1); ix++) {
		for (int iy = 0; iy < (nnodes.y - 1); iy++) {

			n[0] = c;
			n[1] = n[0] + 1;
			n[2] = n[1] + nnodes.y;
			n[3] = c + nnodes.y;
			
			c++;
			write4nodedShell(file, elID++, n, format);
			if (false && (elID > (20))) {
				stop = true;
				break;
			}
		}
		c++;
		if (stop) break;
	}
	
}

int Mesh2DPlate::numberOfNodes() {
	return nnodes.x * nnodes.y;
}
int Mesh2DPlate::numberOfElements() {
	return (nnodes.x - 1) * (nnodes.y - 1);
}