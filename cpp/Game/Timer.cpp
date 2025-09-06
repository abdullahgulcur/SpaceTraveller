#include "pch.h"
#include "Timer.h"
#include "Game.h"

namespace Game{

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
            float now = static_cast<unsigned short>(Game::getInstance()->systemTimer.getTotalSeconds());
            float elapsed = now - lastTriggerTime;
            if (elapsed >= interval) {
                lastTriggerTime = now;
                return true;
            }
            return false;
        }

        //---------------------------------------------

        void StopWatch::start() {
            startTime = static_cast<float>(Game::getInstance()->systemTimer.getTotalSeconds());
        }

        float StopWatch::getDuration() {
            return static_cast<float>(Game::getInstance()->systemTimer.getTotalSeconds()) - startTime;
        }
    }

}