#ifndef LOCKGUARD_H_
#define LOCKGUARD_H_

/*
Reimplement c++11 lock_guard (NOT use std::lock_guard). Use namespace
to allow you to call your class impl "lock_guard" and not conflict with
std::lock_guard

LockGuard.h          // header file only impl
*/

namespace codingChallenge {
class lock_guard;
};

class codingChallenge::lock_guard {
 private:
        std::mutex *mu;

 public:
        lock_guard() {}
        explicit lock_guard(std::mutex &m) {
            mu = &m;
            mu->lock();
        }
        ~lock_guard() { mu->unlock(); }
};

#endif  // LOCKGUARD_H_
