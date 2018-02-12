#include "MyMatrix3.h"



MyMatrix3::MyMatrix3() :
	m11{ 0.0 },
	m12{ 0.0 },
	m13{ 0.0 },
	m21{ 0.0 },
	m22{ 0.0 },
	m23{ 0.0 },
	m31{ 0.0 },
	m32{ 0.0 },
	m33{ 0.0 }
{
}

MyMatrix3::MyMatrix3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33) :
	m11{ a11 },
	m12{ a12 },
	m13{ a13 },
	m21{ a21 },
	m22{ a22 },
	m23{ a23 },
	m31{ a31 },
	m32{ a32 },
	m33{ a33 }
{
}

MyMatrix3::MyMatrix3(MyVector3D row1, MyVector3D row2, MyVector3D row3)
{

	m11 = row1.X();
	m12 = row1.Y();
	m13 = row1.Z();
	m21 = row2.X();
	m22 = row2.Y();
	m23 = row2.Z();
	m31 = row3.X();
	m32 = row3.Y();
	m33 = row3.Z();

}


MyMatrix3::~MyMatrix3()
{
}

std::string MyMatrix3::toString()
{
	char tmpbuf[512];
	sprintf_s(tmpbuf, "{ [ %g, %g, %g ] [ %g, %g, %g ] [ %g, %g, %g ] }", m11, m12, m13, m21, m22, m23, m31, m32, m33);
	return tmpbuf;


}

MyMatrix3 MyMatrix3::operator+(const MyMatrix3 otherOne) const
{
	return MyMatrix3(m11 + otherOne.m11, m12 + otherOne.m12, m13 + otherOne.m13, m21 + otherOne.m21, m22 + otherOne.m22, m23 + otherOne.m23, m31 + otherOne.m31, m32 + otherOne.m32, m33 + otherOne.m33);

}

MyMatrix3 MyMatrix3::operator-(const MyMatrix3 otherOne) const
{
	return MyMatrix3(m11 - otherOne.m11, m12 - otherOne.m12, m13 - otherOne.m13, m21 - otherOne.m21, m22 - otherOne.m22, m23 - otherOne.m23, m31 - otherOne.m31, m32 - otherOne.m32, m33 - otherOne.m33);
}

MyMatrix3 MyMatrix3::operator*(const MyMatrix3 otherOne) const
{
	double n11 = m11;
	double n12 = m12;
	double n13 = m13;
	double n21 = m21;
	double n22 = m22;
	double n23 = m23;
	double n31 = m31;
	double n32 = m32;
	double n33 = m33;

	n11 = ((m11 * otherOne.m11) + (m12 * otherOne.m21) + (m13 * otherOne.m31));
	n12 = ((m11 * otherOne.m12) + (m12 * otherOne.m22) + (m13 * otherOne.m32));
	n13 = ((m11 * otherOne.m13) + (m12 * otherOne.m23) + (m13 * otherOne.m33));
	n21 = ((m21 * otherOne.m11) + (m22 * otherOne.m21) + (m23 * otherOne.m31));
	n22 = ((m21 * otherOne.m12) + (m22 * otherOne.m22) + (m23 * otherOne.m32));
	n23 = ((m21 * otherOne.m13) + (m22 * otherOne.m23) + (m23 * otherOne.m33));
	n31 = ((m31 * otherOne.m11) + (m32 * otherOne.m21) + (m33 * otherOne.m31));
	n32 = ((m31 * otherOne.m12) + (m32 * otherOne.m22) + (m33 * otherOne.m32));
	n33 = ((m31 * otherOne.m13) + (m32 * otherOne.m23) + (m33 * otherOne.m33));

	return MyMatrix3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
}

MyVector3D MyMatrix3::operator*(const MyVector3D otherOne) const
{
	double x = (m11 * otherOne.X()) + (m12 * otherOne.Y()) + (m13 * otherOne.Z());
	double y = (m21 * otherOne.X()) + (m22 * otherOne.Y()) + (m23 * otherOne.Z());
	double z = (m31 * otherOne.X()) + (m32 * otherOne.Y()) + (m33 * otherOne.Z());

	return{ x, y, z };

}

MyMatrix3 MyMatrix3::operator*(const double scalar) const
{
	double n11 = m11;
	double n12 = m12;
	double n13 = m13;
	double n21 = m21;
	double n22 = m22;
	double n23 = m23;
	double n31 = m31;
	double n32 = m32;
	double n33 = m33;

	n11 = m11 * scalar;
	n12 = m12 * scalar;
	n13 = m13 * scalar;
	n21 = m21 * scalar;
	n22 = m22 * scalar;
	n23 = m23 * scalar;
	n31 = m31 * scalar;
	n32 = m32 * scalar;
	n33 = m33 * scalar;

	return MyMatrix3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
}

MyMatrix3 MyMatrix3::transpose() const
{
	double n11 = m33;
	double n12 = m32;
	double n13 = m31;
	double n21 = m23;
	double n22 = m22;
	double n23 = m21;
	double n31 = m13;
	double n32 = m12;
	double n33 = m11;
	return MyMatrix3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
}

double MyMatrix3::determinant() const
{
	double n11 = m11;
	double n12 = m12;
	double n13 = m13;
	double n21 = m21;
	double n22 = m22;
	double n23 = m23;
	double n31 = m31;
	double n32 = m32;
	double n33 = m33;
	double determinant = 0;
	determinant = ((n11 * ((n22*n33) - (n32 * n23))) - (n21 *((n33 * n12) - (n32 * n13))) + (n31 * ((n23 * n12) - (n22 * n13))));
	return determinant;
}

MyMatrix3 MyMatrix3::inverse() const
{

	double deter = determinant();
	double deterMultiplier = 1 / deter;
	double n11 = m11;
	double n12 = m12;
	double n13 = m13;
	double n21 = m21;
	double n22 = m22;
	double n23 = m23;
	double n31 = m31;
	double n32 = m32;
	double n33 = m33;

	n11 = ((m33 * m22) - (m32 * m23)) * deterMultiplier;
	n12 = ((m32 * m13) - (m33 * m12)) * deterMultiplier;
	n13 = ((m23 * m12) - (m22 * m13)) * deterMultiplier;
	n21 = ((m31 * m23) - (m33 * m21)) * deterMultiplier;
	n22 = ((m33 * m11) - (m31 * m13)) * deterMultiplier;
	n23 = ((m21 * m13) - (m23 * m11)) * deterMultiplier;
	n31 = ((m32 * m21) - (m31 * m22)) * deterMultiplier;
	n32 = ((m31 * m12) - (m32 * m11)) * deterMultiplier;
	n33 = ((m22 * m11) - (m21 * m12)) * deterMultiplier;


	return MyMatrix3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
}

MyVector3D MyMatrix3::row(int row) const
{


	if (row == 1)
	{
		return MyVector3D(m11, m12, m13);
	}
	else if (row == 2)
	{
		return MyVector3D(m21, m22, m23);
	}
	else if (row == 3)
	{
		return MyVector3D(m31, m32, m33);
	}
	else
	{
		std::cout << "the value input is not wwithin the specified boundaries" << std::endl;
	}



}

MyVector3D MyMatrix3::column(int column) const
{
	if (column == 1)
	{
		return MyVector3D(m11, m21, m31);
	}
	if (column == 2)
	{
		return MyVector3D(m12, m22, m32);
	}
	if (column == 3)
	{
		return MyVector3D(m13, m23, m33);
	}
	else
	{
		std::cout << "the value input is not wwithin the specified boundaries" << std::endl;
	}
}

bool MyMatrix3::operator==(const MyMatrix3 otherOne) const
{
	if ((m11 == otherOne.m11) && (m12 == otherOne.m12) && (m13 == otherOne.m13)
		&& (m21 == otherOne.m21) && (m22 == otherOne.m22) && (m23 == otherOne.m23)
		&& (m31 == otherOne.m31) && (m32 == otherOne.m32) && (m33 == otherOne.m33))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MyMatrix3::operator!=(const MyMatrix3 otherOne) const
{
	if ((m11 != otherOne.m11) || (m12 != otherOne.m12) || (m13 != otherOne.m13)
		|| (m21 != otherOne.m21) || (m22 != otherOne.m22) || (m23 != otherOne.m23)
		|| (m31 != otherOne.m31) || (m32 != otherOne.m32) || (m33 != otherOne.m33))
	{
		return true;
	}
	else
	{
		return false;
	}
}

MyMatrix3 MyMatrix3::rotationX(double radNess)
{
	const double PI = 3.14159265358979323;
	double n11 = 1;
	double n12 = 0;
	double n13 = 0;
	double n21 = 0;
	double n22 = cos(radNess * (PI / 180));
	double n23 = sin(radNess *(PI / 180));
	double n31 = 0;
	double n32 = -sin(radNess *(PI / 180));
	double n33 = cos(radNess *(PI / 180));
	MyMatrix3 rotatorX{ n11,n12,n13,n21,n22,n23,n31,n32,n33 };
	return MyMatrix3(rotatorX);
}

MyMatrix3 MyMatrix3::rotationY(double radNess)
{
	const double PI = 3.141592653538979323;
	double n11 = cos(radNess * (PI / 180));
	double n12 = 0;
	double n13 = sin(radNess * (PI / 180));
	double n21 = 0;
	double n22 = 1;
	double n23 = 0;
	double n31 = -sin(radNess * (PI / 180));
	double n32 = 0;
	double n33 = cos(radNess * (PI / 180));
	return MyMatrix3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
}

MyMatrix3 MyMatrix3::rotationZ(double radNess)
{
	const double PI = 3.141592653538979323;
	double n11 = cos(radNess * (PI / 180));
	double n12 = sin(radNess * (PI / 180));
	double n13 = 0;
	double n21 = -sin(radNess * (PI / 180));
	double n22 = cos(radNess * (PI / 180));
	double n23 = 0;
	double n31 = 0;
	double n32 = 0;
	double n33 = 1;
	return MyMatrix3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
}

MyMatrix3 MyMatrix3::translation(MyMatrix3 displacement)
{
	displacement.m11 += 0.05;
	displacement.m12 += 0.05;
	displacement.m21 += 0.05;
	displacement.m22 += 0.05;
	displacement.m31 += 0.05;
	displacement.m32 += 0.05;
	

	return displacement;
}

MyVector3D MyMatrix3::translation2(MyVector3D displacement)
{
	double m11 = displacement.X() + 0.05;
	double m12 = displacement.Y() + 0.05;
	double m13 = displacement.Z() + 0.05;
	return MyVector3D(m11,m12,m13);
}

MyMatrix3 MyMatrix3::scale(double scaleFactor)
{
	double n11 = scaleFactor;
	double n12 = 0;
	double n13 = 0;
	double n21 = 0;
	double n22 = scaleFactor;
	double n23 = 0;
	double n31 = 0;
	double n32 = 0;
	double n33 = scaleFactor;
	return MyMatrix3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
}

