#include <iostream>
#include<string>
#include <vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<limits>
#include<cmath>
#include<ctime>
#define noOfTest 10
#define noOfInt 10000
using namespace std;
class minMaxHeap //Would be trivial using heaps in STL vector
{
private:
    int *data;
    int heapSize,maxSize;
    bool isMinHeap;
public:
    int getSize()
    {
        return heapSize;
    }

    minMaxHeap(bool isMinHeap)
    {
        maxSize=100;
        data=new int[maxSize]; //free up using destructor
        this->isMinHeap=isMinHeap;
        heapSize=0;
    }

    ~minMaxHeap()
    {
        delete[] data;
    }
    int parent(int i)
    {
        return (int)((i-1)/2);
    }

    int left(int i)
    {
        return 2*i+1;
    }

    int right(int i)
    {
        return 2*i+2;
    }

    void minHeapify(int i)
    {
        int smallest=i;
        if(left(i)<heapSize&&data[smallest]>data[left(i)])
            smallest=left(i);
        if (right(i)<heapSize&&data[smallest]>data[right(i)])
            smallest=right(i);
        if(smallest!=i)
        {
            swap(data[i],data[smallest]);
            minHeapify(smallest);
        }
    }

    void maxHeapify(int i)
    {
        int largest=i;
        if(left(i)<heapSize&&data[largest]<data[left(i)])
            largest=left(i);
        if (right(i)<heapSize&&data[largest]<data[right(i)])
            largest=right(i);
        if(largest!=i)
        {
            swap(data[i],data[largest]);
            maxHeapify(largest);
        }
    }

    void increaseCapacity()
    {
        maxSize*=2;
        int *temp=new int[maxSize];
        for(int i=0; i<heapSize; i++)
        {
            temp[i]=data[i];
        }
        delete []data;
        data=temp;
    }

    void insertInHeap(int inp)
    {
        if(maxSize-3<heapSize)
        {
            increaseCapacity();
        }
        data[heapSize]=inp;
        int ci=heapSize;
        heapSize++;
        if(isMinHeap)
        {
            while(ci>0&&data[parent(ci)]>data[ci])
            {
                swap(data[ci],data[parent(ci)]);
                ci=parent(ci);
            }
        }
        else
        {
            while(ci>0&&data[parent(ci)]<data[ci])
            {
                swap(data[ci],data[parent(ci)]);
                ci=parent(ci);
            }
        }
    }

    int get()
    {
        if(heapSize>0)
            return data[0];
        else
            cout<<"BUFFER UNDERFLOW"<<endl;
        return 0;
    }

    bool working()
    {
        for(int i=0; i<100; i++)
        {
            insertInHeap(rand()%2000);
        }
        bool ans=true;
        for(int i=0; i<100; i++)
        {
            if(isMinHeap)
            {
                if(left(i)<heapSize)
                {
                    if(data[left(i)]>=data[i])
                    {
                        ans&=true;
                    }
                    else
                    {
                        ans&=false;
                    }
                }
                if(right(i)<heapSize)
                {
                    if(data[right(i)]>=data[i])
                    {
                        ans&=true;
                    }
                    else
                    {
                        ans&=false;
                    }
                }
            }
            else
            {
                if(left(i)<heapSize)
                {
                    if(data[left(i)]<=data[i])
                    {
                        ans&=true;
                    }
                    else
                    {
                        ans&=false;
                    }
                }
                if(right(i)<heapSize)
                {
                    if(data[right(i)]<=data[i])
                    {
                        ans&=true;
                    }
                    else
                    {
                        ans&=false;
                    }
                }
            }
        }
        for(int i=0; i<100; i++)
            pop();
        return ans;
    }

    int pop()
    {
        if(heapSize>0)
        {
            int min_max=data[0];
            swap(data[heapSize-1],data[0]);
            heapSize--;
            if(isMinHeap)
                minHeapify(0);
            else
                maxHeapify(0);
            return min_max;
        }
        else
            cout<<"BUFFER UNDERFLOW"<<endl;
        return 0;
    }

    void printHeap()
    {
        cout<< (isMinHeap ? "MinHeap- ":"MaxHeap- ");
        for(int i=0; i<heapSize; i++)
            cout<<data[i]<<" ";
        cout<<endl;
    }
};

void generate_testcases(int noOfCases,int maxn,int maxval)
{
    ofstream test,ans;
    string t;
    int a;
    for(int k=0; k<noOfCases; k++)
    {
        t="test/testcase"+to_string(k)+".txt";
        test.open(t,ios::out|ios::trunc);
        t="test/ans"+to_string(k)+".txt";
        ans.open(t,ios::out|ios::trunc);
        int N=1+rand()%maxn;
        test<<N<<endl;
        vector<int> v;
        for(int i=0; i<N; i++)
        {
            a=2*(rand()%maxval)-maxval;
            v.push_back(a);
            test<<a<<endl;
            sort(v.begin(),v.end());
            if(v.size()%2==1)
            {
                ans<<fixed<<setprecision(2)<<v[v.size()/2]/1.0<<endl;
            }
            else
            {
                ans<<fixed<<setprecision(2)<<(v[v.size()/2]+v[v.size()/2-1])/2.0<<endl;
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
//    generate_testcases(noOfTest,noOfInt,9999); //VERY SLOW

//    cout<<minHeap.working()<<" "<<maxHeap.working()<<endl;
    for(int testno=0; testno<noOfTest; testno++)
    {
        minMaxHeap minHeap(true);
        minMaxHeap maxHeap(false);
        string t;
        t="test/testcase"+to_string(testno)+".txt";
        ifstream test;
        test.open(t);
        ofstream ans;
        t="test/myans"+to_string(testno)+".txt";
        ans.open(t,ios::trunc);
        int a,N;
        test>>N;
        for(int i=0; i<N; i++)
        {
            test>>a;
            if(minHeap.getSize()==0)
            {
                minHeap.insertInHeap(a);
                ans<<fixed<<setprecision(2)<<a/1.0<<endl;
                continue;
            }
            if(a<minHeap.get())
            {
                maxHeap.insertInHeap(a);
            }
            else
            {
                minHeap.insertInHeap(a);
            }
            if(minHeap.getSize()>maxHeap.getSize()+1)
            {
                maxHeap.insertInHeap(minHeap.pop());
            }
            if(minHeap.getSize()+1<maxHeap.getSize())
            {
                minHeap.insertInHeap(maxHeap.pop());
            }
//        minHeap.printHeap();
//        maxHeap.printHeap();
            if((minHeap.getSize()+maxHeap.getSize())%2==0)
            {
                ans<<fixed<<setprecision(2)<<((minHeap.get()+maxHeap.get())/2.0)<<endl;
            }
            else
            {
                ans<<fixed<<setprecision(2)<<((minHeap.getSize()>maxHeap.getSize()) ? minHeap.get()/1.0:maxHeap.get()/1.0)<<endl;
            }

        }
        test.close();
        ans.close();
        compareAns(testno);
    }
    return 0;
}
