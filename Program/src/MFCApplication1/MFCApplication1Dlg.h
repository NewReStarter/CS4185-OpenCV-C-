
// MFCApplication1Dlg.h: header file
//

#pragma once
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "CvvImage.h"

// CMFCApplication1Dlg chatbox
class CMFCApplication1Dlg : public CDialogEx
{
// init
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// data of chatbox
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// realization
protected:
	HICON m_hIcon;
	CComboBox retrievallist;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton1();
	void DrawPicToHDC(IplImage *img, UINT ID);
	int imageretrieval();
	int objectdetection();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};
