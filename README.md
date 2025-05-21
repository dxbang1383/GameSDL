# 🔫 2D Shooting Game - Đỗ Xuân Bằng (MSSV: 24021383)

Đây là một trò chơi bắn nhau 2D đơn giản được phát triển bằng SDL2. Trò chơi mô phỏng các nhân vật có thể di chuyển, nhảy, và chiến đấu trên nhiều nền tảng vật cản. Nhân vật có khả năng nhảy xuyên qua vật cản nếu đi từ dưới lên, và có thể đứng, nhảy hoặc di chuyển trên các vật cản một cách hợp lý.

## 🎮 Chế độ chơi

### 1. 🧍‍♂️ Người chơi với người chơi (PVP)
- Có 2 người chơi điều khiển thông qua bàn phím:
  - **Người chơi 1**
    - Di chuyển: `A`, `D`
    - Nhảy: `W`
    - Bắn: `Space`
  - **Người chơi 2**
    - Di chuyển: `←`, `→`
    - Nhảy: `↑`
    - Bắn: `Enter`

- **Luật chơi:**
  - Nếu một người bị bắn **vào phía trước mặt**, họ sẽ chết và được hồi sinh tại vị trí phía trên cùng trục X.
  - Nếu bị bắn **vào sau lưng**, nhân vật không chết.
  - Mỗi lần tiêu diệt đối phương, người chơi sẽ được cộng **1 điểm**.

---

### 2. 🤖 Người chơi với Bot (PvE)
- Người chơi sẽ điều khiển theo bộ điều khiển của **Người chơi 1**.
- Bot sẽ xuất hiện ngẫu nhiên và **bị tiêu diệt khi trúng đạn**.
- **Bot boss** sẽ bắn một viên đạn về phía người chơi sau một khoảng thời gian nhất định.
- Mỗi lần tiêu diệt một bot, người chơi được cộng **1 điểm**.
- Người chơi có **3 mạng**. Nếu hết 3 mạng, trò chơi sẽ quay lại màn hình chính.

---

## ⚙️ Cài đặt và chạy

### 📦 Yêu cầu:
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf 


