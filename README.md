 ## OpenCVforAE
adobe after effectsのエフェクトプラグインでオープンソースの画像
ライブラリ[OpenCV](https://github.com/opencv/opencv)を使う為のスケルトンプロジェクトとライブラリです。  
なるべく楽にエフェクトプラグインが作れるように工夫してあります。  
スケルトンプロジェクトの**OpenCVSkelton**を使えばだれでもプラグインが作れます。

 ## Description
 * Visual studio 2017 Community 2017 C++
 * OpenCV v3.4.6 [https://github.com/opencv/opencv/releases](https://github.com/opencv/opencv/releases)
 * Adobe After Effects CC 15.0 Win SDK
 * Windows10(64bit)
 * Adobe after effects CS6 orCC2018
自分が主にデバッグに使用しているのはCS6ですが、SDKはCC2018で最終的にCC2018での動作確認をしています。  
    
  OpenCVのバージョンはネットに資料が多そうなOpenCV3にしていますが、プロジェクトの設定を変えれば他のバージョンでも動くと思います。OpenCV自体は自分自身が触り始めたばかりなのでなんともいえません。    

 このライブラリはサンプルプロジェクト**OpenCVSkelton**とライブラリで構成されています。
 ファイル構成は以下の通りです。
```
\OPENCVFORAE
│  OpenCVforAE.sln //visual studioソリューションファイル
├─Lib
│      CAE.h       //コーディングを楽にするためのクラス
│      CAEcv.h     //OpenCVをプラグイン内で使う為の関数が入ったクラス
│      FsUtils.h   //F's Pluginsから持ってきたマクロ等。
│      
├─OpenCVSkelton
│  │  OpenCVSkelton.cpp      //プラグインのUI部品登録等、記述に必要なもの
│  │  OpenCVSkelton.h        //プラグイン固有のものが定義されるもの
│  │  OpenCVSkeltonPiPL.r    //PiPLリソース。基本的に書き換え不要
│  │  OpenCVSkelton_Entry.h  //OpenCVSkelton.cppで使う変更不要なコードをまとめたもの
│  │  OpenCVSkelton_Target.h //プラグイン固有のものが定義されるものその２
│  │  
│  └─Win
│      │  OpenCVSkelton.vcxproj
│      │  OpenCVSkelton.vcxproj.filters
│      │  OpenCVSkelton.vcxproj.user
│      │  OpenCVSkeltonPiPL.aps
│      │  OpenCVSkeltonPiPL.rc
├─outPlugins
└─utils
        AE_Effects_Version.exe    // バージョン定数を計算するアプリ
        AE_out_flags.exe          // out_flagsを計算するアプリ
        CPP_ProjectRename.exe     // C++のソース内の文字を置換するアプリ
                                  // OpenCVSkeltoをリネームするときに使う
```
utilsに入っているアプリは、バージョン及びout_flagsの定数はsdkではマクロで実装していますが、
PiPLリソースのコンパイルの都合で記述がマクロで処理できなく結局自前で計算する必要があるので作ったものです。  
計算するならマクロ展開やめて一か所書き換えればいいようにしています。

## Usage
OpenCVv3.4.6をインストールしてください。  
"C:\opencv"へインストールすれば、プロジェクトの書き換えの必要はありません。  
PATHに"C:\opencv\build\x64\vc15\bin"を追加しておくと楽です。  
  
oepncv自体のインストールは特に問題ないと思います。大変なのはVisualStudioの設定です。これは別に書きます

このプロジェクトファイル自身はSDKフォルダ内のExampleフォルダ内へ配置してください。  
こんな感じです。  
```
\ADOBESDK\ADOBE AFTER EFFECTS CC 15.0 WIN SDK
├─Examples
│  ├─AEGP
│  ├─Effect
│  ├─F's PluginsProjects
│  ├─Headers
│  ├─OpenCVforAE
│  │  ├─Lib
│  │  ├─OpenCVSkelton
│  │  └─utils
│  ├─Resources
│  ├─Template
│  ├─UI
│  └─Util
```
プラットホームはx64のみになります。

デバッグ時はdll出力先をAfter Effectsのplug-insフォルダへ設定すれば、デバッガが使用できます。

重要なのはプロジェクトのプロパティでincludeするヘッダーやライブラリの設定です。  
プロジェクトのプロパティで注意するところは以下の点  
 * 構成プロパティ/VC++プロパティ/VC++ディレクトリ/インクルードディレクトリ  
$(VC_IncludePath);$(WindowsSDK_IncludePath);**C:¥opencv¥build¥include**
 * 構成プロパティ/VC++プロパティ/VC++ディレクトリ/ライブラリディレクトリ  
$(LibraryPath);**C:¥opencv¥build¥x64¥vc15¥lib**
 * C/C++/全般/追加のインクルードディレクトリ 
..\..\..\Headers;..\..\..\Headers\SP;..\..\..\Resources;..\..\..\Util;..\..\Lib;**C:\opencv\build\include**
 * C/C++/コード生成/構造体メンバーのアライメント  
**8バイト(/Zp8)** もしくは **16バイト(/Zp16)**
 * リンカー/全般/追加のライブラリディレクトリ  
**C:\opencv\build\x64\vc15\lib**
 * リンカー/入力/追加の依存ファイル  
%(AdditionalDependencies);**opencv_world346d.lib** //デバッグ時  
%(AdditionalDependencies);**opencv_world346.lib** //リリース時

結構はまります。絶対あってるのに**opencv_world346.lib**や**opencv_world346.lib**がないとエラーが出たら、visual studioを再起動させるか、いったん設定から外して再度登録すると何故かうまくいく時があります。

# License
This software is released under the MIT License, see LICENSE.txt. 
  

## Authors

bry-ful(Hiroshi Furuhashi) [http://bryful.yuzu.bz](http://bryful.yuzu.bz)
twitter:[bryful](https://twitter.com/bryful)  
bryful@gmail.com  

# References

