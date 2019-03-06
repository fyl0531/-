  /*
 *File name:rbtree
 *Author:Fei Yuling		Version:1.0		Date:2018.9.10 
 *Description:��������������в��룬ɾ������ӡ�Ȳ��� 
 */ 	


#include<stdio.h>
#include<stdlib.h>

#define RED 0
#define BLACK 1

//����������� 
typedef struct RBTreeNode
{
	char color;//��ɫ 
	int key;//ֵ 
	struct RBTreeNode *lchild;//���� 
	struct RBTreeNode *rchild;//�Һ��� 
	struct RBTreeNode *parent;//����� 
}Node,*RBTree;
 
//�������������
typedef struct rb_root
{
	Node *node;	
} RBRoot;

//��������������غ�����ĸ�
RBRoot* creat_rbtree()
{
	RBRoot *root=(RBRoot*)malloc(sizeof(RBRoot));//�������㣬������ռ� 
	root->node=NULL;//��ʼ�� 
	return root;
}

//�½�һ�����
Node*  creat_rbtree_node(int key,Node *parent,Node *lchild,Node *rchild)
{
	Node* p;
	p=(Node*)malloc(sizeof(Node));
	p->key=key;
	p->lchild=lchild;
	p->rchild=rchild;
	p->color=BLACK;
	
	return p;
}

//���� 
void rbtree_left_rotate(RBRoot *root,Node *x)
{
	Node *y=x->rchild;//����x���ҽ�����y
	//���ȣ����ҵ�y������,�����ձ�x����Ϊ�Һ��� 
	x->rchild=y->lchild;
	if (y->lchild!= NULL)
        y->lchild->parent = x;
	
	y->parent=x->parent;
		//x->rchild=y->lchild;
		//y->lchild->parent=x;
	
	//yȱ�����ӣ�x��Ϊy������
	if(x->parent==NULL)//��xΪ������ʱ��
	{
		root->node=y;//��y��Ϊ����� 
	}
	else//��x���Ǹ��ڵ��ʱ�� 
	{
		//y->parent=x->parent;//y����x�����˵Ķ��� 
		if(x->parent->lchild==x) 
		{//Ҫȷ��y���������ӻ����Һ��� 
			x->parent->lchild=y;	
		}
		else
		{
			x->parent->rchild=y;
		}
	}
	y->lchild=x;//x��λ 
	x->parent=y;
}

//���� 
void rbtree_right_rotate(RBRoot *root,Node *y)
{
	Node *x=y->lchild;
	
	y->lchild=x->rchild;
	//�ҵ�x���Һ��ӣ������ձ�y����Ϊ����
	if(x->rchild!=NULL)
	{
		x->rchild->parent=y;
	} 
	x->parent=y->parent;
	//��ʱx���Һ����ǿյģ�y����x���Һ���
	if(y->parent==NULL)//���yΪ�����
	{
		root->node=x;//��x��Ϊ���ڵ� 
	} 
	else//��y���Ǹ��ڵ��ʱ�� 
	{
		//y->parent=x->parent;//x����y�����˵Ķ��� 
		if(y->parent->rchild==y)
		{ //Ҫȷ��x���������ӻ����Һ��� 
			y->parent->rchild=x;	
		}
		else
		{
			y->parent->lchild=x;
		}
	}
	x->rchild=y;//y��λ 
	y->parent=x;
}

//�������� 
void rbtree_insert_fixup(RBRoot *root, Node *node)
{
    Node *parent, *gparent;
	// �����ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ
    while ((parent = node->parent) && (parent->color==RED))
    {
        gparent = parent->parent;
        //�������ڵ㡱�ǡ��游�ڵ�����ӡ�
        if (parent == gparent->lchild)
        { // Case 1����������ڵ��Ǻ�ɫ
            {
                Node *uncle = gparent->rchild;
                if (uncle && uncle->color==RED)
                {//�������ڣ�ү���,��ү�����ж� 
                    uncle->color=BLACK;
                    parent->color=BLACK;
                    gparent->color=RED;
                    node = gparent;
                    continue;
                }
            }
            if (parent->rchild == node)
            {// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
                Node *tmp;
                rbtree_left_rotate(root, parent);//������ 
                tmp = parent;
                parent = node;
                node = tmp;
            }
            // Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
            parent->color=BLACK;
            gparent->color=RED;
            rbtree_right_rotate(root, gparent);
        } 
        else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
        { // Case 1����������ڵ��Ǻ�ɫ
            {
                Node *uncle = gparent->lchild;
                if (uncle && (uncle->color==RED))
                {
                    uncle->color=BLACK;
                    parent->color=BLACK;
                    gparent->color=RED;
                    node = gparent;
                    continue;
                }
            }
            if (parent->lchild == node)
            {// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
                Node *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
            parent->color=BLACK;
            gparent->color=RED;
            rbtree_left_rotate(root, gparent);
        }
    }
    root->node->color=BLACK;// �����ڵ���Ϊ��ɫ
}

//����
void rbtree_insert(RBRoot *root,Node *node)
{
	Node *y=NULL;
	Node *x=root->node;
	while(x!=NULL)//xΪҶ�ӽ������ѭ�� 
	{
		y=x;
		if(x->key>node->key)
			{x=x->lchild;}
		else
			{x=x->rchild;}
	}
	node->parent=y;
	if(y!=NULL)
	{
		if(node->key<y->key)
			{y->lchild=node;}
		else 
			{y->rchild=node;}
	}
	else//��yΪNULL��˵����Ϊ�գ���node��Ϊ���ڵ�
	{root->node=node;}
	node->color=RED;//����ɫ��Ϊ��ɫ
	//�������� 
	rbtree_insert_fixup(root, node);
 } 
 
int insert_rbtree(RBRoot *root,int key)
{
	Node *node;//�½�һ�����
	node=creat_rbtree_node(key,NULL,NULL,NULL); 
	if(node==NULL) return -1;
	else rbtree_insert(root,node);
	return 0;
}

/*
 * �������"�����"
 */
void inorder(RBTree tree)
{
    if(tree != NULL)
    {
        inorder(tree->lchild);
        printf("%d", tree->key);
        if(tree->color==0)
        	{
        		printf("(RED) ");
			}
		else 
		{
			printf("(BLACK) ");	
		}
        inorder(tree->rchild);
    }
}

void inorder_rbtree(RBRoot *root) 
{
	 if (root)
        inorder(root->node);
}

//�������ҽ��key 
Node* search(RBTree x,int key)
{	
	if(x==NULL)
	{
		printf("\n**********ɾ��ʧ�ܣ����޴���**********\n");
	}
	if(x->key==key)
	{
		return x;
	}
 
	if(x->key<key)
	{
		search(x->rchild,key);
	}
	else
	{
		search(x->lchild,key);	
	}
	
 } 

//ɾ������
void rbtree_delete_fixup(RBRoot *root,Node *node,Node *parent)
{
	Node *bro;
	int color;
	while((node!=root->node)&&(node->color!=BLACK||node==NULL))//����������Ǹ���㲢���Ǻ�ɫ�Ļ����ǿյģ�������ѭ�� 
	{  
		if(parent->lchild==node)
		{//���������������
			bro=parent->rchild;
			if(bro->color==RED)
			{//�ֵ�Ϊ�죬����Ϊ�� 
				rbtree_left_rotate(root,parent);//�Ը����� 
				color=parent->color;//���ֽ�����ɫ 
				parent->color=bro->color;
				bro->color=color;
				bro=parent->rchild;
			}
			if(bro->color==BLACK)
			{// �ֵ�Ϊ�ڣ�����Ϊ�� 
				if(bro->lchild!=NULL&&bro->rchild!=NULL)
				{ 
					if(bro->lchild->color==RED&&bro->rchild->color==BLACK)
					{//�ֵ�����Ϊ�죬�Һ���Ϊ�� 
						rbtree_right_rotate(root,bro);//�ֵ����� 
						color=bro->color;//�ֵܺ��ֵ����ӽ�����ɫ 
						bro->color=bro->lchild->color;
						bro->lchild->color=color;
						bro=parent->rchild; 
					}
					if(bro->lchild->color==BLACK&&bro->rchild->color==BLACK)
					{//�ֵ����Һ��Ӷ�Ϊ�� 
						bro->color=RED;//�ֵ�Ϳ�� 
						node=parent;//�о������ 
						parent=node->parent;
					}
					if(bro->rchild->color==RED)
					{// �ֵ��Һ���Ϊ�죬�������� 
						rbtree_left_rotate(root,parent);//�Ը����� 
						color=parent->color;//���ֽ�����ɫ 
						parent->color=bro->color;
						bro->color=color;
						bro->rchild->color=BLACK;//�ֵ��Һ���Ϳ�� 
						bro=parent->rchild;
						
						node = root->node;
						break;
					}
				}
			}
		}
		else
		{//������������Һ���
			bro=parent->lchild;
			if(bro->color==RED)
			{
				rbtree_left_rotate(root,parent);
				color=parent->color;
				parent->color=bro->color;
				bro->color=color;
				bro=parent->lchild;
			}
			if(bro->color==BLACK)
			{
				if(bro->lchild!=NULL&&bro->rchild!=NULL)
				{
					if(bro->lchild->color==RED&&bro->rchild->color==BLACK)
					{
						rbtree_right_rotate(root,bro);
						color=bro->color;
						bro->color=bro->lchild->color;
						bro->lchild->color=color;
						bro=parent->lchild; 
					}
					if(bro->lchild->color==BLACK&&bro->rchild->color==BLACK)
					{
						bro->color=RED;
						node=parent;
						parent=node->parent;
					}
					if(bro->rchild->color==RED)
					{
						rbtree_left_rotate(root,parent);
						color=parent->color;
						parent->color=bro->color;
						bro->color=color;
						bro->rchild->color=BLACK;
						bro=parent->lchild;
						
						node = root->node;
						break;
					}
				}
			}
		}
	}
	node->color=BLACK;
} 

//ɾ�� 
void rbtree_delete(RBRoot *root,Node *node)
{
	Node *temp,*child,*parent;//�滻��� 
	int color;
	//��node��������ʱ
	if((node->lchild!=NULL)&&(node->rchild!=NULL))
	{ 	
		//�ҵ���ɾ�����ĺ�̽�㣬��������������ߵ�Ҷ�ӽ�� 
		temp=node->rchild;
		parent=node->parent;
		while(temp->lchild!=NULL)
		{
			temp=temp->lchild;
		}
		//�жϴ�ɾ������Ƿ�Ϊ���ڵ�
		if(node->parent!=NULL) 
		{//��Ϊ��
			if(node==node->parent->lchild)
			{
				node->parent->lchild=temp;
			} 
			 else 
			{
			 	node->parent->rchild=temp;
			}
		}
		else
		{//Ϊ�� 
			root->node=temp;
		}
		parent=temp->parent;//parent���temp����� 
		
		//child��temp���Һ��ӣ�temp��Ȼû������,��ȻҪ��child���е����� 
		child=temp->rchild;
		
		
		//�ж�temp�Ƿ�Ϊnode�ĸ��ڵ�
		if(parent==node)
		{//�ǣ�ֱ����� 
			parent=temp;	
		} 
		else
		{//���ǣ����� 
		 //child�����ڣ�����Ϊparent������
		if(child!=NULL)
			{
		 		child->parent=parent;
			} 
		parent->lchild=child;
		temp->rchild=node->rchild;
		node->rchild->parent=temp;
		}
		temp->parent=node->parent;
		temp->color=node->color;
		temp->lchild=node->lchild;
		node->lchild->parent=temp;
	}
	else
	{//��ֻ��1������
		if(node->lchild!=NULL)
		{
			child=node->lchild;
		} 
		else
		{
			child=node->rchild;
		}
		parent=node->parent;
		color=node->color;
		
		if(child!=NULL)
		{
			child->parent=parent;
		}
		if(parent!=NULL)
		{//node��Ϊ��ʱ 
			if(parent->lchild==node)
			{
				parent->lchild=child;	
			} 
			else
			{
				parent->rchild=child;
			}
		}
		else
		{//nodeΪ�� 
			root->node=child;
		}
		
	}
	if(color==BLACK)
		{
			rbtree_delete_fixup(root, child, parent);
			free(node);
			return; 
		}	 
 } 
 
 void delete_rbtree(RBRoot *root,int key)
{
	Node *z,*node;
	z=search(root->node,key);
	if(z!=NULL)
	{
		rbtree_delete(root,z);
	}
}

int main()
{
	int a[15]={2,10,6,7,15,4,14,1,13,3,8,12,5,9,11};
	int i;//������
	int key;
	int n=sizeof(a)/sizeof(int);
	printf("**********ԭʼ����**********\n");
	for(i=0;i<n;i++)
	{
		printf("%d  ",a[i]);	
	}
	printf("\n");
	
	//���濪ʼ��������� 
	RBRoot *root=NULL;//���ȴ���������ĸ� 
	root=creat_rbtree();
	
	for(i=0;i<n;i++)
	{
		printf("== ��ӽڵ�: %d\n", a[i]);
		insert_rbtree(root,a[i]);
		printf("== �������: ");
    	inorder_rbtree(root);
		printf("\n");
	 } 
	
	printf("\n==�������в���һ��ֵ: ");
	scanf("%d",&key);
	insert_rbtree(root,key);
	printf("\n== �ɹ��������������: ");
    	inorder_rbtree(root);
		printf("\n");
	
	printf("\n==�ں������ɾ��һ��ֵ: ");
	scanf("%d",&key);
	delete_rbtree(root,key); 
	printf("\n== �ɹ�ɾ������������: ");
    	inorder_rbtree(root);
		printf("\n");
	 return 0;
}







