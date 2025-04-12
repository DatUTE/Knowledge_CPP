## Command Linux
- `reference`: https://kb.hostvn.net/danh-sach-nhng-lnh-command-co-ban-tren-linux_121.html
### Lệnh liên quan đến hệ thống 
- exit: thoát khỏi cửa sổ dòng lệnh.
- logout: tương tự exit.
- reboot: khởi động lại hệ thống.
- halt: tắt máy.
- startx: khởi động chế độ xwindows từ cửa sổ terminal.
- mount: gắn hệ thống tập tin từ một thiết bị lưu trữ vào cây thư mục chính.
- unmount: ngược với lệnh mount.
### Lệnh thao tác trên tập tin 
- ls: lấy danh sách tất cả các file và thư mục trong thư mục hiện hành.
- pwd: xuất đường dẫn của thư mục làm việc.
- cd: thay đổi thư mục làm việc đến một thư mục mới.
- mkdir: tạo thư mục mới.
- rmdir: xoá thư mục rỗng.
- cp: copy một hay nhiều tập tin đến thư mục mới.
- mv: đổi tên hay di chuyển tập tin, thư mục.
- rm: xóa tập tin.
- wc: đếm số dòng, số kí tự... trong tập tin.
- touch: tạo một tập tin.
- cat: xem nội dung tập tin.
- vi: khởi động trình soạn thảo văn bản vi.
- df: kiểm tra dung lượng đĩa.
- du: xem dung lượng đĩa đã dùng cho một số tập tin nhất định
- nano: Khởi dộng trình soạn thảo văn bản nano
- less: Xem nội dung tập tin theo dòng
- tail: Xem nội dung tập tin (mặc định xem 10 dòng cuối, muốn xem 100 dòng cuối thì dùng lệnh sau: tail 100 tenfile)
- more: Xem nội dung tập tin theo trang
- head: Xem nội dung tập tin (mặc định xem 10 dòng đầu, muốn xem 100 dòng đầu thì dùng lệnh sau: head 100 tenfile)
### Lệnh khi làm việc trên terminal 
- clear: xoá trắng cửa sổ dòng lệnh.
- date: xem ngày, giờ hệ thống.
- cal: xem lịch hệ thống.
### Lệnh quản lí hệ thống 
- rpm: kiểm tra gói đã cài đặt hay chưa, hoặc cài đặt một gói, hoặc sử dụng để gỡ bỏ một gói.
- ps: kiểm tra hệ thống tiến trình đang chạy.
- kill: dừng tiến trình khi tiến trình bị treo. Chỉ có người dùng super-user mới có thể dừng tất cả các tiến trình còn người dùng bình thường chỉ có thể dừng tiến trình mà mình tạo ra.
- top: hiển thị sự hoạt động của các tiến trình, đặc biệt là thông tin về tài nguyên hệ thống và việc sử dụng các tài nguyên đó của từng tiến trình.
- pstree: hiển thị tất cả các tiến trình dưới dạng cây.
- sleep: cho hệ thống ngừng hoạt động trong một khoảng thời gian.
- useradd: tạo một người dùng mới.
- groupadd: tạo một nhóm người dùng mới.
- passwd: thay đổi password cho người dùng.
- userdel: xoá người dùng đã tạo.
- groupdel: xoá nhóm người dùng đã tạo.
- gpasswd: thay đổi password của một nhóm người dùng.
- su: cho phép đăng nhập với tư cách người dùng khác.
- groups: hiển thị nhóm của user hiện tại.
- who: cho biết ai đang đăng nhập hệ thống.
- w: tương tự như lệnh who.
- man: xem hướng dẫn về dòng lệnh như cú pháp, các tham số...
Để hiểu và sử dụng tốt các câu lệnh trên, các bạn nên sử dụng lệnh man với cú pháp: man ten_cau_lenh để có được những thông tin đầy đủ về chức năng cũng như cú pháp của câu lệnh.

### Các câu lệnh kiểm tra thông tin hệ thống (system information) trong Linux
- cat /proc/cpuinfo: Kiểm tra thông tin CPU (số core)
- cat /proc/meminfo: Kiểm tra thông tin về RAM đang sử dụng
- cat /proc/version: Kiểm tra phiên bản của Kernel Linux
- cat /proc/ioports: Xem thông tin port I/O
- cat /etc/redhat-release: Kiểm tra phiên bản Centos
- uname -a: Kiểm tra các thông tin về Kernel
- free -m: Kiểm tra dung lượng RAM còn trống
- init 0: Tắt máy (tương đương lệnh shutdown -h now hoặc telinit 0)
- df -h: Hiển thị thông tin những file hệ thống, nơi file được lưu hoặc tất cả những file mặc định. Lệnh này có thể xem được dung lượng ổ cứng đã sử dụng và còn trống.
- du -sh	Kiểm tra dung lượng thư mục hiện tại
- du  -ah	Hiển thị dung lượng của thư mục con và các file trong thư mục hiện tại
- du -h –max-depth=1	Hiển thị dung lượng các thư mục con ở cấp 1 (ngay trong thư mục hiện tại)
- df	Kiểm tra dung lượng đĩa cứng, các phân vùng đĩa
- lspci	Xem thông tin mainboard   /sbin/ifconfig Xem các địa chỉ IP của máy
- hostname	Xem tên máy (hostname)
- finger user@server	Thu thập thông tin chi tiết về người dùng hiện đang dùng hệ thống
- arch	Kiểm tra kiến trúc của máy (architech)
- cat /proc/swaps	Kiểm tra thông tin SWAP của máy (tương tự như virtual RAM của Windows)
- last reboot	Xem lịch sử reboot máy
Các lệnh shutdown, restart… trong Linux

### Lệnh Linux	Mô tả
- logout	Kết thúc session (phiên làm việc) hiện tại
- reboot	Khởi động lại máy
- shutdown -r now	Khởi động lại máy (tương đương với lệnh reboot)
- shutdown -h now	Tắt máy (ngay lập tức)
- shutdown -h 9:30	Hẹn giờ tắt máy (schedule) vào lúc 9h30 (tính theo khung 24h)
- shutdown -c	Hủy bỏ tất cả các lệnh tắt máy trước đó (các lệnh tắt máy theo schedule)
- telinit 0	Tắt máy (tương đương lệnh shutdown -h now)
- init 0	Tắt máy (tương đương lệnh shutdown -h now hoặc telinit 0)
- exit	Thoát khỏi terminal
- halt	Tắt máy (tương tự shutdown)
- sleep	Cho hệ thống ngừng hoạt động trong một thời gian (ngủ – tương tự Windows)

### Các lệnh Quản lý services và process trong Linux
- top	Lệnh top khá giống như Task Manager trong Windows. Nó đưa ra thông tin về tất cả tài nguyên hệ thống, các process đang chạy, tốc độ load trung bình… Lệnh top -d thiết lập khoảng thời gian làm mới lại hệ thống
- wget	Tải các ứng dụng từ một website về
- sh	Chạy một ứng dụng có đuôi .sh
- kill PID hoặc %job	Ngừng một process bằng số PID (Process Identification Number) hoặc số công việc
- pstree	Hiển thị tất cả các process dưới dạng cây
- service –status-all	Kiểm tra tất cả các service và tình trạng của nó
- whereis mysql	Hiển thị nơi các file dịch vụ được cài đặt
- service –status-all | grep abc	Xem tình trạng của process abc
- kill -9 PID	Bắt buộc đóng một process ID
- kill -1 PID	Bắt buộc đóng một process ID và load lại cấu hình mặc định của process đó

### Một số lệnh hữu ích khác trong Linux
- clear	Xoá trắng cửa sổ dòng lệnh
- hwclock	Fix lịch của BIOS
- cal	Xem lịch hệ thống
- date	Xem lịch ngày, giờ hệ thống
- date –s “1 JAN 2018 15:29:00”	Đặt ngày giờ hệ thống theo string
- date +%Y%m%d -s “20180101″	Đặt ngày hệ thống (không thay đổi giờ)
- date +%T -s “00:29:00″	Đặt giờ hệ thống, không thay đổi ngày

### Lệnh nén và giải nén trong Linux 
- tar -cvf	Nén file/thư mục sang định dạng .tar
- tar -xvf	Giải nén file tar
- gzip	Chuyển file .tar sang .tar.gz
- gunzip	Chuyển file .tar.gz về .tar
- tar -xzf	Giải nén file .tar.gz, ví dụ:  tar -xvf archive.tar
- tar -zxvf	Giải nén file .tar.bz2
- tar -jxvf	Giải nén file .tar.gz2
- unzip	Giải nén file zip