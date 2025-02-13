#!/bin/bash

# 設定編譯時標頭檔 & 庫的搜尋路徑
export CPATH=/usr/local/include:$CPATH
export LIBRARY_PATH=/usr/local/lib:$LIBRARY_PATH

# 設定執行時動態連結庫的搜尋路徑
export DYLD_LIBRARY_PATH=/opt/homebrew/lib:/opt/homebrew/opt/openal-soft/lib:$DYLD_LIBRARY_PATH

export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH
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
