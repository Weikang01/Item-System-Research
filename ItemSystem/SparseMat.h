#pragma once
#include "pch.h"

template<typename T>
class SparseMat
{
	int m, n;
	std::vector<T>* vals;
	std::vector<int>* rows, * cols;
public:
	SparseMat(int r, int c)
	{
		this->m = r;
		this->n = c;

		this->vals = NULL;
		this->cols = NULL;
		this->rows = new std::vector<int>(r + 1, 1);
	}

	SparseMat(int n)
	{
		SparseMat(n, n);
	}
	
	SparseMat(const SparseMat<T>& mat)
	{
		this->m = mat.m;
		this->n = mat.n;
		this->rows = new std::vector(*(mat.rows));
		if (mat.vals != NULL)
		{
			this->cols = new std::vector<int>(*(mat.cols));
			this->vals = new std::vector<T>(*(mat.vals));
		}
	}

	SparseMat<T>& operator = (const SparseMat<T>& o)
	{
		if (&o != this)
		{
			this->destruct();
			this->deepCopy();
		}

		return *this;
	}

	void destruct()
	{
		if (this->vals != NULL)
		{
			delete this->vals;
			delete this->cols;
		}
		delete this->rows;
	}

	void deepCopy(const SparseMat<T>& mat)
	{
		this->m = mat.m;
		this->n = mat.n;
		this->rows = new std::vector<int>(*(mat.rows));

		if (mat.vals != NULL)
		{
			this->cols = new std::vector<int>(*(mat.cols));
			this->vals = new std::vector<T>(*(mat.vals));
		}
	}

	~SparseMat()
	{
		this->destruct();
	}

	void insert(int index, int r, int c, T val)
	{
		if (this->vals == NULL)
		{
			this->vals = new std::vector<T>(1, val);
			this->cols = new std::vector<int>(1, c);
		}
		else
		{
			this->vals->insert(this->vals->begin() + index, val);
			this->cols->insert(this->vols->begin() + index, val);
		}

		for (int i = r; i < this->m; i++)
		{
			(*(this->rows))[i] += 1;
		}
	}

	void remove(int index, int r)
	{
		this->vals->erase(this->vals->begin() + index);
		this->cols->erase(this->cols->begin() + index);

		for (int i = r; i < this->m; i++)
		{
			(*(this->rows))[i] -= 1;
		}
	}

	void get(int r, int c) const
	{
		int curCol;

		for (int pos = 0; pos < pos < (*(this->rows))[r] - 1; pos++)
		{
			curCol = (*(this->cols))[pos];

			if (curCol == c)
			{
				return (*(this->vals))[pos];
			}
			else if (curCol > c)
				break;
		}
		return T();
	}

	void set(T val, int r, int c)
	{
		int pos = (*(this->rows))[r - 1] - 1;
		int curCol = 0;

		for (; pos < (*(this->rows))[r - 1] - 1; pos++)
		{
			curCol = (*(this->cols))[pos];

			if (curCol >= c)
				break;
		}

		if (curCol != c)
		{
			if (!(val == T()))
			{
				this->insert(pos, r, c, val);
			}
		}
		else if (val == T())
		{
			this->remove(pos, r);
		}
		else
		{
			(*(this->vals))[pos] = val;
		}
		return *this;
	}
};