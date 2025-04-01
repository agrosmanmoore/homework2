#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Time {
private:

    int hour, min, sec;
    bool am_pm; // true = PM, false = AM
    
    vector<int> isValid(int h, int m, int s) {

        int isHourValid = (h >= 1 && h <= 12) ? 1 : 0;
        int isMinuteValid = (m >= 0 && m < 60) ? 1 : 0;
        int isSecondValid = (s >= 0 && s < 60) ? 1 : 0;
    
        return {isHourValid, isMinuteValid, isSecondValid};
    }
    

public:
    // Constructor con valores por defecto
    Time(int h = 12, int m = 0, int s = 0, bool am_pm = false) : hour(h), min(m), sec(s), am_pm(am_pm) {
        auto valid = isValid(h, m, s);
        if (valid[0] == 0) hour = 12;
        if (valid[1] == 0) min = 0;
        if (valid[2] == 0) sec = 0;
    }

    // Método para establecer la hora
    void setTime(int h, int m, int s, bool am_pm) {
        auto valid = isValid(h, m, s);
        if (valid[0] == 0) hour = 12;
        if (valid[1] == 0) min = 0;
        if (valid[2] == 0) sec = 0;

        hour = h;
        min = m;
        sec = s;
        am_pm = am_pm;
    }

    // Mostrar en formato 12h y 24h
    void printTime() const {
        cout << setw(2) << setfill('0') << hour << "h, "<< setw(2) << min << "m, " << setw(2) << sec << "s "<< (am_pm ? "p.m." : "a.m.") << endl;
    }

    void print24HourFormat() const {
        int h24 = (hour % 12) + (am_pm ? 12 : 0);
        cout << setw(2) << setfill('0') << h24 << ":"<< setw(2) << min << ":" << setw(2) << sec << std::endl;
    }
};

int main() {
    Time t(3, 90, 42, true);
    t.printTime();           // 03h, 14m, 42s p.m.
    t.print24HourFormat();   // 15:14:42
    return 0;
}
