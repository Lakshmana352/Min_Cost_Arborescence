#include <bits/stdc++.h>
using namespace std;

#define ull   unsigned long long int
#define ll   long long int

// void printedges(vector<vector<ll>> edges,ll m)
// {
//     for(ll i=0;i<m;i++) cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << " " << endl;
//     return;
// }

void printvec(vector<ll> v,ll n)
{
    for(ll i=0;i<n;i++) cout << v[i] << " ";
}

vector<vector<ll>> edmonds_algorithm(vector<vector<ll>> edges,ll n,ll s) 
{
    ll m = edges.size();
    vector<ll> y(n,1000000000),parent(n,-1);
    for(ll i=0;i<n;i++)
    {
        if(i+1!=s){
            for(ll j=0;j<m;j++)
            {
                if(edges[j][1]==i && y[i]>edges[j][2] && edges[j][0]!=edges[j][1]) {y[i] = edges[j][2];parent[i] = edges[j][0];} 
            }
            for(ll j=0;j<m;j++)
            {
                if(edges[j][1]==i && edges[j][0]!=edges[j][1]) edges[j][2] = edges[j][2] - y[i];
            }
        }
    }
    // printvec(parent);
    // printvec(y);
    //conforming whether there is a cycle or not..........................................//
    vector<ll> ind(n,-1),comp(n,-1);
    ll detect = 0;
    for(ll j=0;j<n;j++)
    {
        ll so = j;
        while(ind[so]==-1 && comp[so] != j && y[j]!=1000000000) {comp[so] = j;so = parent[so];}
        if(y[so]!=1000000000 && ind[so]==-1)
        {
            ll temp = parent[so];
            while(temp != so)
            {
                ind[temp] = detect;
                temp = parent[temp];
            }
            ind[temp] = detect;detect++;
        }
    }
    //conformation code completed.........................................................//

    //No circle then return the Edges.....................................................//
    if(detect == 0) {return edges;}
    // cout<< "In recursive" << endl;printedges(edges,m);

    //IF CIRCLE IS DETECTED IN T..........................................................//
    for(ll i=0;i<n;i++) if(ind[i]==-1) ind[i]=detect++;
    vector<vector<ll>> T = edges;
    for(ll i=0;i<m;i++)
    {
        T[i][0] = ind[edges[i][0]];
        T[i][1] = ind[edges[i][1]];
    }
    // printedges(T,m);
    // cout << "Before T runned" << endl;
    // printedges(T,m);
    T = edmonds_algorithm(T,n,ind[s]);
    // cout << "T inner runnered" << endl;
    // printedges(T,m);
    for(ll i=0;i<m;i++)
    {
        if(T[i][2] == 0) edges[i][2] = 0;
    }
    // printedges(edges,m);
    return edges;
}

// void answer(vector<vector<ll>> edges,ll n)
// {

// }


int main()
{
    ll tt;cin >> tt;
    while(tt--)
    {
        ll n,m,s;cin >> n >> m >> s;
        vector<vector<ll>> edges,ans;
        for(ll i=0;i<m;i++)
        {
            ll a,b,r;cin >> a >> b >> r;
            vector<ll> v = {a-1,b-1,r};
            edges.push_back(v);
        }

        ans = edmonds_algorithm(edges,n,s);
        // map<ll,vector<ll>> mm;
        // for(ll i=0;i<m;i++)
        // {
        //     vector<ll> ind(n,0);
        //     if(ans[i][2] == 0)
        //     {
        //         if(ind[ans[i][0]]==0)
        //         {
        //             vector<ll> v = {ans[i][1]};
        //             mm[ans[i][0]]=v;
        //             ind[ans[i][0]]==1;
        //         }
        //         else mm[ans[i][0]].push_back(ans[i][1]);
        //     }
        // }
        queue<ll> q;q.push(s-1);
        vector<ll> ind(n,0);
        while(!q.empty())
        {
            ll temp = q.front();q.pop();
            ind[temp] = 1;
            // for(ll i=0;i<siz;i++)
            // {
                
            // }
            for(ll i=0;i<m;i++)
            {
                if(ans[i][0] == temp && ans[i][1] != temp && ans[i][2] == 0)
                {
                    if(ind[ans[i][1]] == 1) ans[i][2] = -1;
                    else q.push(ans[i][1]);
                }
            }
        }

        vector<ll> parent(n,-1),dis(n,-1);
        ll mincost = 0;
        for(ll i=0;i<m;i++)
        {
            if(ans[i][2] == 0)
            {
                parent[ans[i][1]] = ans[i][0]+1;dis[ans[i][1]] = edges[i][2];
                mincost+=edges[i][2];
            }
        }

        cout << mincost << " ";
        vector<ll> mindist(n,0);
        for(ll i=0;i<n;i++)
        {
            ll source = i;
            while(source!=s-1)
            {
                mindist[i]+=dis[source];
                source = parent[source]-1;
            }
        }

        parent[s-1] = 0;
        // ll source = s;
        // vector<ll> ind(n,0);
        // for(ll i=0;i<n;i++)
        // {

        // }
        // answer(ans,n);
        // printedges(ans,m);
        printvec(mindist,n);cout << "# ";
        printvec(parent,n);cout << endl;
    }
    return 0;
}
