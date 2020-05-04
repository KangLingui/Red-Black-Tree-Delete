

#include<stdio.h>
#include<stdlib.h>

enum COLOR{RED,BLACK};

typedef struct node
{
	int nvalue;
	int ncolor;
	struct node *pleft;
	struct node*pright;
	struct node *pfather;
}rbt;


rbt *prbt = NULL;

//右旋
void right(rbt **ptree)
{
	if(*ptree == NULL || (*ptree)->pleft == NULL)return ;
	rbt *pnode = *ptree;
	rbt *pmark = pnode->pleft;

	pnode->pleft = pmark->pright;
	pmark->pright = pnode;

	if(pnode->pfather == NULL)
	{
		prbt = pmark;	
	}
	else
	{
		if(pnode == pnode->pfather->pleft)
		{
			pnode->pfather->pleft = pmark;	
	
		}
		else
		{
			pnode->pfather->pright = pmark;	
		}
	}

	if(pnode->pleft!=NULL)
	{
		pnode->pleft->pfather = pnode;	
	}
	pmark->pfather = pnode->pfather;
	pnode->pfather = pmark;
}


//左旋
void left(rbt **ptree)
{
	if(*ptree == NULL || (*ptree)->pright == NULL)return ;
	rbt *pnode = *ptree;
	rbt *pmark = pnode->pright;

	pnode->pright = pmark->pleft;
	pmark->pleft = pnode;

	if(pnode->pfather == NULL)
	{	
	prbt = pmark;	
	}
else
{
	if(pnode == pnode->pfather->pleft)
	{
	pnode->pfather->pleft = pmark;	
	
	}
	else
	{
	pnode->pfather->pright = pmark;	
	
	}
}
	if(pnode->pright!=NULL)
	{
	pnode->pright->pfather = pnode;	
	}
pmark->pfather = pnode->pfather;
pnode->pfather = pmark;
}


//查找
rbt *search(rbt*ptree,int num)
{
		while(ptree)
		{
			if(ptree->nvalue>num)
			{
				if(ptree->pleft ==NULL)
				{
					return ptree;	
				}
				ptree = ptree->pleft;	
			}
			else if(ptree->nvalue<num)
			{
				if(ptree->pright==NULL)
				{
					return	ptree;	
				}
				ptree = ptree->pright;	
			}
			else
			{	
				printf("数据错误\n");
				exit(1);
			}			
		}
	
	return NULL;
	
}

rbt *getuncle(rbt *pnode)
{
	if(pnode ==pnode->pfather->pleft)
	{
		return  pnode->pfather->pright;	
	}
	else
	{
		return pnode->pfather->pleft;	
	}
	
	
}

void addnode(rbt *ptree,int num)
{
	rbt *pnode = NULL;//父亲节点

	pnode = search(prbt,num);//查找到的节点 是要插入节点的父亲节点


	rbt *ptemp = NULL;//要查入节点
	ptemp = (rbt*)malloc(sizeof(rbt));
	ptemp->nvalue  = num;
	ptemp->ncolor = RED;
	ptemp->pfather = pnode;//指向父亲
	ptemp->pleft =NULL;
	ptemp->pright = NULL;

	//当树中无节点时
	if(pnode == NULL)
	{
		prbt = ptemp;//让根指向新来的
		ptemp->ncolor = BLACK;
		return;
	}
	
	//树中又节点
	//新来的要和父亲先连接 后讨论调整颜色 ----但是要判断左子和右子
	if(pnode->nvalue  >num)
	{
		pnode->pleft = ptemp;	
	}
	else
	{
		pnode->pright = ptemp;	
	}

	rbt *puncle = NULL;//叔叔
	rbt *pgreadfather = NULL;

		//父亲黑
		if(pnode->ncolor == BLACK)
		{
			return;	
		}
		
		
		//父亲为红
	while(pnode->ncolor ==RED)
	{
	      puncle = getuncle(pnode);//叔叔颜色
		  pgreadfather = pnode->pfather;

		  //叔叔红色
		  if(puncle != NULL && puncle->ncolor == RED)
		  {
			  pnode->ncolor = BLACK;
			  puncle->ncolor = BLACK;

			  pgreadfather->ncolor= RED;

				ptemp =pgreadfather;//爷爷为新Z   父亲也会变化
				pnode = ptemp->pfather;

				if(pnode==NULL)//原类爷爷父亲为空  则是根
				{
					prbt->ncolor = BLACK;
					break;
				}
				continue;
		 }
		//叔叔是黑的
		 if(puncle != NULL ||puncle->ncolor == BLACK)
		 {
			   //父亲方向左
			   if(pnode == pgreadfather->pleft)
			   {
				   
					//Z的方向
					//Z是父亲右子
					if(ptemp == pnode->pright)
					{
						ptemp = pnode; //父亲是新Z
					//注意当左旋时 ----父亲节点发生改变--而且是在旋转后变得
					left(&ptemp);//左旋
					pnode = ptemp->pfather;//父亲节点变化
					continue;
					}
				   
				   //Z是父亲左
				   if(ptemp == pnode->pleft)
				   {
						pnode->ncolor = BLACK;
						pgreadfather->ncolor = RED;
						right(&pgreadfather);
					   break ;
					}
				   
				   
				}

			//父亲是爷爷右
			if(pnode == pgreadfather->pright)
			{
				
				//Z是父亲的左
				if(ptemp == pnode->pleft)
				{
					ptemp = pnode;//父亲为新Z
					//右旋
					right(&ptemp);
					//右旋完后父亲节点发生变化
					 pnode = ptemp->pfather;
				continue;
				}
								
				//Z是父亲的右
								
				//Z是父亲的右
				if(ptemp == pnode->pright)
				{
					
					pnode->ncolor =BLACK;
					pgreadfather->ncolor = RED;
					left(&pgreadfather);//左旋
					break;
				}		
	     	}
		}	
	}
	
}




void createrbt(int arr[], int nlenght)
{
	if(arr==NULL  || nlenght <=0)return ;

	int i;
	for(i = 0;i<nlenght;i++)
	{
		addnode(prbt,arr[i]);	
	}
	
}

void   qianxu(rbt *ptree)
{
	if(ptree==NULL)return;
	printf(" nval == %d    ncolor == %d  \n ",ptree->nvalue,ptree->ncolor);

	qianxu(ptree->pleft);
	qianxu(ptree->pright);

}

rbt * findnode(rbt *ptree,int num)//找到要删除的节点   
{
	while(ptree)
	{
		
		if(ptree->nvalue  == num)
		{
			return ptree;
		}
		else if(ptree->nvalue > num)
		{
			ptree = ptree->pleft;	
		}
		else
		{
			ptree = ptree->pright;
		}
		
	}
	return NULL;
}

void delnode(rbt *ptree,int num)
{
	if(ptree == NULL)return;
	rbt *ptemp = NULL;	
	ptemp = findnode(prbt,num);//查找到要删除的点
	rbt *pmark = ptemp;//标记要删除的点

	//讨论两个孩子情况
	if(ptemp->pright !=NULL && ptemp->pleft != NULL)
	{
		//左
			ptemp = ptemp->pleft;
		//左的额最右
		while(ptemp->pright !=NULL)
		{
			ptemp  =ptemp->pright;	
		}
		//值的覆盖
		pmark->nvalue = ptemp->nvalue;
	}

	//颜色讨论
	rbt *pnode = ptemp->pfather;//pnode是父亲
	//1--只有根 无子
	if(pnode == NULL && ptemp->pleft == NULL && ptemp->pright == NULL)
	{
		free(ptemp);
		ptemp = NULL;
		prbt = NULL;
		return;
	}
	//2 根---一个红子   --不用判断颜色，因为只有一个子一定是红（保持平衡）
	if(pnode ==NULL && (ptemp->pleft != NULL || ptemp->pright !=NULL))
	{
		if(ptemp->pleft != NULL)
		{
			prbt = ptemp->pleft;
			prbt->ncolor = BLACK;
			prbt->pfather = NULL;
			free(ptemp);
			ptemp = NULL;
			return;
		}
		
		if(ptemp->pright !=NULL)
		{
			
			prbt = ptemp->pright;
			prbt->ncolor = BLACK;
			prbt->pfather = NULL;
			free(ptemp);
			ptemp =NULL;
			return ;
		}
			
	}
	//3 非根   红叶子--红叶子一定无子（1子不能是红 2子不能是两黑/一黑）
	if(pnode != NULL && ptemp->ncolor ==RED)
	{
			if(ptemp == pnode->pright)
			{
				pnode->pright =NULL;
			}
			if(ptemp == pnode->pleft)
			{
				pnode->pleft ==NULL;
			}
			free(ptemp);
			ptemp = NULL;
		return ;
	}

	//4非根  黑  且一个红子  (一个子那只能是红子 无需判断颜色)
	if(pnode != NULL && ptemp->ncolor ==BLACK &&
		(ptemp->pleft != NULL || ptemp->pright != NULL))
	{
		if(pnode->pleft == ptemp)
		{
			pnode->pleft == ptemp->pleft ? ptemp->pleft :ptemp->pright;
			pnode->pleft->ncolor= BLACK;
			pnode->pleft->pfather =pnode;
		}
		else
		{
			pnode->pright = ptemp->pleft? ptemp->pleft:ptemp->pright;
			pnode->pright->ncolor =BLACK;
			pnode->pright->pfather = pnode;
		}
		free(ptemp);
		ptemp = NULL;
		return;
	}
		
	//5非根  黑  无子
	rbt *pbrother =getuncle(ptemp);//兄弟
	//假删除
	if(ptemp == pnode->pleft)
	{
		pnode->pleft = NULL;	
	}
	else
	{
		pnode->pright= NULL;
	}
	pmark = ptemp;

	while(ptemp->ncolor == BLACK)
	{
		//5.1 兄的是红   ----不用判断兄弟是否为空  ptemp是黑的他一定有兄弟
		if(pbrother->ncolor==RED)
		{
				pnode->ncolor =RED;
				pbrother->ncolor=BLACK;
			//5.1.1兄弟是父亲的右
			if(pbrother == pnode->pright)
			{
				left(&pnode);
				pbrother=pnode->pright; //旋转后兄弟发生变化
				continue;
			}
			//5.1.2兄弟是父亲的左
			if(pbrother == pnode->pleft)
			{
				right(&pnode);
				pbrother = pnode->pleft;//兄弟发生变化
				continue;
			}	
		}
	
		//5.2兄弟是黑
		if(pbrother->ncolor ==BLACK)
		{
			//5.2.1	两侄子全黑（都真黑/都空）（不能一空一黑不平衡）
		if((pbrother->pleft==NULL &&pbrother->pright ==NULL) || 
		((pbrother->pleft !=NULL &&pbrother->pleft->ncolor==BLACK) &&
		(pbrother->pright !=NULL&& pbrother->pright->ncolor==BLACK)))
			{
				//5.2.1.1父亲颜色红
				if(pnode->ncolor ==RED)
				{
					pnode->ncolor =BLACK;
					pbrother->ncolor=RED;
					break;
				}
				//5.2.1.2父亲是黑
				if(pnode->ncolor == BLACK)
				{
					pbrother->ncolor=RED;
					ptemp = pnode;
					pnode = ptemp->pfather;

					//判断是否为空
					if(pnode==NULL)
					{
						break;	
					}
					pbrother = getuncle(ptemp);
					continue;
				}
			}
			
			//5.2.2左侄子红  右侄子黑（真黑/空）
			if((pbrother->pleft!=NULL &&pbrother->pleft->ncolor == RED) && 
				(pbrother->pright==NULL ||pbrother->pright->ncolor==BLACK))
			{
				//5.2.2.1兄弟是父亲的右
				if(pbrother==pnode->pright)
				{
					pbrother->ncolor=RED;
					pbrother->pleft->ncolor =BLACK;
					right(&pnode);
					pbrother = pnode->pright;
					continue;
				}
				//5.2.2.2兄弟是父亲左
				if(pbrother == pnode->pleft)
				{
					pbrother->ncolor=pnode->ncolor;
					pnode->ncolor = BLACK;
					pbrother->pleft->ncolor = BLACK;
					break;
				}
			}

			//5.2.3右侄子为红
			if(pbrother->pright!=NULL&& pbrother->pright->ncolor==RED)
			{
				//5.2.3.1兄弟是父亲右
				if(pbrother==pnode->pright)
				{
					pbrother->ncolor= pnode->ncolor;
					pnode->ncolor = BLACK;
					pbrother->pright->ncolor=BLACK;
					left(&pnode);
					break;
				}
				//5.2.3.2兄弟是父亲左
				if(pbrother==pnode->pleft)
				{
					pbrother->ncolor =RED;
					pbrother->pright->ncolor=BLACK;
					left(&pbrother);
					pbrother = pnode->pleft;
					continue;
				}
				
				
				
			}
		}
		
	}


free(pmark);
pmark=NULL;
	
}

int main()
{
		int arr[] ={11,2,14,1,7,15,5,8};
		createrbt(arr,sizeof(arr)/sizeof(arr[0]));
		qianxu(prbt);
		printf("-------------------------------\n");
		delnode(prbt,1);
		qianxu(prbt);
	
	return 0;
	
}
