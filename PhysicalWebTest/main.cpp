#include <iostream>
#include <queue>
#include <fstream>
#define noOfTest 10
#define noOfInt 100000
using namespace std;

template <class T> class queueImp //would be trivial using STL
{
private:
    class node
    {
    public:
        T data;
        node *next;
    };

    node *head,*tail;
    int siz;

public:
    queueImp()
    {
        head=tail=0;
        siz=0;
    }

    ~queueImp()
    {
        node *temp;
        while(head!=0)
        {
            temp=head;
            head=head->next;
            delete temp;
        }
    }

    void put(T inp)
    {
        node *temp=new node;
        temp->data=inp;
        temp->next=0;
        if(siz==0)
        {
            siz++;
            head=tail=temp;
            return;
        }
        siz++;
        tail->next=temp;
        tail=temp;
        return;
    }

    T pop()
    {
        if(siz==0)
        {
            cout<<"BUFFER UNDERFLOW"<<endl;
            return 0;
            //raise error
        }
        siz--;
        T temp=head->data;
        node *t;
        t=head;
        head=head->next;
        delete t; //after all elements deleted can we push?
        return temp;
    }

    T peek()
    {
        if(siz==0)
        {
            cout<<"BUFFER UNDERFLOW"<<endl;
            return 0;
        }
        return head->data;
    }

};

void generate_testcases(int noOfCases,int maxn,int maxval)
{
    ofstream test,ans;
    string t;
    int op,a;
    for(int k=0; k<noOfCases; k++)
    {
        t="test/testcase"+to_string(k)+".txt";
        test.open(t,ios::out|ios::trunc);
        t="test/ans"+to_string(k)+".txt";
        ans.open(t,ios::out|ios::trunc);
        queue<int> q;
        int N=1+rand()%maxn;
        test<<N<<endl;
        for(int i=0; i<N; i++)
        {
            op=1+(rand()%3);
            if(op==2)
            {
                if(q.empty())
                {
                    op=1;
                }
                else
                {
                    test<<op<<endl;
                    q.pop();
                }
            }

            if(op==3)
            {
                if(q.empty())
                {
                    op=1;
                }
                else
                {
                    test<<op<<endl;
                    ans<<q.front()<<endl;
                }
            }

            if(op==1)
            {
                test<<op;
                a=2*(rand()%maxval)-maxval;
                test<<" "<<a<<endl;
                q.push(a);
            }
        }
        test.close();
        ans.close();
    }
    cout<<"Generated "<<noOfCases<<" cases"<<endl;
}


void compareAns(int no)
{
    ifstream ans,myans;
    string t;
    t="test/ans"+to_string(no)+".txt";
    ans.open(t);
    t="test/myans"+to_string(no)+".txt";
    myans.open(t);
    string s1,s2;
    while(!ans.eof())
    {
        ans>>s1;
        myans>>s2;
        if(s1!=s2)
        {
            cout<<"TestCase "<<no<<" failed"<<endl;
            return;
        }
    }
    cout<<"TestCase "<<no<<" passed"<<endl;
    myans.close();
    ans.close();
}

int main()
{
 //   generate_testcases(noOfTest,noOfInt,10);

    for(int testno=0; testno<noOfTest; testno++)
    {
        string t;
        t="test/testcase"+to_string(testno)+".txt";
        ifstream test;
        test.open(t);
        ofstream ans;
        t="test/myans"+to_string(testno)+".txt";
        ans.open(t,ios::trunc);
        queueImp<int> q;
        int no,a,b;
        test>>no;
        for(int i=0; i<no; i++)
        {
            test>>a;
            if(a==1)
            {
                test>>b;
                q.put(b);
            }
            else if(a==2)
            {
                q.pop();
            }
            else if(a==3)
            {
                ans<<q.peek()<<endl;
            }
        }
        compareAns(testno);
    }
    return 0;
}
