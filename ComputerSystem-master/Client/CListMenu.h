#pragma once


// CListMenu

class CListMenu : public CListBox
{
	DECLARE_DYNAMIC(CListMenu)

public:
	CListMenu();
	virtual ~CListMenu();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


