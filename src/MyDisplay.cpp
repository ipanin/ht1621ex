#include "HT1621.h"

class MyDisplay {
public:
    MyDisplay() : _ht(2, 3, 4) {} 

    void Init() {
        _ht.begin();
        _ht.sendCommand(HT1621::RC256K);
        _ht.sendCommand(HT1621::BIAS_THIRD_4_COM);
        _ht.sendCommand(HT1621::SYS_EN);
        _ht.sendCommand(HT1621::LCD_ON);
    }

    // clear memory
    void Clear() {
        register uint8_t i;
        for (i = 0; i < 32; i++)
            _ht.write(i, 0);
    }

    void ShowAll() {
        register uint8_t i;
        for (i = 0; i < 32; i++)
            _ht.write(i, 0xff);
    }

    void Show(uint32_t number) {
        uint16_t buf[MaxDigits] = {0, 0, 0, 0, 0, 0, 0, 0};
        ConvertToString(number, buf);
        ShowDigits(buf, MaxDigits);
    }

    void ConvertToString(uint32_t number, uint16_t *buf)
    {
        if (number == 0) {
            buf[0] = Font[0];
            return;
        }

        uint8_t digit;
        register uint8_t i = 0;
        while (number > 0 && i < MaxDigits)
        {

            digit = number % 10;
            buf[i++] = Font[digit];
            number /= 10;
        }
    }

    void ShowDigits(uint16_t *buf, uint8_t count)
    {
        for (int pos=0; pos<count; pos++) {
            _ht.write(StartAddress + 3*pos, buf[pos], 12);
        }
    }

    /* 0,1,2,3,4,5,6,7,8,9,A,b,C,c,d,E,F,H,h,L,n,N,o,P,r,t,U,-, , */
    const uint16_t Font[11] = {
        0b001101010011, // 0 
        0b000000000011, // 1
        0b001001110001, 
        0b000001110011, 
        0b000100100011, 
        0b000101110010, 
        0b001101110010, 
        0b000000010011, 
        0b001101110011, 
        0b000101110011, // 9
        0b00 // space
    };
    // seg = 0..127
    void ShowSegment(uint8_t seg) {
        uint8_t addr = seg / 4;
        uint8_t bit = seg % 4;
        uint8_t data = 1 << bit;
        _ht.write(addr, data);
    }
    HT1621 _ht;

private: 

    const uint8_t MaxDigits = 8; // Available number of digits in LCD (depend of LCD model)
    const uint8_t StartAddress = 8;
};

MyDisplay display;
int i = 0;

void setup() {
    display.Init();

    display.Clear();
    delay(1000);

    display.ShowAll();
    delay(1000);

    display.Clear();
    display.Show(12345678);

//    delay(1000);
//    display._ht.sendCommand(HT1621::SYS_DIS);
}

void loop() {
/*    if (i >= 4*6) 
        i=0;

    const char StartAddress = 8;
    display.ShowSegment(4 * StartAddress + i);
    */
    i++;
    display.Show(i);
    delay(1000);


}
