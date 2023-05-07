#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class headquarters
{
private:
    static string priorNames[5];//��¼սʿ���ֵ�����
    int allLifeValue;//������������ֵ
    int count;//������սʿ����
    int warriorCounts[5];//��¼ÿ��սʿ����������
    string headquarterName;//�ܲ�������
    string warriorNames[5];//��¼ÿ��սʿ���ֵ�����
    int warriorValues[5];//��¼ÿ��սʿ����ֵ������ 
    int currentPosition;//��¼����սʿ���ĵ�ǰλ��
    int minWarriorValue;//�����սʿ�е���С����ֵ
    void product(int time, int position);//��time����positionλ������ʿ��
public:
    bool hadStop;//�Ƿ�ֹͣ����
    static int time;//����սʿ�Ĵ���
    headquarters(const int theallLifeValue, string theHeadquarterName, const int theWarriorValue[],
        const int order[]);
    //  ~headquarters() {};    
    void dispatchWarrior();//����ʿ��
};
string headquarters::priorNames[5] = { "dragon", "ninja", "iceman" ,"lion" ,"wolf" };
int headquarters::time = 0;
/*
���캯������س�ʼ��
*/
headquarters::headquarters(const int theAllLifeValue, string theHeadquarterName, const int theWarriorValue[],
    const int order[]) :hadStop(false), currentPosition(0), count(0), allLifeValue(theAllLifeValue), headquarterName(theHeadquarterName)
{
    for (int i = 0; i < 5; i++)
    {
        warriorCounts[i] = 0;
        warriorNames[i] = priorNames[order[i]];//�ɸ�����˳���ԭʼսʿ���ֵ����飬�õ����ܲ�սʿ���ֵ�����
        warriorValues[i] = theWarriorValue[order[i]];//�ɸ�����˳���ԭʼսʿ���ֵ����飬�õ����ܲ�սʿ����ֵ������
    }

    minWarriorValue = warriorValues[0];
    for (int i = 1; i < 5; i++)
    {
        if (warriorValues[i] < minWarriorValue)
        {
            minWarriorValue = warriorValues[i];
        }
    }
}
/*
����������սʿ
������time,����սʿ�����Ļغ�
    position,�궡��սʿ��˾�����սʿ�е�λ��
*/
void headquarters::product(int time, int position)
{
    count++;
    warriorCounts[position]++;//����սʿ��������һ
    //�����ĿҪ������
    cout << setfill('0') << setw(3) << time << " " << headquarterName << " " << warriorNames[position]
        << " " << count << " born with strength " << warriorValues[position] << "," << warriorCounts[position]
        << " " << warriorNames[position] << " in " << headquarterName << " headquarter" << endl;
    allLifeValue -= warriorValues[position];
}
/*
����
*/
void headquarters::dispatchWarrior()
{
    //����ֵС����Сսʿ����ֵ��ֹͣ��������ӡ����
    if (allLifeValue < minWarriorValue)
    {
        cout << setfill('0') << setw(3) << time << ' ' << headquarterName << " headquarter stops making warriors" << endl;
        hadStop = true;
    }
    else
    {
        //��������жϾ�ɸѡ������һ���ܳ���
        //�ӵ�ǰposition��ʼ���ӣ���ĳ��λ�ó�����ֹͣ
        while (true)
        {
            if (allLifeValue >= warriorValues[currentPosition])
            {
                product(time, currentPosition);
                currentPosition == 4 ? currentPosition = 0 : currentPosition++;
                break;
            }
            else
            {
                currentPosition == 4 ? currentPosition = 0 : currentPosition++;
            }
        }
    }
}
int main()
{
    const int redOrder[5] = { 2, 3, 4, 1, 0 };//��ɫ�ܲ��ĳ���˳��
    const int blueOrder[5] = { 3, 0, 1, 2, 4 };//��ɫ�ܲ��ĳ���˳��
    int n = 0;//������
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int priorValue[5], headquartersValue;
        cin >> headquartersValue; //��ȡ�ܲ�����ֵ
        //��ȡÿ��սʿ������ֵ
        for (int j = 0; j < 5; j++)
        {
            cin >> priorValue[j];
        }
        cout << "Case:" << i << endl;

        //��ʼ������ܲ��������ܲ�
        headquarters redOne = headquarters(headquartersValue, "red", priorValue, redOrder);
        headquarters blueOne = headquarters(headquartersValue, "blue", priorValue, blueOrder);
        headquarters::time = 0;//�ɱ���������
        while (!redOne.hadStop || !blueOne.hadStop)
        {
            if (!redOne.hadStop)
            {
                redOne.dispatchWarrior();
            }
            if (!blueOne.hadStop)
            {
                blueOne.dispatchWarrior();
            }
            headquarters::time++;
        }
    }
    return 0;
}