#ifndef BASE64
#define BASE64

//***************define***************//
#define USEASM

//***************class***************//
class Base64
{
private:
    char FullCode = '=';
protected:
    char BaseText[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//0-64 ' [64]=0 : 0-63
public:
    Base64(void) = default;
    ~Base64(void) = default;

    void SetBaseText(const char* const cpBaseText){
        for (int i = 0; i < 64; i += 1)
            BaseText[i] = cpBaseText[i];
    }

    const char* const GetBaseText(void){
        return BaseText;
    }

    void SetFullCode(char cFullCode){
        FullCode = cFullCode;
    }

    char GetFullCode(void){
        return FullCode;
    }

    unsigned long GetEnCodeNum(unsigned long ulEncodeNum){
        return ((ulEncodeNum / 3) * 4) + ((ulEncodeNum % 3) ? 4 : 0) + 1;
    }

    void EnCode(const unsigned char* const cpCode, unsigned long num, unsigned char* cpEncode){
        unsigned long i, j;
        num -= 1;

        for (i = 3, j = 4; i <= num; i += 3, j += 4)
        {
            cpEncode[j - 4] = BaseText[(cpCode[i - 3] >> 2)];
            cpEncode[j - 3] = BaseText[(((cpCode[i - 3] & 0x03) << 4) | ((cpCode[i - 2] & 0xF0) >> 4))];
            cpEncode[j - 2] = BaseText[(((cpCode[i - 2] & 0x0F) << 2) | ((cpCode[i - 1] & 0xC0) >> 6))];
            cpEncode[j - 1] = BaseText[cpCode[i - 1] & 0x3F];
        }

        switch ((num % 3) - 1)
        {
        case 0:
            cpEncode[j - 4] = BaseText[(cpCode[i - 3] >> 2)];
            cpEncode[j - 3] = BaseText[((cpCode[i - 3] & 0x03) << 4)];
            cpEncode[j - 2] = FullCode;
            cpEncode[j - 1] = FullCode;
            cpEncode[j - 0] = 0;
            break;
        case 1:
            cpEncode[j - 4] = BaseText[(cpCode[i - 3] >> 2)];
            cpEncode[j - 3] = BaseText[(((cpCode[i - 3] & 0x03) << 4) | ((cpCode[i - 2] & 0xF0) >> 4))];
            cpEncode[j - 2] = BaseText[(((cpCode[i - 2] & 0x0F) << 2) | ((cpCode[i - 1] & 0xC0) >> 6))];
            cpEncode[j - 1] = FullCode;
            cpEncode[j - 0] = 0;
            break;
        default:
            cpEncode[j - 4] = 0;
            break;
        }
    }

    unsigned long GetDeCodeNum(unsigned long ulDecodeNum){
        return ((ulDecodeNum / 4) * 3) + ((ulDecodeNum % 4) ? 3 : 0) + 1;
    }

    void DeCode(const unsigned char* const cpCode, unsigned long num, unsigned char* cpDecode){
        unsigned long i, j;
        unsigned char cCode[4];

        num -= 1;
        if (cpCode[num - 2] == FullCode)
            num -= 3;
        else
        {
            if (cpCode[num - 1] == FullCode)
                num -= 2;
        }

        for (i = 4, j = 3; i <= num; i += 4, j += 3)
        {
            for (int k = -4; k < 0; k += 1)
            {
                for (int l = 0; l < 64; l += 1)
                {
                    if (cpCode[i + k] == BaseText[l])
                    {
                        cCode[k + 4] = l;
                        break;
                    }
                }
            }

            cpDecode[j - 3] = (cCode[0] << 2) | ((cCode[1] & 0x30) >> 4);
            cpDecode[j - 2] = (((cCode[1] & 0x0F) << 4) | ((cCode[2] & 0x3C) >> 2));
            cpDecode[j - 1] = (((cCode[2] & 0x03) << 6) | (cCode[3] & 0x3F));
        }

        switch ((num % 4) - 1)
        {
        case 0:
            for (int k = -4; k < -2; k += 1)
            {
                for (int l = 0; l < 64; l += 1)
                {
                    if (cpCode[i + k] == BaseText[l])
                    {
                        cCode[k + 4] = l;
                        break;
                    }
                }
            }

            cpDecode[j - 3] = (cCode[0] << 2) | ((cCode[1] & 0x30) >> 4);
            cpDecode[j - 2] = 0;
            break;
        case 1:
            for (int k = -4; k < -1; k += 1)
            {
                for (int l = 0; l < 64; l += 1)
                {
                    if (cpCode[i + k] == BaseText[l])
                    {
                        cCode[k + 4] = l;
                        break;
                    }
                }
            }

            cpDecode[j - 3] = (cCode[0] << 2) | ((cCode[1] & 0x30) >> 4);
            cpDecode[j - 2] = (((cCode[1] & 0x0F) << 4) | ((cCode[2] & 0x3C) >> 2));
            cpDecode[j - 1] = 0;
            break;
        default:
            cpDecode[j - 3] = 0;
            break;
        }
    }
};

#endif // BASE64

