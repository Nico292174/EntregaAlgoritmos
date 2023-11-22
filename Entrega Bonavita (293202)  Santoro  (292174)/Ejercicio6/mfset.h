
class MFSet
{
    int *altura, *padre, n;

public:
    MFSet(int n)
    {
        padre = new int[n];
        altura = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet()
    {
        for (int i = 0; i < n; i++)
        {
            padre[i] = -1;
            altura[i] = 0;
        }
    }

    int find(int x)
    {
        if (padre[x] == -1)
        {
            return x;
        }
        return padre[x] = find(padre[x]);
    }

    void merge(int x, int y)
    {
        int xset = find(x);
        int yset = find(y);

        if (xset == yset)
        {
            return;
        }

        if (altura[xset] < altura[yset])
        {
            padre[xset] = yset;
        }

        else if (altura[xset] > altura[yset])
        {
            padre[yset] = xset;
        }

        else
        {
            padre[yset] = xset;
            altura[xset] = altura[xset] + 1;
        }
    }

    void destruir()
    {
        delete[] padre;
        delete[] altura;
    }
};