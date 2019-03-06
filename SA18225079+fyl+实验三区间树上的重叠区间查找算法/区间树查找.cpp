  /*
 *File name:���������� 
 *Author:Fei Yuling		Version:1.0		Date:2018.11.14 
 *Description:���������������в��Ҳ��� 
 */ 	
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
#define SIZE 15 
struct Node
{
	int low;//�Ͷ˵� 
	int high;//�߶˵� 
	int max;
	string color;//��ɫ 
	Node *pParent;//����� 
	Node *pLeft;//���� 
	Node *pRight;//�Һ��� 
};

class RBT
{
public:
	RBT();
	~RBT();
	void LeftRotate(Node* px);//����
	void RightRotate(Node* px);//����
	void Insert(Node* pz);//����
	void InsertFixUp(Node* pz);//�������
	void InorderTreeWalk( Node* px );//�������
	Node* GetRoot(){ return this->pT_root; }
	Node* GetNil(){ return this->pT_nil; }
	Node* IntervalSearch( Node* i );//���������� 
private:
	Node* pT_nil;
	Node* pT_root;
};

RBT::RBT()
{//����һ�������� 
	pT_nil = new Node; 
	pT_nil->color = "Black";//��ɫ��ΪBLACK 
	pT_nil->max = 0;
	pT_root = pT_nil;
}
RBT::~RBT()
{
	if( pT_nil != NULL )
		delete pT_nil;
}

void RBT::LeftRotate(Node *px)
{//���� 
	Node* py = px->pRight;//��py��¼px���Һ��� 
	px->pRight = py->pLeft;//px���Һ�����py������ 
	if( py->pLeft != pT_nil )
		py->pLeft->pParent = px;
	py->pParent = px->pParent;//py�ĸ����Ϊpx�ĸ���� 
	if(px->pParent == pT_nil )//�����ж�pyΪ�������ĸ����� 
		pT_root = py;//�� 
	else if( px == px->pParent->pLeft )
		px->pParent->pLeft = py;//�� 
	else px->pParent->pRight = py;//�� 
	py->pLeft = px;
	px->pParent = py;
	py->max = px->max;
	px->max = max( px->max,max(px->pLeft->max,px->pRight->max) );
}
void RBT::RightRotate(Node *py)
{//���� 
	Node* px = py->pLeft;
	py->pLeft = px->pRight;
	px->pRight->pParent = py;
	px->pParent = py->pParent;
	if(py->pParent == pT_nil )
		pT_root = px;
	else if( py == py->pParent->pLeft )
		py->pParent->pLeft = px;
	else py->pParent->pRight = px;
	px->pRight = py;
	py->pParent = px;
	px->max = py->max;
	py->max = max( py->max,max(py->pLeft->max,py->pRight->max) );
}

void RBT::Insert( Node* pz)
{//���� 
	pz->max = pz->high;
	Node* py = pT_nil;
	Node *px  = pT_root;
	while( px != pT_nil )
	{
		px->max = max( pz->high,px->max );
		py = px;//��py��¼px 
		if( pz->low < px->low )
			px = px->pLeft;
		else
			px = px->pRight;
	}
	pz->pParent = py;
	if( py == pT_nil )
		pT_root = pz;
	else if( pz->low < py->low )
		py->pLeft = pz;
	else
		py->pRight = pz;
	pz->pLeft = pT_nil;
	pz->pRight = pT_nil;
	pz->color = "Red";
	InsertFixUp( pz );
}

void RBT::InsertFixUp(Node* pz)
{//�������� 
	Node* py = NULL;
	while( "Red" == pz->pParent->color )
	{
		if(pz->pParent == pz->pParent->pParent->pLeft )
		{
			py = pz->pParent->pParent->pRight;
			if( py->color == "Red" )
			{
				pz->pParent->color = "Black";
				py->color = "Black";
				pz->pParent->pParent->color = "Red";
				pz = pz->pParent->pParent;
			}
			else
			{
				if( pz == pz->pParent->pRight )
				{
					pz = pz->pParent;
					LeftRotate( pz );
				}
				pz->pParent->color = "Black";
				pz->pParent->pParent->color = "Red";
				RightRotate( pz->pParent->pParent );
			}
		}
		else if(pz->pParent == pz->pParent->pParent->pRight )
		{
			py = pz->pParent->pParent->pLeft;
			if( py->color == "Red" )
			{
				pz->pParent->color = "Black";
				py->color = "Black";
				pz->pParent->pParent->color = "Red";
				pz = pz->pParent->pParent;
			}
			else
			{
				if( pz == pz->pParent->pLeft )
				{
					pz = pz->pParent;
					RightRotate( pz );
				}
				pz->pParent->color = "Black";
				pz->pParent->pParent->color = "Red";
				LeftRotate( pz->pParent->pParent );
			}
		}
	}
	pT_root->color = "Black";
}
void RBT::InorderTreeWalk( Node* px )
{//������� 
	if( px != pT_nil )
	{
		InorderTreeWalk( px->pLeft );
		cout << px->low << "-" << px->color << '-' << px->max <<endl;
		InorderTreeWalk( px->pRight );
	}
}
Node* RBT::IntervalSearch( Node* i)
{//���������� 
	Node* x = pT_root;////������i�ص�������x�Ĺ��̴���xΪ����������ʼ  
	while( x != pT_nil && ( x->high < i->low || i->high < x->low ) )
	{//��xָ��pT.nil���ҵ��ص�����ʱ���̽��� 
		if( x->pLeft != pT_nil && x->pLeft->max >= i->low )
			x = x->pLeft;//ȥ��������� 
		else
			x = x->pRight;//ȥ��������� 
	}
	return x;
}
int main()
{
	RBT rbt;
	int a[10][2] = {{6,20},{5,9},{25,36},{3,8},{15,23},{17,30},{26,28},{0,5},{6,12},{19,25}};
	Node* ptemp = new Node[ SIZE ];
	for(int i=0;i<10;i++)
	{
		ptemp[i].low = a[i][0];
		ptemp[i].high = a[i][1];
		rbt.Insert( &ptemp[i] );
	}

	rbt.InorderTreeWalk( rbt.GetRoot() );
	cout << endl;

	bool bquit = true;
	Node temp;
	while(bquit)
	{
		cout << "����Ͷ˵�͸߶˵�: ";
		cin >> temp.low >> temp.high;
		Node* p = rbt.IntervalSearch(&temp);
		if(p != rbt.GetNil() )
			cout << p->low << "-" << p->color << '-' << p->max <<',' << endl;
		else
			cout << "���ص�����" << endl;
		cout << "1-����/0-����): ";
		cin >> bquit;
	}
	delete []ptemp;
	return 0;
}
