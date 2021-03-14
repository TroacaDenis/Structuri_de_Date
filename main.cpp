#include<iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
///1
void bubble_sort(int n, int v[]){
    for(int i=1;i<n;i++)
        for(int j=0;j<n-i;j++)
            if(v[j]>v[j+1])
                swap(v[j],v[j+1]);
}
///2
void interclasare(int st,int mij, int dr, int v[]){
    int k,i,j,n,m,aux[dr];
    n=mij;
    m=dr;
    i=st;
    j=mij+1;
    k=st;
    while(i<=n && j<=m){
        if(v[i]<v[j])
            aux[k++]=v[i++];
        else
           aux[k++]=v[j++];
    }
    while(i<=n)
        aux[k++]=v[i++];
    while(j<=m)
        aux[k++]=v[j++];
    for(i=st;i<=dr;i++)
        v[i]=aux[i];

}
void merge_sort(int st, int dr, int v[]){
    int mij=(st+dr)/2;
    if(st!=dr){
        merge_sort(st,mij,v);
        merge_sort(mij+1,dr,v);
        interclasare(st,mij,dr,v);
    }

}
///3
void count_sort(int n, int v[]){
    int maxim=v[0];
    for(int i=1;i<n;i++)
        if(v[i]>maxim)
            maxim=v[i];
    int fr[maxim+1];
    for(int i=0;i<=maxim;i++)
        fr[i]=0;
    for(int i=0;i<n;i++)
        fr[v[i]]++;
    for(int i=1;i<=maxim;i++)
        fr[i]+=fr[i-1];
    int aux[n];
    for(int i=0;i<n;i++){
        fr[v[i]]--;
        aux[fr[v[i]]]=v[i];
    }
    for(int i=0;i<n;i++)
        v[i]=aux[i];
}
///4
void counting_sort(int n, int v[],int p){
    int maxim=0;
    for(int i=1;i<n;i++)
        if(v[i]/p%10>maxim)
            maxim=v[i]/p%10;

    int fr[maxim+1];
    for(int i=0;i<=maxim;i++)
        fr[i]=0;
    for(int i=0;i<n;i++)
        fr[v[i]/p%10]++;
    for(int i=1;i<=maxim;i++)
        fr[i]+=fr[i-1];
    int aux[n];
    for(int i=n-1;i>=0;i--){
        fr[v[i]/p%10]--;
        aux[fr[v[i]/p%10]]=v[i];
    }
    for(int i=0;i<n;i++)
        v[i]=aux[i];
}
void radix_sort(int n,int v[]){
    int maxim=v[0];
    for(int i=1;i<n;i++)
        if(v[i]>maxim)
            maxim=v[i];
    for(int p=1;p<=maxim;p=p*10)
        counting_sort(n,v,p);

}
///5
int pivot(int st, int dr, int v[]){
    srand(time(0));
    int a,b,c,k;
    k=dr-st+1;
    a=rand()%k+st;
    b=rand()%k+st;
    c=rand()%k+st;
    if(v[a]>v[b]){
        if(v[a]<v[c])
            return v[a];
        if(v[b]>v[c])
            return v[b];
        return v[c];
    }
    if(v[b]<v[c])
        return v[b];
    if(v[a]>v[c])
        return v[a];
    return v[c];
}
int partition(int st, int dr, int p, int v[]){
    while(st<dr){
        while(v[st]<p)
            st++;
        while(v[dr]>p)
            dr--;
        if(st<dr)
            swap(v[st],v[dr]);
    }
    return st;
}
void quick_sort(int st, int dr, int v[]){
    if(st<dr){
        int p=v[(st+dr)/2];
        ///int p=pivot(st, dr, v);
        int k=partition(st, dr, p, v);
        quick_sort(st,k-1,v);
        quick_sort(k+1,dr,v);
    }
}

int main(){
    int n,k,maxim,v[100001];
    time_t time_start,time_stop;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>v[i];
    quick_sort(0,n-1,v);
    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";
    /*cin>>k;
    for(int i=1;i<=k;i++){
        cin>>n>>maxim;
        cout<<"n="<<n<<" maxim="<<maxim<<'\n';
        srand(time(0));
        ///bubble sort
        for(i=0;i<n;i++){
            v[i]=rand()%(maxim+1);
        }
            time_start=time();
            bubble_sort(n,v);
            time_stop=time();
            cout<<"bubble sort: "<<time_stop-time_start<<'\n';
        ///merge sort
        for(i=0;i<n;i++){
            v[i]=rand()%(maxim+1);
        }
            time_start=time();
            merge_sort(0,n-1,v);
            time_stop=time();
            cout<<"merge sort: "<<time_stop-time_start<<'\n';
        ///count sort
        for(i=0;i<n;i++){
            v[i]=rand()%(maxim+1);
        }
            time_start=time();
            count_sort(n,v);
            time_stop=time();
            cout<<"count sort: "<<time_stop-time_start<<'\n';
        ///radix sort
        for(i=0;i<n;i++){
            v[i]=rand()%(maxim+1);
        }
            time_start=time();
            radix_sort(n,v);
            time_stop=time();
            cout<<"radix sort: "<<time_stop-time_start<<'\n';
        ///quick sort
        for(i=0;i<n;i++){
            v[i]=rand()%(maxim+1);
        }
            time_start=time();
            quick_sort(0,n-1,v);
            time_stop=time();
            cout<<"quick sort: "<<time_stop-time_start<<'\n';
    }
    */
}
