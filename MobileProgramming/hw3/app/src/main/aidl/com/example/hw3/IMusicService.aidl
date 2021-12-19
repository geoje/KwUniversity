// IMusicService.aidl
package com.example.hw3;

// Declare any non-default types here with import statements
import com.example.hw3.MusicItem;
parcelable MusicItem;

interface IMusicService {
    MusicItem Play(int index);
    void Pause();
    void Resume();
    MusicItem Next();
    MusicItem Prev();

    List<MusicItem> getMusicItems();
    MusicItem getMusicItem(int index);
    boolean isPlaying();
}