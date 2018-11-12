# KXR_ROSE
二足歩行ロボットKXR-L2をGR-ROSEで制御するファームウェア

## できること
- 二足歩行ロボットKXR-L2をスマホでラジコン操縦
- 歩行、起き上がり、パンチなどのモーション
    - 一部のモーションはバランスが悪く、コケる

## まだできてないこと
- モーション作成ツール
- モーションデータをSDカードからロード
- 姿勢制御に6軸センサからのフィードバック
- プレステコントローラでの操縦
- ROS2対応

## ターゲット
- ロボット: 近藤科学 KXR-L2
- ボード: GR-ROSE (ベータ版)
- 開発環境: IDE for GR 1.04 + GR-ROSEベータ版サポート (rx65n_004.zip)

## GR-ROSEの接続
- 電源(Vm): 6セルNi-MHバッテリーを接続
- Serial1: 右足系と右腕系を接続
- Serial2: 左足系と左腕系を接続
- USB: USBシリアルポート (開発用)
- #21ピン: GNDに短絡して電源ONするとESP8266書き換えモードになる(後述)
- #22ピン: GNDに短絡して電源ONするとUSBシリアルポートに's'が送られてくるまでロボットを起動しない。(開発用)

## ESP8266のファームウェア
GR-ROSEにはESP8266が搭載されており、出荷時にはATコマンド用のファームウェアが書かれている。本プロジェクトではESP8266のファームウェアを下記のGPduino-Mに書き換えて使用する。
- [GPduino-M](https://github.com/lipoyang/GPduinoM)
### ファームウェアの書き換え方法
本プロジェクトのファームウェアをGR-ROSEに書き込み、#21ピンをGNDに短絡して起動すると、GR-ROSEはUSBシリアル⇔Serial6ブリッジになる。この状態でGR-ROSEとPCをUSBで接続する。

ESP8266ボードをインストールしたArduino IDE環境でGPduinoMのスケッチを開き、シリアルポートを選んで書き込む。(ESP8266ボードのインストールと設定についてはググってください。)

## Android用WiFiラジコンアプリ
Android端末に下記のアプリをインストールしてWiFiラジコンのコントローラとする。
- [GP Remocon (Android版)](https://github.com/lipoyang/GPRemocon-Android)


### コマンド表
下記コマンド表のボタン操作で各種モーションを実行できる。
- [コマンド表](command.pdf)

## 動画
[![GR-ROSE(ベータ版)でロボットの制御](https://img.youtube.com/vi/Kdf4wtiY5I4/0.jpg)](https://www.youtube.com/watch?v=Kdf4wtiY5I4)

## 発表資料
[![thumbnail](https://image.slidesharecdn.com/gr-rose-181110105007/95/kxrl2grrose-1-638.jpg)](https://www.slideshare.net/lipoyang/kxrl2grrose)

## モーションについて
まだ自前のモーション作成ツールがない状況です。本プロジェクトでハードコーディングされているモーションは、近藤科学のモーション作成ツールHeartToHeart4用に提供されているKXR-L2用サンプルモーションから関節角度と時間のデータを抽出して流用しています。
- [KXR-L2用サンプルプロジェクトV1.1](https://kondo-robot.com/faq/kxr-l2_samplev1_1)

KXR-L2用サンプルプロジェクトV1.1の著作権は近藤科学株式会社に帰属します。

HeartToHeart4のデータはXML形式であり、ツールを作成して容易にデータを抽出することができますが、作成したツールの公開は差し控えます。
