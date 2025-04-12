#include "pch.h"
#include "Timer.h"
#include "Core.h"

namespace Engine{

    namespace Timer{

        SystemTimer::SystemTimer() : startTime(Clock::now()), lastFrameTime(startTime), paused(false) {}

        void SystemTimer::update() {
            if (paused) return;

            TimePoint now = Clock::now();
            deltaTime = now - lastFrameTime;
            lastFrameTime = now;
        }

        void SystemTimer::reset() {
            startTime = Clock::now();
            lastFrameTime = startTime;
            deltaTime = Duration::zero();
        }

        void SystemTimer::setPaused(bool isPaused) {
            paused = isPaused;
        }

        float SystemTimer::getDeltaSeconds() {
            return std::chrono::duration<float>(deltaTime).count();
        }

        double SystemTimer::getTotalSeconds() {
            return std::chrono::duration<double>(Clock::now() - startTime).count();
        }

        double SystemTimer::getTotalMilliseconds() {
            return std::chrono::duration<double, std::milli>(Clock::now() - startTime).count();
        }

        double SystemTimer::getTotalMicroseconds(){
            return std::chrono::duration<double, std::micro>(Clock::now() - startTime).count();
        }

        double SystemTimer::getTotalNanoseconds(){
            return std::chrono::duration<double, std::nano>(Clock::now() - startTime).count();
        }


        //---------------------------------------------

        bool TimerTrigger::shouldTrigger(float interval){
            float now = static_cast<unsigned short>(Core::getInstance()->systemTimer.getTotalSeconds());
            float elapsed = now - lastTriggerTime;
            if (elapsed >= interval) {
                lastTriggerTime = now;
                return true;
            }
            return false;
        }
    }


/*    Timer::Timer()
            : running(false), startTime(Clock::now()), endTime(startTime) {}

    void Timer::reset() {
        running = false;
        startTime = Clock::now();
        endTime = startTime;
    }

    void Timer::start() {
        if (!running) {
            startTime = Clock::now();
            running = true;
        }
    }

    void Timer::stop() {
        if (running) {
            endTime = Clock::now();
            running = false;
        }
    }

    float Timer::getElapsedSeconds() {
        auto duration = running ? Clock::now() - startTime : endTime - startTime;
        return std::chrono::duration<float>(duration).count();
    }

    double Timer::getElapsedMilliseconds() {
        auto duration = running ? Clock::now() - startTime : endTime - startTime;
        return std::chrono::duration<double, std::milli>(duration).count();
    }

    long long Timer::getElapsedMicroseconds() {
        auto duration = running ? Clock::now() - startTime : endTime - startTime;
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    bool Timer::isRunning() {
        return running;
    }*/
}