#include "sparse_matrix.h"

SparseMatrix::SparseMatrix(fs::path fname) {
    std::ifstream stream(fname);
    int32_t n_rows;
    stream >> n_rows;
    data.resize(n_rows);

    for (int32_t i = 0; i < n_rows; i++) {
        int32_t n_cols;
        stream >> n_cols;
        data[i].reserve(n_cols);
        for (int32_t j = 0; j < n_cols; j++) {
            int32_t index;
            double value;
            stream >> index >> value;
            data[i].push_back({index, value});
        }
    }
}

void SparseMatrix::Print() {
    int32_t n = data.size();
    printf("%d rows:\n", n);
    for (int32_t i = 0; i < n; i++) {
        int32_t element_index = 0;
        for (int32_t j = 0; j < n; j++) {
            if (element_index < data[i].size()) {
                if (data[i][element_index].index == j) {
                    printf("%.2f ", data[i][element_index].value);
                    element_index++;
                } else {
                    printf("%.2f ", 0.);
                }
            } else {
                printf("%.2f ", 0.);
            }
        }
        printf("\n");
    }
}

double SparseMatrix::checkColumn(int &row, int&column){
    for (int i = 0; i < this->data[row].size(); ++i) {
        if (this->data[row][i].index==column){
            return this->data[row][i].value;
        }
        if (this->data[row][i].index>column){
            return 0;
        }
    }
}
SparseMatrix SparseMatrix::operator*(const SparseMatrix &m) {
    SparseMatrix result;
    result.data.resize(this->data.size());
    for (int i=0;i<this->data.size(); ++i){
        for(int j=0; j<this->data.size();++j){
            for (int k = 0; k <this->data[i].size(); ++k) {
                double curr = checkColumn(this->data[i][k].index,i)!=0;
                if(curr!=0){
                    result.data[i].push_back({k,curr*(this->data[i][k].value)});
                }
            }
        }
    }
    return result;
}
/* Моя мысль в том, что нужно сделать функцию, которая будет проверять наличие элемента в правой матрице с нужным нам индексом, который мы знаем из левой.
Поскольку массив отсортирован, то можно проверять на то, стал ли больше интереируемый индекс, чем искомый и останавливать цикл соответсвтенно.*.
