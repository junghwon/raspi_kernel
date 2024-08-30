# ラズパイでLinuxデバイスドライバ開発

## 環境構築
###  参考サイト
https://blog.natade.net/2020/03/05/raspberry-pi-arm-linux-driver/
https://www.raspberrypi.com/documentation/computers/linux_kernel.html#cross-compiling-the-kernel

### ビルド (パターン1)
export ARCH=arm
export KERNEL=kernel
make bcmrpi_defconfig
export CROSS_COMPILE=~/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-
make -j4

### ビルド (パターン2)
パターン1でGCCバージョンのエラーが出る場合、パターン2でビルドする

・ツールチェインのインストール
sudo apt install bc bison flex libssl-dev make libc6-dev libncurses5-dev
sudo apt install crossbuild-essential-arm64

・ビルド
cd raspberrypi/linux
KERNEL=kernel8
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcm2711_defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- Image modules dtbs


## ドライバの実装
###  参考サイト
組み込みLinuxデバイスドライバの作り方 (1)
https://qiita.com/iwatake2222/items/1fdd2e0faaaa868a2db2

