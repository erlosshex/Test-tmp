#include<iostream>
#include<string>
#include<queue>
using namespace std;

template <typename KT,typename VT>
class MyMap		//自定义类,键重载=和<，值重载=
{
private:
	class Node
	{
	public:
		Node(KT k,VT v,int c,Node* f);
		bool IsLeaf();
		int id,color;
		KT key;VT value;
		Node *father,*lchild,*rchild;	
	};
public:
	MyMap():RED(1),BLACK(-1),T(NULL){}
	void insert(const KT& key,const VT& value);
	void remove(const KT& key);
	const VT& query(const KT& key);
	void modify(const KT& key,const VT& value);
	void show(int mode);
private:
	Node* NewNode(KT k,VT v,int c,Node* f);
	void IAdjust(Node* p);
	void DAdjust(Node* p);
	void LRotate(Node* p);
	void RRotate(Node* p);
	Node* Brother(Node* p);
	Node* Uncle(Node* p);
	Node* Next(Node* p);
	Node* Pre(Node* p);
	Node* find(const KT& key);
	int Depth(Node* T);
	string Space(int n);
private:
	MyMap(const MyMap<KT,VT>&);
	MyMap operator = (const MyMap<KT,VT>&);
	const int RED,BLACK; Node* T;
};

template <typename KT,typename VT>
void MyMap<KT,VT>::insert(const KT& key,const VT& value)
{
	Node* p=T;
	if(p==NULL) 
		p=T=NewNode(key,value,RED,NULL);
	else
	{
		Node* f=T;
		while(!p->IsLeaf())
		{
			f=p;
			if(key<p->key) p=p->lchild;
			else if(key>p->key) p=p->rchild;
			else return ;
		}
		if(key<f->key)
		{
			delete f->lchild;
			p=f->lchild=NewNode(key,value,RED,f);
		}
		else
		{
			delete f->rchild;
			p=f->rchild=NewNode(key,value,RED,f);
		}
	}
	IAdjust(p);
}

template <typename KT,typename VT>
void MyMap<KT,VT>::IAdjust(Node* p)
{
	while(true)
	{
		if(p->father==NULL)	//case 1
		{
			p->color=BLACK;
			return ;
		}
		else if(p->father->color==BLACK)	//case 2
			return ;
		else
		{
			if(Uncle(p)->color==RED)	//case 3
			{
				p->father->color=BLACK;
				Uncle(p)->color=BLACK;
				p=p->father->father;
				p->color=RED;
			}
			else	
			{
				if(p->father==p->father->father->lchild)
				{
					if(p==p->father->rchild)	//case 4
						LRotate(p->father);
					else p=p->father;	//case 5
					p->father->color=RED;
					RRotate(p->father);
				}
				else
				{
					if(p==p->father->lchild)	//case 4'
						RRotate(p->father);
					else p=p->father;	//case 5'
					p->father->color=RED;
					LRotate(p->father);
				}
				p->color=BLACK; return ;
			}
		}
	}
}

template <typename KT,typename VT>
typename MyMap<KT,VT>::Node* MyMap<KT,VT>::Brother(Node* p)
{
	if(p->father==NULL) return NULL;
	else
	{
		if(p==p->father->lchild) return p->father->rchild;
		else p->father->lchild;
	}
}

template <typename KT,typename VT>
typename MyMap<KT,VT>::Node* MyMap<KT,VT>::Uncle(Node* p)
{
	if(p->father==NULL) return NULL;
	p=p->father;
	if(p->father==NULL) return NULL;
	else return Brother(p);
}

template <typename KT,typename VT>
void MyMap<KT,VT>::LRotate(Node* p)
{
	Node* f=p->father;
	Node* r=p->rchild;
	if(r->IsLeaf()) return;
	p->rchild=r->lchild;
	if(r->lchild!=NULL)
		r->lchild->father=p;
	r->lchild=p;p->father=r;
	if(f!=NULL)
	{
		if(p==f->lchild) f->lchild=r;
		else f->rchild=r;
	}
	else T=r;
	r->father=f;
}

template <typename KT,typename VT>
void MyMap<KT,VT>::RRotate(Node* p)
{
	Node* f=p->father;
	Node* l=p->lchild;
	if(l->IsLeaf()) return;
	p->lchild=l->rchild;
	if(l->rchild!=NULL)
		l->rchild->father=p;
	l->rchild=p; p->father=l;
	if(f!=NULL)
	{
		if(p==f->lchild) f->lchild=l;
		else f->rchild=l;
	}
	else T=l;
	f->father=l;
}

template <typename KT,typename VT>
void MyMap<KT,VT>::remove(const KT& key)
{
	Node* p=find(key),*n=NULL;
	if(p==NULL) return ;
	if(p->lchild->IsLeaf()&&p->rchild->IsLeaf())
	{
		if(p->father==NULL) {T=NULL;return;}
		if(p==p->father->lchild)
			n=p->father->lchild=p->lchild;
		else n=p->father->rchild=p->lchild;
		n->father=p->father;
		delete p->rchild;
	}
	else if(p->lchild->IsLeaf())
	{
		if(p->father==NULL)
		{
			n=T=p->rchild;
			n->father=NULL;
		}
		else
		{
			if(p==p->father->lchild)
				n=p->father->lchild=p->rchild;
			else n=p->father->rchild=p->rchild;
			n->father=p->father;
		}
		delete p->lchild;
	}
	else if(p->rchild->IsLeaf())
	{
		if(p->father==NULL)
		{
			n=T=p->lchild;
			n->father=NULL;
		}
		else
		{
			if(p==p->father->lchild)
				n=p->father->lchild=p->lchild;
			else n=p->father->rchild=p->lchild;
			n->father=p->father;
		}
		delete p->rchild;
	}
	else
	{
		n=Next(p);
		if(n==n->father->lchild)
			n->father->lchild=n->rchild;
		else n->father->rchild=n->rchild;
		n->rchild->father=n->father;
		p->key=n->key,p->value=n->value;
		delete n->lchild;
		p=n,n=n->rchild;
	}
	if(p->color==BLACK) DAdjust(n);
	delete p;
}

template <typename KT,typename VT>
void MyMap<KT,VT>::DAdjust(Node* n)
{
	while(true)
	{
		if(n->father==NULL)	//case 1
		{				
			n->color=BLACK,T=n;	
			return ;
		}
		else
		{
			if(Brother(n)!=NULL&&Brother(n)->color==RED)	//case 2 ---> 3/4/5
			{
				n->father->color=RED;
				Brother(n)->color=BLACK;
				if(n==n->father->lchild)	LRotate(n->father);
				else RRotate(n->father);
			}
			else
			{
				Node* b=Brother(n);
				if(n==n->father->lchild&&b->rchild->color==RED)	//case 3
				{
					b->color=n->father->color;
					n->father->color=BLACK;
					b->rchild->color=BLACK;
					LRotate(n->father);
					return ;
				}
				else if(n==n->father->rchild&&b->lchild->color==RED)	//case 3'
				{
					b->color=n->father->color;
					n->father->color=BLACK;
					b->lchild->color=BLACK;
					RRotate(n->father);
					return ;
				}
				else
				{
					if(n==n->father->lchild&&b->lchild->color==RED)	//case 4 ---> 3
					{
						b->color=RED;
						b->lchild->color=BLACK;
						RRotate(b);
					}
					else if(n==n->father->rchild&&b->rchild->color==RED)	//case 4' --->3
					{
						b->color=RED;
						b->rchild->color=BLACK;
						LRotate(b);
					}
					else
					{
						if(n->father->color==RED)	//case 5
						{
							n->father->color=BLACK;
							Brother(n)->color=RED;
							return ;							
						}
						else	//case 6 --->1/2/3/4/5
						{
							b->color=RED;
							n=n->father;
						}
					}
				}
			}
		}
	}		
}

template <typename KT,typename VT>
const VT& MyMap<KT,VT>::query(const KT& key)
{
	Node* p=find(key);
	if(p==NULL) return NULL;
	else return p->value;
}

template <typename KT,typename VT>
void MyMap<KT,VT>::modify(const KT& key,const VT& value)
{
	remove(key);
	insert(key,value);
}

template <typename KT,typename VT>
typename MyMap<KT,VT>::Node* MyMap<KT,VT>::Pre(Node* x)
{
	Node* p=x;
	if(!p->lchild->IsLeaf())
	{
		p=p->lchild;
		while(!p->rchild->IsLeaf()) p=p->rchild;
		return p;
	}
	else
	{
		while(p->father!=NULL&&p!=p->father->rchild) 
			p=p->father;
		return p->father;
	}
}

template <typename KT,typename VT>
typename MyMap<KT,VT>::Node* MyMap<KT,VT>::Next(Node* x)
{
	Node* p=x;
	if(!p->rchild->IsLeaf())
	{
		p=p->rchild;
		while(!p->lchild->IsLeaf()) p=p->lchild;
		return p;
	}
	else
	{
		while(p->father!=NULL&p!=p->father->lchild)
			p=p->father;
		return p->father;
	}
	return NULL;
}

template <typename KT,typename VT>
typename MyMap<KT,VT>::Node* MyMap<KT,VT>::find(const KT& key)
{
	Node* p=T;
	while(!p->IsLeaf())
	{
		if(key==p->key) return p;
		else if(key<p->key) p=p->lchild;
		else p=p->rchild;
	}
	return NULL;
}

template <typename KT,typename VT>
void MyMap<KT,VT>::show(int mode)
{
	if(T==NULL)
	{
		cout<<"It's a empty tree!"<<endl;
		return ;
	}
	queue<Node> Q;
	int pl=0,pid=0,H=Depth(T),h=0;
	T->id=1;
	Q.push(*T);					
	while(!Q.empty())
	{
		Node& p=Q.front();
		for(h=0;;h++)	
			if((1<<h)>=p.id+1) break;
		int offset=(1<<(H-h+1))-1;
		if(h==pl) 
		{												
			cout<<Space((p.id-pid)*offset)<<Space(p.id-pid-1);
			if(mode) cout<<p.value;
			else
			{
				if(p.color==RED) cout<<"R";
				else cout<<"B";
			}
			pid=p.id;
		}
		else 
		{
			pid=1<<(h-1);
			int of=(1<<(H-h))-1;
			cout<<endl<<Space(of)<<Space((p.id-pid)*offset)<<Space(p.id-pid);
			if(mode) cout<<p.value;
			else
			{
				if(p.color==RED) cout<<"R";
				else cout<<"B";
			}
			pid=p.id;pl=h;
		}
		Q.pop();
		if(!p.lchild->IsLeaf())
		{
			p.lchild->id=p.id*2;
			Q.push(*p.lchild);
		}
		if(!p.rchild->IsLeaf())
		{
			p.rchild->id=p.id*2+1;
			Q.push(*p.rchild);
		}
	}
	cout<<endl<<endl;
}

template <typename KT,typename VT>
int MyMap<KT,VT>::Depth(Node* T)
{
	if(T->IsLeaf()) return 0;
	int a=Depth(T->lchild)+1;
	int b=Depth(T->rchild)+1;
	return a>b?a:b;
}

template <typename KT,typename VT>
string MyMap<KT,VT>::Space(int n)
{
	string s=string("");
	for(int i=0;i<n;i++) s+=" ";
	return s;
}

template <typename KT,typename VT>
MyMap<KT,VT>::Node::Node(KT k,VT v,int c,Node* f)
{
	key=k;value=v;
	color=c;father=f; 
	lchild=rchild=NULL;
}

template <typename KT,typename VT>
typename MyMap<KT,VT>::Node* MyMap<KT,VT>::NewNode(KT k,VT v,int c,Node* f)
{
	Node* p=new Node(k,v,c,f);
	p->lchild=new Node(KT(),VT(),BLACK,p);
	p->rchild=new Node(KT(),VT(),BLACK,p);
	return p;
}

template <typename KT,typename VT>
bool MyMap<KT,VT>::Node::IsLeaf()
{
	if(lchild==NULL&&rchild==NULL) 
		return true;
	else return false;
}