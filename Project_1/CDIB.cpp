// Dib.cpp: implementation of the CDIB class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <atlimage.h>
#include "Project_1.h"
#include "CDib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDIB::CDIB()
{
	m_pData = NULL;
	m_Rect = CRect(0, 0, 0, 0);
	m_CenterPoint = CPoint(0, 0);
}

CDIB::~CDIB()
{
	if (m_pData != NULL)
	{
		delete	m_pData;
		m_pData = NULL;
		m_Rect = CRect(0, 0, 0, 0);
	}
}

BITMAPINFO* CDIB::GetInfoPtr()
{
	return	(BITMAPINFO*)m_pData;
}

BITMAPINFOHEADER* CDIB::GetHeaderPtr()
{
	return	(BITMAPINFOHEADER*)m_pData;
}

BOOL CDIB::LoadFile(LPCTSTR pName)
{
	CFile	file(pName, CFile::modeRead);

	if (m_pData != NULL)
		delete	m_pData;

	m_pData = new	BYTE[file.GetLength()];

	file.Seek(sizeof(BITMAPFILEHEADER), CFile::begin);

	file.Read(m_pData, sizeof(BITMAPINFOHEADER));

	BOOL	bFlag = FALSE;
	GetHeaderPtr()->biBitCount = 24;
	GetHeaderPtr()->biClrImportant = 0;
	GetHeaderPtr()->biClrUsed = 0;
	GetHeaderPtr()->biCompression = 0;
	if (GetHeaderPtr()->biHeight > 0)
	{
		GetHeaderPtr()->biHeight *= -1;
		bFlag = TRUE;

	}
	GetHeaderPtr()->biPlanes = 1;
	GetHeaderPtr()->biXPelsPerMeter = 0;
	GetHeaderPtr()->biYPelsPerMeter = 0;

	//그림이거꾸로있는경우
	if (bFlag == TRUE)
	{
		for (int i = 1; i <= Height(); ++i)
		{
			//뒤에서부터읽어서
			file.Seek(-GetBytesPerLine() * i, CFile::end);
			//대상에처음부터쓴다
			file.Read(&(GetImgPtr()[(i - 1) * GetBytesPerLine()]), GetBytesPerLine());
		}
	}
	else
	{
		file.Read(GetImgPtr(), GetBytesPerLine() * Height());
	}
	m_Rect = CRect(0, 0, Width(), Height());
	return	TRUE;
}

RECT CDIB::GetOptRect(POINT point)
{
	CRect	rect(point.x, point.y, point.x, point.y);

	while (1)
	{
		BOOL	f1 = FALSE, f2 = FALSE, f3 = FALSE, f4 = FALSE;

		int	i;
		for (i = rect.left; i <= rect.right; ++i)
		{
			if ((GetImgPtr()[0] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3]) ||
				(GetImgPtr()[1] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3 + 1]) ||
				(GetImgPtr()[2] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3 + 2]))
			{
				f1 = TRUE;
				break;
			}
		}
		for (i = rect.top; i <= rect.bottom; ++i)
		{
			if ((GetImgPtr()[0] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3]) ||
				(GetImgPtr()[1] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3 + 1]) ||
				(GetImgPtr()[2] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3 + 2]))
			{
				f2 = TRUE;
				break;
			}
		}
		for (i = rect.left; i <= rect.right; ++i)
		{
			if ((GetImgPtr()[0] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3]) ||
				(GetImgPtr()[1] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3 + 1]) ||
				(GetImgPtr()[2] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3 + 2]))
			{
				f3 = TRUE;
				break;
			}
		}
		for (i = rect.top; i <= rect.bottom; ++i)
		{
			if ((GetImgPtr()[0] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3]) ||
				(GetImgPtr()[1] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3 + 1]) ||
				(GetImgPtr()[2] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3 + 2]))
			{
				f4 = TRUE;
				break;
			}
		}

		if (f1 == TRUE)
		{
			if (rect.top > 0)
			{
				rect.top--;
			}
			else
			{
				f1 = FALSE;
			}
		}
		if (f2 == TRUE)
		{
			if (rect.right < (Width() - 1))
			{
				rect.right++;
			}
			else
			{
				f2 = FALSE;
			}
		}
		if (f3 == TRUE)
		{
			if (rect.bottom < (Height() - 1))
			{
				rect.bottom++;
			}
			else
			{
				f3 = FALSE;
			}
		}
		if (f4 == TRUE)
		{
			if (rect.left > 0)
			{
				rect.left--;
			}
			else
			{
				f4 = FALSE;
			}
		}

		if ((f1 == FALSE) && (f2 == FALSE) && (f3 == FALSE) && (f4 == FALSE))
			break;
	}

	if (rect.IsRectEmpty())
		return	CRect(0, 0, 0, 0);

	BOOL	f1 = FALSE, f2 = FALSE, f3 = FALSE, f4 = FALSE;
	int	i;
	for (i = rect.left; i <= rect.right; ++i)
	{
		if ((GetImgPtr()[0] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3]) ||
			(GetImgPtr()[1] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3 + 1]) ||
			(GetImgPtr()[2] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3 + 2]))
		{
			f1 = TRUE;
			break;
		}
	}
	for (i = rect.top; i <= rect.bottom; ++i)
	{
		if ((GetImgPtr()[0] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3]) ||
			(GetImgPtr()[1] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3 + 1]) ||
			(GetImgPtr()[2] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3 + 2]))
		{
			f2 = TRUE;
			break;
		}
	}
	for (i = rect.left; i <= rect.right; ++i)
	{
		if ((GetImgPtr()[0] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3]) ||
			(GetImgPtr()[1] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3 + 1]) ||
			(GetImgPtr()[2] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3 + 2]))
		{
			f3 = TRUE;
			break;
		}
	}
	for (i = rect.top; i <= rect.bottom; ++i)
	{
		if ((GetImgPtr()[0] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3]) ||
			(GetImgPtr()[1] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3 + 1]) ||
			(GetImgPtr()[2] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3 + 2]))
		{
			f4 = TRUE;
			break;
		}
	}
	if ((f1 == FALSE) && (rect.top < rect.bottom))
		rect.top++;

	if ((f2 == FALSE) && (rect.right > rect.left))
		rect.right--;

	if ((f3 == FALSE) && (rect.bottom > rect.top))
		rect.bottom--;

	if ((f4 == FALSE) && (rect.left < rect.right))
		rect.left++;

	rect.NormalizeRect();

	rect.right++;
	rect.bottom++;

	return	rect;
}

BOOL CDIB::LoadFromDib(CDIB* pDib, CRect rect)
{
	if (m_pData != NULL)
		delete	m_pData;

	m_pData = new	BYTE[sizeof(BITMAPINFOHEADER) + (((rect.Width() * 24 + 31) & ~31) >> 3) * rect.Height()];

	GetHeaderPtr()->biBitCount = 24;
	GetHeaderPtr()->biClrImportant = 0;
	GetHeaderPtr()->biClrUsed = 0;
	GetHeaderPtr()->biCompression = 0;
	GetHeaderPtr()->biHeight = -rect.Height();
	GetHeaderPtr()->biPlanes = 1;
	GetHeaderPtr()->biSize = sizeof(BITMAPINFOHEADER);
	GetHeaderPtr()->biSizeImage = (((rect.Width() * 24 + 31) & ~31) >> 3) * rect.Height();
	GetHeaderPtr()->biWidth = rect.Width();
	GetHeaderPtr()->biXPelsPerMeter = 0;
	GetHeaderPtr()->biYPelsPerMeter = 0;

	for (int i = 0; i < rect.Height(); ++i)
	{
		::memcpy(&((GetImgPtr())[i * GetBytesPerLine()]),
			&((pDib->GetImgPtr())[(rect.top + i) * pDib->GetBytesPerLine() + rect.left * 3]), rect.Width() * 3);
	}

	m_Rect = rect;

	m_CenterPoint.x = Width() / 2;
	m_CenterPoint.y = Height() / 2;

	return	TRUE;
}

BYTE* CDIB::GetImgPtr()
{
	return	(BYTE*)(m_pData + sizeof(BITMAPINFOHEADER));
}

int CDIB::Width()
{
	return	GetHeaderPtr()->biWidth;
}

int CDIB::Height()
{
	return	-(GetHeaderPtr()->biHeight);
}

int CDIB::GetBytesPerLine()
{
	return	((Width() * 24 + 31) & ~31) >> 3;
}

BOOL CDIB::IsEmpty()
{
	if (m_pData == NULL)
		return	TRUE;
	return	FALSE;
}

RECT CDIB::GetOptRect(RECT _rect)
{
	CRect	rect = _rect;

	BOOL	f1 = FALSE, f2 = FALSE, f3 = FALSE, f4 = FALSE;

	while (1)
	{
		int	i;
		if (f1 == FALSE)
		{
			for (i = rect.left; i <= rect.right; ++i)
			{
				if ((GetImgPtr()[0] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3]) ||
					(GetImgPtr()[1] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3 + 1]) ||
					(GetImgPtr()[2] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3 + 2]))
				{
					f1 = TRUE;
					break;
				}
			}
		}
		if (f2 == FALSE)
		{
			for (i = rect.top; i <= rect.bottom; ++i)
			{
				if ((GetImgPtr()[0] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3]) ||
					(GetImgPtr()[1] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3 + 1]) ||
					(GetImgPtr()[2] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3 + 2]))
				{
					f2 = TRUE;
					break;
				}
			}
		}
		if (f3 == FALSE)
		{
			for (i = rect.left; i <= rect.right; ++i)
			{
				if ((GetImgPtr()[0] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3]) ||
					(GetImgPtr()[1] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3 + 1]) ||
					(GetImgPtr()[2] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3 + 2]))
				{
					f3 = TRUE;
					break;
				}
			}
		}
		if (f4 == FALSE)
		{
			for (i = rect.top; i <= rect.bottom; ++i)
			{
				if ((GetImgPtr()[0] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3]) ||
					(GetImgPtr()[1] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3 + 1]) ||
					(GetImgPtr()[2] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3 + 2]))
				{
					f4 = TRUE;
					break;
				}
			}
		}

		if (f1 == FALSE)
		{
			if (rect.top < rect.bottom)
			{
				rect.top++;
			}
			else
			{
				f1 = TRUE;
			}
		}
		if (f2 == FALSE)
		{
			if (rect.right > rect.left)
			{
				rect.right--;
			}
			else
			{
				f2 = TRUE;
			}
		}
		if (f3 == FALSE)
		{
			if (rect.bottom > rect.top)
			{
				rect.bottom--;
			}
			else
			{
				f3 = TRUE;
			}
		}
		if (f4 == FALSE)
		{
			if (rect.left < rect.right)
			{
				rect.left++;
			}
			else
			{
				f4 = TRUE;
			}
		}

		if ((f1 == TRUE) && (f2 == TRUE) && (f3 == TRUE) && (f4 == TRUE))
			break;
	}

	f1 = FALSE;
	f2 = FALSE;
	f3 = FALSE;
	f4 = FALSE;

	int	i;

	for (i = rect.left; i <= rect.right; ++i)
	{
		if ((GetImgPtr()[0] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3]) ||
			(GetImgPtr()[1] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3 + 1]) ||
			(GetImgPtr()[2] != GetImgPtr()[rect.top * GetBytesPerLine() + i * 3 + 2]))
		{
			f1 = TRUE;
			break;
		}
	}
	for (i = rect.top; i <= rect.bottom; ++i)
	{
		if ((GetImgPtr()[0] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3]) ||
			(GetImgPtr()[1] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3 + 1]) ||
			(GetImgPtr()[2] != GetImgPtr()[i * GetBytesPerLine() + rect.right * 3 + 2]))
		{
			f2 = TRUE;
			break;
		}
	}
	for (i = rect.left; i <= rect.right; ++i)
	{
		if ((GetImgPtr()[0] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3]) ||
			(GetImgPtr()[1] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3 + 1]) ||
			(GetImgPtr()[2] != GetImgPtr()[rect.bottom * GetBytesPerLine() + i * 3 + 2]))
		{
			f3 = TRUE;
			break;
		}
	}
	for (i = rect.top; i <= rect.bottom; ++i)
	{
		if ((GetImgPtr()[0] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3]) ||
			(GetImgPtr()[1] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3 + 1]) ||
			(GetImgPtr()[2] != GetImgPtr()[i * GetBytesPerLine() + rect.left * 3 + 2]))
		{
			f4 = TRUE;
			break;
		}
	}
	if ((f1 == FALSE) || (f2 == FALSE) || (f3 == FALSE) || (f4 == FALSE))
		return	CRect(0, 0, 0, 0);

	rect.NormalizeRect();

	rect.right++;
	rect.bottom++;

	return	rect;
}

BOOL CDIB::Save(HANDLE hFile)
{
	DWORD dwBytesWritten;

	if (IsEmpty())
	{
		return FALSE;
	}
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!WriteFile(hFile, &(GetHeaderPtr()->biWidth), 2, &dwBytesWritten, NULL)
		|| (dwBytesWritten != 2))
	{
		return FALSE;
	}
	if (!WriteFile(hFile, &(GetHeaderPtr()->biHeight), 2, &dwBytesWritten, NULL)
		|| (dwBytesWritten != 2))
	{
		return FALSE;
	}
	if (!WriteFile(hFile, &(GetHeaderPtr()->biSizeImage), 4, &dwBytesWritten, NULL)
		|| (dwBytesWritten != 4))
	{
		return FALSE;
	}
	if (!WriteFile(hFile, GetImgPtr(), GetHeaderPtr()->biSizeImage, &dwBytesWritten, NULL)
		|| (dwBytesWritten != GetHeaderPtr()->biSizeImage))
		return FALSE;

	return TRUE;
}

BOOL CDIB::InitFromHandle(HANDLE hFile)
{
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD				dwBytesRead;
	BITMAPINFOHEADER* pBmih;
	BYTE* pBits;
	short int Width, Height;
	int SizeImage;

	if (!ReadFile(hFile, &Width, 2, &dwBytesRead, NULL)
		|| (dwBytesRead != 2))
		return FALSE;
	if (!ReadFile(hFile, &Height, 2, &dwBytesRead, NULL)
		|| (dwBytesRead != 2))
		return FALSE;
	if (!ReadFile(hFile, &SizeImage, 4, &dwBytesRead, NULL)
		|| (dwBytesRead != 4))
		return FALSE;
	pBits = new BYTE[SizeImage];
	if (pBits == NULL)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, pBits, SizeImage, &dwBytesRead, NULL)
		|| (dwBytesRead != (DWORD)SizeImage))
	{
		delete pBits;
		return FALSE;
	}
	pBmih = new BITMAPINFOHEADER;
	if (pBmih == NULL)
	{
		delete pBits;
		return FALSE;
	}

	pBmih->biBitCount = 24;
	pBmih->biClrImportant = 0;
	pBmih->biClrUsed = 0;
	pBmih->biCompression = 0;
	pBmih->biHeight = Height;
	pBmih->biPlanes = 1;
	pBmih->biSize = sizeof(BITMAPINFOHEADER);
	pBmih->biSizeImage = SizeImage;
	pBmih->biWidth = Width;
	pBmih->biXPelsPerMeter = 0;
	pBmih->biYPelsPerMeter = 0;

	if (IsEmpty() == FALSE)
	{
		delete m_pData;
		m_pData = NULL;
	}

	m_pData = new BYTE[sizeof(BITMAPINFOHEADER) + SizeImage];
	memcpy(m_pData, pBmih, sizeof(BITMAPINFOHEADER));
	memcpy(m_pData + sizeof(BITMAPINFOHEADER), pBits, SizeImage);

	//	m_CenterPoint.x = Width / 2;
	//	m_CenterPoint.y = Height / 2;

	return TRUE;
}
