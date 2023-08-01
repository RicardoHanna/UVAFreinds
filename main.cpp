#include<iostream>
using namespace std;
#include<vector>
#include<ctime>
#include <cmath>
#include <cstdlib>

class wQuickUnionUF{
	private:
		vector<int> id; // access to component id
		vector<int> sz; // size of component for roots
		int Nc;//nb of components
		int count;
	public:
		//initialize union-find data structure with N singleton objects (0 to N – 1)
		wQuickUnionUF(int N):id(N),sz(N){
			for(int i=0; i<N; i++) id[i] = i;
			for(int i=0; i<N; i++) sz[i] = 1;
			Nc = N;
			count = 0;
		}

		//are p and q in the same component?
		bool connected(int p, int q){return find(p) == find(q);}

		//component identifier for i (0 to N – 1)
		int find(int i){ // Follow links to find a root.
			count = 0;
			while(i != id[i])	{i = id[i]; count+=2;}
			return i;
		}
/*
		int findcomp(int i){
			// Follow links to find a root.
			while(i != id[i]){
				id[i] = id[id[i]];
				i = id[i];
			}
			return i;
		}
		*/
		//add connection between p and q
		void Union(int p, int q){
			int i = find(p);
			int j = find(q);
			if(i == j) return;
			if(sz[i] < sz[j]){ id[i] = j; sz[j] += sz[i];count++;}
			else             { id[j] = i; sz[i] += sz[j];count++;}

			Nc--;
		}

		int nbComp(){return Nc;};
		int Count(){return count;};
		void resetCount(){count = 0;};

};



int main(){
	int n=10000, p, q, k=0, nc, sum = 0, c=0;
	float aver;
	cout<<"Nb of nodes: "<<n<<endl;
	wQuickUnionUF uf(n);
	nc = uf.nbComp();
	while(nc!=1){ // Read pair to connect.
		p = rand() % n;
		q = rand() % n;
		k++;
		if(uf.connected(p,q)) continue; // Ignore if connected
		c++;
		uf.Union(p,q); // Combine components
		cout<<"Count: "<<uf.Count()<<endl;
		sum+=uf.Count();
		uf.resetCount();
		cout<<p<<" "<<q<<" now connected"<<endl;
		nc = uf.nbComp();
		if(nc==1)break;
	}
	cout<<"nb of pairs: "<<k<<endl;
	cout<<" "<<0.5*n*log(n)<<endl;
	cout<<"Average running time of union: "<<sum/c<<endl;
	cout<<log(n)/log(10)<<endl;

	return 0;
}
