package tw.idv.windperson.androidstudiocmakendkdemo;

import android.util.Log;


public class NativeCallee {
    private static String TAG = "NativeCallee(Java)";

    public void javaCalleeMethod(String fromC) {
        Log.i(TAG, "fromC=" + fromC);
    }
}
