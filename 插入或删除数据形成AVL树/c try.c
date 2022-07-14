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
	//删除时执行一次右侧双旋转
	tree* root1;
	root1 = creat1();
	root1 = Delete(root1, 1);
	printf("\n");
	traverse(root1);
	printf("\n");
	//删除时执行一次左侧双旋转
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
//插入并旋转（不考虑有相同的数插入）
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
		//插入数在所给的节点的左侧
		if (t < root->num)
		{
			root->left = insert(root->left, t);
			//不满足AVL树的条件的第一个节点
			if (height(root->left) - height(root->right) == 2)
			{
				//左左的情况（执行一次左侧单旋转）
				if (t < root->left->num)
				{
					root = SingleRotateWithLeft(root);
				}
				//左右的情况（执行一次左侧双旋转）
				else
				{
					root = DoubleRotateWithLeft(root);
				}
			}
		}
		else
		{
			//插入数在所给节点的右侧
			if (t > root->num)
			{
				root->right = insert(root->right, t);
				if (height(root->right) - height(root->left) == 2)
				{
					//右右的情况（执行一次右侧单旋转）
					if (t > root->right->num)
					{
						root = SingleRotateWithRight(root);
					}
					//右左的情况（执行一次右侧双旋转）
					else
					{
						root = DoubleRotateWithRight(root);
					}
				}
			}
		}
	}
	//重新计算节点的高度（一层一层往上计算）
	root->height = max(height(root->left), height(root->right)) + 1;
	return root;
}
//求该点树的高度
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
//左侧单旋转,使左节点成为新的节点（网上的右旋）
tree* SingleRotateWithLeft(tree* root)
{
	//每个节点的左右儿子都必须要有确定的值
	tree* k1, * k2;
	k2 = root;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	//更新被改变节点的高度
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	return k1;
}
//左侧双旋转 即左右双旋转(网上的)
tree* DoubleRotateWithLeft(tree* root)
{
	tree* k1, * k2, * k3;
	k3 = root;
	k1 = k3->left;
	k2 = k1->right;
	k3->left = SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}
//右侧单旋转,使右节点成为新的节点（网上的左旋）
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
//右侧双旋转 即右左双旋转（网上的）
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
//树的中序遍历
void traverse(tree* root)
{
	if (root)
	{
		traverse(root->left);
		printf("%d %d\n", root->num, root->height);
		traverse(root->right);
	}
}
//删除一个数并通过旋转重新形成AVL树
tree* Delete(tree* root, int t)
{
	tree* tmp;
	if (root == NULL)
	{
		return NULL;
	}
	else
	{
		//被删除的数在节点的左边,只可能右树高于左树
		if (t < root->num)
		{
			root->left = Delete(root->left, t);
			//从下到上一层层计算受影响的节点的高度
			root->height = max(height(root->left), height(root->right)) + 1;
			if (height(root->right) - height(root->left) == 2)
			{
				//右右的情况（此时进行一次右侧单旋转）
				if (height(root->right->right) > height(root->right->left))
				{
					root = SingleRotateWithRight(root);
				}
				//右左的情况（进行一次右侧双旋转）
				else
				{
					root = DoubleRotateWithRight(root);
				}
			}
		}
		else
		{
			//被删除的数在节点的右边,只可能左树高于右树
			if (t > root->num)
			{
				root->right = Delete(root->right, t);
				root->height = max(height(root->left), height(root->right)) + 1;
				if (height(root->left) - height(root->right) == 2)
				{
					//此时进行一次左侧单旋转
					if (height(root->left->left) > height(root->left->right))
					{
						root = SingleRotateWithLeft(root);
					}
					//否则进行左侧双旋转
					else
					{
						root = DoubleRotateWithLeft(root);
					}
				}
			}
			else
			{
				//左右孩子都存在的情况
				if (root->left && root->right)
				{
					/*左子树高于右子树
					此时取节点左侧的最大值代替节点
					AVL树的平衡性不会被破坏*/
					if (height(root->left) > height(root->right))
					{
						tmp = Findmax(root->left);
						root->num = tmp->num;
						root->left = Delete(root->left, root->num);
					}
					/*右子树高于左子树
					此时取节点右侧的最小值代替节点
					AVL树的平衡性不会被破坏*/
					else
					{
						tmp = Findmin(root->right);
						root->num = tmp->num;
						root->right = Delete(root->right, root->num);
					}
					//重新计算代替完之后节点的高度
					root->height = max(height(root->left), height(root->right)) + 1;
				}
				//只有左孩子，只有右孩子，没有孩子三种情况
				//哪边存在取哪边返回，否则返回NULL
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
//查找该节点以下节点的最小值
tree* Findmin(tree* p)
{
	//一直向左走即可找到
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
//查找该节点以下节点的最大值
tree* Findmax(tree* p)
{
	//一直向右走即可找到
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