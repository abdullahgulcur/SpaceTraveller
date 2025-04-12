#pragma once

namespace Engine {

    namespace Timer{

        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = Clock::time_point;
        using Duration = Clock::duration;

        class SystemTimer{
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

        class TimerTrigger{
        private:
            float lastTriggerTime;
        public:
            bool shouldTrigger(float interval);
        };

        /*struct TimerParticleEmissive{
            unsigned short startTime;
            unsigned short

        };*/


/*        struct TimerBasic {
            TimePoint startTime;
            TimePoint endTime;
        };

        struct TimerParticle {
            TimePoint startTime;
            unsigned int lastTriggerIndex;

        };

        template<typename T>
        void reset(T& timer){
            timer.startTime = Clock::now();
            timer.endTime = timer.startTime;
        }

        template<typename T>
        void start(T& timer){
            timer.startTime = Clock::now();
        }

        template<typename T>
        void stop(T& timer){
            timer.endTime = Clock::now();
        }

        template<typename T>
        unsigned int getElapsedSeconds(T& timer){
            auto duration = Clock::now() - timer.startTime;
            return std::chrono::duration<unsigned int>(duration).count();
        }

        template<typename T>
        unsigned int getElapsedMilliseconds(T& timer){
            auto duration = Clock::now() - timer.startTime;
            return std::chrono::duration<unsigned int, std::milli>(duration).count();
        }*/

    }

    /*class Timer {
    public:
        Timer();

        void reset();
        void start();
        void stop();

        float getElapsedSeconds();
        double getElapsedMilliseconds();
        long long getElapsedMicroseconds();
        bool isRunning();

    private:
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = Clock::time_point;

        TimePoint startTime;
        TimePoint endTime;
        bool running;
    };*/
}