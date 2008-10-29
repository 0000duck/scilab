/*
*  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
*  Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
*
*  This file must be used under the terms of the CeCILL.
*  This source file is licensed as described in the file COPYING, which
*  you should have received as part of this distribution.  The terms
*  are also available at
*  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/

#include <sstream>
#include <math.h>
#include "double.hxx"

void GetFormat(double _dblVal, int _iPrecision, int *_piEntNb, int *_piDecNb);

using namespace std;
namespace types
{
	/*------------*/
	/*	~Double		*/
	/*------------*/
	Double::~Double()
	{
		all_delete();
	}

	/*--------------------*/
	/*				Double			*/
	/*	Empty constructor	*/
	/*--------------------*/
	Double::Double(int _iRows, int _iCols, bool _bComplex)
	{
		double *pReal = NULL;
		double *pImg	= NULL;
		if(_bComplex == false)
		{
			CreateDouble(_iRows, _iCols, &pReal, NULL);
		}
		else
		{
			CreateDouble(_iRows, _iCols, &pReal, &pImg);
		}
		m_bComplex = _bComplex;
		return;
	}

	/*--------------------*/
	/*				Double			*/
	/*	Real constructor	*/
	/*--------------------*/
	Double::Double(double _dblReal)
	{
		double *pdblVal;
		CreateDouble(1, 1, &pdblVal, NULL);
		pdblVal[0] = _dblReal;
		m_bComplex = false;
		return;
	}

	/*--------------------*/
	/*		 	 Double				*/
	/*	Real constructor	*/
	/*--------------------*/
	Double::Double(int _iRows, int _iCols, double **_pdblReal)
	{
		CreateDouble(_iRows, _iCols, _pdblReal, NULL);
		m_bComplex = false;
		return;
	}
	
	/*----------------------*/
	/*				Double				*/
	/*	Complex constructor	*/
	/*----------------------*/
	Double::Double(int _iRows, int _iCols, double **_pdblReal, double **_pdblImg)
	{
		CreateDouble(_iRows, _iCols, _pdblReal, _pdblImg);
//		m_bComplex = false;
		return;
	}

	/*----------------------*/
	/*			CreateDouble		*/
	/*	Commun constructor	*/
	/*----------------------*/
	void Double::CreateDouble(int _iRows, int _iCols, double **_pdblReal, double **_pdblImg)
	{
		m_iCols	= _iCols;
		m_iRows	= _iRows;
		m_iSize = m_iCols * m_iRows;

		if(_pdblReal != NULL)
		{
			/*alloc Real array*/
			m_pdblReal = new double[m_iSize];
		
			/*return it*/
			*_pdblReal = m_pdblReal;
		}
		else
			m_pdblReal = NULL;

		if(_pdblImg != NULL)
		{
			/*alloc Img array*/
			m_pdblImg = new double[m_iSize];

			/*return it*/
			*_pdblImg = m_pdblImg;

			/*set complex flag*/
			m_bComplex = true;
		}
		else
			m_pdblImg = NULL;
	}

	bool Double::isComplex()
	{
		return m_bComplex;
	}

	void Double::complex_set(bool _bComplex)
	{
		if(_bComplex == false)
		{
			if(isComplex() == true)
			{
				img_delete(!_bComplex);
			}
		}
		else // _bComplex == true
		{
			if(isComplex() == false)
			{
				m_pdblImg = new double[m_iSize];
				memset(m_pdblImg, 0x00, sizeof(double) * m_iSize);
			}
		}
	}

	/*------------*/
	/*	real_get	*/
	/*------------*/
	double*	Double::real_get() const
	{ 
		return m_pdblReal;
	}

	/*------------*/
	/*	img_get	*/
	/*------------*/
	double*	Double::img_get() const
	{ 
		return m_pdblImg;
	}

	/*------------*/
	/*	real_set	*/
	/*------------*/
	bool Double::real_set(double *_pdblReal)
	{
		if(_pdblReal != NULL)
		{
			if(m_pdblReal == NULL)
			{
				m_pdblReal = new double[m_iSize];
			}

			memcpy(m_pdblReal, _pdblReal, m_iSize * sizeof(double));
		}
		else
			return false;

		return true;
	}

	/*------------*/
	/*	real_get	*/
	/*------------*/
	double	Double::real_get(int _iRows, int _iCols) const
	{ 
		if(m_pdblReal != NULL)
		{
			return m_pdblReal[_iCols * m_iRows + _iRows];
		}
		else
		{
			return 0;
		}
	}

	/*------------*/
	/*	img_set		*/
	/*------------*/
	bool Double::img_set(double *_pdblImg)
	{
		if(_pdblImg != NULL)
		{
			if(m_pdblImg == NULL)
			{
				m_pdblImg = new double[m_iSize];
			}

			memcpy(m_pdblImg, _pdblImg, m_iSize * sizeof(double));
		}
		else
			return false;

		return true;
	}

	/*------------*/
	/*	img_get	*/
	/*------------*/
	double	Double::img_get(int _iRows, int _iCols) const
	{ 
		if(m_pdblImg != NULL)
		{
			return m_pdblImg[_iCols * m_iRows + _iRows];
		}
		else
		{
			return 0;
		}
	}

	/*--------------*/
	/*		val_set		*/
	/*--------------*/
	bool Double::val_set(int _iRow, int _iCol, double _dblVal)
	{
		return val_set(_iRow, _iCol, _dblVal, 0);
	}

	/*--------------*/
	/*		val_set		*/
	/*--------------*/
	bool Double::val_set(int _iRow, int _iCol, double _dblReal, double _dblImg)
	{
		if(m_pdblReal != NULL)
		{
			if(_iRow < m_iRows && _iCol < m_iCols)
			{
				m_pdblReal[_iCol * m_iRows + _iRow] = _dblReal;
				if(m_bComplex)
				{
					m_pdblImg[_iCol * m_iRows + _iRow] = _dblImg;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	/*--------------*/
	/*		whoIAm		*/
	/*--------------*/
	void Double::whoAmI() 
	{ 
		std::cout << "types::Double" << std::endl; 
	}

	/*--------------*/
	/*	getAsUInt		*/
	/*--------------*/
	Double* Double::getAsDouble(void)		
	{ 
		return this; 
	}

	/*------------*/
	/*	getType		*/
	/*------------*/
	GenericType::RealType Double::getType(void)
	{
		return RealDouble; 
	}

	/*--------------*/
	/*	real_clean	*/
	/*--------------*/
	void Double::real_delete()
	{
		if(m_pdblReal != NULL)
		{
			delete m_pdblReal;
			m_pdblReal = NULL;
		}
	}

	/*------------*/
	/*	img_clean	*/
	/*------------*/
	void Double::img_delete(bool _bSetReal)
	{
		if(m_pdblImg != NULL)
		{
			delete m_pdblImg;
			m_pdblImg = NULL;
			m_bComplex = !_bSetReal;
		}
	}

	/*------------*/
	/*	all_clean	*/
	/*------------*/
	void Double::all_delete(bool _bSetReal)
	{
		real_delete();
		img_delete(_bSetReal);
	}

	/*------------*/
	/*	zero_set	*/
	/*------------*/
	bool Double::zero_set()
	{
		if(m_pdblReal != NULL)
		{
			for(int iIndex = 0 ; iIndex < m_iSize ; iIndex++)
			{
				m_pdblReal[iIndex] = 0;
			}
		}
		else
			return false;

		if(m_bComplex == true)
		{
			if(m_pdblImg != NULL)
			{
				for(int iIndex = 0 ; iIndex < m_iSize ; iIndex++)
				{
					m_pdblImg[iIndex] = 0;
				}
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/*------------*/
	/*	one_set	*/
	/*------------*/
	bool Double::one_set()
	{
		if(m_pdblReal != NULL)
		{
			for(int iIndex = 0 ; iIndex < m_iSize ; iIndex++)
			{
				m_pdblReal[iIndex] = 1;
			}
		}
		else
			return false;

		if(m_bComplex == true)
		{
			if(m_pdblImg != NULL)
			{
				for(int iIndex = 0 ; iIndex < m_iSize ; iIndex++)
				{
					m_pdblImg[iIndex] = 1;
				}
			}
			else
				return false;
		}
		else
			return false;

		return true;	
	}

	string Double::toString(int _iPrecision, int _iLineLen)
	{
		std::ostringstream ostr;
		std::ostringstream szTemp;

		/*Comment tenir compte de la longueur des lignes dans le formatage de variable ? */
		if(cols_get() == 1 && rows_get() == 1)
		{//scalar
			bool bSign	= m_pdblReal[0] < 0;
			bool bStartByZero = false;

			/*if the value start by zero, we have 1 caracter less for the precision*/
			if(m_pdblReal[0] < 1 && m_pdblReal[0] > -1)
				bStartByZero = true;


			int iNbEnt = 0, iNbDec = 0;
			GetFormat(m_pdblReal[0], _iPrecision, &iNbEnt, &iNbDec);
			cout << "|";
			cout << (bSign == true ? "- " : "  ");

			//width is the min value between the max size and the needed space.
			int width = min(_iPrecision, iNbEnt + iNbDec );
			cout.width(width);
			//presicion is the min vlaue between needed precision - 1 ( I don't not why Oo ) less NbEnt size ( +1 for the dot ) and iNbDec
			int prec = _iPrecision - 1 - bStartByZero;
			cout.precision(prec);
			cout.fill(' ');
			cout << left << abs(m_pdblReal[0]);
			cout.width(0);
			cout.precision(0);
			cout << "|" << endl;
		}
		else if(cols_get() == 1)
		{//column vector
			ostr << "[" << std::endl;
			for(int i = 0 ; i < rows_get() ; i++)
			{
				ostr << m_pdblReal[i] << std::endl;
			}
			ostr << "\x09]" << std::endl;
		}
		else if(rows_get() == 1)
		{//row vector
			bool bWordWarp = false;
			int iLineTag = 5000; //or not Oo

			if(_iLineLen == -1)
			{
				bWordWarp = true;
			}

			ostr << "[ ";
			for(int i = 0 ; i < cols_get() ; i++)
			{
				if(i != 0)
				{
					szTemp << "\x09,";
				}

				if(bWordWarp == false && (int)szTemp.str().size() >= _iLineLen)
				{
					bWordWarp = true;
					iLineTag	= i;
				}

				if(bWordWarp == true && i%iLineTag == 0)
				{
					ostr << std::endl << "\t\tcolumn " << (i - 1) / (iLineTag + 1) * iLineTag + 1 << " to " << i << std::endl;
					ostr << szTemp << std::endl;
					szTemp.clear();
				}

				szTemp << m_pdblReal[i];
			}
			if(bWordWarp == true)
			{
				ostr << std::endl << "\t\tcolumn " << (cols_get() - 1) / (iLineTag + 1) * iLineTag + 1 << " to " << cols_get() << std::endl;
			}
			ostr << szTemp;
			ostr << " ]" << std::endl;
		}
		else 
		{
			bool bWordWarp = false;
			int iLineTag = 5000; //or not Oo

			unsigned int  *iSize = new unsigned int[cols_get()];
			memset(iSize, 0x00, cols_get() * sizeof(int));

			int iRows = rows_get();
			for(int i = 0 ; i < cols_get() ; i++)
			{
				for(int j = 0 ; j < rows_get() ; j++)
				{
					double entier = (int)m_pdblReal[i * iRows + j];
					double virgule = m_pdblReal[i * iRows + j] - entier;
					double LogEntier = log10(entier);
					double LogVirgule = abs(log10(virgule));
					if(entier == 0)
						LogEntier = 0;

					if(virgule == 0)
						LogVirgule = 0;

					int iPres = /*(int)(LogEntier) +*/ (int)(LogVirgule);
//					if((int)LogEntier != LogEntier)
//						iPres += 1;
					if((int)LogVirgule != LogVirgule)
						iPres += 1;
					std::ostringstream os;
					//os.setf(std::ios_base::fixed);
					os.precision(iPres);
					os << std::fixed << m_pdblReal[i * iRows + j];
					iSize[i] = (iSize[i] > os.str().size()) ? iSize[i] : os.str().size();
					//std::cerr.precision(_iPrecison);
					std::cerr << os.str() << "  " << os.str().size() << std::endl;
				}
				std::cerr << std::endl;
			}

			for(int i = 0 ; i < cols_get() ; i++)
			{
				//cout << "width : " << iSize[i] + 4 << endl;
				cout.width(iSize[i] + 4 );
				//cout.precision(iSize[i]);
				
				cout.fill('*');

				for(int j = 0 ; j < rows_get() ; j++)
				{
					cout << fixed << left << m_pdblReal[i * rows_get() + j] << " ";
				}
				cout << endl;

			}
		}
		return ostr.str();
	}
}

void GetFormat(double _dblVal, int _iPrecision, int *_piEntNb, int *_piDecNb)
{
	double dblDec = 0;
	double dblEnt = 0;
	double dblAbs = abs(_dblVal);
	int iNbDigit	= 0;
	double dblTmp	= 0;

	dblDec				= modf(dblAbs, &dblEnt);

	iNbDigit = ((int)log10(dblEnt + 0.4)) + 1;
	if(iNbDigit <= _iPrecision - 2)
	{
		*_piEntNb	= iNbDigit;
		iNbDigit	= _iPrecision - *_piEntNb;
		*_piDecNb	= 0;
		dblTmp		= dblDec * pow(10.0e+0, iNbDigit + 1);
		dblDec		= floor(dblTmp / 10.0e+0 + 0.5);

		if(dblDec != 0)
		{
			*_piDecNb = iNbDigit;
			while(fmod(dblDec, 10.0e+0) == 0)
			{
				*_piDecNb -= 1;
				dblDec = dblDec / 10.0e+0;
			}
			//*_piEntNb = _iPrecision - *_piDecNb;
		}
	}
}
