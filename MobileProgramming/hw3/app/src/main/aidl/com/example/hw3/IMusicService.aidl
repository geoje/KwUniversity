// IMusicService.aidl
package com.example.hw3;

// Declare any non-default types here with import statements

interface IMusicService {
    void Start(String filename);
    void Pause();
    void Resume();
}