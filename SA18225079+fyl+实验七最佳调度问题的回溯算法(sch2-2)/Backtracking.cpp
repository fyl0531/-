#include <iostream>
#include <cstdlib>
#include <stdio.h>
//#include <ctime>
#define MAX 99999999		//�������ֵ 
#define MAXSIZE 100		//�������������
using namespace std;

//��������ȫ�ֱ���
int N,K;	//N-��������K-������
int taskTime[MAXSIZE];	//�����Ӧ��ʱ�� 
int bestTime=MAX;      //���Ž⣺�����ȫ���������ʱ�䣬��ʼ��Ϊ�����
int scheduleNow[MAXSIZE];   //��ǰ���ŵ��ȷ�����ֵΪ0��ʾ��δ����
int best_N_to_K[MAXSIZE];   //���Ž�ĵ��ȷ�����best_N_to_K[i]=m,��ʾ��i+1
							//��i��0��ʼ�㣩����������m̨����

//������ʾ������N��K��ֵ
void Display()
{
    cout<<"**********��ѵ�������Ļ����㷨***********"<<endl;
    cout<<"��������ȵ�������N= ";
    cin>>N;
    cout<<endl<<"������ɲ��й����Ļ�����K= ";
    cin>>K;
}

//��������������i��Ҫ��ʱ��
void setTaskTime(int taskTime[],int N)
{
	
	//srand((unsigned)time(NULL));
	for(int i=0;i<N;i++)
	{
		taskTime[i]=rand()%20+1;
	}
 } 

void printTaskTime(int taskTime[],int N)
{
    cout<<"1��ԭʼ����ʱ���Ӧ�����£�\n"<<"<����,ʱ��>"<<endl<<"-------------------"<<endl;
    for(int i=0;i<N;i++)
        cout<<"<Task "<<i+1<<" , "<<"ʱ�� "<<taskTime[i]<<" hours>"<<endl;
}


//������Ҷ�ڵ�ʱ������Ҷ�ڵ���н���������ʱ��
int ScheduleTime()
{
    int k[MAXSIZE]={0};    //���ڼ�¼ÿ��������Ӧ��������ʱ��,�����±�
                           //��1��ʼ�㣬��ΪscheduleNow[i]=0ʱ��ʾδ����
    for(int i=0;i<N;i++)
    {//����i������ʱ��ӵ��ڡ�scheduleNow[i]����������ȥ
        k[scheduleNow[i]]+=taskTime[i];
    }

    int max=k[1];      
    for(int i=1;i<=K;i++)
    {//���й��������л����й���ʱ������Ǹ�ʱ�����Ҷ�ӽڵ���н�ʱ��
        if(k[i]>max)max=k[i];
    }
    return max;
}

//���������ݷ�������֦��
void BackTrack(int deep)
{
    if (deep==N)
    {
        int temp=ScheduleTime();    //��ʱ���Ҷ�ڵ�Ŀ��н��ֵ
        if(temp<bestTime)           //���н��뵱ǰ���Ž���бȽ�
        {
            bestTime=temp;
            for(int i=0;i<N;i++)
            {
                best_N_to_K[i]=scheduleNow[i];
            }
        }
        return;
    }

    for(int i=1;i<=K;i++)
    {
        scheduleNow[deep]=i;         //������deep�������ǰ����
        if(ScheduleTime()<bestTime)  //��֦��Լ������
            BackTrack(deep+1); 
        scheduleNow[deep]=0;         //���ݣ���������������ǰ������i=0��ʾΪ����
    }
}

//��ӡ���տ��н���
void printSchedulePlan()
{
    //���ÿ�������ӡ��ѵ�������
    cout<<endl<<"2�����ÿ���������ѵ������У�\n";
    cout<<"Best Scheduling Sequence(����i��Ӧ����Ļ�����) :\n";
    for(int i=0;i<N;i++)
    {
        cout<<best_N_to_K[i]<<"  ";
    }
	cout<<endl<<"��ǰ�����������ʱ��:"<<bestTime<<endl;
    //���ÿ̨������ӡ���Ӧ�����Щ����
    cout<<endl<<endl<<"3��ÿ̨������Ӧ��ɵ��������£� \n";
    for(int i=1;i<=K;i++)
    {
        bool hasTask=false;    //hasTask���ڼ�¼�����Ƿ��з��䣬��һ
                               //������û���䣬����ʾ"δ��������
        cout<<"����"<<i<<"���� �� ";
        for(int j=0;j<N;j++)
        {
            if(i==best_N_to_K[j])
            {
                cout<<"Task"<<j+1<<" ";
                hasTask=true;
            }
        }
        if(hasTask==false)cout<<"δ��������";
        cout<<endl;
    }
    
}

int main()
{
	
    Display();                   //������ʾ������N��K
    setTaskTime(taskTime,N);     //��������������i��Ҫ��ʱ��
    printTaskTime(taskTime,N);   //��ӡԭʼ����ʱ���Ӧ��
    BackTrack(0);                //���������ݷ�������֦��
    printSchedulePlan();         //��ӡ���տ��н���
	
    system("pause");
    return 0;
}



