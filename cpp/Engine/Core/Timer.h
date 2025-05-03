#pragma once

namespace Engine {

    namespace Timer {

        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = Clock::time_point;
        using Duration = Clock::duration;

        class SystemTimer {
        private:
        public:

            TimePoint startTime;
            TimePoint lastFrameTime;
            Duration deltaTime;
            bool paused;

            SystemTimer();
            void update();
            void reset();
            void setPaused(bool isPaused);
            float getDeltaSeconds();
            double getTotalSeconds();
            double getTotalMilliseconds();
            double getTotalMicroseconds();
            double getTotalNanoseconds();

        };

        class TimerTrigger {
        private:
            float lastTriggerTime;
        public:
            bool shouldTrigger(float interval);
        };
    }
}