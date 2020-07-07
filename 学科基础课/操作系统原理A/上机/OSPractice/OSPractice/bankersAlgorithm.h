#pragma once

#include <iostream>
using namespace std;
const int processesNumbers = 5;  //��������
const int resourcesTypes = 3;    //��Դ����

int Available[resourcesTypes] = {2, 3, 3};
int Max[processesNumbers][resourcesTypes] = {
    {5, 5, 9}, {5, 3, 6}, {3, 0, 8}, {4, 2, 5}, {4, 2, 4}};
int Allocation[processesNumbers][resourcesTypes] = {
    {2, 1, 2}, {4, 0, 2}, {3, 0, 5}, {2, 0, 4}, {3, 1, 4}};
int Need[processesNumbers + 1][resourcesTypes] = {
    {3, 4, 7}, {1, 3, 4}, {0, 0, 3}, {2, 2, 1}, {1, 1, 0}};
int Request[resourcesTypes] = {0, 0, 0};

void showStatus()  //��ʾϵͳ��״
{
    cout << endl << "Available:";
    for (int j = 0; j < resourcesTypes; j++) cout << Available[j] << " ";
    cout << endl;
    for (int i = 1; i <= 5; i++) cout << "     process " << i;

    cout << endl << "Max    ";
    for (int i = 1; i <= processesNumbers; i++) {
        for (int j = 0; j < resourcesTypes; j++) cout << Max[i - 1][j] << " ";
        cout << "        ";
    }

    cout << endl << "Allo   ";
    for (int i = 1; i <= processesNumbers; i++) {
        for (int j = 0; j < resourcesTypes; j++)
            cout << Allocation[i - 1][j] << " ";
        cout << "        ";
    }

    cout << endl << "Need   ";
    for (int i = 1; i <= processesNumbers; i++) {
        for (int j = 0; j < resourcesTypes; j++) cout << Need[i - 1][j] << " ";
        cout << "        ";
    }
    cout << endl;
}

//Ԥ�ȼ�������Ƿ�Ϸ�
bool beforCheck(int i) {
    for (int k = 0; k < resourcesTypes; k++) {
        if (Request[k] > Need[i][k]) {
            cout << "request quantity is greater than demand quantity! "
                 << endl;
            return false;
        }
        if (Request[k] > Available[k]) {
            cout << "request quantity is greater than available quantity! "
                 << endl;
            return false;
        }
    }
    return true;
}

//����������ʱ������ϵͳ������
void change(int i) {
    for (int j = 0; j < resourcesTypes; j++) {
        Available[j]     = Available[j] - Request[j];
        Allocation[i][j] = Allocation[i][j] + Request[j];
        Need[i][j]       = Need[i][j] - Request[j];
    }
}

//��������ʱ���ж��Ƿ��ʹϵͳ�������������������ǰ�İ�ȫ����
int check() {
    int Finish[processesNumbers] = {0};
    // WorkΪϵͳ��ǰ��Դ����ľ���
    int Work[resourcesTypes];
    // Result��¼��ȫ����
    int Result[processesNumbers] = {0};
    // sumΪϵͳ���Ѿ���ȫִ�в��ͷ���Դ�Ľ�����
    int sum = 0;
    //��ʼ��Work
    for (int i = 0; i < resourcesTypes; i++) Work[i] = Available[i];

    while (true) {
        // isSatisfied �ж�ϵͳ��ǰ��Դ���ܷ�����ĳ���̻���Ҫ����Դ��
        // isSafeExcu  �ж���ǰϵͳ�Ƿ��н����ܰ�ȫִ�в��ͷ���Դ
        bool isSatisfied, isSafeExcu = 0;

        for (int i = 0; i < processesNumbers; i++) {
            isSatisfied = 1;
            if (Finish[i] == 0) {
                for (int j = 0; j < resourcesTypes; j++)
                    if (Need[i][j] > Work[j]) isSatisfied = 0;
                //��ĳ���̻���Ҫ����Դ�ܰ�ȫ�õ�
                if (isSatisfied) {
                    isSafeExcu = 1;
                    //����ִ����ϣ��ͷŸý��̵õ�����Դ
                    for (int j = 0; j < resourcesTypes; j++)
                        Work[j] = Work[j] + Allocation[i][j];
                    Finish[i] = 1;  //״̬�����¼��ǰ������ִ������ͷ�
                    Result[sum] = i + 1;  //�ڰ�ȫ�����м�¼���̺�
                    sum++;                //��ɵĽ���������1
                }
            }
        }
        //�����еĽ��̶���ȫִ����ϣ���ϵͳ�ǰ�ȫ��
        if (sum == processesNumbers) {
            cout << "the security sequence of the current system is:";
            for (int i = 0; i < processesNumbers; i++) cout << Result[i] << " ";
            cout << endl;
            cout << endl;
            return 0;
        }

        //������ִ������ʣ��Ľ����޷�����㹻����Դ����˵��ϵͳ�ǲ���ȫ��
        if (!isSafeExcu) {
            return 1;
        }
    }
}

void restore(int i) {  //�����󲻱�����ʱ���ָ�ϵͳ������
    cout << "The request will cause the system to deadlock and refuse to "
            "execute!"
         << endl;
    for (int j = 0; j < resourcesTypes; j++) {
        Available[j] = Available[j] + Request[j];
        Allocation[i][j] = Allocation[i][j] - Request[j];
        Need[i][j] = Need[i][j] + Request[j];
    }
}

int run(int flag) {
    int i = 0;
    showStatus();
    if (flag == 1) {
        cout << "input the process number to apply for resources:";
        cin >> i;
        cout << "input the resources numbers of process" << i
             << " need to requeste" << endl;
        i--;
        cout << "resources A,B,C:";
        cin >> Request[0] >> Request[1] >> Request[2];
        cout << endl;
        if (beforCheck(i)) {
            change(i);
            if (check()) {
                restore(i);
                showStatus();
            } else
                showStatus();
        }

        cout << "continue?, 1 for yes��0 for no:";
        cin >> flag;
    }
    return flag;
}

void bankersAlgorithm() {
    int flag = 1;
    while (flag == 1) flag = run(flag);
}
