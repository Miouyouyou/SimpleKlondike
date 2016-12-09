package com.miouyouyou.simpleklondike;

import android.app.NativeActivity;
import android.content.Intent;
import android.content.res.Configuration;
import android.net.Uri;

public class NativeInsanity extends NativeActivity {

  public static class Log {
    public static final String LOG_TAG = "Java_native-insanity";
    public static void print(final String message, Object... args) {
      android.util.Log.e(LOG_TAG, String.format(message, args));
    }
  }

  public void openWebsite(final byte[] url_as_bytes) {
    final String url_as_string = new String(url_as_bytes);
    try {
      final Uri url = Uri.parse(url_as_string);
      startActivity(new Intent(Intent.ACTION_VIEW, url));
      Log.print("Website opened !\n");
    }
    catch(Exception e) {
      Log.print("Trying to open %s triggered : \n%s\n",
                url_as_string, e.getMessage());
    }
  }

  /* This avoid destroying and recreating the activity on screenChange,
   * which helps avoiding EGL_BAD_DISPLAY issues when locking the
   * screen orientation */
  @Override
  public void onConfigurationChanged(Configuration newConfig)
  {
      super.onConfigurationChanged(newConfig);
  }

}
