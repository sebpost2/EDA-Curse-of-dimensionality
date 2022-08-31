#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>


struct euclidean {
    int vectors = 0, data = 0;
    std::vector<int>* arr;
    std::vector<std::pair<int, unsigned int>> total;

    euclidean() {}

    //crea v vectores con d datos generados al azar.
    void resize(int v, int d) {
        vectors = v;
        data = d;
        arr = new std::vector<int>[vectors];
        srand((unsigned)time(0));
        for (int i=0; i<vectors; i++){
            arr[i] = std::vector<int>(d);
            std::generate(arr[i].begin(), arr[i].end(), rand);
        }
    }

    //exporta los datos a un txt para luego ingresarlos a un excel
    void a_txt() {
        std::ofstream out;
        out.open("datos/resultados" + std::to_string(vectors/1000) +"k"+std::to_string(data)+"d.txt");
        for (auto i : total) {
            out << i.first << ", " << i.second << std::endl;
        }
        out.close();
    }

    //saca las distancias del primer vector con todos los otros vectores.
    void distances() {
        int n_size = vectors;
        int* A = new int[n_size];
        int count = 1, size = 0;
        //distancias con el primer vector y todos los demas
        for (int i = 1; i < n_size; i++) {
            A[i - 1] = dist(arr[0], arr[i]);
        }
        std::sort(A, A + n_size);
        /*encuentro el nuevo size de mi vector de pares que tendra
        el valor del dato y sus repiticiones*/
        for (int i = 1; i < n_size; i++) {
            if (A[i] == A[i - 1])
                continue;
            size++;
        }
        /*creo mi vector de pares y empiezo a buscar las repeticiones
        de las distancias*/
        std::vector<std::pair<int, unsigned int>> DV(size);
        size = 0;
        for (int i = 1; i < n_size; i++) {
            if (A[i] == A[i - 1])
                continue;
            for (int j = i + 1; j < n_size; j++) {
                if (A[i] == A[j]) {
                    count++;
                }
                else {
                    break;
                }
            }
            DV[size].first = A[i];
            DV[size++].second = count;
            count = 1;
        }
        std::sort(DV.begin(), DV.end());
        //printpair(DV);
        total = DV;
        delete[] A;
    
    }

    int dist(std::vector<int>A, std::vector<int>B) {
        int i;
        long long sum=0;
        for (i = 0; i < A.size() || i < B.size(); i++) {
            sum += (A[i] - B[i]) * (A[i] - B[i]);
        }
        return int(sqrt(sum));
    }

    //imprime un vector de pares(int, unsigned int)
    void printpair(std::vector<std::pair<int, unsigned int>> A) {
        for (auto i : A) {
            std::cout << "number: " << i.first << " | count: " << i.second << std::endl;
        }
    }

    //imprime un array(int)
    void printarr(int* A) {
        std::cout << "| ";
        for (int i = 0; i < vectors; i++) {
            std::cout << A[i] << " | ";
        }
        std::cout << std::endl;
    }

    //imprime un vector(int)
    void printvec(std::vector<int> A) {
        std::cout << "| ";
        for (auto i : A) {
            std::cout << i << " | ";
        }
        std::cout << std::endl;
    }

    ~euclidean() {
        delete[] arr;
    }

};

int main()
{
    euclidean x;
    for (int i = 10000, c=0; i < 50001; i = i + 10000,c++) {
        for (int j = 10; j < 51; j = j + 10) {
            x.resize(i, j);
            x.distances();
            x.a_txt();
            if (j!=50 && i !=50000)
                delete[] x.arr;
        }
    }
}

