#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class headquarters
{
private:
    static string priorNames[5];//记录战士名字的数组
    int allLifeValue;//部落所有生命值
    int count;//生产的战士数量
    int warriorCounts[5];//记录每种战士数量的数组
    string headquarterName;//总部的名字
    string warriorNames[5];//记录每种战士名字的数组
    int warriorValues[5];//记录每种战士生命值的数组 
    int currentPosition;//记录产生战士类别的当前位置
    int minWarriorValue;//计算出战士中的最小生命值
    void product(int time, int position);//第time次在position位置制造士兵
public:
    bool hadStop;//是否停止出兵
    static int time;//产生战士的次数
    headquarters(const int theallLifeValue, string theHeadquarterName, const int theWarriorValue[],
        const int order[]);
    //  ~headquarters() {};    
    void dispatchWarrior();//制造士兵
};
string headquarters::priorNames[5] = { "dragon", "ninja", "iceman" ,"lion" ,"wolf" };
int headquarters::time = 0;
/*
构造函数，相关初始化
*/
headquarters::headquarters(const int theAllLifeValue, string theHeadquarterName, const int theWarriorValue[],
    const int order[]) :hadStop(false), currentPosition(0), count(0), allLifeValue(theAllLifeValue), headquarterName(theHeadquarterName)
{
    for (int i = 0; i < 5; i++)
    {
        warriorCounts[i] = 0;
        warriorNames[i] = priorNames[order[i]];//由给定的顺序和原始战士名字的数组，得到该总部战士名字的数组
        warriorValues[i] = theWarriorValue[order[i]];//由给定的顺序和原始战士名字的数组，得到该总部战士生命值的数组
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
函数：生产战士
参数：time,给定战士出生的回合
    position,戈丁该战士在司令部出生战士中的位置
*/
void headquarters::product(int time, int position)
{
    count++;
    warriorCounts[position]++;//该种战士的总数加一
    //输出题目要求的语句
    cout << setfill('0') << setw(3) << time << " " << headquarterName << " " << warriorNames[position]
        << " " << count << " born with strength " << warriorValues[position] << "," << warriorCounts[position]
        << " " << warriorNames[position] << " in " << headquarterName << " headquarter" << endl;
    allLifeValue -= warriorValues[position];
}
/*
出兵
*/
void headquarters::dispatchWarrior()
{
    //生命值小于最小战士生命值，停止出兵，打印命令
    if (allLifeValue < minWarriorValue)
    {
        cout << setfill('0') << setw(3) << time << ' ' << headquarterName << " headquarter stops making warriors" << endl;
        hadStop = true;
    }
    else
    {
        //从上面的判断句筛选后，现在一定能出兵
        //从当前position开始增加，到某个位置出兵了停止
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
    const int redOrder[5] = { 2, 3, 4, 1, 0 };//红色总部的出兵顺序
    const int blueOrder[5] = { 3, 0, 1, 2, 4 };//蓝色总部的出兵顺序
    int n = 0;//测试数
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int priorValue[5], headquartersValue;
        cin >> headquartersValue; //获取总部生命值
        //获取每种战士的生命值
        for (int j = 0; j < 5; j++)
        {
            cin >> priorValue[j];
        }
        cout << "Case:" << i << endl;

        //初始化红军总部和蓝军总部
        headquarters redOne = headquarters(headquartersValue, "red", priorValue, redOrder);
        headquarters blueOne = headquarters(headquartersValue, "blue", priorValue, blueOrder);
        headquarters::time = 0;//派兵次数置零
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