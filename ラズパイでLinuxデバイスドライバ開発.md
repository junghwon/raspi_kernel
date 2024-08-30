# ラズパイでLinuxデバイスドライバ開発

## 環境構築
###  参考サイト
https://blog.natade.net/2020/03/05/raspberry-pi-arm-linux-driver/

## ドライバの実装
###  参考サイト
組み込みLinuxデバイスドライバの作り方 (1)
https://qiita.com/iwatake2222/items/1fdd2e0faaaa868a2db2

export CROSS_COMPILE=~/pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf- make -j4