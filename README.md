# Seminar_DSA: Tối ưu các thuật toán sắp xếp
## Báo Cáo Đồ Án

### I. Thông Tin Chung
* **Môn học:** Cấu trúc Dữ liệu và Giải thuật (Học kỳ 2, 2025-2026)
* **Thành viên:**
  * Bùi Minh Trí - 25120451 
  * Bùi Hữu Phúc - 25120417
  * Lê Tuấn Phong - 25120412

---

### II. Bài A: [Integer Sort]

#### 1. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 1)

* **Thuật toán tốt nhất:** LSD Radix Sort (Least Significant Digit)

* **Các phương thức tối ưu hóa liên quan:**
  * Sử dụng Radix Sort cơ số 256 để xử lý trực tiếp theo từng byte của số nguyên 32-bit, giúp giảm số pass xuống còn 4 lượt duyệt.
  * Sử dụng phép biến đổi bit dấu `x ^ 0x80000000` để đưa miền số nguyên signed sang unsigned nhằm xử lý đúng thứ tự giữa số âm và số dương.
  * Sử dụng `ios::sync_with_stdio(false)` và `cin.tie(nullptr)` để tối ưu thao tác nhập xuất.

* **Lý giải nguyên nhân hiệu quả:**
  * Trong khi Quick Sort, Merge Sort hay Heap Sort bị giới hạn bởi độ phức tạp `O(NlogN)`, LSD Radix Sort hoạt động theo cơ chế phân phối bucket nên có độ phức tạp gần tuyến tính `O(kN)` với `k = 4` cho số nguyên 32-bit. Thuật toán gần như không bị ảnh hưởng bởi thứ tự dữ liệu đầu vào, đồng thời phép đổi bit dấu cho phép xử lý trực tiếp cả số âm và số dương mà không cần thêm bước sort phụ.

#### 2. Phân Tích Bộ Sinh Test (test_gen.cpp)

* **Test 1: Random Uniform**
  * *Mục tiêu:* Tất cả các thuật toán sort tổng quát.
  * *Lý do:* Dữ liệu được sinh ngẫu nhiên trên khoảng giá trị rất lớn nhằm đánh giá hiệu năng trung bình của thuật toán. Những cài đặt tối ưu kém hoặc quản lý bộ nhớ chưa tốt sẽ có thời gian chạy cao.

* **Test 2: Sorted**
  * *Mục tiêu:* Quick Sort chọn pivot đầu/cuối, Hybrid Sort dùng Insertion Sort.
  * *Lý do:* Dữ liệu đã được sắp xếp tăng dần. Quick Sort với chiến lược chọn pivot đơn giản sẽ tạo phân hoạch cực lệch, làm độ phức tạp tăng từ `O(NlogN)` lên gần `O(N²)`.

* **Test 3: Reverse Sorted**
  * *Mục tiêu:* Insertion Sort, Quick Sort với pivot cuối.
  * *Lý do:* Dữ liệu đảo ngược hoàn toàn. Insertion Sort phải thực hiện số lần dịch chuyển tối đa ở mọi vòng lặp, trong khi Quick Sort chọn pivot không phù hợp sẽ tiếp tục rơi vào trường hợp phân hoạch mất cân bằng và tiệm cận `O(N²)`.

* **Test 4: Many Duplicates**
  * *Mục tiêu:* Quick Sort với phân hoạch 2 chiều (2-way Partitioning).
  * *Lý do:* Chỉ tồn tại rất ít giá trị khác nhau nhưng lặp lại với tần suất lớn. Các cài đặt Quick Sort không xử lý tốt phần tử trùng lặp có thể liên tục tạo ra phân hoạch mất cân bằng, làm tăng số lần đệ quy.

* **Test 5: Clustered Values**
  * *Mục tiêu:* Comparison Sort và các thuật toán tối ưu chưa tốt.
  * *Lý do:* Dữ liệu được sinh quanh một giá trị trung tâm với sai lệch nhỏ, tạo mật độ phần tử cao trong cùng một vùng giá trị. Điều này giúp kiểm tra khả năng xử lý dữ liệu phân bố cụm của các thuật toán sort.

#### 3. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 2)

* **Thuật toán tốt nhất:** American Flag Sort (MSD Radix Sort in-place)

* **Các phương thức tiếp tục tối ưu hóa:**
  * Chuyển từ LSD Radix Sort sang American Flag Sort để giảm số lần copy dữ liệu và thực hiện phân bucket trực tiếp trên mảng gốc.
  * Kết hợp Insertion Sort cho các bucket nhỏ nhằm giảm chi phí đệ quy.
  * Sử dụng low-level buffered I/O bằng `streambuf`, `sgetn()` và `sputn()` để giảm overhead của thao tác nhập xuất.
  * Áp dụng `#pragma GCC optimize("Ofast,unroll-loops")` cùng loop unrolling ở bước counting.

* **Lý giải nguyên nhân hiệu quả:**
  * Mặc dù LSD Radix Sort ở lần chạy 1 đã đạt độ phức tạp gần tuyến tính, điểm yếu chính vẫn nằm ở việc phải dùng mảng phụ và copy toàn bộ dữ liệu sau mỗi pass. American Flag Sort cải thiện điều này bằng cách thực hiện hoán vị trực tiếp trên mảng nguồn (in-place), giúp giảm đáng kể chi phí bộ nhớ và thao tác copy.

  * Việc chuyển sang chiến lược MSD cho phép chia bucket từ byte cao nhất trước, giúp các nhóm dữ liệu nhỏ được xử lý sớm hơn. Khi bucket giảm xuống dưới ngưỡng nhỏ, thuật toán chuyển sang Insertion Sort để tận dụng cache locality và giảm overhead đệ quy. Kết hợp với fast I/O và compiler optimization, phiên bản lần 2 đạt thời gian chạy tốt hơn so với lần chạy đầu tiên.

---

### III. Bài B: [Lexicographic Sort]

#### 1. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 1)
* **Thuật toán tốt nhất:** MSD Radix Sort (Most Significant Digit Radix Sort) kết hợp Insertion Sort
* **Các phương thức tối ưu hóa liên quan:**
  * Sử dụng Insertion Sort cho các đoạn có kích thước nhỏ (≤ 32 phần tử) để giảm chi phí đệ quy và phân hoạch
  * Tối ưu trường hợp các chuỗi có cùng ký tự tại vị trí đang xét, giúp bỏ qua bước phân hoạch và chuyển sang ký tự tiếp theo
* **Lý giải nguyên nhân hiệu quả:**
  * MSD Radix Sort giảm số lần so sánh toàn chuỗi bằng cách xử lý theo từng ký tự
  * Insertion Sort hiệu quả trên các đoạn nhỏ giúp giảm overhead đệ quy
  * Tối ưu tiền tố chung giúp giảm số lần phân hoạch không cần thiết

#### 2. Phân Tích Bộ Sinh Test (test_gen.cpp)
* **Test 1: Random Strings**
  * *Mục tiêu:* Tất cả thuật toán sắp xếp chuỗi
  * *Lý do:* Chuỗi ngẫu nhiên với độ dài 10–100 và ký tự a–z, đánh giá hiệu năng trung bình
* **Test 2: Common Prefix**
  * *Mục tiêu:* MSD Radix Sort
  * *Lý do:* Chuỗi có tiền tố rất dài, chỉ khác ở ký tự cuối, làm tăng độ sâu đệ quy
* **Test 3: Identical Strings**
  * *Mục tiêu:* MSD Radix Sort
  * *Lý do:* Tất cả chuỗi giống nhau, kiểm tra khả năng xử lý trường hợp trùng lặp
* **Test 4: Many Duplicates**
  * *Mục tiêu:* Thuật toán xử lý dữ liệu trùng lặp
  * *Lý do:* Ít giá trị khác nhau nhưng lặp lại nhiều, gây mất cân bằng bucket
* **Test 5: Variable Length Strings**
  * *Mục tiêu:* MSD Radix Sort và thuật toán so sánh chuỗi
  * *Lý do:* Chuỗi có độ dài khác nhau (10–100), bao gồm trường hợp một chuỗi là tiền tố của chuỗi khác

#### 3. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 2)
* **Thuật toán tốt nhất:** MSD Radix Sort sử dụng bảng chữ cái giới hạn (a–z) kết hợp Insertion Sort
* **Các phương thức tiếp tục tối ưu hóa:**
  * Thu hẹp bảng đếm từ 256 ký tự xuống 27 ký tự (a–z + ký tự kết thúc chuỗi)
  * Sử dụng memory pool để lưu chuỗi liên tiếp trong bộ nhớ, giảm cache miss
  * Ánh xạ ký tự trực tiếp thay vì dùng ASCII đầy đủ để giảm overhead xử lý

---

### IV. Bài C: [Length-aware Lexicographic String Sort]

#### 1. Đánh Giá Thuật Toán Cài Đặt (Lần Chạy 1)

* **Thuật toán tốt nhất: MSD Radix Sort + Counting Sort (Most Significant Digit):**
  Sort bằng Radix Sort trước, sau khi sort xong bằng Radix Sort thì do tính stable của Counting Sort nên sort lại 1 lần nữa bằng Counting Sort sẽ cho kết quả đủng.

* **Các phương thức tối ưu hóa liên quan:**
  * Sử dụng mảng tần số (count array) để phân lô trực tiếp các ký tự và độ dài chuỗi, đạt độ phức tạp lý thuyết tuyến tính $O(N.L)$ thay vì $O(N \log N)$ như các thuật toán dựa trên phép so sánh.
  * Sử dụng hàm swap thay cho gán trực tiếp giá trị vì hàm swap sẽ swap địa chỉ thay vì gán lại toàn bộ dữ liệu.

* **Lý giải nguyên nhân hiệu quả:**
  Trong khi Merge Sort hay Quick Sort tiêu chuẩn mất thời gian $O(N \log N \times L)$ (với $L$ là độ dài chuỗi) do phải duyệt lại từ đầu chuỗi trong mỗi lần so sánh, MSD Radix Sort xử lý theo từng ký tự từ trái sang phải. Các chuỗi có chung tiền tố sẽ được gom vào cùng một bucket và chỉ tiếp tục so sánh các ký tự phía sau, giúp độ phức tạp giảm đáng kể.

#### 2. Phân Tích Bộ Sinh Test (test_gen.cpp)

* **Test 1: Phần lớn các kí tự đầu giống hệt nhau**
  * *Mục tiêu:* Standard Quick Sort, Merge Sort.
  * *Lý do:* 99 ký tự đầu tiên giống hệt nhau và chỉ khác biệt ở ký tự cuối. Các thuật toán so sánh chuỗi nguyên khối sẽ phải lặp qua 99 ký tự này liên tục.
* **Test 2: Anti-QuickSort Median-of-Three**
  * *Mục tiêu:* Quick Sort chọn Pivot là trung vị của 3 phần tử (Median of 3).
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
 Mặc dù Radix và Counting Sort trên lý thuyết nhanh nhưng có lẽ việc đệ quy liên tục khiến thời gian chạy tăng lên đáng kể, nên chuyển hẳn sang thuật toán Merge Sort kết hợp Insertion Sort hợp lý hơn vì có phần nhỉnh hơn về tốc độ.
* **Các phương thức tối ưu hóa liên quan:**
  * Sắp xếp qua mảng chỉ số
  * Ngắt đệ quy khi số lượng phần tử mảng nhỏ
  * Tối ưu bước Skip Merge
  * Output Buffering
  * Lưu mảng độ dài chuỗi
* **Lý giải nguyên nhân hiệu quả:**
  * Sắp xếp qua mảng chỉ số giúp loại bỏ bước hoán vị chuỗi kí tự dài
  * Khi số lượng phần tử của mảng bị chia nhỏ hơn 32 thì thuật toán chuyển sang dùng Insertion Sort thay cho Merge Sort giúp cải thiện tốc độ
  * Skip Merge được dùng khi phần tử lớn nhất của nửa trái đã nhỏ hơn hoặc bằng phần tử nhỏ nhất của nửa phải giúp giảm số lần so sánh
  * Output Buffering để tạo 1 string cực dài và toàn bộ kết quả được nối trực tiếp vào chuỗi này và thực hiện xuất chỉ bằng một lệnh I/O duy nhất.
  * Lưu trước mảng lenArr để mỗi lần so sánh 2 chuỗi thì không cần phải gọi lại hàm .size()
