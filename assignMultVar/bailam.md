# Hướng làm bài gán nhiều biến
Ví dụ như: 
```
x, y, z := y, z, x;
```
## Ý tưởng
- Cú pháp và ngữ nghĩa:
	-- Với lệnh gán mặc định: 
    ```
    x:= 1
    ```
	- Nhưng khi số lượng biến tăng lên -> cần 1 list lưu các biến bên trái và 1 list lưu các giá trị bên phải
	- Đọc lần lượt từ trái sang phải: Đọc được đến trước `:=` -> list các biến bên phải
	- Đọc lần lượt từ trái sang phải: Đọc được đến khi hết `,` -> list các biến bên trái
	
	- So sánh số lượng biến bên trái và bên phải
	- So sánh lần lượt tương ứng các phần tử của 2 list về kiểu 
- sinh mã:
	chúng ta sẽ `LA` và `LV` đúng theo thứ tự để có thể `ST`
	Sau đó cũng ta sẽ `ST` n lần với n là số biến bên trái mà chúng ta cần gán
	
## Triển khai
- Sủa hàm `compileAssignSt();` trong `parser.c`
- Thêm hàm `compileMultLValue(Object **resVar);` trong `parser.c`, `parser.h`		 
