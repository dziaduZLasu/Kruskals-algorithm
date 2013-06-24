#include<algorithm>
#include<cstdio>
using namespace std;

int tab[7000];

int ile[7000]; // 7000 - to liczba wszystkich elementów UWAGA NA LIMIT
 
//int Find(int a) { return (tab[a]==a) ? a : (tab[a] = Find(tab[a])); }
int Find(int a)
{
	if (tab[a]==a) return a; // jesli a jest reprezentantem zbioru zawierajacego a to zwracamy a
	// W przeciwnym wypadku pytamy sie kto jest reprezentantem zbioru zawierajacego tab[a], bo w koncu to ten sam zbior :
	int fa = Find(tab[a]);
	tab[a] = fa; // zaktualizujmy wartosc tab[a] na nowszą!, w razie czego, gdyby ktoś się pytał kiedyś jeszcze raz o find(a)
	return fa;
}
bool UnionOp(int a, int b)
{
	int fa = Find(a); // szukaj reprezentanta zbioru zawierającego element 'a'
	int fb = Find(b); // szukaj reprezentanta zbioru zawierającego element 'b'
 
	if (fa==fb) return false; // nie trzeba nic łączyć
	if (ile[fa] <= ile[fb])
	{
		ile[fb] += ile[fa];
		tab[fa] = fb;
	}
	else
	{
		ile[fa] += ile[fb];
		tab[fb] = fa;
	}
	return true;
}
 
pair< int,pair<int,int> > Edges[9]; // tablica krawędzi do posortowania
 
int main(void)
{
	/*
	Na poczatku mamy n zbiorów rozłącznych : każdy ma jeden elelement
	{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}
	*/
	int n, m, a,b,c,cost=0;
	FILE *input= fopen("graph.txt", "r+");
	fscanf(input, "%d %d", &n, &m);
	//scanf("%d %d", &n, &m);
	for (int i=0; i<n; i++)
	{
		tab[i] = i; //	reprezentantem zbioru zawierającego element
		//		'i' jest np 'i' (nikt inny być nie może :-)
		ile[i] = 1; //	jeden element; chyba jasne, co nie?
	}
	for (int i=0; i<m; i++)
	{
		fscanf(input, "%d %d %d", &a, &b, &c);a--; b--;;
		Edges[i] = make_pair( c, make_pair(a,b) );
	}
	sort(Edges, Edges+m); // sortujemy listę krawędzi wg kosztów
	printf("Drzewo złożone jest z następujących krawędzi:\n");
	printf("Tablica reprezentantow\n");
	for (int i=0; i<n+4; i++){
		
	printf("%d\t", tab[i]);	
	}
	printf("\n");
	
	for (int i=0; i<m; i++)
		if (UnionOp(Edges[i].second.first,Edges[i].second.second) ) // właściwie cała sprawa UNION FIND
		/*
		 * Algorytm polega na łączeniu wielu poddrzew w jedno za pomocą krawędzi o najmniejszej wadze.
		 *  W rezultacie powstałe drzewo będzie minimalne. 
		 * Na początek należy posortować wszystkie krawędzie w porządku niemalejącym.
		 *  Po tej czynności można przystąpić do tworzenia drzewa. 
		 * Proces ten nazywa się rozrastaniem lasu drzew. 
		 * Wybieramy krawędzie o najmniejszej wadze i jeśli wybrana krawędź należy do dwóch różnych drzew należy je scalić (dodać do lasu).
		 *  Krawędzie wybieramy tak długo, aż wszystkie wierzchołki nie będą należały do jednego drzewa.
		 * */
		
		{
			cost += Edges[i].first;
			// krawędz drzewa : Edges[i].second.first -- Edges[i].second.second
			printf("%d -- %d # koszt %d\n", Edges[i].second.first+1, Edges[i].second.second+1,Edges[i].first);
		}
		for (int i=0; i<n+4; i++){
		
	printf("%d\t", tab[i]);	
	}
	printf("\n");
	printf("[KRUSKAL]\nKoszt minimalnego drzewa spinającego wynosi %d\n", cost);
	return 0;
}
