# raspi karnel

https://www.tssol.net/blog/2020/03/28/raspberrypi-how-to-build-kernel/#%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB%E5%AF%BE%E8%B1%A1%E3%81%AEraspberry-pi%E6%9C%AC%E4%BD%93%E3%81%AB%E5%AF%BE%E5%BF%9C%E3%81%97%E3%81%A6%E3%81%84%E3%82%8B%E3%81%8B%E3%83%81%E3%82%A7%E3%83%83%E3%82%AF

https://aquarius-train.hatenablog.com/entry/Raspberry_Pi_OS%E3%81%AE%E3%82%AB%E3%83%BC%E3%83%8D%E3%83%AB%E3%82%BD%E3%83%BC%E3%82%B9%E3%83%93%E3%83%AB%E3%83%89%E6%89%8B%E9%A0%86%E8%A7%A3%E8%AA%AC

## 環境のインストール
### ビルドに必要なモジュール
```shell
$ sudo apt install git bc bison flex libssl-dev make 
```
### カーネルソース
```shell
$ git clone --depth=1 https://github.com/raspberrypi/linux
```
### compiler
```shell
$ sudo apt install g++-arm-linux-gnueabihf
```
<br>

## 環境変数の設定
```shell
$ export ARCH=arm
$ export KERNEL=kernel7
$ export CROSS_COMPILE=arm-linux-gnueabihf-
```
<br>

## クロスコンパイル
### .config(kernel パラメーター設定)ファイル
```shel
cd linux
make bcm2709_defconfig
```

### build
```shell
make -j4 zImage modules dtbs
```

### install
```shell
sudo make modules_install
```
<br>

## SDカードへのコピー
### SD mount
 #### boot
```shell
sudo mkdir /mnt/g
sudo mount -t drvfs G: /mnt/g
```
 #### root
```shell
sudo mkdir /mnt/e
sudo mount -t drvfs E: /mnt/e
```

### COPY
```shell
$ sudo cp arch/arm/boot/zImage /mnt/g/kernel7.img
$ sudo cp arch/arm/boot/dts/*.dtb /mnt/g
$ sudo cp arch/arm/boot/dts/overlays/*.dtb* /mnt/g/overlays
$ sudo cp -r /lib/modules/5.4.74-v7l+ /mnt/e/lib/modules
```