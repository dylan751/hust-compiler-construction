## Huong lam
1. Them dinh nghia Keyword REPEAT, UNTIL trong token.c, token.h
2. Sua ham getToken(), printToken() trong scanner.c
3. Luat trong parser.c, parser.h (them ham compileRepeatSt()): repeat <statement> until <condition>
5. Sua trong ham compileStatement
    - Them case KW_REPEAT: compileRepeatSt()
6. Sinh ma (xem trong compileRepeatSt())
    - Note: Dieu kien dung lap cua Repeat..Until nguoc voi Do..While

## Kiến thức cần học
- Thuộc tính tổng hợp, kế thừa, ... của quy tắc ngữ nghĩa của sản xuất
- Phân tích trái, phân tích phải
- Suy dẫn trái, suy dẫn phải
- Các chiến lược tối ưu mã
- Ôtômat: Hữu hạn đơn định, đẩy xuống, ...

## Những câu trong Forms không hiểu
- Form 2: Câu 4, 5
- Form 3: Câu 3, 4

## Dạng bài tập:
- Văn phạm nào ko nhập nhằng (là LL(1))
- Giải thuật đệ quy quay lui: Stack D1, D2 (?)
- Hoàn thiện code

## Notes
- Các văn phạm vi phạm LL(1): Factor + Assign
