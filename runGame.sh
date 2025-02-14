#!/bin/zsh

# 設定編譯時標頭檔 & 庫的搜尋路徑
# 這些變數影響的是 **編譯階段**，但 CMake 本身已經能夠找到標頭檔和函式庫，
# 所以如果你的 CMakeLists.txt 正常運作，那麼這兩行 **可以註解掉**。
# export CPATH=/usr/local/include:$CPATH  # 指定 C/C++ 編譯器查找標頭檔 (.h, .hpp) 的路徑
# export LIBRARY_PATH=/usr/local/lib:$LIBRARY_PATH  # 指定編譯時要查找靜態庫 (.a) 或共享庫 (.dylib) 的路徑


# 設定執行時動態連結庫的搜尋路徑
# 這行的作用是讓執行時 (runtime) 可以找到 **Homebrew 安裝的函式庫 (如 SFML 依賴的 OpenAL)**
# 但你的 SFML 不是從 Homebrew 安裝的，而且 OpenAL 可能已經安裝在 /usr/local/lib，
# 所以這行 **可能可以註解**，但需要確認 OpenAL 是否真的在 /usr/local/lib
export DYLD_LIBRARY_PATH=/opt/homebrew/lib:/opt/homebrew/opt/openal-soft/lib:$DYLD_LIBRARY_PATH


# 這行是 **讓執行時可以找到 SFML 的函式庫**
# 你的 SFML .dylib 檔案位於 /usr/local/lib，所以這行 **不能註解**                                                           
export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH 


# 設定編譯器 LLVM (clang++) 的路徑，確保 CMake 和 make 使用正確的工具鏈
# 如果你的編譯環境 **沒有使用 Homebrew 安裝的 LLVM**，這行可以註解。
# 但如果 CMake 需要這個路徑來找到 clang++，這行就不能註解。                                                          
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

# 定義顏色
RED='\033[0;31m'
ORANGE='\033[38;5;214m' # 這個是較接近橘色的 ANSI 256 顏色
NC='\033[0m'            # No Color

set -e # 啟用錯誤檢查

echo -e "${ORANGE}開始編譯遊戲...${NC}"

rm -rf build
mkdir -p build

cd build || {
  echo "${RED}無法進入 build 目錄${NC}"
  exit 1
}

cmake -S .. -B . -DSFML_DIR=/usr/local/lib/cmake/SFML
make || {
  echo -e "${RED}編譯失敗${NC}"
  exit 1
}

echo -e "${ORANGE}編譯完成，啟動遊戲...${NC}"
./GameProject || {
  echo -e "${RED}遊戲執行失敗${NC}"
  exit 1
}

echo -e "${ORANGE}遊戲執行成功！${NC}"
