#pragma once
#include "mesh_types.h"
#include "MeshPrimitive.h"
#include "string_utilities.h"
#include <vector>
#include "error_codes.h"
//#include "FeaWrite.h"

class MeshGenerator
{
public:
	MeshGenerator();
	~MeshGenerator();
	
	virtual int generate() = 0;

	int writeToFile(const std::string& _filepath, format_type _format, const std::string& _stlpath = "");
	virtual int processInputParameters(const std::map<std::string, std::vector<std::string>>& parameters);

protected:
	std::string outpath;
	std::string stlpath;
	format_type format;
	
	std::vector<MeshPrimitive*>	nodeRegions;

	std::vector<std::string>	valid_parameters;
	std::vector<double*>		param_values;

	void writeNodes(std::ofstream& file);
	void writeElements(std::ofstream& file);

	virtual void writeConnectionElements(std::ofstream& file) = 0;
};

/*

enum class ExtrudeMode{x,y,z, none};
class NodeSet {
public:
	NodeSet(int sx, int sy) {
		x = Eigen::MatrixXd::Zero(sx, sy);
		y = Eigen::MatrixXd::Zero(sx, sy);
		z = Eigen::MatrixXd::Zero(sx, sy);
	}

	void setExtrudeMode(ExtrudeMode mode, int nLayers, double layerSize) {
		extrudeMode = mode;
		nExtrudeLayers = nLayers;
		extrudeLayersize = layerSize;
	}
	ExtrudeMode getExtrudeMode() { return extrudeMode; }

	Eigen::MatrixXd x;
	Eigen::MatrixXd y;
	Eigen::MatrixXd z;



	void addX(double v, int row) {
		x.row(row).array() += v;
	}
	void addY(double v, int row) {
		y.row(row).array() += v;
	}
	void addZ(double v, int row) {
		z.row(row).array() += v;
	}

	void setAllRowsX(double v) {
		x.setOnes();
		x *= v;
	}
	void setAllRowsY(double v) {
		z.setOnes();
		z *= v;
	}
	void setAllRowsZ(double v) {
		z.setOnes();
		z *= v;
	}

	void setX(double v, int row) {
		if (row < 0)
			setAllRowsX(v);
		else
			setRow(&x.row(row), v);
	}
	void setY(double v, int row) {
		if (row < 0)
			setAllRowsY(v);
		else
			setRow(&y.row(row), v);
	}
	void setZ(double v, int row) {
		if (row < 0)
			setAllRowsY(v);
		else
			setRow(&y.row(row), v);
	}

	void setAllRowsX(const Eigen::VectorXd& vec) {
		for (int i = 0; i < x.rows(); i++)
			x.row(i) = vec;
	}
	void setAllRowsY(const Eigen::VectorXd& vec) {
		for (int i = 0; i < y.rows(); i++)
			y.row(i) = vec;
	}
	void setAllRowsZ(const Eigen::VectorXd& vec) {
		for (int i = 0; i < z.rows(); i++)
			z.row(i) = vec;
	}

	void LinSpacedX(int row, int size, double low, double high) {
		Eigen::VectorXd tmpVec = Eigen::VectorXd::LinSpaced(size, low, high);
		if (row < 0)
			setAllRowsX(tmpVec);
		else
			x.row(row) = tmpVec;
	}
	void LinSpacedY(int row, int size, double low, double high) {
		Eigen::VectorXd tmpVec = Eigen::VectorXd::LinSpaced(size, low, high);
		if (row < 0)
			setAllRowsY(tmpVec);
		else
			y.row(row) = tmpVec;
	}
	void LinSpacedZ(int row, int size, double low, double high) {
		Eigen::VectorXd tmpVec = Eigen::VectorXd::LinSpaced(size, low, high);
		if (row < 0)
			setAllRowsZ(tmpVec);
		else
			z.row(row) = tmpVec;
	}

private:
	ExtrudeMode extrudeMode = ExtrudeMode::none;
	int nExtrudeLayers = 0;
	double extrudeLayersize = 0.0;

	void setRow(Eigen::DenseBase<Eigen::MatrixXd>::RowXpr* row, double v) {
		row->setOnes();
		(*row) *= v;
	}

};

*/