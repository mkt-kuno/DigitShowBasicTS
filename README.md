# DigitShowBasicTS 中空ねじり三軸試験版

![Github License](https://img.shields.io/github/license/mkt-kuno/DigitShowBasicTS)  [![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)

## 簡単な説明

東京大学の地盤研で使用されている、三軸試験機制御ソフトウェア [DigitShowBasic](https://github.com/mkt-kuno/DigitShowBasic)（以降DSB）を、**中空ねじり三軸試験（中空円筒供試体への軸荷重とねじりトルクの独立制御）用に拡張した版**です。  
ContecのAD/DAボードで動作させることを前提としています。  
オリジナルのDSB（一般三軸試験版）は[こちら](https://github.com/mkt-kuno/DigitShowBasic)。ModbusRTUのAD/DAは[DigitShowBasicM](https://github.com/mkt-kuno/DigitShowBasicM)まで。  
このリポジトリはDSBと同じく **GPLv3** です。注意してください。    

## 本バージョンの特徴

### ねじり載荷系の制御

D/A出力によりねじり駆動系を制御します。

| DAチャンネル | 内容 | 備考 |
|------|----|----|
| CH04 | ねじりモータ ON/OFF | 0V: On, 5V: Off |
| CH05 | ねじりクラッチ | |
| CH06 | ねじりモータ回転数 | 校正係数 V/RPM で設定 |

### 制御モード

軸載荷とねじり載荷の各種制御モードを実装しています。

- 単調ねじり載荷（Monotonic Torsional Loading）/ CNS 版
- 繰返しねじり載荷（Cyclic Torsional Loading）/ CNS 版 / 小振幅版
- 単調軸載荷（Monotonic Axial Loading）/ Const-P 版
- 繰返し軸載荷（Cyclic Axial Loading）/ 小振幅版
- 有効応力経路載荷（Effective Stress Path Loading）
- クリープ（Creep）
- ファイル制御圧密（File Controllable Consolidation）

### ねじりメンブレン力の補正

中空円筒供試体の内外径、ゴム膜の弾性係数・厚さから、ねじり方向のメンブレン抵抗トルクを算出・補正します（`DigitShowBasicDoc.cpp` 内 `TorqueM`）。  
実装は Hashimoto による修正（2022.12.28, TorqueM のみ考慮）に基づきます。

### 電子天秤との RS232C 連携

RS232C経由で電子天秤の読み取りを行い、含水比管理等に使用できます。

## 動作環境

- Windows 11  
x64のみ
- Visual Studio 2022
Community版でOK, MFCライブラリ必須  
- CONTEC API-AIO(WDM) Ver.9.20 
適宜、CAIO.H, CAIO.LIBを置き換えて使用するDLLバージョン一致させれば最新版でも可。
- CPU: x64 Intel/AMD問わず  
[Passmark性能(マルチスレッド)](https://www.cpubenchmark.net/multithread/) 最低5000 推奨8000以上
- RAM: 最低4GB 推奨8GB以上  
他に動かすアプリケーション次第。MS Officeは重い。
- GPU: 依存なし、iGPU/dGPU/APU いずれも可
- 液晶: 最低XGA 推奨FHD以上  
縦長画面だと表示が見切れると思います。
- 記憶媒体: 最低HDD 推奨SSD  
容量はビルドPCと動作PCが同じなら最低128GB 推奨256GB

### Contecボードのデバイス名

ADボードのデバイス名は`AIO000`、DAボードのデバイス名は`AIO001`に固定しています。  
デバイスマネージャで確認して、もし異なっている場合は、デバイス名を変更してください。  
変更できない場合は、非表示のデバイスを表示すると、該当デバイス名を占有したAIOボードが見つかるはずです。

### AIスキャンクロックの自動設定

比較的新しいCONTECドライバでは、AI計測開始前に必ず `AioSetAiScanClock()` を設定する必要があります。  
本ソフトウェアは `SamplingClock ÷ 有効チャンネル数` を**切り捨てた値**（例: 1000µs / 16ch → 62µs、安全側に丸め）を起動時およびサンプリング設定変更時に自動設定します。  

## 注意点

- 本ソフトウェアの動作について、一切の保証を行いません。
- 本ソフトウェアの使用により発生したいかなる損害についても、一切の責任を負いません。
- 本ソフトウェアを使用する場合は、自己責任で行ってください。
- 本ソフトウェアの動作または初期設定についてのサポートは行いません。

## ライセンスについて

一部の大学・企業・研究所では秘伝のタレ状態のDigitShowBasicをお持ちだと思います。  
当時(2010年頃)配布されたDigitShowBasicのソースコードは何もライセンスが決められていませんでした。  
そのため、お持ちの古いDigitShowBasicは高確率でライセンスフリーのハズです。  
ですが、このリポジトリはDSBと同じくGPLv3です。このコードを安易に参考・参照・引用した場合GPLv3に感染するので、  
GPLv3とは何か知ったうえで、覚悟して使い始めてください。  
ざっくりといえば、改変部分がある場合、ソースコードを公開する必要があります。

## バグ報告やプルリクエストについて

基本的な方針は[DSB本体](https://github.com/mkt-kuno/DigitShowBasic)に準じます。  
「どう使うの？」「ボードが認識しない」「設定方法を教えてほしい」などの初歩的な質問は避けてください。無視します。  
貢献する意思のある、オープンソースの理念に沿った要求は大歓迎します。  
本バージョン固有の不具合（ねじり載荷、メンブレン補正等）については、このリポジトリのIssueへお願いします。  
「うちのコードとかなり違う」「そもそも動作しないし落ちる」などの場合は、  
AI協業でリファクタリングする前の[legacy版](https://github.com/mkt-kuno/DigitShowBasicTS/tree/legacy)で試してみて下さい。
