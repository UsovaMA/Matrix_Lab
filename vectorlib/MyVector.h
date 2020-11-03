#pragma once

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;

// ������ �������
template <class ValType>
class TVector
{
protected:
	ValType *pVector;
	int Size;       // ������ �������
	int StartIndex; // ������ ������� �������� �������
public:
	TVector(int s = 10, int si = 0);          // ������������ ����������� �� ���������
											  // � ����������� � �����������
	TVector(const TVector &v);                // ����������� �����������
	~TVector();
	int GetSize()   const { return Size; } // ������ �������
	int GetStartIndex()const { return StartIndex; }
	ValType* GetVector()const { return pVector; }// ������ ������� ��������
	ValType& operator[](int pos);
	ValType& operator[](int pos) const;// ������
	bool operator==(const TVector &v) const;  // ���������
	bool operator!=(const TVector &v) const;  // ���������
	TVector& operator=(const TVector &v);     // ������������

											  // ��������� ��������
	TVector  operator+(const ValType &val);   // ��������� ������
	TVector  operator-(const ValType &val);   // ������� ������
	TVector  operator*(const ValType &val);   // �������� �� ������

											  // ��������� ��������
	TVector  operator+(const TVector &v);     // ��������
	TVector  operator-(const TVector &v);     // ���������
	ValType  operator*(const TVector &v);     // ��������� ������������

											  // ����-�����
	friend istream& operator >> (istream &in, TVector &v)
	{
		for (int i = 0; i < v.Size - v.StartIndex; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream &out, const TVector &v)
	{
		for (int i = 0; i < v.Size - v.StartIndex; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s < 0) || (si<0) || (s>MAX_VECTOR_SIZE)) throw logic_error("");
	pVector = new ValType[s];
	for (int i = 0; i < s; i++)
	{
		pVector[i] = 0;
	}
	StartIndex = si;
	Size = s + StartIndex;
}

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType> &v)
{

	pVector = new ValType[v.Size - v.StartIndex];
	for (int i = 0; i < v.Size - v.StartIndex; i++)
	{
		pVector[i] = v.pVector[i];
	}
	StartIndex = v.StartIndex;
	Size = v.Size;
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[]pVector;
} 

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < StartIndex) || (pos < 0) || (pos > StartIndex + Size)) throw logic_error("");
	return pVector[pos - StartIndex];
}
template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)const
{
	if ((pos < StartIndex) || (pos < 0) || (pos > StartIndex + Size)) throw logic_error("");
	return pVector[pos - StartIndex];
}

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (this == &v)
		return true;

	if ((this->GetSize() == v.GetSize()) && (this->GetStartIndex() == v.GetStartIndex()))
	{
		for (int i = 0; i < v.GetSize() - v.GetStartIndex(); i++)
		{
			if (this->pVector[i] != v.pVector[i])
			{
				return false;
			}
			return true;
		}
	}
	return false;
}

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(*this == v);
} 

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this == &v)
	{
		return (*this);
	}
	if (this->GetSize() == v.GetSize())
	{
		for (int i = 0; i < v.Size - v.StartIndex; i++)
		{
			pVector[i] = v.pVector[i];
		}
		Size = v.Size;
		StartIndex = v.StartIndex;
		return (*this);
	}
	delete[]pVector;
	pVector = new ValType[v.Size - v.StartIndex];
	for (int i = 0; i < v.Size - v.StartIndex; i++)
	{
		pVector[i] = v.pVector[i];
	}
	Size = v.Size;
	StartIndex = v.StartIndex;
	return (*this);
}

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] += val;
	}
	return res;
}

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] -= val;
	}
	return res;
}

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] *= val;
	}
	return res;
}

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] = res.pVector[i] + v.pVector[i];
	}
	return res;
}

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] = res.pVector[i] - v.pVector[i];
	}
	return res;
}

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	float res = 0;
	for (int i = 0; i < v.Size - v.StartIndex; i++)
	{
		res = res + v.pVector[i] * this->pVector[i];
	}
	return sqrt(res);
}