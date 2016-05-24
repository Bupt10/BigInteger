//////////////////////////////////////////////////////////////////// 
//                          _ooOoo_                               // 
//                         o8888888o                              // 
//                         88" . "88                              // 
//                         (| ^_^ |)                              // 
//                         O\  =  /O                              // 
//                      ____/`---'\____                           // 
//                    .'  \\|     |//  `.                         // 
//                   /  \\|||  :  |||//  \                        // 
//                  /  _||||| -:- |||||-  \                       // 
//                  |   | \\\  -  /// |   |                       // 
//                  | \_|  ''\---/''  |   |                       // 
//                  \  .-\__  `-`  ___/-. /                       // 
//                ___`. .'  /--.--\  `. . ___                     // 
//              ."" '<  `.___\_<|>_/___.'  >'"".                  // 
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 // 
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 // 
//      ========`-.____`-.___\_____/___.-`____.-'========         // 
//                           `=---='                              // 
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        // 
//              佛祖保佑       永无BUG     永不修改                   // 
//////////////////////////////////////////////////////////////////// 

#include "BigInteger.h"
#include "StopWatch.h"

#include <iostream>
#include <vector>

using namespace std;
 
int main()
{
    {
        BigInteger a("123457123457123457");
        BigInteger b("123456");
        BigInteger c("57");
        BigInteger d = b - a;
        int i = 0;
        i++;
    }

    BigInteger b("12345678901234567890123456789");
                //12345678901234567890123456782

    bool ok = false;
    long long rtaa = b.convert_2_long_long(&ok);

    BigInteger cccc = b - 2;
    BigInteger pa[9];

    pair<string, long long> ps;
    ps = b.divide(b.getNumber(), 5);


    StopWatch sw;
    sw.start();

    double rt = 0;
    int ct = 10000;
    long long tmp = 2;
    vector<BigInteger> v(ct + 1, 1);

    for(int i = 0; i < ct; i++) {
        v[i + 1] = v[i] * tmp;
        if(i % 100 == 0) {
            rt = sw.seconds(); 
            cout << " * second:" << rt << " * second per:" << rt / (i + 1) << endl; 
        }
    }
    rt = sw.seconds(); 
    cout << " * second:" << rt << " * second per:" << rt / (ct) << endl; 

    return 0;
}