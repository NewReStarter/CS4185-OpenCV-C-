
// MFCApplication1Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/nonfree/nonfree.hpp"  
#include "opencv2/nonfree/features2d.hpp"
#include "opencv/cv.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <io.h>  
#include <direct.h>

using namespace std;
using namespace cv;
char IMAGE_folder[MAX_PATH] = "";
//#define IMAGE_folder ".."     //folder location
#define IMAGE_LIST_FILE_1 "dataset1"         //the dataset1 for retrieval
#define IMAGE_LIST_FILE_2 "dataset2"      //the dataset2 for detection
#define SEARCH_IMAGE "football.png"     //input information

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
double avep[10];
double aver[10];
double aveiou[10];
double aveacc[10];
int countvalue1[10], countvalue2[10];

int countnum1 = 0, countnum2 = 0;

int found1 = 0, found2 = 0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// chatbox data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// realization
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg chatbox



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, retrievallist);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CMFCApplication1Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCApplication1Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handler

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// set big icon
	SetIcon(m_hIcon, FALSE);		// set small icon

	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	GetDlgItem(IDC_STATICSEC)->ShowWindow(0);
	retrievallist.AddString("990.jpg");
	retrievallist.AddString("991.jpg");
	retrievallist.AddString("992.jpg");
	retrievallist.AddString("993.jpg");
	retrievallist.AddString("994.jpg");
	retrievallist.AddString("995.jpg");
	retrievallist.AddString("996.jpg");
	retrievallist.AddString("997.jpg");
	retrievallist.AddString("998.jpg");
	retrievallist.AddString("999.jpg");
	retrievallist.SetCurSel(0);

	SetDlgItemTextA(IDC_EDIT2, IMAGE_folder);
	return TRUE;  
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// draw UI
void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedRadio1()
{
	GetDlgItem(IDC_STATICSEC)->ShowWindow(0);
	retrievallist.ResetContent();
	retrievallist.AddString("990.jpg");
	retrievallist.AddString("991.jpg");
	retrievallist.AddString("992.jpg");
	retrievallist.AddString("993.jpg");
	retrievallist.AddString("994.jpg");
	retrievallist.AddString("995.jpg");
	retrievallist.AddString("996.jpg");
	retrievallist.AddString("997.jpg");
	retrievallist.AddString("998.jpg");
	retrievallist.AddString("999.jpg");
	retrievallist.SetCurSel(0);
}


void CMFCApplication1Dlg::OnBnClickedRadio2()
{
	GetDlgItem(IDC_STATICSEC)->ShowWindow(1);
	retrievallist.ResetContent();
	retrievallist.AddString("1.jpg");
	retrievallist.AddString("2.jpg");
	retrievallist.AddString("3.jpg");
	retrievallist.AddString("4.jpg");
	retrievallist.AddString("5.jpg");
	retrievallist.AddString("6.jpg");
	retrievallist.AddString("7.jpg");
	retrievallist.AddString("8.jpg");
	retrievallist.AddString("9.jpg");
	retrievallist.AddString("10.jpg");
	retrievallist.SetCurSel(0);
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	CString str;

	ZeroMemory(IMAGE_folder, sizeof(IMAGE_folder));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = IMAGE_folder;
	bi.lpszTitle = "please select the directory：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, IMAGE_folder))
	{
		//str.Format("folder selected is %s", szPath);
		SetDlgItemTextA(IDC_EDIT2, IMAGE_folder);
		//AfxMessageBox(str);


	}
	else
		AfxMessageBox("Invalid Folder, select again");

}
void CMFCApplication1Dlg::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);
}


int  removeDir(char*  dirPath)  //delete specified directory
{

	struct _finddata_t fb;
	char  path[250];
	long    handle;
	int  resultone;
	int   noFile;

	noFile = 0;
	handle = 0;

	strcpy(path, dirPath);
	strcat(path, "\\*");
	strcat(path, "\0");

	handle = _findfirst(path, &fb);

	if (handle != 0)
	{

		while (0 == _findnext(handle, &fb))
		{

			noFile = strcmp(fb.name, "..");

			if (0 != noFile)
			{

				memset(path, 0, sizeof(path));
				strcpy(path, dirPath);
				strcat(path, "\\");
				strcat(path, fb.name);

				if (fb.attrib == 16)
				{
					removeDir(path);
				}

				else
				{
					remove(path);
				}
			}
		}

		_findclose(handle);
	}

	return 0;
}



double compareImgs(CvHistogram *Histogram1, CvHistogram *Histogram2)
{
	return cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA);
}


// select circles
// since football are black and white, colors in the circles should be black and white
int selectCircle(Mat &img, Vec3f circle) 
{
	// get circle's center and radius
	int r = cvRound(circle[2] / 2);
	int top = cvRound(circle[1] - r);
	int left = cvRound(circle[0] - r);
	// beyond image area
	if (left < 0 || top < 0 || left + 2 * r >= img.cols || top + 2 * r >= img.rows) {
		return 0;
	}
	Rect rect(left, top, 2 * r, 2 * r);
	Mat roi = img(rect);
	int thres = roi.rows * roi.cols / 5;
	int color_diff_thres = 20;
	int cnt = 0;
	for (int r = 0; r < roi.rows; r++) {
		for (int c = 0; c < roi.cols; c++) {
			Vec3b bgr = roi.at<Vec3b>(r, c);
			if (bgr[1] > bgr[0] + color_diff_thres && bgr[1] > bgr[2] + color_diff_thres) {
				cnt++;
			}
			else if (bgr[2] > bgr[0] + color_diff_thres && bgr[2] > bgr[1] + color_diff_thres) {
				cnt++;
			}
			else if (bgr[0] > bgr[1] + color_diff_thres && bgr[0] > bgr[2] + color_diff_thres) {
				cnt++;
			}
		}
	}
	if (cnt < thres) {
		return 1;
	}

	return 0;
}

// Algorithm:
// 1. use HoughCircle to remove fps which do not contain "circle"
// 2. use hsv color space to calculate hist
int CMFCApplication1Dlg::imageretrieval() {

	int counttemp = retrievallist.GetCurSel();
	CString searchimg;
	retrievallist.GetLBText(counttemp, searchimg);

	if (countnum1 == 0)
	{
		countvalue1[countnum1] = counttemp;
		countnum1++;

	}
	else {
		found1 = 0;
		for (int i = 0; i < countnum1; i++)
			if (countvalue1[i] == counttemp)
			{
				found1 = 1;
				break;
			}
		if (found1 == 0)
		{
			countvalue1[countnum1] = counttemp;
			countnum1++;
		}

	}

	CEdit* etx = (CEdit*)GetDlgItem(IDC_EDIT1);
	etx->SetWindowTextA("");
	const int filename_len = 900;
	char tempname[filename_len];

	const int db_size = 1000;
	int db_id = 0;

	const int score_size = 10;
	double minscore[score_size] = { DBL_MAX };
	int minFilename[score_size];

	char minimg_name[filename_len];
	Mat min_img;

	sprintf_s(tempname, filename_len, "%s\\%s\\%s", IMAGE_folder, IMAGE_LIST_FILE_1, searchimg);
	IplImage *image1 = cvLoadImage(tempname, 1);
	IplImage *image5 = cvLoadImage(tempname, 1);
	if (NULL == image1)
	{
		etx->SetSel(-1, -1);
		etx->ReplaceSel("Cannot find the input image!\r\n");

		return -1;
	}

	DrawPicToHDC(image5, IDC_STATIC);

	// BGR -> HSV
	IplImage *image3;
	CvHistogram *Histogram1;
	CvHistogram *Histogram2;
	image3 = cvCreateImage(cvSize(500, 500), 8, 3);
	cvResize(image1, image3);
	IplImage* hsv1 = cvCreateImage(cvGetSize(image3), 8, 3);
	cvCvtColor(image3, hsv1, CV_BGR2HSV);

	IplImage* h_plane = cvCreateImage(cvGetSize(image3), 8, 1);
	IplImage* s_plane = cvCreateImage(cvGetSize(image3), 8, 1);
	IplImage* v_plane = cvCreateImage(cvGetSize(image3), 8, 1);
	IplImage* planes[] = { h_plane, s_plane };
	cvCvtPixToPlane(hsv1, h_plane, s_plane, v_plane, 0);

	// init hist
	int h_bins = 15, s_bins = 15;
	{
		int hist_size[] = { h_bins, s_bins };
		float h_ranges[] = { 0, 180 };
		float s_ranges[] = { 0, 180 };
		float* ranges[] = { h_ranges, s_ranges };
		Histogram1 = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1);
		Histogram2 = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1);
	};
	cvCalcHist(planes, Histogram1, 0, 0);

	cvNormalizeHist(Histogram1, 1);
	cvReleaseImage(&image1);
	cvReleaseImage(&image3);
	IplImage *image2, *image4;
	//Read Database
	for (db_id; db_id < db_size; db_id++) {
		sprintf_s(tempname, filename_len, "%s\\%s\\%d.jpg", IMAGE_folder, IMAGE_LIST_FILE_1, db_id);

		image2 = cvLoadImage(tempname, 1);    //read the compared image
		if (NULL == image2)
		{
			CString err;
			err.Format("Cannot find the database image number %d!\r\n", db_id + 1);
			etx->SetSel(-1, -1);
			etx->ReplaceSel(err);

			return -1;
		} 
	
		// calculate current image's hsv color hist 
		image4 = cvCreateImage(cvSize(500, 500), image2->depth, image2->nChannels);
		cvResize(image2, image4);
		IplImage* hsv_cmp = cvCreateImage(cvGetSize(image4), 8, 3);
		cvCvtColor(image4, hsv_cmp, cv::COLOR_BGR2HSV);
		IplImage* h_plane_cmp = cvCreateImage(cvGetSize(image4), 8, 1);
		IplImage* s_plane_cmp = cvCreateImage(cvGetSize(image4), 8, 1);
		IplImage* v_plane_cmp = cvCreateImage(cvGetSize(image4), 8, 1);
		IplImage* planes_cmp[] = { h_plane_cmp, s_plane_cmp };
		cvCvtPixToPlane(hsv_cmp, h_plane_cmp, s_plane_cmp, v_plane_cmp, 0);
		cvCalcHist(planes_cmp, Histogram2, 0, 0);

		cvNormalizeHist(Histogram2, 1);
		
		double tempScore = compareImgs(Histogram1, Histogram2);
		
		// use houghcircles to detect circles in images
		vector<Vec3f> circles;
		Mat grayImage;
		Mat cmp_mat = cvarrToMat(image2, true);
		if (cmp_mat.rows > 700) {
			resize(cmp_mat, cmp_mat, cvSize(int(cmp_mat.cols / 2), int(cmp_mat.rows / 2)));
		}
		cvtColor(cmp_mat, grayImage, COLOR_BGR2GRAY);
		// smooth; because houghcircles is very Sensitive to noise
		GaussianBlur(grayImage, grayImage, Size(19, 19), 0, 0);
		HoughCircles(grayImage, circles, CV_HOUGH_GRADIENT, 1, 80, 45, 40, 50, 200);
		if (circles.size() > 0) {
			int contain_candi = 0;
			for (int circle_id = 0; circle_id < circles.size(); circle_id++) {
				if (selectCircle(cmp_mat, circles[circle_id])) {
					contain_candi = 1;
				}
			}

			if (contain_candi) {
				for (int k = 0; k < score_size; k++) {
					if (tempScore < minscore[k]) {
						for (int k1 = score_size - 1; k1 > k; k1--) {
							minscore[k1] = minscore[k1 - 1];
							minFilename[k1] = minFilename[k1 - 1];
						}
						minscore[k] = tempScore;
						minFilename[k] = db_id;
						break;
					}
				}
			}
		}
		else if (tempScore < 0.01) {
			for (int k = 0; k < score_size; k++) {
				if (tempScore < minscore[k]) {
					for (int k1 = score_size - 1; k1 > k; k1--) {
						minscore[k1] = minscore[k1 - 1];
						minFilename[k1] = minFilename[k1 - 1];
					}
					minscore[k] = tempScore;
					minFilename[k] = db_id;
					break;
				}
			}
		}

		cvReleaseImage(&image2);
		cvReleaseImage(&image4);
		cvReleaseImage(&h_plane_cmp);
		cvReleaseImage(&s_plane_cmp);
		cvReleaseImage(&v_plane_cmp);
		cvReleaseImage(&hsv_cmp);
	}
	
	char dirpath[filename_len];
	sprintf_s(dirpath, filename_len, "%s\\search_results", IMAGE_folder);
	if (_access(dirpath, 0) == -1)
		_mkdir(dirpath);
	else
	{
		//removeDir(dirpath);
		CString str;

		str.Format("rd /s /q %s", dirpath);
		system(str);
		_mkdir(dirpath);
	}
	for (int k = 0; k < score_size; k++) {
		sprintf_s(minimg_name, filename_len, "%s\\%s\\%d.jpg", IMAGE_folder, IMAGE_LIST_FILE_1, minFilename[k]);

		IplImage *min_img = cvLoadImage(minimg_name, 1);
		CString str;

		str.Format("The most similar image %d is %d.jpg, the Bhattacharyya distance is %f\r\n", k + 1, minFilename[k], minscore[k]);

		etx->SetSel(-1, -1);
		etx->ReplaceSel(str);
		sprintf_s(tempname, filename_len, "%s\\search_results\\%d.jpg", IMAGE_folder, minFilename[k]);
		cvSaveImage(tempname, min_img);

	}
	
	int count = 0;
	for (int k = 0; k < score_size; k++) {
		if (minFilename[k] >= 990 && minFilename[k] <= 999) {
			count++;
		}
	}
	double precision = (double)count / score_size;
	double recall = (double)count / 10;

	if (found1 == 0) {
		avep[countnum1 - 1] = precision;
		aver[countnum1 - 1] = recall;
	}
	double ap = 0, ar = 0;
	for (int i = 0; i < countnum1; i++)
	{
		ap = ap + avep[i];
		ar = ar + aver[i];
	}
	ap = ap / countnum1;
	ar = ar / countnum1;

	CString strf;
	strf.Format("The precision and the recall for %s are %.2f and %.2f\r\n", searchimg, precision, recall);
	etx->SetSel(-1, -1);
	etx->ReplaceSel(strf);
	strf.Format("The average precision and recall so far are %.2f and %.2f\r\n", ap, ar);
	etx->SetSel(-1, -1);
	etx->ReplaceSel(strf);

	return 0;
}

// Algorithm:
// divide top-10 to two part:
// 1. use sliding windows to find first 8 candidates 
// 2. use HoughCircle to find last 2 candidates

int CMFCApplication1Dlg::objectdetection() {

	int detectimg = retrievallist.GetCurSel() + 1;

	if (countnum2 == 0)
	{
		countvalue2[countnum2] = detectimg;
		countnum2++;

	}
	else {
		found2 = 0;
		for (int i = 0; i < countnum2; i++)
			if (countvalue2[i] == detectimg)
			{
				found2 = 1;
				break;
			}
		if (found2 == 0)
		{
			countvalue2[countnum2] = detectimg;
			countnum2++;
		}

	}


	CEdit* etx = (CEdit*)GetDlgItem(IDC_EDIT1);
	etx->SetWindowTextA("");
	const int filename_len = 900;
	char tempname[filename_len];

	const int score_size = 10;
	double score[score_size] = { DBL_MAX };
	int start_x[score_size], start_y[score_size], end_x[score_size], end_y[score_size];

	sprintf_s(tempname, filename_len, "%s\\%s", IMAGE_folder, SEARCH_IMAGE);
	IplImage *image1 = cvLoadImage(tempname, 0);
	if (NULL == image1)
	{
		etx->SetSel(-1, -1);
		etx->ReplaceSel("Cannot find the input image!\r\n");

		return -1;
	}
	DrawPicToHDC(image1, IDC_STATICSEC);


	int HistogramBins = 256;
	float range[] = { 0,255 };
	float *HistogramRange[] = { range };


	CvHistogram *Histogram1 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY, HistogramRange);
	CvHistogram *Histogram2 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY, HistogramRange);

	cvCalcHist(&image1, Histogram1, 0, 0);


	cvNormalizeHist(Histogram1, 1);


	//Read detection IMAGE
	sprintf_s(tempname, filename_len, "%s\\%s\\%d.jpg", IMAGE_folder, IMAGE_LIST_FILE_2, detectimg);

	IplImage *image2 = cvLoadImage(tempname, 0);
	IplImage *image5 = cvLoadImage(tempname, 1);
	if (NULL == image2)
	{
		etx->SetSel(-1, -1);
		etx->ReplaceSel("Cannot find the detection image number!\r\n");

		return -1;
	}
	cvReleaseImage(&image1);

	int w = image2->width, h = image2->height;
	int scale_w = 20, scale_h = 20;
	int max_scale_w = 150, max_scale_h = 150;
	int scale_step = 5, location_step = 5;


	for (scale_w; scale_w < max_scale_w; scale_w += scale_step, scale_h += scale_step) {
		int max_x = w - scale_w, max_y = h - scale_h;
		for (int x = 0; x < max_x; x += location_step)
			for (int y = 0; y < max_y; y += location_step)
			{
				//capture the image region in the searching bounding box
				//Mat db_region_img (db_gray_img, Rect(x, y, scale_w, scale_h)); 
				cvSetImageROI(image2, cvRect(x, y, scale_w, scale_h));
				IplImage *image3 = cvCreateImage(cvGetSize(image2), image2->depth, image2->nChannels);
				cvCopy(image2, image3, NULL);
				cvResetImageROI(image2);
				cvCalcHist(&image3, Histogram2, 0, 0);
				cvNormalizeHist(Histogram2, 1);
				cvReleaseImage(&image3);
				// Apply the Bhattacharyya distance comparison method
				double tempScore = compareImgs(Histogram1, Histogram2);

				//store the top k(k=score_size) match bounding box and score
				for (int k = 0; k < score_size; k++) {
					if (tempScore < score[k]) {
						for (int k1 = score_size - 1; k1 > k; k1--) {
							score[k1] = score[k1 - 1];
							start_x[k1] = start_x[k1 - 1];
							start_y[k1] = start_y[k1 - 1];
							end_x[k1] = end_x[k1 - 1];
							end_y[k1] = end_y[k1 - 1];
						}
						score[k] = tempScore;
						start_x[k] = x;
						start_y[k] = y;
						end_x[k] = x + scale_w;
						end_y[k] = y + scale_h;
						break;
					}
				}
			}
	}

	// hough circles 
	vector<Vec3f> circles;
	Mat grayImage;
	Mat dect_mat = cvarrToMat(image5, true);
	cvtColor(dect_mat, grayImage, COLOR_BGR2GRAY);
	GaussianBlur(grayImage, grayImage, Size(9, 9), 0, 0);
	HoughCircles(grayImage, circles, CV_HOUGH_GRADIENT, 1, 50, 40, 35, 15, 130);
	std::vector<Vec3f>::const_iterator it = circles.begin();
	for (int iii = 8; iii < score_size; iii++) {
		score[iii] = DBL_MAX;
	}

	// select two candidates
	while (it != circles.end())
	{
		Vec3f circle = *it;
		int r = cvRound(circle[2]);
		int top = cvRound(circle[1] - r);
		int left = cvRound(circle[0] - r);
		if (left < 0 || top < 0 || left + 2 * r >= image2->width || top + 2 * r >= image2->height) {
			++it;
			continue;
		}

		cvSetImageROI(image2, cvRect(left, top, r * 2, r * 2));
		IplImage *image3 = cvCreateImage(cvGetSize(image2), image2->depth, image2->nChannels);
		cvCopy(image2, image3, NULL);
		cvResetImageROI(image2);
		cvCalcHist(&image3, Histogram2, 0, 0);
		cvNormalizeHist(Histogram2, 1);
		cvReleaseImage(&image3);
		// Apply the Bhattacharyya distance comparison method
		double tempScore = compareImgs(Histogram1, Histogram2);

		for (int k = 8; k < score_size; k++) {
			if (tempScore < score[k]) {
				for (int k1 = score_size - 1; k1 > k; k1--) {
					score[k1] = score[k1 - 1];
					start_x[k1] = start_x[k1 - 1];
					start_y[k1] = start_y[k1 - 1];
					end_x[k1] = end_x[k1 - 1];
					end_y[k1] = end_y[k1 - 1];
				}
				score[k] = tempScore;
				start_x[k] = left;
				start_y[k] = top;
				end_x[k] = left + 2 * r;
				end_y[k] = top + 2 * r;
				break;
			}
		}
		++it;
	}

	for (int k = 0; k < score_size; k++) {
		CvPoint start = cvPoint(start_x[k], start_y[k]);
		CvPoint end = cvPoint(end_x[k], end_y[k]);
		cvRectangle(image5, start, end, cvScalar(255, 0, 0));

	}

	const int gt_start_x[10] = { 266,220,200,238,350,26,204,128,33,380 };
	const int gt_start_y[10] = { 146,248,83,120,80,10,347,258,196,207 };
	const int gt_end_x[10] = { 353,380,324,314,391,78,248,156,75,404 };
	const int gt_end_y[10] = { 233,398,207,196,121,62,391,288,238,231 };

	CvPoint start = cvPoint(gt_start_x[detectimg - 1], gt_start_y[detectimg - 1]);
	CvPoint end = cvPoint(gt_end_x[detectimg - 1], gt_end_y[detectimg - 1]);
	cvRectangle(image5, start, end, cvScalar(0, 0, 255));
	int gt_area = (gt_end_x[detectimg - 1] - gt_start_x[detectimg - 1]) * (gt_end_y[detectimg - 1] - gt_start_y[detectimg - 1]);

	double best_IoU = 0;
	double accuracy = 0;
	for (int k = 0; k < score_size; k++) {
		int intersect_start_x = start_x[k] > gt_start_x[detectimg - 1] ? start_x[k] : gt_start_x[detectimg - 1];
		int intersect_start_y = start_y[k] > gt_start_y[detectimg - 1] ? start_y[k] : gt_start_y[detectimg - 1];
		int intersect_end_x = end_x[k] < gt_end_x[detectimg - 1] ? end_x[k] : gt_end_x[detectimg - 1];
		int intersect_end_y = end_y[k] < gt_end_y[detectimg - 1] ? end_y[k] : gt_end_y[detectimg - 1];

		int your_area = (end_x[k] - start_x[k]) * (end_y[k] - start_y[k]);
		int intersect_area = 0;
		if (intersect_end_x > intersect_start_x && intersect_end_y > intersect_start_y) {
			intersect_area = (intersect_end_x - intersect_start_x) * (intersect_end_y - intersect_start_y);
		}
		int union_area = gt_area + your_area - intersect_area;
		double IoU = (double)intersect_area / union_area;
		if (IoU > best_IoU) {
			best_IoU = IoU;
		}

	}
	if (best_IoU > 0.1)
		accuracy = 1;
	if (found2 == 0)
	{
		aveiou[countnum2 - 1] = best_IoU;
		aveacc[countnum2 - 1] = accuracy;
	}
	double iou = 0, acc = 0;
	for (int i = 0; i < countnum2; i++)
	{
		iou = iou + aveiou[i];
		acc = acc + aveacc[i];
	}
	iou = iou / countnum2;
	acc = acc / countnum2;

	CString str;
	str.Format("The best IoU in the top 10 detection of this image is %f\r\n", best_IoU);
	etx->SetSel(-1, -1);
	etx->ReplaceSel(str);
	str.Format("The average best IoU so far is %f\r\n", iou);
	etx->SetSel(-1, -1);
	etx->ReplaceSel(str);
	if (accuracy == 1)
		str = "This image is a correct detection\r\n";
	else
		str = "This image is not a correct detection\r\n";
	etx->SetSel(-1, -1);
	etx->ReplaceSel(str);
	str.Format("The accuracy so far is %f\r\n", acc);
	etx->SetSel(-1, -1);
	etx->ReplaceSel(str);

	DrawPicToHDC(image5, IDC_STATIC);
	char dirpath[filename_len];
	sprintf_s(dirpath, filename_len, "%s\\detection_results", IMAGE_folder);
	if (_access(dirpath, 0) == -1)
		_mkdir(dirpath);
	sprintf_s(tempname, filename_len, "%s\\detection_results\\%d.jpg", IMAGE_folder, detectimg);
	cvSaveImage(tempname, image5);
	cvReleaseImage(&image2);
	cvReleaseImage(&image5);

	return 0;
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{

}
BOOL IsDirExist(const CString & csDir)
{
	DWORD dwAttrib = GetFileAttributes(csDir);
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	CString c;
	GetDlgItemText(IDC_EDIT2, c);
	strcpy(IMAGE_folder, c.GetBuffer());
	if (!IsDirExist(IMAGE_folder)) {
		AfxMessageBox("The directory does not exist.");
		return;
	}
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
		imageretrieval();
	else
		objectdetection();
}
