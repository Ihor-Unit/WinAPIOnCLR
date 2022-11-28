#include "KyrsovaDlg.h"
#include "class_kursova.h"
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    QueuingSystemOnCLRNETFrameworks::KyrsovaDlg form;
    Application::Run(% form);
}



//PRESETTINGS
int GenElemQ[6]{};
int GenAppl[3]{};
int N; //������� ��
int qsize = 4; //���̲� �Ѳ� ����
IOStream OutStream;
int transmitter; short int transproir; // ������ ������ � ������ � ������ ���

//PHASE 1
int ph1pow = 3;
//PHASE 2
int ph2pow = 4;




int ChanceGen1 = 20;
int ChanceGen2 = 30;
int ChanceGen3 = 50;
int ChanceNotGen = 100 - (ChanceGen1 + ChanceGen2 + ChanceGen3);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//System::Void �����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
System::Void QueuingSystemOnCLRNETFrameworks::KyrsovaDlg::�����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    Application::Exit();
    return System::Void();
}

System::Void QueuingSystemOnCLRNETFrameworks::KyrsovaDlg::�����������ToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("������� �������� �������������� \n��������: ������� ��������� ����� �14 ������� ������\n\n\t\t\t\t\t    2022 �. (�)", "��� ��������", MessageBoxButtons::OK, MessageBoxIcon::Information);
    return System::Void();
}

System::Void QueuingSystemOnCLRNETFrameworks::KyrsovaDlg::FirstPriorBOX_TextChanged(System::Object^ sender, System::EventArgs^ e)
{

    return System::Void();
}

System::Void QueuingSystemOnCLRNETFrameworks::KyrsovaDlg::checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{

    return System::Void();
}
///////////////////////BUTTONS//////////////////////////
bool IsTouched[5];

System::Void QueuingSystemOnCLRNETFrameworks::KyrsovaDlg::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
    float time1 = 0.0;
    time1 = clock();
    textBox37->Text = Convert::ToString(0);

    textBox5->Text = Convert::ToString(0);
    textBox6->Text = Convert::ToString(0);
    textBox12->Text = Convert::ToString(0);
    textBox11->Text = Convert::ToString(0);
    textBox7->Text = Convert::ToString(0);
    textBox8->Text = Convert::ToString(0);

    for (int i = 0; i < 3; i++) {
        GenAppl[i] = 0;
    }
    FirstPriorBOX->Text = Convert::ToString(0);
    SecondPriorBOX->Text = Convert::ToString(0);
    textBox4->Text = Convert::ToString(0);

    for (int i = 0; i < 5; i++) {
        IsTouched[i] = false;
    }
    OutStream.GeneralAppl = 0;
    OutStream.NotServedAppl = 0;
    OutStream.ServedAppl = 0;
    OutStream.SetACO(0);
    OutStream.SetEfficient(0);
    OutStream.SetWorktime(0);

    N = Convert::ToInt32(textBox36->Text);

    ChanceGen1 = Convert::ToInt32(textBox1->Text);
    ChanceGen2 = Convert::ToInt32(textBox2->Text);
    ChanceGen3 = Convert::ToInt32(textBox9->Text);
    ChanceNotGen = Convert::ToInt32(textBox24->Text);
    //��������� ������
    ph1pow = Convert::ToInt32(textBox28->Text);
    ph1pow = Convert::ToInt32(textBox27->Text);

    ph2pow = Convert::ToInt32(textBox32->Text);
    ph2pow = Convert::ToInt32(textBox31->Text);
    ph2pow = Convert::ToInt32(textBox3->Text);

    //PHASE 1
    STQueue Ph1_Q1(qsize), Ph1_Q2(qsize), Ph1_Q3(qsize);
    Chanel Ph1_Ch1(ph1pow), Ph1_Ch2(ph1pow);
    //PHASE 2
    STQueue Ph2_Q1(qsize), Ph2_Q2(qsize), Ph2_Q3(qsize);
    Chanel Ph2_Ch1(ph2pow), Ph2_Ch2(ph2pow), Ph2_Ch3(ph2pow);


    ChanceNotGen = 100 - (ChanceGen1 + ChanceGen2 + ChanceGen3);
    textBox24->Text = Convert::ToString(ChanceNotGen);

    srand(time(NULL));
    for (int i = 1; i <= N; i++) {//�������� ����
        Generator gen;

        int GentedAppl = gen.MakeAppl(ChanceGen1, ChanceGen2, ChanceGen3, ChanceNotGen);

        int applnum = i; // ����� ������� ������

        //QS

        switch (GentedAppl) // ������ ���������� ������ �� ������
        {
        case 0:

            //����������
            break;
        case 1: // ���� ������ 1 ���������
            GenAppl[0]++;
            if (!Ph1_Q1.IsFull()) { // ���� ����� �� �����, �� �������� ������ � ����� �� �����������
                Ph1_Q1.Push(applnum, 1);
                GenElemQ[0]++;
                textBox5->Text = Convert::ToString(GenElemQ[0]);
            }
            else {//���������� ��������� ����
                OutStream.NotServedAppl++;
            }

            break;
        case 2: // ���� ������ 2 ���������
            GenAppl[1]++;
            if (!Ph1_Q2.IsFull()) { // ���� ����� �� �����, �� �������� ������ � ����� �� �����������
                Ph1_Q2.Push(applnum, 2);
                GenElemQ[1]++;
                textBox6->Text = Convert::ToString(GenElemQ[1]);
            }
            else {//���������� ��������� ����
                OutStream.NotServedAppl++;
            }
            break;
        case 3: // ���� ������ 3 ���������
            GenAppl[2]++;
            if (!Ph1_Q3.IsFull()) { // ���� ����� �� �����, �� �������� ������ � ����� �� �����������
                Ph1_Q3.Push(applnum, 3);
                GenElemQ[2]++;
                textBox7->Text = Convert::ToString(GenElemQ[2]);
            }
            else {//���������� ��������� ����
                OutStream.NotServedAppl++;
            }

            break;
        }

        //���� 1 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //����� 1///////////////
        if (!Ph1_Ch1.IsBusy()) { // ���� 1 ����� �� ��������, �� �������� ������ �� �����������
            Ph1_Ch1.ServeAppl(Ph1_Ch1, Ph1_Q1, Ph1_Q2, Ph1_Q3, transmitter, transproir);
        }
        else { //���� ��������, �� ��� �������� ����������
            Ph1_Ch1.TOOPP();
            IsTouched[0] = true;
        }
        //����� 2///////////////
        if (!Ph1_Ch2.IsBusy()) { // ���� 1 ����� �� ��������, �� �������� ������ �� �����������
            Ph1_Ch1.ServeAppl(Ph1_Ch2, Ph1_Q1, Ph1_Q2, Ph1_Q3, transmitter, transproir);
        }
        else { //���� ��������, �� ��� �������� ����������
            Ph1_Ch2.TOOPP();
            IsTouched[1] = true;
        }
        //���� 2 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (transmitter > 0) {
            if (transproir == 1) {
                if (!Ph2_Q1.IsFull()) {
                    Ph2_Q1.Push(transmitter, transproir);
                    GenElemQ[3]++;
                    textBox12->Text = Convert::ToString(GenElemQ[3]);
                }
                else { OutStream.NotServedAppl++; }
                transmitter = -1;
                transproir = -1;
            }
            else if (transproir == 2) {
                if (!Ph2_Q2.IsFull()) {
                    Ph2_Q2.Push(transmitter, transproir);
                    GenElemQ[4]++;
                    textBox11->Text = Convert::ToString(GenElemQ[4]);
                }
                else { OutStream.NotServedAppl++; }
                transmitter = -1;
                transproir = -1;
            }
            else if (transproir == 3) {
                if (!Ph2_Q3.IsFull()) {
                    Ph2_Q3.Push(transmitter, transproir);
                    GenElemQ[5]++;
                    textBox8->Text = Convert::ToString(GenElemQ[5]);
                }
                else { OutStream.NotServedAppl++; }
                transmitter = -1;
                transproir = -1;
            }
        }
        //����� 1 ///////////////
        if (!Ph2_Ch1.IsBusy()) { // ���� 1 ����� �� ��������, �� �������� ������ �� �����������
            if (Ph2_Ch1.GetAppl() > 0) {
                OutStream.ServedAppl++;
            }
            Ph2_Ch1.ServeAppl(Ph2_Ch1, Ph2_Q1, Ph2_Q2, Ph2_Q3, transmitter, transproir);
        }
        else { //���� ��������, �� ��� �������� ����������
            Ph2_Ch1.TOOPP();
            IsTouched[2] = true;
        }
        //����� 2///////////////
        if (!Ph2_Ch2.IsBusy()) { // ���� 1 ����� �� ��������, �� �������� ������ �� �����������
            if (Ph2_Ch2.GetAppl() > 0) {
                OutStream.ServedAppl++;
            }
            Ph2_Ch1.ServeAppl(Ph2_Ch2, Ph2_Q1, Ph2_Q2, Ph2_Q3, transmitter, transproir);
        }
        else { //���� ��������, �� ��� �������� ����������
            Ph2_Ch2.TOOPP();
            IsTouched[3] = true;
        }
        //����� 3///////////////
        if (!Ph2_Ch3.IsBusy()) { // ���� 1 ����� �� ��������, �� �������� ������ �� �����������
            if (Ph2_Ch3.GetAppl() > 0) {
                OutStream.ServedAppl++;
            }
            Ph2_Ch1.ServeAppl(Ph2_Ch3, Ph2_Q1, Ph2_Q2, Ph2_Q3, transmitter, transproir);
        }
        else { //���� ��������, �� ��� �������� ����������
            Ph2_Ch3.TOOPP();
            IsTouched[4] = true;
        }



        OutStream.GeneralAppl++;
        OutStream.WorkTimePP();
        OutStream.MathACO(Ph1_Ch1.GetGTOO(), Ph1_Ch2.GetGTOO(), Ph2_Ch1.GetGTOO(), Ph2_Ch2.GetGTOO(), Ph2_Ch3.GetGTOO());
        OutStream.MathEffivient();

        textBox17->Text = Convert::ToString(OutStream.GeneralAppl);
        textBox18->Text = Convert::ToString(OutStream.ServedAppl);
        textBox19->Text = Convert::ToString(OutStream.NotServedAppl);
        textBox20->Text = Convert::ToString(OutStream.GetEfficientSMO() * 100.0);
        textBox21->Text = Convert::ToString(OutStream.GetAverageCoefOccup() * 100.0);

        FirstPriorBOX->Text = Convert::ToString(GenAppl[0]);
        SecondPriorBOX->Text = Convert::ToString(GenAppl[1]);
        textBox4->Text = Convert::ToString(GenAppl[2]);

        checkBox12->Checked = IsTouched[0];
        checkBox2->Checked = IsTouched[1];
        checkBox8->Checked = IsTouched[2];
        checkBox7->Checked = IsTouched[3];
        checkBox1->Checked = IsTouched[4];
    }
    float time2 = clock();
    textBox37->Text = Convert::ToString((time2 - time1) / 1000);
    time1 = 0;
    time2 = 0;
    return System::Void();
}

System::Void QueuingSystemOnCLRNETFrameworks::KyrsovaDlg::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
    textBox37->Text = Convert::ToString(0);

    button2->Enabled = true;
    button4->Enabled = true;
    textBox36->Enabled = true;

    for (int i = 0; i < 6; i++) {
        GenElemQ[i] = 0;
    }
    textBox5->Text = Convert::ToString(0);
    textBox6->Text = Convert::ToString(0);
    textBox12->Text = Convert::ToString(0);
    textBox11->Text = Convert::ToString(0);
    textBox7->Text = Convert::ToString(0);
    textBox8->Text = Convert::ToString(0);


    for (int i = 0; i < 3; i++) {
        GenAppl[i] = 0;
    }
    FirstPriorBOX->Text = Convert::ToString(0);
    SecondPriorBOX->Text = Convert::ToString(0);
    textBox4->Text = Convert::ToString(0);

    for (int i = 0; i < 5; i++) {
        IsTouched[i] = false;
    }
    checkBox12->Checked = IsTouched[0];
    checkBox2->Checked = IsTouched[1];
    checkBox8->Checked = IsTouched[2];
    checkBox7->Checked = IsTouched[3];
    checkBox1->Checked = IsTouched[4];

    OutStream.GeneralAppl = 0;
    OutStream.NotServedAppl = 0;
    OutStream.ServedAppl = 0;
    OutStream.SetACO(0);
    OutStream.SetEfficient(0);
    OutStream.SetWorktime(0);

    textBox17->Text = Convert::ToString(OutStream.GeneralAppl);
    textBox18->Text = Convert::ToString(OutStream.ServedAppl);
    textBox19->Text = Convert::ToString(OutStream.NotServedAppl);
    textBox20->Text = Convert::ToString(OutStream.GetEfficientSMO() * 100.0);
    textBox21->Text = Convert::ToString(OutStream.GetAverageCoefOccup() * 100.0);
    //³��������� ����������� (%)
    textBox1->Text = Convert::ToString(ChanceGen1);
    textBox2->Text = Convert::ToString(ChanceGen2);
    textBox9->Text = Convert::ToString(ChanceGen3);
    textBox24->Text = Convert::ToString(ChanceNotGen);
    //��������� ������
    textBox28->Text = Convert::ToString(ph1pow);
    textBox27->Text = Convert::ToString(ph1pow);

    textBox32->Text = Convert::ToString(ph2pow);
    textBox31->Text = Convert::ToString(ph2pow);
    textBox3->Text = Convert::ToString(ph2pow);

    return System::Void();
}

System::Void QueuingSystemOnCLRNETFrameworks::KyrsovaDlg::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
    //PHASE 1
    int ph1pow = 3;
    //PHASE 2
    int ph2pow = 4;


    int ChanceGen1 = 20;
    int ChanceGen2 = 30;
    int ChanceGen3 = 50;
    int ChanceNotGen = 100 - (ChanceGen1 + ChanceGen2 + ChanceGen3);

    //³��������� ����������� (%)
    textBox1->Text = Convert::ToString(ChanceGen1);
    textBox2->Text = Convert::ToString(ChanceGen2);
    textBox9->Text = Convert::ToString(ChanceGen3);
    textBox24->Text = Convert::ToString(ChanceNotGen);
    //��������� ������
    ph1pow = Convert::ToInt32(textBox28->Text);
    ph1pow = Convert::ToInt32(textBox27->Text);

    ph2pow = Convert::ToInt32(textBox32->Text);
    ph2pow = Convert::ToInt32(textBox31->Text);
    ph2pow = Convert::ToInt32(textBox3->Text);

    return System::Void();
}
