#include "DNA_bank_student.h"
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long xseed;
    int Nsize;
    int index1, index2; // 사전식 정렬 후 찾을 인덱스
    int fidx1, fidx2;

    set_DNA_bank();          // DNA 데이터셋 초기화
    Nsize = get_size();      // DNA 시퀀스 개수
    xseed = get_seed();      // 난수 시드 값

    // 찾을 순위 index 받아오기
    get_index(&index1, &index2);

    vector<int> indices(Nsize); // index값들만 일단 벡터에 저장
    for (int i = 0; i < Nsize; i++) indices[i] = i;

    // DNA 시퀀스를 직접 저장하지 않고 인덱스만 비교하며 정렬
    sort(indices.begin(), indices.end(), [xseed](int a, int b) {
        int pos = 0;
        while (true) {
            char ca = DNA_base(xseed, a, pos);
            char cb = DNA_base(xseed, b, pos);

            if (ca != cb) return ca < cb;
            if (ca == '$') return false; // 둘 다 끝나면 동일
            ++pos;
        }
    });

    fidx1 = indices[index1];
    fidx2 = indices[index2];

    report(fidx1, fidx2); // 결과 출력ㄱ
}