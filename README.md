# Seminar_DSA
## Báo Cáo Đồ Án

### I. Thông Tin Chung
* **Môn học:** Cấu trúc Dữ liệu và Giải thuật (Học kỳ 2, 2025-2026)
* **Thành viên:**
  * Bùi Minh Trí - 25120451 
  * Bùi Hữu Phúc - 
  * Phongktv - 

---

### II. Bài A: [Integer Sort]

*(Phần này dành cho thành viên phụ trách Bài A điền vào)*

#### 1. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 1)
* **Thuật toán tốt nhất:** [Điền tên thuật toán]
* **Các phương thức tối ưu hóa liên quan:**
  * [Điền chi tiết phương pháp tối ưu 1]
  * [Điền chi tiết phương pháp tối ưu 2]
* **Lý giải nguyên nhân hiệu quả:**
  * [Giải thích tại sao thuật toán và các tối ưu trên lại đạt hiệu suất cao nhất ở lần 1]

#### 2. Phân Tích Bộ Sinh Test (test_gen.cpp)
* **Test 1:** [Tên Test]
  * *Mục tiêu:* [Thuật toán bị nhắm đến]
  * *Lý do:* [Cách thức test case làm suy biến thời gian chạy]
* **Test 2:** [Tên Test]
  * *Mục tiêu:* [Thuật toán bị nhắm đến]
  * *Lý do:* [Cách thức test case làm suy biến thời gian chạy]
*(Tiếp tục với Test 3, 4, 5...)*

#### 3. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 2)
* **Thuật toán tốt nhất:** [Điền tên thuật toán]
* **Các phương thức tiếp tục tối ưu hóa:**
  * [Làm thế nào để tiếp tục cải tiến so với lần 1?]
  * [Các kỹ thuật kết hợp nếu có]

---

### III. Bài B: [Lexicographic Sort]

*(Phần này dành cho thành viên phụ trách Bài B điền vào)*

#### 1. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 1)
* **Thuật toán tốt nhất:** [Điền tên thuật toán]
* **Các phương thức tối ưu hóa liên quan:**
  * [Điền chi tiết phương pháp tối ưu 1]
  * [Điền chi tiết phương pháp tối ưu 2]
* **Lý giải nguyên nhân hiệu quả:**
  * [Giải thích tại sao thuật toán và các tối ưu trên lại đạt hiệu suất cao nhất ở lần 1]

#### 2. Phân Tích Bộ Sinh Test (test_gen.cpp)
* **Test 1:** [Tên Test]
  * *Mục tiêu:* [Thuật toán bị nhắm đến]
  * *Lý do:* [Cách thức test case làm suy biến thời gian chạy]
*(Tiếp tục với các test tiếp theo)*

#### 3. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 2)
* **Thuật toán tốt nhất:** [Điền tên thuật toán]
* **Các phương thức tiếp tục tối ưu hóa:**
  * [Làm thế nào để tiếp tục cải tiến so với lần 1?]

---

### IV. Bài C: [Length-aware Lexicographic String Sort]

#### 1. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 1)

* **Thuật toán tốt nhất: MSD Radix Sort + Counting Sort (Most Significant Digit)**
  Sort bằng Radix Sort trước, sort lại 1 lần nữa bằng Counting Sort

* **Các phương thức tối ưu hóa liên quan:**
  Sử dụng mảng tần số (count array) để phân lô trực tiếp các ký tự và độ dài chuỗi, đạt độ phức tạp lý thuyết tuyến tính $O(N.L)$ thay vì $O(N \log N)$ như các thuật toán dựa trên phép so sánh.

* **Lý giải nguyên nhân hiệu quả:**
  Trong khi Merge Sort hay Quick Sort tiêu chuẩn mất thời gian $O(N \log N \times L)$ (với $L$ là độ dài chuỗi) do phải duyệt lại từ đầu chuỗi trong mỗi lần so sánh, MSD Radix Sort xử lý theo từng ký tự từ trái sang phải. Các chuỗi có chung tiền tố sẽ được gom vào cùng một bucket và chỉ tiếp tục so sánh các ký tự phía sau, giúp độ phức tạp giảm đáng kể.

#### 2. Phân Tích Bộ Sinh Test (test_gen.cpp)

Bộ test được thiết kế nhằm khai thác trực tiếp vào các lỗ hổng và trường hợp suy biến (worst-case) của các thuật toán phổ biến hiện nay, ép thời gian chạy tiến dần về $O(N^2)$.

* **Test 1: Phần lớn các kí tự đầu giống hệt nhau**
  * *Mục tiêu:* Standard Quick Sort, Merge Sort.
  * *Lý do:* 99 ký tự đầu tiên giống hệt nhau và chỉ khác biệt ở ký tự cuối. Các thuật toán so sánh chuỗi nguyên khối sẽ phải lặp qua 99 ký tự này hàng vạn lần.
* **Test 2: Anti-QuickSort Median-of-Three**
  * *Mục tiêu:* Quick Sort sử dụng chiến lược chọn Pivot là trung vị của 3 phần tử (Median of 3).
  * *Lý do:* Test case này đặt các phần tử cực trị vào đúng vị trí `mid` mà thuật toán Median-of-Three sẽ chọn. Điều này khiến Pivot luôn là giá trị lớn nhất hoặc nhỏ nhất, khiến cây đệ quy thành một danh sách liên kết, ép thời gian chạy từ $O(N \log N)$ xuống $O(N^2)$.
* **Test 3: Tất cả giống hệt nhau**
  * *Mục tiêu:* Quick Sort với phân hoạch 2 chiều (2-way Partitioning).
  * *Lý do:* Khi tất cả chuỗi đều bằng nhau, bộ phân hoạch không xử lý tốt sẽ liên tục chia mảng thành phần kích thước $1$ và $N-1$, khiến tràn bộ nhớ stack (Stack Overflow) hoặc làm tăng thời gian chạy.
* **Test 4: Random**
  * *Mục tiêu:* Làm tăng thời gian chạy tất cả hàm Sort
  * *Lý do:* Với những hàm sort tối ưu kém có thể bị TLE hoặc thời gian chạy sẽ rất cao.
* **Test 5: Reverse Sorted**
  * *Mục tiêu:* Insertion Sort, Quick Sort (với pivot cuối).
  * *Lý do:* Các hàm Sort khác có dùng Insertion Sort cho các đoạn nhỏ phải dịch chuyển mảng tối đa trong mọi vòng lặp. Quick Sort chọn pivot là phần tử ở cuối sẽ bị tăng độ phức tạp lên tiệm cận $O(N^2)$.

#### 3. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 2)

* **Thuật toán tốt nhất: Index-based Hybrid Merge Sort**
 Mặc dù Radix và Counting Sort trên lý thuyết nhanh nhưng điểm yếu của lần chạy 1 nằm ở việc di chuyển khối lượng dữ liệu chuỗi quá lớn, nên chuyển hẳn sang thuật toán Merge Sort kết hợp Insertion Sort vì có phần nhỉnh hơn về tốc độ.
* **Các phương thức tối ưu hóa liên quan:**
  * Sắp xếp qua mảng chỉ số
  * Ngắt đệ quy khi số lượng phần tử mảng nhỏ
  * Tối ưu bước Skip Merge
  * Output Buffering
* **Lý giải nguyên nhân hiệu quả:**
  * Sắp xếp qua mảng chỉ số giúp loại bỏ bước hoán vị chuỗi kí tự dài
  * Khi số lượng phần tử của mảng nhỏ hơn 32 thì thuật toán chuyển sang dùng Insertion Sort thay cho Merge giúp cải thiện tốc độ
  * Skip Merge được dùng khi phần tử lớn nhất của nửa trái đã nhỏ hơn hoặc bằng phần tử nhỏ nhất của nửa phải giúp giảm số lần so sánh
  * Output Buffering để tạo 1 string cực dài và toàn bộ kết quả được nối trực tiếp vào chuỗi này và thực hiện xuất chỉ bằng một lệnh I/O duy nhất.
