#include <iostream>
using namespace std;

void    pol_print(bool poly[], int n);
bool    *pol_cut(bool *A, int *m);
bool    *add(bool A[], bool B[], int m, int n);
bool    *multiply(bool A[], bool B[], int m, int n);
bool    *polyn_compos(bool *A, bool *B, int m, int n);
bool    *pol_pow(bool *A, int m, int power);
bool    *polyn_compos(bool *A, bool *B, int m, int n);

int main()
{
	bool A[] = {1, 1, 0, 0, 1, 0, 1};
	bool B[] = {1, 0, 1};
	int m = sizeof(A)/sizeof(A[0]);
	int n = sizeof(B)/sizeof(B[0]);
	int t;
    cout<<m<<endl<<n<<endl;
    pol_cut(A, &m);
    pol_cut(B, &n);
	cout << "First polynomial \n f(x) = ";
	pol_print(A, m);
	cout <<endl<< "Second polynomial \n g(x) = ";
	pol_print(B, n);
	t = (m-1) * (n-1) + 1;
	cout <<endl<< "Composition of polynomials \n f(g(x)) = ";
    pol_print(polyn_compos(A, B, m, n), t);
	return (0);
}



bool* add(bool A[], bool B[], int m, int n)
{
	int size = max(m, n);
	bool* sum = new bool[size];

	for (int i = 0; i < m; i++)
		sum[i] = A[i];

	for (int i = 0; i < n; i++)
		sum[i] = sum[i] ^ B[i];
	return (sum);
}

bool *multiply(bool A[], bool B[], int m, int n)
{
    bool *prod = new bool[m+n-1];

    for (int i = 0; i<m+n-1; i++)
	    prod[i] = 0;
    for (int i=0; i<m; i++)
    {
	    for (int j=0; j<n; j++)
		    prod[i+j] = prod[i+j] ^ (A[i] && B[j]);
    }
    return (prod);
}

void pol_print(bool poly[], int n)
{
	for (int i=0; i<n; i++)
    {
        if (poly[i] != 0)
        {
        if(i == 0)
            cout << poly[i];
        if (i != 0)
            cout << "x^" << i ;
        if (i != n-1)
            cout << " + ";
        }
    }
	cout << "\n";
}

bool*   pol_cut(bool *A, int *m)
{
    int new_size;
    int index;

    new_size = 0;
    index = 0;
    while (*m-index)
    {
        if (A[index] == 1)
            new_size = index+1;
        ++index;
    }
    *m = new_size;
    return (A);
}

bool    *pol_pow(bool *A, int m, int power)
{
    int i = 0;
    int size = ((m-1) * power) + 1;
    bool *result = new bool[size];

    while (size - i)
    {
        if (m > i)
            result [i] = A[i];
        else
            result[i] = 0;
        ++i;
    }
    i = 0;
    while (power - i - 1 > 0)
    {
        result = multiply(result, A, size, m);
        ++i;
    }
    return (result);
}

bool    *polyn_compos(bool *A, bool *B, int m, int n)
{
    int size;
    size = (m-1) * (n - 1) + 1;
    bool *compos = new bool[size];
    for (int i = 0; i < m; ++i)
    {
        if (A[i])
            compos = add(compos, pol_pow(B, n, i), size, (n-1)*i+1);
    }
    return (compos);
}




