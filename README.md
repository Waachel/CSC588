# CSC588 - Real-Time Multithreaded Architecture
## Description
For CSC588, I learned about real-time constrained multithreaded architecture. Topics covered include multithreaded handle development, inter-thread communication, creating systems for user-defined callbacks, asynchronous loading and streaming of resources, non-blocking threading synchronization, design patterns and data driven messaging with time delivery constraints. For the final project, I created an Audio Engine that integrated the existing single and multithreaded middleware libraries.

## Final Project Description
The final project included 
* Basic audio features
  * XAudio2 Voices
  * Volume, pan, pitch
* Stitching
  * Seamless transitions between voices using Voice Callbacks in Playlist
  * Voice buffers
* Priorities
  * Priority table
  * Cancelling or Calling sounds based on priorities
  * Using "time playing" when calls have the same priority
* Game User Callbacks
  * User supplied callback on StreamEnd()
  * Callback for the game to trigger an event on playing end
* Asynchronous File
  * File load callback when the file is loaded and ready on the audio thread
* Audio Management
  * Handles
  * Buffer
  * Voice
