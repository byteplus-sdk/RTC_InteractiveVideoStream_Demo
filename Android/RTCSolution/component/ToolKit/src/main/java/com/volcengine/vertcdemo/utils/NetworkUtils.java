package com.volcengine.vertcdemo.utils;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

import androidx.annotation.NonNull;

public final class NetworkUtils {
    public static boolean isNetworkAvailable(@NonNull Context context) {
        try {
            ConnectivityManager manager =
                    (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo info = manager.getActiveNetworkInfo();
            return (info != null && info.isConnected());
        } catch (Exception ignored) {
            // ignore
        }
        return false;
    }
}
