package com.volcengine.vertcdemo.core.eventbus;

public class AudioVolumeEvent {
    public final Info[] speakers;

    public AudioVolumeEvent(Info[] speakers) {
        this.speakers = speakers;
    }

    public static class Info {
        public Info(String uid, int linearVolume) {
            this.uid = uid;
            this.linearVolume = linearVolume;
        }

        public final String uid;
        public final int linearVolume;
    }
}
