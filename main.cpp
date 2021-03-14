#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

///bubble sort
void bubble_sort(int n, int v[]){
    for(int i=1;i<n;i++)
        for(int j=0;j<n-i;j++)
            if(v[j]>v[j+1])
                swap(v[j],v[j+1]);
}
///merge sort
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
///count sort
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
///radix sort
void radix_count(int n, int v[],int p, int base){
    int fr[base];
    for(int i=0;i<base;i++)
        fr[i]=0;
    for(int i=0;i<n;i++)
        fr[((v[i]>>p)&(base-1))]++;
    for(int i=1;i<base;i++)
        fr[i]+=fr[i-1];
    int aux[n];
    for(int i=n-1;i>=0;i--){
        fr[((v[i]>>p)&(base-1))]--;
        aux[fr[((v[i]>>p)&(base-1))]]=v[i];
    }
    for(int i=0;i<n;i++)
        v[i]=aux[i];
}
void radix_sort(int n,int v[]){
    int maxim=v[0];
    for(int i=1;i<n;i++){
        if(v[i]>maxim)
            maxim=v[i];
    }
    int base = 2;
    for(int p=0;(1<<p)<=maxim;p++){
        radix_count(n,v,p,base);
    }

}
///quick sort
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
void quick_sort(int st, int dr, int v[]){
    if(st<dr){
        int p=pivot(st, dr, v);
        int aux[dr+1];
        int l,r;
        l=st;
        r=dr;
        for(int i=st;i<=dr;i++){
            if(v[i]<p)
                aux[l++]=v[i];
            if(v[i]>p)
                aux[r--]=v[i];
        }
        for(int i=l;i<=r;i++)
            aux[i]=p;
        for(int i=st;i<=dr;i++)
            v[i]=aux[i];
        quick_sort(st,l-1,v);
        quick_sort(r+1,dr,v);
    }
}

int main(){
    int n[]={1, 2, 5,  10, 10000, 100000, 10000, 100000};
    int maxim[]={1000, 10, 10000, 10000000, 10000, 100000, 100000, 1000000};
    int ok=1;
    for(int i=0;i<=7;i++){
        cout<<"Testul numarul "<<i+1<<", unde "<<"n="<<n[i]<<" maxim="<<maxim[i]<<'\n'<<'\n';
        srand(time(0));
        int v[n[i]];
        int aux1[n[i]];
        int aux2[n[i]];

        for(int j=0;j<n[i];j++){
            v[j]=rand()%(maxim[i]);
            aux1[j]=v[j];
            aux2[j]=v[j];
        }

        auto time_start = high_resolution_clock::now();
        sort(aux1, aux1+n[i]);
        auto time_stop = high_resolution_clock::now();
        cout<<"Sort: "<<(duration_cast<microseconds>(time_stop - time_start)).count()<<'\n';

        ///bubble sort
        auto time_start1 = high_resolution_clock::now();
        bubble_sort(n[i], aux2);
        auto time_stop1 = high_resolution_clock::now();
        cout<<"bubble sort: "<<(duration_cast<microseconds>(time_stop1 - time_start1)).count()<<'\n';
        ok=1;
        for(int j=0;j<n[i];j++){
            if(aux1[j]!=aux2[j]){
                ok=0;
            }
            aux2[j]=v[j];
        }
        if(ok==1)
            cout<<"corect"<<'\n'<<'\n';

        ///merge sort
        auto time_start2 = high_resolution_clock::now();
        merge_sort(0,n[i]-1, aux2);
        auto time_stop2 = high_resolution_clock::now();
        cout<<"merge sort: "<<(duration_cast<microseconds>(time_stop2 - time_start2)).count()<<'\n';
        ok=1;
        for(int j=0;j<n[i];j++){
            if(aux1[j]!=aux2[j]){
                ok=0;
            }
            aux2[j]=v[j];
        }
        if(ok==1)
            cout<<"corect"<<'\n'<<'\n';

        ///count sort
        auto time_start3 = high_resolution_clock::now();
        count_sort(n[i], aux2);
        auto time_stop3 = high_resolution_clock::now();
        cout<<"count sort: "<<(duration_cast<microseconds>(time_stop3 - time_start3)).count()<<'\n';
        ok=1;
        for(int j=0;j<n[i];j++){
            if(aux1[j]!=aux2[j]){
                ok=0;
            }
            aux2[j]=v[j];
        }
        if(ok==1)
            cout<<"corect"<<'\n'<<'\n';

        ///radix sort
        auto time_start4 = high_resolution_clock::now();
        radix_sort(n[i], aux2);
        auto time_stop4 = high_resolution_clock::now();
        cout<<"radix sort: "<<(duration_cast<microseconds>(time_stop4 - time_start4)).count()<<'\n';
        ok=1;
        for(int j=0;j<n[i];j++){
            if(aux1[j]!=aux2[j]){
                ok=0;
            }
            aux2[j]=v[j];
        }
        if(ok==1)
            cout<<"corect"<<'\n'<<'\n';

        ///quick sort
        auto time_start5 = high_resolution_clock::now();
        quick_sort(0, n[i]-1, aux2);
        auto time_stop5 = high_resolution_clock::now();
        cout<<"quick sort: "<<(duration_cast<microseconds>(time_stop5 - time_start5)).count()<<'\n';
        ok=1;
        for(int j=0;j<n[i];j++){
            if(aux1[j]!=aux2[j]){
                ok=0;
            }
            aux2[j]=v[j];
        }
        if(ok==1)
            cout<<"corect"<<'\n'<<'\n';
    }
}
