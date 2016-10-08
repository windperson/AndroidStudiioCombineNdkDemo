package tw.idv.windperson.androidstudiocombinendkdemo;

import android.util.Log;

/**
 * Created by windperson on 10/8/2016.
 */

public class NativeCallee {
    private static String TAG = "NativeCallee(Java)";

    public void javaCalleeMethod(String fromC) {
        Log.i(TAG, "fromC=" + fromC);
    }
}
