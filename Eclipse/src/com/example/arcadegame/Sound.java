package com.example.arcadegame;
import android.media.AudioManager;
import android.media.SoundPool;
import android.content.res.AssetManager;

import java.util.HashMap;
import java.util.Map;
import java.io.IOException;

public class Sound {
    static SoundPool sp;
    static Map<String, Integer> sounds;

    static void loadSounds(AssetManager assets_manager) {

        sp = new SoundPool.Builder()
                .setMaxStreams(100)
                .build();
        sounds = new HashMap<String, Integer>();
        loadSound(assets_manager, "small_explode.ogg");
        loadSound(assets_manager, "big_explode.ogg");
        loadSound(assets_manager, "shoot.ogg");
    }
    private static void loadSound(AssetManager assets_manager, String sound_file_name){
        try {
            int sound_id = sp.load(assets_manager.openFd(sound_file_name), 1);
            sounds.put(sound_file_name, sound_id);
        }catch(IOException e) {
            throw new RuntimeException("cannot load sound");
        }
    }
    public static void play(String sound_file_name) {
        if (!sounds.containsKey(sound_file_name)) {
            throw new RuntimeException("sound not found");
        }
        int sound_id = sounds.get(sound_file_name);
        sp.play(sound_id, 1, 1, 0, 0, 1);
    }
}
