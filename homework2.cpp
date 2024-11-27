#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class tern {
    friend class polynomial;
private:
    float coef; // 係數
    int exp;    // 指數
public:
    tern(float c = 0, int e = 0) : coef(c), exp(e) {}
};

class polynomial {
private:
    tern* termArray; // 儲存項目的動態陣列
    int terms;       // 已使用的項目數量
    int capacity;    // 陣列容量

public:
    polynomial(int initialCapacity = 5) : terms(0), capacity(initialCapacity) {
        termArray = new tern[capacity];
    }
    ~polynomial() {
        delete[] termArray; // 釋放動態陣列
    }

    // 空間不足時重新配置空間
    void NewTerm(const float newCoef, const int newExp) {
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].exp == newExp) { // 如果指數相同，合併係數
                termArray[i].coef += newCoef;
                return;
            }
        }
        if (terms == capacity) {
            capacity *= 2;
            tern* temp = new tern[capacity];
            copy(termArray, termArray + terms, temp);
            delete[] termArray;
            termArray = temp;
        }
        termArray[terms].coef = newCoef;
        termArray[terms++].exp = newExp;
    }

    // 輸入多項式
    void input() {
        int n;
        cout << "輸入多項式的項數: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            float coef;
            int exp;
            cout << "輸入第 " << i + 1 << " 項的係數與指數: ";
            cin >> coef >> exp;
            NewTerm(coef, exp);
        }
    }

    // 多項式相加
    polynomial add(const polynomial& poly) const {
        polynomial result(capacity + poly.capacity); // 預留足夠容量
        for (int i = 0; i < terms; ++i) {
            result.NewTerm(termArray[i].coef, termArray[i].exp);
        }
        for (int i = 0; i < poly.terms; ++i) {
            result.NewTerm(poly.termArray[i].coef, poly.termArray[i].exp);
        }
        return result;
    }

    // 多項式相乘
    polynomial mult(const polynomial& poly) const {
        polynomial result(capacity * poly.capacity); // 預留足夠容量
        for (int i = 0; i < terms; ++i) {
            for (int j = 0; j < poly.terms; ++j) {
                result.NewTerm(
                    termArray[i].coef * poly.termArray[j].coef,
                    termArray[i].exp + poly.termArray[j].exp
                );
            }
        }
        return result;
    }

    // 計算多項式在 x 值上的結果
    float eval(float x) const {
        float result = 0;
        for (int i = 0; i < terms; ++i) {
            result += termArray[i].coef * pow(x, termArray[i].exp);
        }
        return result;
    }

    // 輸出多項式
    void display() const {
        if (terms == 0) {
            cout << "0";
            return;
        }
        for (int i = 0; i < terms; ++i) {
            if (i > 0 && termArray[i].coef > 0) cout << " + ";
            if (termArray[i].exp == 0) {
                cout << termArray[i].coef;
            }
            else {
                cout << termArray[i].coef << "x^" << termArray[i].exp;
            }
        }
        cout << endl;
    }
};

int main() {
    polynomial poly1, poly2;

    cout << "輸入第一個多項式:" << endl;
    poly1.input();
    cout << "輸入第二個多項式:" << endl;
    poly2.input();

    cout << "第一個多項式為: ";
    poly1.display();
    cout << "第二個多項式為: ";
    poly2.display();

    polynomial sum = poly1.add(poly2);
    polynomial product = poly1.mult(poly2);

    cout << "多項式相加結果: ";
    sum.display();
    cout << "多項式相乘結果: ";
    product.display();

    float x;
    cout << "請輸入 x 的值以求解第一個多項式: ";
    cin >> x;
    cout << "第一個多項式在 x = " << x << " 時的值為: " << poly1.eval(x) << endl;

    return 0;
}
