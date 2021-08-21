#include<bits/stdc++.h>

using namespace std;


#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define FOR(a, c) for (int(a) = 0; (a) < (c); (a)++)
#define FORL(a, b, c) for (int(a) = (b); (a) <= (c); (a)++)
#define FORR(a, b, c) for (int(a) = (b); (a) >= (c); (a)--)
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define F first
#define S second
#define max(a, b) (a < b ? b : a)
#define min(a, b) ((a > b) ? b : a)

typedef vector<int> vi;
typedef pair<int, int> pi;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.F); cerr << ","; _print(p.S); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

template <typename V> 
class mapNode{
public:
	string key;
	V data;
	mapNode* next;

	mapNode(string key, V data){
		this->key = key;
		this->data = data;
		next = NULL;
	}

	~mapNode(){
		delete next;
	}

};

template <typename V> 
class ourMap{
mapNode<V>** buckets;
int count;
int numBuckets;

public:
	ourMap(){
		count = 0;
		numBuckets = 0;
		buckets = new mapNode<V>* [numBuckets];
		FOR(i,numBuckets){
			buckets[i] = NULL;
		}
	}

	~ourMap(){
		FOR(i,numBuckets){
			delete buckets[i];
		}
		delete [] buckets; // dynamically created Array
	}


private:
	int getBucketIndex( string key){
		int hashCode = 0;

		int baseP = 1;

		FORR(i,key.length()-1,0){
			hashCode += key[i]*baseP;
			hashCode %= numBuckets;

			baseP *= 37;
			baseP %= numBuckets;
		}

		return hashCode%numBuckets;
	}

	void rehash(){
		mapNode<V> **temp = buckets;
		buckets = new mapNode<V>* [2*numBuckets];
		int oldNumBuckets = numBuckets;
		numBuckets *= 2;

		FOR(i,numBuckets){
			buckets[i] = NULL;
		}

		FOR( i, oldNumBuckets){
			mapNode<V>* head = temp[i];
			while(head != NULL){

				string key = head->key;
				V data = head->data;
				insert(key,data);
				head = head->next;
			}
		}

		FOR(i,oldNumBuckets){
			mapNode<V>* head = temp[i];
			delete head;
		}

		delete [] temp;
	}

public:

	/// To insert Data
	void insert( string key, V data){
		int bucketIndex = getBucketIndex(key);

		mapNode<V> *head = buckets[bucketIndex];
		while( head != NULL){

			if( head->key == key){
				head->data = data;
				return;
			}
			head = head->next;
		}

		mapNode<V> *node = new mapNode<V>(key,data);
		node->next = buckets[bucketIndex];
		buckets[bucketIndex] = node;
		count++;

		double loadFactor = (1.0*count) / numBuckets;
		if( loadFactor > 0.7){
			rehash();
		}
	}

	///// To Delete Data
	V remove( string key){
		int bucketIndex = getBucketIndex(key);
		mapNode<V> *head = buckets[bucketIndex];
		mapNode<V> *prev = NULL;
		while(head != NULL){

			if( head->key == key){

				if( prev == NULL){
					buckets[bucketIndex] = head->next;
				}else{
					prev->next = head->next;
				}

				V data = head->data;
				head->next = NULL;
				delete head;
				count--;
				return data;
			}


			prev = head;
			head = head->next;
		}
		return 0;
	}

	//// For Size
	int size(){
		return count;
	}

	///// To Access the Data Using Key
	V getData( string key){
		int bucketIndex = getBucketIndex(key);
		mapNode<V> *head = buckets[bucketIndex];
		while(head != NULL){

			if( head->key == key){
				return head->data;
			}

			head = head->next;
		}

		return 0;
	}

};


int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
fastio();
 
	ourMap<int> mp;
	FOR(i,10){
		char c = '0'+ i;
		string key = "abc" + c;
		int data = i + 1;
		mp.insert(key,data);
	}

	cout<<"\t SIZE : "<< mp.size()<<"\n" ;
return 0;

}
