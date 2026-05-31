# Seminar_DSA
## Báo Cáo Đồ Án

### I. Thông Tin Chung
* **Môn học:** Cấu trúc Dữ liệu và Giải thuật (Học kỳ 2, 2025-2026)
* **Thành viên:**
* Bùi Minh Trí - 25120451
* Bùi Hữu Phúc -
* Phongktv - 
* **Đơn vị:** Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM (FIT-HCMUS)

---

### II. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 1)

#### 1. Thuật toán tốt nhất: MSD Radix Sort (Most Significant Digit)
Đối với đặc thù dữ liệu đầu vào là tập chuỗi có độ dài cố định hoặc thay đổi (như `strlexi` và `strlenlexi`), thuật toán **MSD Radix Sort** được lựa chọn làm giải pháp tốt nhất ở lần chạy đầu tiên.

#### 2. Các phương thức tối ưu hóa liên quan
* **Quản lý vùng nhớ thủ công:** Thay vì sử dụng các thư viện hỗ trợ mảng động tiêu chuẩn, hệ thống lưu trữ toàn bộ chuỗi dưới dạng mảng con trỏ kép `char**`. Điều này loại bỏ hoàn toàn chi phí (overhead) của việc gọi constructor/destructor liên tục trong quá trình đệ quy.
* **Hoán vị dựa trên con trỏ (Pointer Swapping):** Việc sắp xếp không sao chép giá trị chuỗi (deep copy) mà chỉ thực hiện hoán vị các địa chỉ con trỏ thông qua hàm tự cài đặt, triệt tiêu độ trễ I/O trên RAM.
* **Đếm phân phối (Counting Sort Subroutine):** Ở mỗi chữ số (digit), thuật toán dùng một mảng tần số cục bộ để phân lô (bucketing) trực tiếp bằng chỉ số, đạt độ phức tạp $O(N)$ cho mỗi tầng đệ quy thay vì $O(N \log N)$ như các thuật toán dựa trên phép so sánh (Comparison-based).

#### 3. Lý giải nguyên nhân hiệu quả
Trong khi Merge Sort hay Quick Sort tiêu chuẩn mất thời gian $O(N \log N \times L)$ (với $L$ là độ dài chuỗi) do phải duyệt lại từ đầu chuỗi trong mỗi lần so sánh, MSD Radix Sort xử lý theo từng ký tự từ trái sang phải. Các chuỗi có chung tiền tố sẽ được gom vào cùng một bucket và chỉ tiếp tục so sánh các ký tự phía sau, giúp độ phức tạp chạm ngưỡng tuyến tính tỷ lệ thuận với tổng độ dài các chuỗi, khai thác tối đa cấu trúc của từ điển (Lexicographical).

---

### III. Phân Tích Bộ Sinh Test (test_gen.cpp)

Bộ test được thiết kế nhằm khai thác trực tiếp vào các lỗ hổng và trường hợp suy biến (worst-case) của các thuật toán phổ biến hiện nay, ép thời gian chạy tiến dần về $O(N^2)$.

* **Test 1: LCP Hell (Tiền tố chung cực dài)**
  * *Mục tiêu:* Standard Quick Sort, Merge Sort.
  * *Lý do:* 99 ký tự đầu tiên giống hệt nhau và chỉ khác biệt ở ký tự cuối. Các thuật toán so sánh chuỗi nguyên khối sẽ phải lặp qua 99 ký tự này hàng vạn lần.
* **Test 2: Anti-QuickSort (Bẫy Median-of-Three)**
  * *Mục tiêu:* Quick Sort sử dụng chiến lược chọn Pivot là trung vị của 3 phần tử (Median of 3).
  * *Lý do:* Thay vì mảng giảm dần thông thường, test case này liên tục hoán đổi vị trí của các phần tử cực trị vào đúng vị trí `mid` mà thuật toán Median-of-Three sẽ chọn. Điều này khiến Pivot luôn là giá trị lớn nhất hoặc nhỏ nhất, làm suy biến cây đệ quy thành một danh sách liên kết, ép thời gian chạy từ $O(N \log N)$ xuống $O(N^2)$.
* **Test 3: Identical Bomb (Tất cả giống hệt nhau)**
  * *Mục tiêu:* Quick Sort với phân hoạch 2 chiều (2-way Partitioning).
  * *Lý do:* Khi tất cả chuỗi đều bằng nhau, bộ phân hoạch không xử lý tốt sẽ liên tục chia mảng thành phần kích thước $1$ và $N-1$, dẫn đến tràn bộ nhớ stack (Stack Overflow) hoặc kịch trần thời gian chạy.
* **Test 4: Cache-Miss Chaos (Dữ liệu ngẫu nhiên)**
  * *Mục tiêu:* Tree Sort, Linked-List Sort.
  * *Lý do:* Dữ liệu sinh ngẫu nhiên hoàn toàn làm vô hiệu hóa khả năng dự đoán nhánh (Branch Prediction) của CPU và gây ra lỗi trượt bộ nhớ đệm (Cache Miss) liên tục do các từ khóa phân tán không theo quy luật cục bộ.
* **Test 5: Reverse Sorted (Nghịch đảo từ điển)**
  * *Mục tiêu:* Insertion Sort, Quick Sort (Pivot tĩnh).
  * *Lý do:* Insertion Sort phải dịch chuyển mảng tối đa trong mọi vòng lặp, khiến vòng lặp lồng nhau đạt đỉnh số phép tính cận biên.

---

### IV. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 2)

#### 1. Thuật toán tốt nhất: 3-Way String QuickSort (Multikey QuickSort)
Mặc dù MSD Radix Sort rất nhanh, nhược điểm của nó là tạo ra quá nhiều bước đệ quy phân mảnh khi mảng con có kích thước nhỏ, gây lãng phí bộ nhớ Cache. Để giải quyết triệt để, **Multikey QuickSort** được áp dụng ở lần chạy thứ hai.

#### 2. Các phương thức tiếp tục tối ưu hóa
* **Hybrid Threshold (Kết hợp Insertion Sort):** Khi kích thước mảng đệ quy cắt xuống dưới ngưỡng 16 phần tử, hệ thống lập tức chuyển sang **Insertion Sort** để tận dụng bộ nhớ L1 Cache của CPU, loại bỏ hoàn toàn chi phí thiết lập stack đệ quy.
* **Phân hoạch 3 chiều (3-Way Partitioning):** Trực tiếp bẻ gãy bẫy *LCP Hell* và *Identical Bomb*. Ở mỗi bước đệ quy tại ký tự thứ $d$, thuật toán chia mảng thành 3 tập: nhỏ hơn, bằng, và lớn hơn Pivot. Tập "bằng" sẽ được tăng độ sâu $d+1$ mà không cần so sánh lại các tiền tố đã khớp, gom được ưu điểm của Radix Sort và tính tại chỗ (In-place) của QuickSort. 
* **Custom Swap tự định nghĩa:** Không sử dụng `std::swap` trong thư viện chuẩn để loại trừ overhead từ thư viện `<utility>`, bảo đảm toàn quyền kiểm soát cấp thấp trên các thao tác dịch chuyển bit của con trỏ mảng.
