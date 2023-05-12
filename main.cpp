#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Heap {
private:
    vector<int> data;  // wektor przechowujący dane kopca

    // Metoda do utrzymania własności kopca
    void heapify(int i) {
        int left = 2 * i + 1;  // indeks lewego dziecka
        int right = 2 * i + 2; // indeks prawego dziecka
        int largest = i; // zakładamy, że największy element jest na pozycji i
        // szukamy większego elementu wśród dziecka i rodzica
        if (left < data.size() && data[left] > data[largest]) {
            largest = left;
        }
        if (right < data.size() && data[right] > data[largest]) {
            largest = right;
        }
        // jeśli największy element nie jest na pozycji i, to dokonujemy zamiany
        if (largest != i) {
            swap(data[i], data[largest]);
            // ponieważ zamieniliśmy element, to musimy sprawdzić, czy poddrzewo jest kopcem
            heapify(largest);
        }
    }

public:

    // Domyślny konstruktor
    Heap() {}

    // Konstruktor przyjmujący listę inicjalizacyjną
    Heap(initializer_list<int> list) {
        data = vector<int>(list); // inicjalizujemy wektor danymi z listy
        // odtwarzamy własność kopca
        for (int i = data.size() / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    // Metoda do dodawania elementu do kopca
    void push(int val) {
        data.push_back(val); // dodajemy element na koniec
        int i = data.size() - 1; // indeks ostatniego elementu
        int parent = (i - 1) / 2; // indeks rodzica
        // odtwarzamy własność kopca po dodaniu nowego elementu
        while (i > 0 && data[parent] < data[i]) {
            swap(data[parent], data[i]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    // Metoda zwracająca element z wierzchołka kopca
    int top() {
        return data[0];
    }

    // Metoda do usunięcia elementu z wierzchołka kopca
    void pop() {
        data[0] = data.back(); // przenosimy ostatni element na wierzchołek
        data.pop_back(); // usuwamy ostatni element
        heapify(0); // odtwarzamy własność kopca
    }

    // Metoda sprawdzająca, czy kopiec jest pusty
    bool empty() {
        return data.empty();
    }

    // Przeciążenie operatora == do porównywania kopców
    bool operator==(const Heap& other) const {
        return data == other.data;
    }

    // Przeciążenie operatora != do porównywania kopców
    bool operator!=(const Heap& other) const {
        return !(*this == other);
    }

    // Przeciążenie operatora + do dodawania kopców
    Heap operator+(const Heap& other) const {
        Heap result = *this; // tworzymy kopię obecnego kopca
        // dodajemy wszystkie elementy z drugiego kopca
        for (int i : other.data) {
            result.push(i);
        }
        return result;
    }

    // Przeciążenie operatora - do odejmowania kopców
    Heap operator-(const Heap& other) const {
        Heap result = *this; // tworzymy kopię obecnego kopca
        // usuwamy wszystkie elementy, które są też w drugim kopcu
        for (int i : other.data) {
            auto it = find(result.data.begin(), result.data.end(), i);
            if (it != result.data.end()) {
                result.data.erase(it);
                result.heapify(0);
            }
        }
        return result;
    }

    // Przeciążenie operatora << do wypisywania kopca
    friend std::ostream& operator<<(std::ostream& os, const Heap& heap) {
        for (const auto& value : heap.data) {
            os << value << " ";
        }
        return os;
    }
};

// Funkcja do sortowania kopca
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

    // Tworzymy kopiec z listy inicjalizacyjnej
    Heap heap = { 5, 2, 9, 1, 5, 6 };

    cout << "Original heap: " << heap << endl;

    // Używamy funkcji heapSort do posortowania elementów kopca
    vector<int> arr = { 5, 2, 9, 1, 5, 6 };
    heapSort(arr);

    cout << "Sorted array: ";
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
