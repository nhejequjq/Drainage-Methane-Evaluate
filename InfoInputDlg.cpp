// InfoInputDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "Drainage Methane EvaluateDlg.h"
#include "InfoInputDlg.h"
#include "FactorAssessResult.h"	//���������


//�����������Ի���ȫ��ָ�� pMainViewDlg
extern CDrainageMethaneEvaluateDlg * pMainViewDlg;

// InfoInputDlg �Ի���

IMPLEMENT_DYNAMIC(InfoInputDlg, CDialog)

InfoInputDlg::InfoInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InfoInputDlg::IDD, pParent)
	, strPerson(_T(""))
	, strCompany(_T(""))
	, strCoalseam(_T(""))
{

}

InfoInputDlg::~InfoInputDlg()
{
}

void InfoInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIME, m_DateTime);
	DDX_Text(pDX, IDC_EDIT_COMPANY, strCompany);
	DDV_MaxChars(pDX, strCompany, 50);
	DDX_Text(pDX, IDC_EDIT_COALSEAM, strCoalseam);
	DDV_MaxChars(pDX, strCoalseam, 50);
	DDX_Text(pDX, IDC_EDIT_PERSON, strPerson);
	DDV_MaxChars(pDX, strPerson, 30);
}


BEGIN_MESSAGE_MAP(InfoInputDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &InfoInputDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDB_INPUT, &InfoInputDlg::OnBnClickedInput)
//	ON_EN_CHANGE(IDC_EDIT_PERSON, &InfoInputDlg::OnEnChangeEditPerson)
ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME, &InfoInputDlg::OnDtnDatetimechangeTime)
ON_EN_CHANGE(IDC_EDIT_COMPANY, &InfoInputDlg::OnEnChangeEditCompany)
END_MESSAGE_MAP()


// InfoInputDlg ��Ϣ�������




void InfoInputDlg::OnBnClickedCancel()
{
	OnCancel();
}

void InfoInputDlg::OnBnClickedInput()
{
	UpdateData(TRUE);
	extern CFactorAssessResult m_G_FactorAssessResult;	//����ȫ������
	
	if(strCompany != _T("") && strCoalseam != _T("") && strPerson != _T(""))
	{
		MessageBox(_T("Information has been recorded!"),_T("Tips"),MB_OK);
		CTime time;  
		m_DateTime.GetTime(time);  
		//��¼�����Ϣ����������Ի������
		pMainViewDlg->time = time;
		pMainViewDlg->strCompany = strCompany;
		pMainViewDlg->strCoalseam = strCoalseam;
		pMainViewDlg->strPerson = strPerson;
		OnOK();
		m_G_FactorAssessResult.Isdone_Infoinput = true;	//��Ϣ��¼��
	}
	else
	{
		MessageBox(_T("Please complete the above information!"),_T("Tips"),MB_OK);
	}

	UpdateData(FALSE);
}


void InfoInputDlg::OnDtnDatetimechangeTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void InfoInputDlg::OnEnChangeEditCompany()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
