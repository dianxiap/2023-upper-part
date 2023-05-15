#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class warrior
{
protected:
    int id;
    int lifeValue;//ʿ������ֵ
    string name;
public:
    static string weaponNames[3];
    warrior() :id(-1), lifeValue(0), name("") {}
    warrior(int theId, int theLifeValue, string theName) :id(theId), lifeValue(theLifeValue), name(theName) {}
    ~warrior() {}
    int getId() { return id; }
    string* getWeaponNames() { return weaponNames; }
    virtual void print(const int times, const string campName, const int certainWarriorCounts) {};//���麯��
};
string warrior::weaponNames[3] = { "sword", "bomb", "arrow" };
class dragon : public warrior
{
private:
    float morale;//ʿ������
public:
    dragon(int theId, int theLifeValue, int headquarterLifeValue) :warrior(theId, theLifeValue, "dragon")
    {
        morale = (float)headquarterLifeValue / theLifeValue;
    }
    ~dragon() {}
    float getMorale() { return morale; }
    string getWeaponName()
    {
        int index = this->getId() % 3;
        return this->getWeaponNames()[index];
    }
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
        cout << "It has a " << this->getWeaponName() << ",and it's morale is " << setprecision(2) << fixed << this->getMorale() << endl;
    }
};
class ninja : public warrior
{
private:
public:
    ninja(int theId, int theLifeValue) : warrior(theId, theLifeValue, "ninja") {}
    ~ninja() {}
    string getFirstWeaponName()
    {
        int index = this->getId() % 3;
        return this->getWeaponNames()[index];
    }
    string getSecondWeaponName()
    {
        int index = (this->getId() + 1) % 3;
        return this->getWeaponNames()[index];
    }
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
        cout << "It has a " << this->getFirstWeaponName() << " and a " << this->getSecondWeaponName() << endl;
    }
};
class iceman : public warrior
{

public:
    iceman(int theId, int theLifeValue) : warrior(theId, theLifeValue, "iceman") {}
    ~iceman() {}
    string getWeaponName()
    {
        int index = this->getId() % 3;
        return this->getWeaponNames()[index];
    }
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
        cout << "It has a " << this->getWeaponName() << endl;
    }
};

class lion : public warrior
{
private:
    int loyalty;
public:
    lion(int theId, int theLifeValue, int headquarterLifeValue) : warrior(theId, theLifeValue, "lion")
    {
        loyalty = headquarterLifeValue;
    }
    ~lion() {}
    int getLoyalty() { return loyalty; }
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
        cout << "It's loyalty is " << this->getLoyalty() << endl;
    }
};

class wolf : public warrior
{
public:
    wolf(int theId, int theLifeValue) : warrior(theId, theLifeValue, "wolf") {}
    ~wolf() {}
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
    }
};
class militarycamp
{
private:
    string name;
    int lifeValue;//��������ֵ
    int counts;//ʿ������
    //  int ptrsize;
    //  warrior* ptr;//ָ��̬�������ʿ������
    int currentPosition;//��¼����սʿ���ĵ�ǰλ��
    int minWarriorValue;//�����սʿ�е���С����ֵ  
    int warriorValues[5];//��¼ÿ��սʿ����ֵ������
    string warriorNames[5];//��¼ÿ��սʿ���ֵ�����
    int warriorCounts[5];//��¼ÿ��սʿ����������
public:
    static string priorNames[5];//��¼սʿ���ֵ�����
    static int times;//����սʿ�Ĵ���
    bool hadStop;//�Ƿ�ֹͣ����
    militarycamp(const int theLifeValue, string theName, const int theWarriorValue[],
        const int theWarriorOrder[]);
    ~militarycamp()
    {
        /*
                if(ptr)
                {
                    delete[] ptr;
                }
        */
    }
    void push_back(warrior* w);
    void warriorManufacture();//������ʿ
};
string militarycamp::priorNames[5] = { "dragon", "ninja", "iceman" ,"lion" ,"wolf" };
int militarycamp::times = 0;
militarycamp::militarycamp(const int theLifeValue, string theName, const int theWarriorValue[],
    const int theWarriorOrder[]) :hadStop(false), currentPosition(0), counts(0), lifeValue(theLifeValue), name(theName)//,ptr(NULL),ptrsize(0)
{
    for (int i = 0; i < 5; i++)
    {
        warriorCounts[i] = 0;
        warriorNames[i] = priorNames[theWarriorOrder[i]];//�ɸ�����˳���ԭʼսʿ���ֵ����飬�õ����ܲ�սʿ���ֵ�����
        warriorValues[i] = theWarriorValue[theWarriorOrder[i]];//�ɸ�����˳���ԭʼսʿ���ֵ����飬�õ����ܲ�սʿ����ֵ������
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
������ʿ
*/
void militarycamp::warriorManufacture()
{
    //����ֵС����Сսʿ����ֵ��ֹͣ��������ӡ����
    if (lifeValue < minWarriorValue)
    {
        cout << setfill('0') << setw(3) << times << ' ' << name << " headquarter stops making warriors" << endl;
        hadStop = true;
    }
    else
    {
        //��������жϾ�ɸѡ������һ���ܳ���
        //�ӵ�ǰposition��ʼ���ӣ���ĳ��λ�ó�����ֹͣ
        while (true)
        {
            if (lifeValue >= warriorValues[currentPosition])
            {
                counts++;
                warriorCounts[currentPosition]++;
                lifeValue -= warriorValues[currentPosition];
                if (warriorNames[currentPosition] == "dragon")
                {
                    dragon theDragon(counts, warriorValues[currentPosition], lifeValue);
                    //                  push_back(&theDragon);
                    theDragon.print(times, name, warriorCounts[currentPosition]);
                }
                else if (warriorNames[currentPosition] == "ninja")
                {
                    ninja theNinja(counts, warriorValues[currentPosition]);
                    //                  push_back(&theNinja);
                    theNinja.print(times, name, warriorCounts[currentPosition]);
                }
                else if (warriorNames[currentPosition] == "iceman")
                {
                    iceman theIceman(counts, warriorValues[currentPosition]);
                    //                  push_back(&theIceman);
                    theIceman.print(times, name, warriorCounts[currentPosition]);
                }
                else if (warriorNames[currentPosition] == "lion")
                {
                    lion theLion(counts, warriorValues[currentPosition], lifeValue);
                    //                  push_back(&theLion);
                    theLion.print(times, name, warriorCounts[currentPosition]);
                }
                else if (warriorNames[currentPosition] == "wolf")
                {
                    wolf theWolf(counts, warriorValues[currentPosition]);
                    //                  push_back(&theWolf);
                    theWolf.print(times, name, warriorCounts[currentPosition]);
                }

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
/*
//���ϴ˲��ַ����ڴ�й©���⣬��δ���
void militarycamp::push_back(warrior* w)//������β�����һ��Ԫ��
{
    if (ptr)
    {
        warrior* tmpPtr = new warrior[ptrsize+1];//���·���ռ�
        memcpy(tmpPtr, ptr, sizeof(warrior)*(ptrsize));
        delete[] ptr;
        ptr = tmpPtr;
    }
    else//���鱾�����ǿյ�
    {
        ptr = new warrior[1];
    }

    ptr[ptrsize++] = *w;//�����µ�����Ԫ��

}
*/
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
        militarycamp redOne = militarycamp(headquartersValue, "red", priorValue, redOrder);
        militarycamp blueOne = militarycamp(headquartersValue, "blue", priorValue, blueOrder);
        militarycamp::times = 0;//�ɱ���������
        while (!redOne.hadStop || !blueOne.hadStop)
        {
            if (!redOne.hadStop)
            {
                redOne.warriorManufacture();
            }
            if (!blueOne.hadStop)
            {
                blueOne.warriorManufacture();
            }
            militarycamp::times++;
        }
    }
    return 0;
}