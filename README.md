# **SFML 遊戲專案開發環境設定指南**

### 執行輸入

複製編輯

```
rm -rf build
mkdir build
cd build
cmake -S .. -B . -DSFML_DIR=/usr/local/lib/cmake/SFML
make
./GameProject
```

## **1️⃣ 必要的環境變數設定**

請確保你的 `.zshrc`（或 `.bashrc`）中包含以下設定，以避免執行時找不到 SFML 的標頭檔和 `.dylib`。

### **📂 設定編譯時的標頭檔與庫的搜尋路徑**

複製編輯

```
export CPATH=/usr/local/include:$CPATH
```

```
export LIBRARY_PATH=/usr/local/lib:$LIBRARY_PATH`
```

### **⚡ 設定執行時的動態連結庫搜尋路徑**

複製編輯

```
export DYLD_LIBRARY_PATH=/opt/homebrew/lib:/opt/homebrew/opt/openal-soft/lib:$DYLD_LIBRARY_PATH
```

```
export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH
```

📌 **這些變數的用途：**

- `CPATH`：讓編譯器（如 `clang++`）可以找到 SFML 的標頭檔（`SFML/Graphics.hpp`）。
- `LIBRARY_PATH`：讓編譯器可以找到 SFML 的靜態或動態庫（`.dylib`）。
- `DYLD_LIBRARY_PATH`：讓 macOS 的動態連結器 `dyld` 在執行時能找到 SFML 所需的 `.dylib`。

📌 **如何永久生效？**
執行以下指令，將環境變數存入 `~/.zshrc`：

複製編輯

```
echo 'export CPATH=/usr/local/include:$CPATH' >> ~/.zshrc echo 'export LIBRARY_PATH=/usr/local/lib:$LIBRARY_PATH' >> ~/.zshrc echo 'export DYLD_LIBRARY_PATH=/opt/homebrew/lib:/opt/homebrew/opt/openal-soft/lib:$DYLD_LIBRARY_PATH' >> ~/.zshrc echo 'export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH' >> ~/.zshrc source ~/.zshrc
```

---

## **2️⃣ 常見錯誤 & 解決方案**

### **❌ **`dyld: Library not loaded: libsfml-graphics.2.6.dylib`

**🔹 解決方法：**

- **確認 **`.dylib`** 是否存在**：

  複製編輯

  ```
  ls /usr/local/lib/libsfml-*.dylib`
  ```

  如果檔案缺失，請重新下載或安裝 SFML。

- **嘗試手動增加 **`rpath`：

  複製編輯

  ```
  install_name_tool -add_rpath /usr/local/lib ./build/GameProject
  ```

---

## **3️⃣ 編譯 & 執行**

**使用 CMake 建立專案並編譯：**

複製編輯

```
rm -rf build mkdir build cd build cmake -S .. -B . -DSFML_DIR=/usr/local/lib/cmake/SFML make
```

**執行遊戲**

複製編輯

```
./build/GameProject
```

## **我最後是使用 runGame.sh 腳本來編譯和執行遊戲**

\*但因為 Bash 不會繼承 zsh 設置的環境變數，導致 ./GameProject 找不到 SFML 的函式庫。所以要在 runGame.sh 裡加入:

複製編輯

```
echo 'export CPATH=/usr/local/include:$CPATH' >> ~/.zshrc echo 'export LIBRARY_PATH=/usr/local/lib:$LIBRARY_PATH' >> ~/.zshrc echo 'export DYLD_LIBRARY_PATH=/opt/homebrew/lib:/opt/homebrew/opt/openal-soft/lib:$DYLD_LIBRARY_PATH' >> ~/.zshrc echo 'export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH' >> ~/.zshrc source ~/.zshrc
```

\*然後在終端輸入:

複製編輯

```
bash runGame.sh
```

\*即可
