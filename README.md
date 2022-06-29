# Compiler Construction
## Weekly homework of subject Compiler Construction

# Description
- Repositories includes: Code of every weeks
- Compile with C's makefile tool

# Compile instruction:
## Run bai1:
```
cd bai1/src
make dev
```

## Run bai2:
```
cd bai2/completed
make
./mytest.sh
```

Cách biên dịch trên đã bao gồm các đoạn mã để so sánh kết quả và các test. Để xem kết quả trên terminal của từng ví dụ, thực thi lệnh dưới đây sau khi đã biên dịch make:

./scanner ../test/example1.kpl

## Run bai3:
```
cd bai3/completed
make
./mytest.sh
```

Cách biên dịch trên đã bao gồm các đoạn mã để so sánh kết quả và các test. Để xem kết quả trên terminal của từng ví dụ, thực thi lệnh dưới đây sau khi đã biên dịch make:

./parser ../test/example1.kpl

## Run bai4 - day1:
Pha 3: Phân tích ngữ nghĩa
\day1: -> Xây dựng bảng kí hiệu
```
cd bai4/day1/completed
make
./symtab
```
Xây dựng và in bảng kí hiệu cho 1 đoạn mã cụ thể trong file main.c

---
## complete + interpreter
- 2 thư mục chứa code đầy đủ
- `complete`: Sinh mã đích
- `interpreter`: Thư mục để chạy chương trình

### Cách biên dịch
- `complete`:
```
- make clean
- make
- Usage: ./kplc input output [-dump]
       input: input kpl program
       output: executable
       -dump: code dump
```

- `interpreter`:
```
- make clean
- make
- Usage: ./kplrun input [-s=stack_size] [-c=code_size] [-debug] [-dump]
       input: input kpl program
       -s=stack_size: set the stack size
       -c=code_size: set the code size
       -debug: enable code dump

```
