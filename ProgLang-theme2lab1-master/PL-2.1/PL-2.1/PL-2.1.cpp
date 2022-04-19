#include <windows.h> 
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

condition_variable cv;
mutex mtx;

bool flag = true;
int thrIdx;


BOOL Ctrl_C(DWORD fdwCtrlType) {
    switch (fdwCtrlType) {
    case CTRL_C_EVENT: {
        lock_guard <mutex> lck(mtx);
        flag = false;
        cv.notify_all();
        return TRUE;
    }
    }
}


void pickThread(int curIdx) {
    cout << "Thread started: " << curIdx << " (Real ID: " << this_thread::get_id() << ")" << endl;

    while (true) {
        unique_lock <mutex> ul(mtx);

        cv.wait(ul, [curIdx] {
            if (flag) {
                if (curIdx == thrIdx) {
                    thrIdx = -1;
                    return true;
                }

                else return false;
            }

            else return true;;
            });

        if (!flag) {
            cout << "Thread was terminated: " << curIdx << " (Real ID: " << this_thread::get_id() << ")" << endl;
            break;
        }

        else {
            cout << "Thread woke up: " << curIdx << " (Real ID: " << this_thread::get_id() << ")" << endl;
        }
    }
}


int main() {
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)Ctrl_C, TRUE);
    srand(time(nullptr));

    cout << "Enter number of threads:" << endl;
    int threadsNum;
    cin >> threadsNum;

    vector <thread> threads;
    for (int i = 1; i <= threadsNum; i++) {
        this_thread::sleep_for(0.1s);
        threads.push_back(thread(pickThread, i));
    }

    while (true) {
        mtx.lock();
        thrIdx = (rand() % threadsNum) + 1;
        mtx.unlock();

        this_thread::sleep_for(0.5s);
        if (!flag) break;

        cv.notify_all();
    }

    for (int i = 0; i < threadsNum; i++) {
        threads[i].join();
    }

    cout << "Main thread was terminated" << " (Real ID: " << this_thread::get_id() << ")" << endl;;
}