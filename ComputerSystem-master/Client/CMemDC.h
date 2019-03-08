#pragma once
#include"stdafx.h"
class MemDC :public CDC
{
private:
	CBitmap  m_bitmap;      // ʵ�ʵ�bitmap
	CBitmap* m_pOldBitmap;  // ԭ����MemDC�е�λͼ
	CDC*     m_pDC;         // ����ӹ��캯���д�����CDC
	CRect    m_rect;        // ���ľ�������
	BOOL     m_bMemDC;      // ���CDC��һ���ڴ�DC����ΪTRUE

public:

	MemDC(CDC* pDC) : CDC()
	{
		ASSERT(pDC != NULL);

		m_pDC = pDC;
		m_pOldBitmap = NULL;
		m_bMemDC = !pDC->IsPrinting();//�ж��Ƿ���һ���ڴ�DC

		if (m_bMemDC)    // ����һ���ڴ�DC
		{
			pDC->GetClipBox(&m_rect);
			CreateCompatibleDC(pDC);
			m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_pOldBitmap = SelectObject(&m_bitmap);
			SetWindowOrg(m_rect.left, m_rect.top);
		}
		else  // �ⲻ��һ���ڴ�DC������ֻ������ص�DC�����Ա���ӡ
		{
			m_bPrinting = pDC->m_bPrinting;
			m_hDC = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}
	}

	~MemDC()
	{
		if (m_bMemDC)
		{
			// ����ʵ�ʵ�λͼ����Ļ��
			m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				this, m_rect.left, m_rect.top, SRCCOPY);
			//װ��ԭʼ��λͼ
			SelectObject(m_pOldBitmap);
		}
		else
		{
			m_hDC = m_hAttribDC = NULL;
		}
	}

	// ������Ϊָ��
	MemDC* operator->() { return this; }
	operator MemDC*() { return this; }

};