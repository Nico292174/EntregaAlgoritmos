class MinHeap
{
private:
    
    int largo;
    int primeroLibre;

    void swap(int a, int b)
    {
        char aux = this->vec[a];
        this->vec[a] = this->vec[b];
        this->vec[b] = aux;
    }

    int padre(int pos)
    {
        return (pos / 2);
    }

    int hijoDer(int pos)
    {
        return (pos * 2 + 1);
    }

    int hijoIzq(int pos)
    {
        return (pos * 2);
    }

    void hundir(int pos)
    {
        if (hijoDer(pos) < this->primeroLibre && hijoIzq(pos) < this->primeroLibre)
        {
            char menor;
            if (this->vec[hijoDer(pos)] < this->vec[hijoIzq(pos)])
            {
                menor = hijoDer(pos);
            }
            else
            {
                menor = hijoIzq(pos);
            }
            if (this->vec[menor] < this->vec[pos])
            {
                swap(pos, menor);
                hundir(menor);
            }
        }
        else if (hijoIzq(pos) < this->primeroLibre && this->vec[hijoIzq(pos)] < this->vec[pos])
        {
            swap(pos, hijoIzq(pos));
            hundir(hijoIzq(pos));
        }
    }
    void flotar(int pos)
    {
        if (pos > 1)
        { // Para que no sea la raiz
            if (this->vec[pos] < this->vec[padre(pos)])
            {
                swap(pos, padre(pos));
                flotar(padre(pos));
            }
        }
    }

public:
    // Constructor
    char *vec;
    MinHeap(int tamanio)
    {
        this->vec = new char[tamanio + 1]();
        this->largo = tamanio + 1;
        this->primeroLibre = 1;
    }
    bool vacio()
    {
        if (this->primeroLibre == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool lleno()
    {
        if (this->primeroLibre >= this->largo + 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void insertar(char unNumero)
    {
        int posInsertar = this->primeroLibre;
        if (posInsertar <= this->largo)
        {
            this->vec[posInsertar] = unNumero;
            flotar(posInsertar);
            this->primeroLibre++;
        }
    }

    int tope()
    {
        char ret = this->vec[1];
        this->vec[1] = this->vec[primeroLibre - 1];
        hundir(1);
        this->primeroLibre--;
        return ret;
    }

    void destruir()
    {
        delete[] this->vec;
    }
};