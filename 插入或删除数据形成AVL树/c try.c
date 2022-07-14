#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define len sizeof(tree)
typedef struct tree
{
	int num;
	int height;
	struct tree* left;
	struct tree* right;
}tree;

tree* creat1();
tree* creat2();
tree* insert(tree* root, int t);
tree* SingleRotateWithLeft(tree* root);
tree* DoubleRotateWithLeft(tree* root);
tree* SingleRotateWithRight(tree* root);
tree* DoubleRotateWithRight(tree* root);
tree* Delete(tree* root, int t);
tree* Findmin(tree* p);
tree* Findmax(tree* p);
int height(tree* p);
void traverse(tree* root);

int main()
{
	//ɾ��ʱִ��һ���Ҳ�˫��ת
	tree* root1;
	root1 = creat1();
	root1 = Delete(root1, 1);
	printf("\n");
	traverse(root1);
	printf("\n");
	//ɾ��ʱִ��һ�����˫��ת
	tree* root2;
	root2 = creat2();
	root2 = Delete(root2, 7);
	traverse(root2);
	return 0;
}
tree* creat1()
{
	tree* root, * n1, * n2, * n3, * n4, * n5, * n6;
	root = malloc(len);
	n1 = malloc(len);
	n2 = malloc(len);
	n3 = malloc(len);
	n4 = malloc(len);
	n5 = malloc(len);
	n6 = malloc(len);
	root->num = 5;
	n1->num = 2;
	n2->num = 8;
	n3->num = 1;
	n4->num = 7;
	n5->num = 9;
	n6->num = 6;
	root->height = 4;
	n1->height = n4->height = 2;
	n2->height = 3;
	n3->height = n6->height = n5->height = 1;
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = NULL;
	n2->left = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = NULL;
	n3->left = n5->left = n6->left = NULL;
	n3->right = n5->right = n6->right = NULL;
	return root;
}
tree* creat2()
{
	tree* root, * n1, * n2, * n3, * n4, * n5, * n6;
	root = malloc(len);
	n1 = malloc(len);
	n2 = malloc(len);
	n3 = malloc(len);
	n4 = malloc(len);
	n5 = malloc(len);
	n6 = malloc(len);
	root->num = 5;
	n1->num = 2;
	n2->num = 6;
	n3->num = 1;
	n4->num = 3;
	n5->num = 7;
	n6->num = 4;
	root->height = 4;
	n1->height = 3;
	n2->height = n4->height = 2;
	n3->height = n5->height = n6->height = 1;
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = NULL;
	n2->right = n5;
	n4->left = NULL;
	n4->right = n6;
	n3->left = n5->left = n6->left = NULL;
	n3->right = n5->right = n6->right = NULL;
	return root;
}
//���벢��ת������������ͬ�������룩
tree* insert(tree* root, int t)
{
	if (root == NULL)
	{
		root = malloc(len);
		root->num = t;
		root->height = 1;
		root->left = root->right = NULL;
	}
	else
	{
		//�������������Ľڵ�����
		if (t < root->num)
		{
			root->left = insert(root->left, t);
			//������AVL���������ĵ�һ���ڵ�
			if (height(root->left) - height(root->right) == 2)
			{
				//����������ִ��һ����൥��ת��
				if (t < root->left->num)
				{
					root = SingleRotateWithLeft(root);
				}
				//���ҵ������ִ��һ�����˫��ת��
				else
				{
					root = DoubleRotateWithLeft(root);
				}
			}
		}
		else
		{
			//�������������ڵ���Ҳ�
			if (t > root->num)
			{
				root->right = insert(root->right, t);
				if (height(root->right) - height(root->left) == 2)
				{
					//���ҵ������ִ��һ���Ҳ൥��ת��
					if (t > root->right->num)
					{
						root = SingleRotateWithRight(root);
					}
					//����������ִ��һ���Ҳ�˫��ת��
					else
					{
						root = DoubleRotateWithRight(root);
					}
				}
			}
		}
	}
	//���¼���ڵ�ĸ߶ȣ�һ��һ�����ϼ��㣩
	root->height = max(height(root->left), height(root->right)) + 1;
	return root;
}
//��õ����ĸ߶�
int height(tree* p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		return p->height;
	}
}
//��൥��ת,ʹ��ڵ��Ϊ�µĽڵ㣨���ϵ�������
tree* SingleRotateWithLeft(tree* root)
{
	//ÿ���ڵ�����Ҷ��Ӷ�����Ҫ��ȷ����ֵ
	tree* k1, * k2;
	k2 = root;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	//���±��ı�ڵ�ĸ߶�
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	return k1;
}
//���˫��ת ������˫��ת(���ϵ�)
tree* DoubleRotateWithLeft(tree* root)
{
	tree* k1, * k2, * k3;
	k3 = root;
	k1 = k3->left;
	k2 = k1->right;
	k3->left = SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}
//�Ҳ൥��ת,ʹ�ҽڵ��Ϊ�µĽڵ㣨���ϵ�������
tree* SingleRotateWithRight(tree* root)
{
	tree* k1, * k2;
	k2 = root;
	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	return k1;
}
//�Ҳ�˫��ת ������˫��ת�����ϵģ�
tree* DoubleRotateWithRight(tree* root)
{
	tree* k1, * k2, * k3;
	k3 = root;
	k1 = k3->right;
	k2 = k1->left;
	/*k3->right = SingleRotateWithLeft(k3->right);
	return SingleRotateWithRight(k3);*/
	k1->left = k2->right;
	k3->right = k2->left;
	k2->left = k3;
	k2->right = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k3->height = max(height(k3->left), height(k3->right)) + 1;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	return k2;
}
//�����������
void traverse(tree* root)
{
	if (root)
	{
		traverse(root->left);
		printf("%d %d\n", root->num, root->height);
		traverse(root->right);
	}
}
//ɾ��һ������ͨ����ת�����γ�AVL��
tree* Delete(tree* root, int t)
{
	tree* tmp;
	if (root == NULL)
	{
		return NULL;
	}
	else
	{
		//��ɾ�������ڽڵ�����,ֻ����������������
		if (t < root->num)
		{
			root->left = Delete(root->left, t);
			//���µ���һ��������Ӱ��Ľڵ�ĸ߶�
			root->height = max(height(root->left), height(root->right)) + 1;
			if (height(root->right) - height(root->left) == 2)
			{
				//���ҵ��������ʱ����һ���Ҳ൥��ת��
				if (height(root->right->right) > height(root->right->left))
				{
					root = SingleRotateWithRight(root);
				}
				//��������������һ���Ҳ�˫��ת��
				else
				{
					root = DoubleRotateWithRight(root);
				}
			}
		}
		else
		{
			//��ɾ�������ڽڵ���ұ�,ֻ����������������
			if (t > root->num)
			{
				root->right = Delete(root->right, t);
				root->height = max(height(root->left), height(root->right)) + 1;
				if (height(root->left) - height(root->right) == 2)
				{
					//��ʱ����һ����൥��ת
					if (height(root->left->left) > height(root->left->right))
					{
						root = SingleRotateWithLeft(root);
					}
					//����������˫��ת
					else
					{
						root = DoubleRotateWithLeft(root);
					}
				}
			}
			else
			{
				//���Һ��Ӷ����ڵ����
				if (root->left && root->right)
				{
					/*����������������
					��ʱȡ�ڵ��������ֵ����ڵ�
					AVL����ƽ���Բ��ᱻ�ƻ�*/
					if (height(root->left) > height(root->right))
					{
						tmp = Findmax(root->left);
						root->num = tmp->num;
						root->left = Delete(root->left, root->num);
					}
					/*����������������
					��ʱȡ�ڵ��Ҳ����Сֵ����ڵ�
					AVL����ƽ���Բ��ᱻ�ƻ�*/
					else
					{
						tmp = Findmin(root->right);
						root->num = tmp->num;
						root->right = Delete(root->right, root->num);
					}
					//���¼��������֮��ڵ�ĸ߶�
					root->height = max(height(root->left), height(root->right)) + 1;
				}
				//ֻ�����ӣ�ֻ���Һ��ӣ�û�к����������
				//�ıߴ���ȡ�ı߷��أ����򷵻�NULL
				else
				{
					tmp = root;
					if (root->left == NULL)
					{
						root = root->right;
					}
					else if (root->right == NULL)
					{
						root = root->left;
					}
					free(tmp);
				}
			}
		}
	}
	return root;
}
//���Ҹýڵ����½ڵ����Сֵ
tree* Findmin(tree* p)
{
	//һֱ�����߼����ҵ�
	if (p)
	{
		if (p->left)
		{
			return Findmin(p->left);
		}
		else
		{
			return p;
		}
	}
	else
	{
		return NULL;
	}
}
//���Ҹýڵ����½ڵ�����ֵ
tree* Findmax(tree* p)
{
	//һֱ�����߼����ҵ�
	if (p)
	{
		if (p->right)
		{
			return Findmax(p->right);
		}
		else
		{
			return p;
		}
	}
	else
	{
		return NULL;
	}
}