#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Heap {
private:
    vector<int> data;
    void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < data.size() && data[left] > data[largest]) {
            largest = left;
        }
        if (right < data.size() && data[right] > data[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(data[i], data[largest]);
            heapify(largest);
        }
    }
public:
    //todo - dodać konstruktor przyjmujący {1,2,3,4...} tworzący z tego kopiec
    Heap() {}
    void push(int val) {
        data.push_back(val);
        int i = data.size() - 1;
        int parent = (i - 1) / 2;
        while (i > 0 && data[parent] < data[i]) {
            swap(data[parent], data[i]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }
    int top() {
        return data[0];
    }
    void pop() {
        data[0] = data.back();
        data.pop_back();
        heapify(0);
    }
    bool empty() {
        return data.empty();
    }

    //operators overload
    bool operator==(const Heap& other) const {
        return data == other.data;
    }

    bool operator!=(const Heap& other) const {
        return !(*this == other);
    }

    Heap operator+(const Heap& other) const {
        Heap result = *this;
        for (int i : other.data) {
            result.push(i);
        }
        return result;
    }

    Heap operator-(const Heap& other) const {
        Heap result = *this;
        for (int i : other.data) {
            auto it = find(result.data.begin(), result.data.end(), i);
            if (it != result.data.end()) {
                result.data.erase(it);
                result.heapify(0);
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Heap& heap) {
        for (const auto& value : heap.data) {
            os << value << " ";
        }
        return os;
    }
};

void heapSort(vector<int>& arr) {
    Heap heap;
    for (int i : arr) {
        heap.push(i);
    }
    int i = arr.size() - 1;
    while (!heap.empty()) {
        arr[i--] = heap.top();
        heap.pop();
    }
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    heapSort(arr);
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;

    // operator == presentation
    Heap heap1;
    for (int i : arr) {
        heap1.push(i);
    }

    Heap heap2;
    for (int i : arr) {
        heap2.push(i);
    }

    if (heap1 == heap2) {cout << "Równe\n";}

    //operator + presentation
    Heap heap3 = heap1 + heap2;

    // operator == presentation
    if (heap3 != heap2) {cout << "Różne\n";}
    cout << heap3;

    return 0;
}

//Kod implementuje sortowanie przez kopcowanie (heap sort), które korzysta z klas Heap oraz vector do przechowywania danych.
//Metoda Heap::heapify jest prywatną metodą klasy Heap i służy do odtwarzania własności kopca dla wierzchołka w danym indeksie i, który może naruszać własność. Metoda ta znajduje indeks lewego i prawego syna wierzchołka i (jeśli istnieją), a następnie porównuje wartości tych wierzchołków z wartością wierzchołka i. Jeśli któryś z synów ma większą wartość niż wierzchołek i, to zamienia wartość wierzchołka i z wartością większego syna i wywołuje metodę heapify dla wierzchołka o nowym indeksie, który został zamieniony.
//Metoda Heap::push dodaje nowy element do kopca i utrzymuje jego własność. W tym celu dodaje nowy element na końcu wektora i zamienia go z jego rodzicem, jeśli wartość rodzica jest mniejsza niż wartość dodawanego elementu, a następnie powtarza tę operację dla rodzica nowego elementu, dopóki nie zostanie przywrócona własność kopca.
//Metoda Heap::top zwraca wartość elementu, który znajduje się na szczycie kopca.
//Metoda Heap::pop usuwa element znajdujący się na szczycie kopca i przywraca jego własność poprzez wywołanie metody Heap::heapify na szczycie kopca.
//Metoda Heap::empty zwraca true, jeśli kopiec jest pusty, a false w przeciwnym przypadku.
//Funkcja heapSort przyjmuje wektor arr jako argument i tworzy obiekt klasy Heap. Następnie każdy element wektora arr jest dodawany do kopca za pomocą metody push klasy Heap. Następnie funkcja heapSort przenosi elementy kopca do wektora arr za pomocą metody top i usuwa je za pomocą metody pop, aż kopiec będzie pusty. Elementy wektora arr są ustawiane w odwrotnej kolejności, co zapewnia, że wektor arr będzie posortowany w kolejności rosnącej. Na końcu funkcja wypisuje posortowany wektor.
//Funkcja main tworzy wektor arr i wywołuje funkcję heapSort, aby posortować jego elementy. Następnie wypisuje posortowany wektor na ekranie.
//klasa jak typ predefiniowany, konstruktor, destruktor, przeciążenie operatorów
