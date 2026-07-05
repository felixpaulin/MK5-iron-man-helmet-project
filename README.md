# MK5 Helmet Controller Project

Custom ESP32-based controller replacement and AI upgrade project for the AutoKing MK5 Iron Man Helmet.

---

# Project Overview

This repository contains the code, experiments and future plans for replacing the original controller board inside an AutoKing MK5 helmet with a custom ESP32-based control system.

The long-term goal is to create an expandable platform inspired by JARVIS while preserving the original functionality of the helmet.

Current features include:

* Sectional opening
* Sectional closing
* Integral opening
* Integral closing
* Touch sensor support
* Servo smoothing
* Dynamic servo detach logic
* Reduced buzzing
* Reduced stuttering
* Fully custom firmware

Future features include:

* ESP32-S3 migration
* TinyML voice commands
* Wake word detection
* LED control
* Audio playback
* Local AI capabilities
* LLM integration
* Additional suit components

---

# Helmet Information

Helmet Model:

AutoKing MK5 Helmet

Observed hardware:

* 6 servos total
* Two captive touch sensors
* Eye LEDs
* Speaker
* Microphone
* 6V battery pack
* Original proprietary controller PCBs

---

# Current Progress

## Reverse Engineering

Completed:

* Servo count identified
* Servo placement mapped
* Servo directions determined
* Motion sequences documented
* Motion/servo sequences discovered to the angle
* Helmet sucsefully opens and closes both in sections and as one piece.

---

## Controller Replacement

Completed:

* ESP32 Plus prototype
* Sectional movement implementation
* Integral movement implementation
* Smooth movement routines
* Servo angle calibration
* Dynamic attach/detach logic
* Buzz reduction
* Stutter reduction

In progress:

* Motion timing refinement
* LED reverse engineering

---

## Future Migration

Planned hardware:

ESP32-S3 N16R8

Features:

* 16 MB Flash
* 8 MB PSRAM
* WiFi
* Bluetooth
* TinyML support
* Audio processing capabilities

Planned microphone:

INMP441

Planned power system:

6V battery

↓
Buck converter

↓
Servos

↓
ESP32-S3

Common ground shared between all components.

---

# Roadmap

## Phase 1 — Controller Recreation

Status: Completed

* Recreate stock behavior
* Sectional open/close
* Integral open/close
* Touch sensor support

---

## Phase 2 — Hardware Migration

Status: Planned

* ESP32-S3 installation
* Permanent wiring
* 3D printed mounting adapters
* Speaker replacement
* Microphone installation

---

## Phase 3 — TinyML

Status: Planned

Goals:

Offline voice commands.

Examples:

* "Open helmet"
* "Close helmet"
* "Sectional mode"
* "Integral mode"
* "Red eyes"
* "Blue eyes"

TinyML will operate entirely offline.

No internet required.

---

## Phase 4 — JARVIS Integration

Status: Researching

Potential features:

* General conversation
* Weather
* Questions
* Information retrieval
* Personality
* Smart responses

This will likely use:

* WiFi
* Speech recognition
* Cloud-hosted LLM APIs

---

## Phase 5 — Expansion

Long-term concepts:

* Chest piece
* Additional armor components
* HUD concepts
* Improved mechanics
* Future redesigns

---

# Development Philosophy

The project is being built incrementally.

Every phase should leave the helmet in a functional state.

Example:

Stock Helmet

↓

Custom Controller

↓

TinyML

↓

Voice Commands

↓

AI Integration

↓

Future Upgrades

---

# Disclaimer

This is an independent hobby project.

No affiliation with Marvel, Disney, or AutoKing.

Proceed carefully when modifying commercial hardware.

Servos, wiring, and mechanical systems can be damaged if incorrect angles or motion limits are used.

Always test movements slowly and piece by piece, never mvoe all the servos together on the first try, if you have a AutoKing MK5 helmet you can use this code.

---

# Current Status

MK5 Controller Project

Sectional Opening       ✅

Sectional Closing       ✅

Integral Opening        ✅

Integral Closing        ✅

Touch Sensors           ✅

Servo Smoothing         ✅

Dynamic Detach Logic    ✅

ESP32-S3 Migration      ⏳

TinyML                  ⏳

LLM Integration         ⏳

JARVIS                  ⏳

---

Built because Tony Stark probably would have done the same thing.

---

## Attribution Request

If this project contributes significantly to your work, products, videos, repositories, or other public projects, attribution is greatly appreciated.

Suggested attribution:

"Based on the MK5 Helmet Controller Project by Felix Paulin"

GitHub Repository Link:
https://github.com/felixpaulin/Iron-man-helmet-test-and-final-scripts
