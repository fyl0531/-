#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;

struct point
{//��ṹ 
	double x;//x���� 
	double y;//y���� 
};

double Distance(point a,point b)
{//������������ 
	double s;
	s=sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	return s;
}
bool cmp1(point a,point b)
{//��y���������� 
	return a.y<b.y;
}
bool cmp2(point a,point b)
{//��x���������� 
	return a.x<b.x;
}

double ClosestPoint(point s[],int low,int high,point rec[])
{
	double d1,d2,d3,d;
	int mid,i,j,index;
	double x1,y1,x2,y2;//��¼������λ��
	point P[high-low+1],temp1[2],temp2[2],temp3[2];//temp1��¼��ߵ�������,temp2��¼�ұߣ�temp3��¼�м� 
	if(high-low==1)
	{//ֻ���������ʱ�� 
		rec[0].x=s[low].x;
		rec[0].y=s[low].y;
		rec[1].x=s[high].x;
		rec[1].y=s[high].y;
		return Distance(s[low],s[high]); 
	} 
	if(high-low==2)
	{//�����������ʱ��
		//�������㣬�ҳ�������������� 
		d1=Distance(s[low],s[low+1]);
		d2=Distance(s[low+1],s[high]);
		d3=Distance(s[low],s[high]);
		if((d1<d2)&&(d1<d3))
		{
			rec[0].x=s[low].x;
			rec[0].y=s[low].y;
			rec[1].x=s[low+1].x;
			rec[1].y=s[low+1].y;
			return d1;
		} 
		else if (d2<d3)
		{
		 	rec[0].x=s[low+1].x;
			rec[0].y=s[low+1].y;
			rec[1].x=s[high].x;
			rec[1].y=s[high].y;	
			return d2;
		}
		else
		{
		 	rec[0].x=s[low].x;
			rec[0].y=s[low].y;
			rec[1].x=s[high].x;
			rec[1].y=s[high].y;
			return d3;
		}	
	}
	//����������ϵĲ��õݹ�İ취
	
	mid=(low+high)/2;
	d1=ClosestPoint(s,low,mid,rec);//��ݹ� 
	temp1[0]=rec[0];
	temp1[1]=rec[1];
	d2=ClosestPoint(s,mid+1,high,rec);//�ҵݹ� 
	temp2[0]=rec[0];
	temp2[1]=rec[1];
	if(d1<d2)
	{//�Ƚ����ҵݹ����õ������Ծ��� 
		d=d1;
		rec[0]=temp1[0];
		rec[1]=temp1[1];
	 } 
	else
	{
		d=d2;
		rec[0]=temp2[0];
		rec[1]=temp2[1];
	}
	
	index=0;
	for(i=mid;(i>=low)&&((s[mid].x-s[i].x)<d);i--)
	{//��¼[mid-d,mid]����ĵ� 
		P[index++]=s[i];
	}
	for(i=mid+1;(i<=high)&&((s[i].x-s[mid].x)<d);i++)
	{//��¼[mid,mid+d]����ĵ� 
		P[index++]=s[i];
	}
	sort(P,P+index,cmp1);//�Ը�����������Ԫ�ؽ�������
	for(i=0;i<index;i++)
	{//�ҳ�[mid-d,mid+d]�е�������
		for(j=i+1;j<i+7&&j<index;j++)
		{
			if((P[j].y-P[i].y)>=d)
			{
				break;
			}
			else
			{
				d3=Distance(P[i],P[j]);
				if(d3<d)
				{
					rec[0].x=P[i].x;
					rec[0].y=P[i].y;
                    rec[1].x=P[j].x;
					rec[1].y=P[j].y;	
					d=d3;
				}
			}
		 } 
		 //return d;	
	 }
	 return d;
}


int main()
{
	point p[100];
	int n;
	double minDist;
	cout<<"�����ĸ�����"<<endl;
	cin>>n;
	cout<<"���е�����꣺"<<endl;
	for(int i=0;i<n;i++)
	{
		p[i].x=rand()%100;
		p[i].y=rand()%100;	
		cout<<"("<<p[i].x<<","<<p[i].y<<")"<<"  "; 
	 } 
	sort(p,p+n,cmp2);//�����е���x�������� 
	
	cout<<endl<<"��x������������е�����꣺"<<endl;
	for(int i=0;i<n;i++)
	{	
		cout<<"("<<p[i].x<<","<<p[i].y<<")"<<"  "; 
	 } 
	point index[2];
	minDist=ClosestPoint(p,0,n-1,index);

	cout<<endl<<"��С������Ϊ��("<<index[0].x<<","<<index[0].y<<"),("<<index[1].x<<","<<index[1].y<<")"<<endl;
    cout<<"��С����Ϊ��"<<minDist<<endl;    
    system("pause");
    return 0;
}






















