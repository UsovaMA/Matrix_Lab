#pragma once

#include "MyVector.h"

const int MAX_MATRIX_SIZE = 10000; 

template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix &mt);                    // копирование
	TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
	bool operator==(const TMatrix &mt) const;      // сравнение
	bool operator!=(const TMatrix &mt) const;      // сравнение
	TMatrix& operator= (const TMatrix &mt);        // присваивание
	TMatrix  operator+ (const TMatrix &mt);        // сложение
	TMatrix  operator- (const TMatrix &mt);        // вычитание

												   // ввод / вывод
	friend istream& operator >> (istream &in, TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream & operator<<(ostream &out, const TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE) throw logic_error("");
	for (int i = 0; i < this->Size - this->StartIndex; i++)
	{
		TVector<ValType>res(s - i, i);
		this->pVector[i] = res;
	}
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :
	TVector<TVector<ValType> >(mt)
{
	for (int i = this->StartIndex; i < this->Size; i++)
	{
		TVector<ValType>res(mt[i]);
		(*this)[i] = res;
	}
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) :
	TVector<TVector<ValType> >(mt)
{
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)
	{
		TVector<ValType>ms(mt[i]);
		(*this)[i] = ms;
	}
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt) 
		return true;

	if (((*this).GetStartIndex() == mt.GetStartIndex()) && ((*this).GetSize() == mt.GetSize()))
	{
		for (int i = mt.GetStartIndex(); i < mt.GetSize(); i++)
		{
			if ((*this)[i] != mt[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !((*this) == mt);
} 

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (&mt == this)
	{
		return (*this);
	}
	if (this->GetSize() == mt.GetSize())
	{
		for (int i = 0; i < this->Size - this->StartIndex; i++)
		{
			(*this).pVector[i] = mt.pVector[i];
		}
		return(*this);
	}
	delete[]pVector;
	pVector = new TVector<ValType>[mt.Size - mt.StartIndex];

	(*this).Size = mt.Size;
	(*this).StartIndex = mt.StartIndex;
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)
	{
		(*this)[i] = mt[i];
	}
	return (*this);
}

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (mt.Size != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)
	{
		Res[i] = (*this)[i] + mt[i];
	}
	return Res;
}

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)
	{
		Res[i] = (*this)[i] - mt[i];
	}
	return Res;
}