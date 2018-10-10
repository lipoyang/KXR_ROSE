#ifndef    _UDP_COMM_H_
#define    _UDP_COMM_H_

// 受信バッファサイズ
#define UDP_COMM_BUFF_SIZE 256

// UDP通信処理クラス
class UdpComm
{
public:
    UdpComm();
    // 開始する
    void begin();
    // 周期処理 loop()で必ず呼び出す
    void loop();
    // データを送信する
    void send(char* data);
    
    // 受信コールバック
    void (*onReceive)(char* data);
    
private:
    // 受信状態
    int state;
    // 受信データのバッファ
    char buff[UDP_COMM_BUFF_SIZE];
    int ptr;
};

#endif
