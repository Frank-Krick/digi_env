#ifndef __UI__MODELS__DURATION__MODEL__
#define __UI__MODELS__DURATION__MODEL__

namespace ui::models {
    enum DurationType { RealTime, MusicalTime };

    class MusicalFraction {};

    class DurationModel {
        public:
            DurationModel(unsigned int durationInMs): _durationInMs(durationInMs) {}

            unsigned int getDurationInMs() const { return _durationInMs; }
            void setDurationinMs(unsigned int durationInMs) { _durationInMs = durationInMs; } 

        private:
            unsigned int _durationInMs;
            MusicalFraction _durationAsMusicalFraction;
    };
}

#endif
