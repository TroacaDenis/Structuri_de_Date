#include<iostream>
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
    for(int p=1;p<=maxim;p=p*10){
        counting_sort(n,v,p);

}

int main(){
    int n,v[100];
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>v[i];
    radix_sort(n,v);
    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";
}
