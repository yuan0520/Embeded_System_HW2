# Embedded System HW2

## (1) how to setup and run my program

在這次的作業中，我在 **main.cpp** 中實作了包含 uLCD、button、調整波的頻率，以及 sample data 等等工作。並利用和 Lab 時相同的 **FFT.py** 去畫出 waveform 以及 frequency 的圖。


### 1. uLCD 選單 

首先，我設計了 `menu` 這個 function 來控制 uLCD 的顯示，利用傳入的 `freq_pos` 的值來選擇顯示的樣式，如下圖，初始值為選擇 10Hz 的頻率，可以透過 button 的操作來改變 `freq_pos` 的值，進而操作選單，等等會在介紹 `freq_pos` 這個 counter 的操作方式。

<div align=center><img src="https://i.imgur.com/A2BnRzd.png" width="50%" height="50%" /></div>


### 2. button 之操作

在 main function 的一開始，我先宣告了`freq_pos` 這個 counter 和 `freq_scale` 這個變數，`freq_pos` 是用來控制在 uLCD 上該選擇哪個頻率的波，而 `freq_scale` 則是用來計算使用者選擇的波的真實頻率大小（base 為 100Hz），實作如下圖：

<div align=center><img src="https://i.imgur.com/Py89bxh.png" width="50%" height="50%" /></div>


### 3. 變數宣告

接下來我宣告了一些變數，`wavelength_scale` 就是使用者選擇的頻率對應的波長，大小為 1 / `freq_scale`。

再來是 `S` 的值，因為我的學號是 `107060002`，所以 `S` 值為 (1+0+7+0+6+0+0+0+2) mod 10 = 6，所以我的波的 peak 值會在第六格，也代表電壓上升之時間間隔 `up_len` 為 1/6，電壓下降之時間間隔 `down_len` 為 1/(10-6)。

再來因為我要 sample 1000 個 data，所以將變數 `sample` 值定為 1000，而 `ADCdata` 這個 array 就是用來存 sample 出來的 data 的，我將他的大小開超過 1000 以利安全。而因為我只要在 screen 中 print 一次我 sample 出來的資料，所以我設一個 `flag`，如果 print 過了就將 `flag` 設為 1，就不會再跑進去 print data 的地方了。`idx` 則是在存 data 時控制的 index 值。

<div align=center><img src="https://i.imgur.com/WeH7MME.png" width="60%" height="60%" /></div>


### 4. 控制波的部分、I/O

因為要將波呈現在 picoscope 中，所以我將電壓上升和下將分成兩個迴圈來寫，而因為我把電壓上升和下將的時間間隔設為一個定值，所以當頻率改變時，必須去調整上升到 peak 以及下降到 0 的速率，因此迴圈要跑的次數就會被 `wavelength_scale` 這個變數所控制，若波長較大時，迴圈就要跑較多次。

但 aout 值的 scale 不應該受到頻率的影響，所以會將迴圈中的 i, j 值再乘上 `freq_scale`，讓 aout 的值回到一樣的 scale。

我是以 100 Hz 當作頻率的 base，所以波的值每隔 1ms 會調整一次，而為了讓畫出來的圖儘量符合原始的 waveform，我便每 1ms sample 一個 data。

<div align=center><img src="https://i.imgur.com/3576MO0.png" width="50%" height="50%" /></div>

---

## (2) what are the results

透過公式，我算出來 RC-based low-pass filter 的 cut-off frequency 為 **25 Hz**，因此我選擇了 `10 Hz`、`25 Hz`、`50 Hz`，以及 `100 Hz`四種頻率來作圖及觀察。

經過實驗後，可以看出隨著頻率越來越大，尤其是當頻率超過 `25 Hz` 這個 cut-off frequency 時，波的 amplitude 確實會小很多，下面四張圖為我的實驗結果：


### 1. 10 Hz

<img src="https://i.imgur.com/Wd8Dpwu.png" width="50%" height="50%" />


### 2. 25 Hz

<img src="https://i.imgur.com/YGhvcBS.png" width="50%" height="50%" />


### 3. 50 Hz

<img src="https://i.imgur.com/sa1xVMR.png" width="50%" height="50%" />


### 4. 100 Hz

<img src="https://i.imgur.com/QLpV3Xs.png" width="50%" height="50%" />
