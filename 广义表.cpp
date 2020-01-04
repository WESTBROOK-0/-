#include <iostream>
using namespace std;
typedef int Status;
typedef enum{ATOM,LIST}elemtag;//ATOM==0:ԭ�ӣ�LIST==1���ӱ�
typedef char ElemType;


typedef struct GLNode
{
	int tag;//�������֣���������ԭ�ӽ��ͱ���
	int mark;
	union {
		ElemType data;   //data��ԭ�ӽ���ֵ��
		GLNode *hp;
	}val; 
	GLNode *tp;
}GLNode ,*GList;
//val�Ǳ����ָ����val.hp��val.tp�ֱ�ָ���ͷ�ͱ�β

void CreateGList(GList &L)//�����Ĵ���
{
	char ch;
	cin>>ch;
	if(ch == ')')
	{  //������Ϊ�����ţ�����L�ĺ��ָ����Ϊ��
		L = 0;
		return ;
	}
	else if(ch >='a'&&ch <='z')
	{
		L = new GLNode;
		L->tag = 0;
		L->val.data =ch;
		L->tp = 0;
	}
	else if(ch == '(')
	{  //������Ϊ������������L��ָ����ӱ��㲢�ݹ鹹���ֱ�
		L = new GLNode;
		L->tag = 1;
		CreateGList(L->val.hp);
		if(L->val.hp == 0)
		{
			L->tp = 0;
			return ;
		}
		GLNode *p;
		p = L;
		cin>>ch;
		while(ch == ',')
		{  //������Ϊ������ݹ鹹���̱�
			p->tp = new GLNode;
			p = p->tp;
			p->tag = 1;
			CreateGList(p->val.hp);
			cin>>ch;
		}
		p->tp = 0;
	}
}
void DisplayGList(GList &L)//���������
{
	if(L == 0)
		return ;
	else if(L->tag == 0)
	{   //���ڵ�Ԫ�ؽ�㣬����ý���ֵ 
		cout<<L->val.data;
		} 
	else
	{
		cout<<"("; //���ڱ��㣬������������ţ���Ϊ��ʼ����
		DisplayGList(L->val.hp);
		GLNode *p;
		p = L->tp;
		while(p)
		{  //��Ϊ�ǿ��ֱ���ݹ�����˱� 
			cout<<",";
			DisplayGList(p->val.hp);
			p = p->tp;
		}
		cout<<")";
	}
}
GList GListCopy(GList L)//���ƹ����
{
	GList M;
	if(L == 0)
		return 0;
	else 
	{
		M = new GLNode;
		M->tag = L->tag;
		if(L->tag == 0)
		{   //��ԭ�ӵĻ�������ԭ��
			M->val.data = L->val.data;
			M->tp = 0;
		}
		else 
		{   //�ֱ��Ʊ�ͷ�ͱ�β
			M->val.hp = GListCopy(L->val.hp);
			M->tp = GListCopy(L->tp);
		}
		return M;
	}
}
int LenthGList1(GList M)  //��M����
{
    if(M!=NULL)
	{   //���M��Ϊ�գ��ݹ���ó��Ȳ���1��ֱ��Ϊ�� 
        return 1+LenthGList1(M->tp);
    }
	else
	{   //����Ϊ0 
        return 0;
    }
}
int DepthGList1(GList M)//������M������㷨
{
	if(M == 0)
		return 0;
		
	if(M->tag == 0)
	{ 
		return 0;
		} 
	else if(M->val.hp == 0)
	{ 
		return 1;
		} 
	else
	{   //����ÿ����㣬��������ӱ��������
		int m1 ,m2;
		//�ݹ���һ���ӱ�����
		m1 = DepthGList1(M->val.hp)+1; 
		m2 = DepthGList1(M->tp);
		if(m1>=m2) //������ȡ�ϴ�ֵ 
		{ 
			return m1;
			} 
		else
		{ 
			return m2;
			} 
	}
}
GList Head(GList L)//���ͷ���㷨
{
	GList H;
	if(L == 0)
	{   //���Ϊ�գ����ޱ�ͷ 
		cout<<"�ձ��ޱ�ͷ"<<endl;
		return 0;
	}
	else if(L->tag == 0)
	{   //���Ϊԭ�ӣ��ޱ�ͷ 
		cout<<"ԭ���ޱ�ͷ"<<endl;
		return 0;
	}
	else
	{   //���ú�����ֵ��ͷ 
		H = GListCopy(L->val.hp);
		if(H == 0)
			cout<<"�ձ��ޱ�ͷ"<<endl;
		return H;
	}
}
void GListTraverse1(GList L) //���������L 
{
	if(!L)
	{   //���Ϊ�գ�������� 
		cout<<"()";
	}
	else
	{
		if(L->tag==ATOM)
		{   //���Ϊԭ�ӣ����ԭ�� 
			cout<<L->val.data;
		}
		else
		{   //����������� 
			cout<<"(";
			GLNode *p=L;
			while(p)
			{   //�ݹ����p 
				GListTraverse1(p->val.hp);
				p=p->tp;
				if(p)
				{   //�м��ö��ŷֿ� 
					cout<<",";
				 } 
			}
			cout<<")"; //������������ 
		}
	}
	
}
GList Tail(GList L)//���β���㷨
{
	GList T;
	if(L == 0)
	{   
		cout<<"�ձ��ޱ�β"<<endl;
		return 0;
	}
	else if(L->tag == 0)
	{
		cout<<"ԭ���ޱ�β"<<endl;
		return 0;
	}
	else
	{   //���ú�����ֵ��β 
		T = GListCopy(L->tp);
		if(T == 0)
		{   //���TΪ0�����βΪ0 
			T =new GLNode;
			T->tag = 1;
			T->tp = 0;
			T->val.hp = 0;
		}
		return T;
	}
}
void GListTraverse2(GList L) //���������L 
{
	if(!L)
	{
		cout<<"()";
	}
	else
	{
		if(L->tag==ATOM)
		{
			cout<<L->val.data;
		}
		else
		{
			cout<<"(";
			GLNode *p=L;
			while(p)
			{
				GListTraverse2(p->val.hp);
				p=p->tp;
				if(p)
				{
					cout<<",";
				 } 
			}
			cout<<")";
		}
	}
	
}
int LenthGList(GList L)  //��L����
{
    if(L!=NULL){
        return 1+LenthGList(L->tp);
    }
	else
	{
        return 0;
    }
}
int DepthGList(GList L)//������L������㷨
{
	if(L == 0)
	{ 
		return 0;
		} 
	if(L->tag == 0)
	{ 
		return 0;
		} 
	else if(L->val.hp == 0)
	{ 
		return 1;
		} 
	else
	{
		int m1 ,m2;
		m1 = DepthGList(L->val.hp)+1;
		m2 = DepthGList(L->tp);
		if(m1>=m2)
			return m1;
		else
			return m2;
	}
}
void GListTraverse(GList L) //���������L 
{
	if(!L)
	{
		cout<<"()";
	}
	else
	{
		if(L->tag==ATOM)
		{
			cout<<L->val.data;
		}
		else
		{
			cout<<"(";
			GLNode *p=L;
			while(p)
			{
				GListTraverse(p->val.hp);
				p=p->tp;
				if(p)
				{
					cout<<",";
				 } 
			}
			cout<<")";
		}
	}
	
}

void MarkList(GList M)  //�ǵݹ��㷨���� 
{
	GLNode *t=NULL, *p=M, *q;
	//tָ��p��ĸ���㣬 pָ��ǰ
	Status finished;
	finished=false;
	
	while(!finished)
	{ 
		
		while(p->mark==0)
		{
			//�����ͷһ·������������ԭ�ӣ��˳�ѭ��
			p->mark=1;//�˽���Ѿ�����
			q=p->val.hp;//qָ��p�ı�ͷ���߱�β
			if(q&&q->mark==0)
			{
				if(q->tag==0)
				{
					//qΪԭ�ӣ������
					q->mark=1;
					cout<<q->val.data<<",";
				}
				else
				{
					//����������±�����
					p->val.hp=t;
					p->tag=ATOM;
					t=p;
					p=q;
					//��ͷ��־�꣬��¼·���ķ���p��hp��ָ��t��p��tag��Ϊ0
				}
				
			}
				
		}
		q=p->tp;//qָ���ʱp�ı�β
		if(q&&q->mark==0)//�����β�ǿգ���δ���������������������β���ص�����whileѭ��
		{
			
			p->tp=t;
			t=p;
			p=q;
		}
		else
		{ //qΪ�ջ��Ѿ������������ �ֱ�ͷ���ݣ��ͱ�β����
			while(t&&t->tag==1)
			{//��β����,����˽��ı�ͷ�Ѿ���������᲻�ϱ�β����
				q=t;
				t=q->tp;
				q->tp=p;
				p=q;
			}
			if(!t)
			{
				
				finished=true;
			}
		
			else
			{
				//��ͷ���ݣ��ӱ�ͷ�������ף�Ȼ�����ϻ��ݣ����޸Ĵ�ʱp��tag�Է��ڱ�β����ʱ�����ף�
				q=t;
				t=q->val.hp;
				q->val.hp=p;
				p=q;
				p->tag=LIST;
			
			}
		}
	}
     
}

void showmenu()
{
	cout<<"***********************************\n";
	cout<<"    ��������ѡ��Ĳ�����\n"
	         <<"1.���������\n"
			 <<"2.������L�ĳ���\n"
			 <<"3.������L�����\n"
			 <<"4.���õݹ��㷨���������L\n"
			 <<"5.���ƹ����L�������M\n"
			 <<"6.������M�ĳ���\n"
			 <<"7.������M�����\n"
			 <<"8.���÷ǵݹ��㷨���������M\n"
			 <<"9.������L�ı�ͷ,������\n"
			 <<"10.������L�ı�β,������\n"
			 <<"0.�˳�\n";
	cout<<"************************************"<<endl;
	
	cout<<"����(0-10):";
	
}
			  

int main()
{
	 
	GList L;

	int i;
	showmenu();
	cin>>i;
	for(;i!=0;cin>>i)
	{
	
	switch(i)
	{
		
		case 0:
			break;
		case 1:
			cout<<"��������L"<<endl;
			CreateGList(L);
			DisplayGList(L);
			cout<<endl;
			cout<<"����(0-10):";
			break;
		case 2:
		    cout<<"��������L"<<endl;
			CreateGList(L);
			cout<<"�����L����Ϊ "<<LenthGList(L)<<endl;
			cout<<"����(0-10):";
			break;
		case 3:
			cout<<"��������L"<<endl;
			CreateGList(L);
			cout<<"��������Ϊ "<<DepthGList(L)<<endl;
			cout<<"����(0-10):";
			break;
		case 4:
			cout<<"��������L"<<endl;
			CreateGList(L);
			cout<<"�ݹ��㷨���������Ϊ"<<endl;
	        GListTraverse(L);
	        cout<<endl;
	        cout<<"����(0-10):";
	        break;
	    case 5:
	    	{
	    	cout<<"��������L"<<endl;
			CreateGList(L);
	    	GList M = GListCopy(L);
	        DisplayGList(M);
	        cout<<endl;
	        cout<<"����(0-10):";
	    }
	        break;
	    case 6:
	    	{
	    	cout<<"��������L"<<endl;
			CreateGList(L);
			
			GList M = GListCopy(L);
	    	cout<<"�����M����Ϊ "<<LenthGList1(M)<<endl;
	    	cout<<"����(0-10):";
	    }
			break;
		case 7:
			{
			cout<<"��������L"<<endl;
			CreateGList(L);
			
			GList M = GListCopy(L);
			cout<<"�����M���Ϊ "<<DepthGList1(M)<<endl;
			cout<<"����(0-10):";
		}
			break;
		case 8:
			{
			cout<<"��������L"<<endl;
			CreateGList(L);
			
			GList M = GListCopy(L);
			cout<<"�ǵݹ��㷨���������Ϊ\n";
	        MarkList(M);
	        cout<<endl;
	        cout<<"����(0-10):";
	    }
	        break;
	    case 9:
	    	{
			cout<<"��������L"<<endl;
			CreateGList(L);
	    	GList H = Head(L);
	        DisplayGList(H);
	        cout<<endl;
	        GListTraverse1(L);
	        cout<<endl;
	        cout<<"����(0-10):";
	    }
	        break;
	    case 10:
	    	{
			cout<<"��������L"<<endl;
			CreateGList(L);
	    	GList T = Tail(L);
	        DisplayGList(T);
	        cout<<endl;
	        GListTraverse2(L);
	        cout<<endl;
	        cout<<"����(0-10):";
	    }
	        break;   				
	}
}
	    
    return 0;
}
//((e),(a,(b,c,d)))
