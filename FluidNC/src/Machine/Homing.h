// Copyright (c) 2021 -  Stefan de Bruijn
// Copyright (c) 2021 -  Mitch Bradley
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include "../Configuration/Configurable.h"
#include "../System.h"  // AxisMask, MotorMask

namespace Machine {
    class Homing : public Configuration::Configurable {
        static void set_mpos(AxisMask axisMask);

        static const int REPORT_LINE_NUMBER = 0;

        static bool needsPulloff2(MotorMask motors);

        enum class HomingPhase {
            FastApproach,
            Pulloff0,
            SlowApproach,
            Pulloff1,
            Pulloff2,
        };

        static uint32_t plan_move(MotorMask motors, HomingPhase phase);

    public:
        Homing() = default;

        static const int AllCycles = 0;  // Must be zero.

        static volatile bool _approach;

        static void run_cycles(AxisMask axisMask);
        static void run_one_cycle(AxisMask axisMask);

        static AxisMask axis_mask_from_cycle(int cycle);
        static void     run(MotorMask remainingMotors, HomingPhase phase);

        // The homing cycles are 1,2,3 etc.  0 means not homed as part of home-all,
        // but you can still home it manually with e.g. $HA
        int      _cycle             = -1;    // what auto-homing cycle does this axis home on?
        bool     _allow_single_axis = true;  // Allow use of $H<axis> command on this axis
        bool     _positiveDirection = true;
        float    _mpos              = 0.0f;    // After homing this will be the mpos of the switch location
        float    _feedRate          = 50.0f;   // pulloff and second touch speed
        float    _seekRate          = 200.0f;  // this first approach speed
        uint32_t _settle_ms         = 250;     // ms settling time for homing switches after motion
        float    _seek_scaler       = 1.1f;    // multiplied by max travel for max homing distance on first touch
        float    _feed_scaler       = 1.1f;    // multiplier to pulloff for moving to switch after pulloff

        // Configuration system helpers:
        void validate() const override { Assert(_cycle >= 0, "Homing cycle must be defined"); }

        void group(Configuration::HandlerBase& handler) override {
            handler.item("cycle", _cycle, -1, 6);
            handler.item("allow_single_axis", _allow_single_axis);
            handler.item("positive_direction", _positiveDirection);
            handler.item("mpos_mm", _mpos);
            handler.item("feed_mm_per_min", _feedRate, 1.0, 100000.0);
            handler.item("seek_mm_per_min", _seekRate, 1.0, 100000.0);
            handler.item("settle_ms", _settle_ms, 0, 1000);
            handler.item("seek_scaler", _seek_scaler, 1.0, 100.0);
            handler.item("feed_scaler", _feed_scaler, 1.0, 100.0);
        }

        void init() {}
    };

}
