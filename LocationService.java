package in.pay1.rmapp.core;

import android.annotation.TargetApi;
import android.app.AlarmManager;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.location.Location;
import android.os.Build;
import android.os.IBinder;
import android.support.v4.app.NotificationCompat;
import android.util.Log;

import com.google.gson.Gson;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.concurrent.TimeUnit;

import in.pay1.rmapp.database.DatabaseManager;
import in.pay1.rmapp.R;
import in.pay1.rmapp.entity.LocationEntry;
import in.pay1.rmapp.utilities.LocationHelper;
import in.pay1.rmapp.ui.activities.PopupActivity;
import in.pay1.rmapp.ui.activities.MainActivity;
import in.pay1.rmapp.utilities.Utils;
import io.reactivex.CompletableObserver;
import io.reactivex.disposables.Disposable;

public class LocationService extends Service {
    public static final String TAG = "LocationService";
    Disposable disposable;
    private static final int FOREGROUND_SERVICE_NOTIFICATION_ID = 101;

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        if(Build.VERSION.SDK_INT >= 26) {
            showForegroundNotification();
            Log.d(TAG, "SERVICE FOREGROUND STARTED");
        }
        else Log.d(TAG, "SERVICE STARTED");

        boolean isAlarmOn;
        isAlarmOn = Utils.getPreferences(this).getBoolean("isAlarmOn", false);
        if(!isAlarmOn) {
            stopMyService();
            return START_STICKY;
        }

        nextAlarm();
        LocationHelper mLocationHelper = new LocationHelper(this);
        mLocationHelper.getLocation(new LocationHelper.callback() {
            @Override
            public void onLocationUpdate(Location location, int status) {
                boolean isAlarmOn;
                isAlarmOn = Utils.getPreferences(LocationService.this).getBoolean("isAlarmOn", false);
                if(!isAlarmOn) return;
                if(location == null) {
                    displayPopup();
                }
                else updateLocation(location);
                stopMyService();
            }
        });
        return START_STICKY;
    }

    private void showForegroundNotification() {
        Intent notificationIntent = new Intent(this, MainActivity.class);
        notificationIntent.setAction(Utils.constant.MAIN_ACTION);
        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0,
                notificationIntent, 0);

        Bitmap icon = BitmapFactory.decodeResource(getResources(), R.drawable.one);

        NotificationManager mNotifyManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) createChannel(mNotifyManager);

        NotificationCompat.Builder mBuilder = new NotificationCompat.Builder(this, Utils.constant.NOTIFICATION_CHANNEL);
        mBuilder.setContentTitle("PAY1")
                .setTicker("")
                .setContentText("Relationship Manager")
                .setSmallIcon(R.drawable.one)
                .setLargeIcon(Bitmap.createScaledBitmap(icon, 128, 128, false))
                .setContentIntent(pendingIntent)
                .setOngoing(true);
        startForeground(FOREGROUND_SERVICE_NOTIFICATION_ID, mBuilder.build());

    }

    private void nextAlarm() {
        boolean isAlarmOn;
        isAlarmOn = Utils.getPreferences(this).getBoolean("isAlarmOn", false);
        if(!isAlarmOn) return;

        AlarmManager alarmMgr;
        PendingIntent alarmIntent;
        alarmMgr = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
        Intent i = new Intent(getApplicationContext(), LocationService.class);

        if(Build.VERSION.SDK_INT >= 26) {
            alarmIntent = PendingIntent.getForegroundService(this, 0, i, PendingIntent.FLAG_CANCEL_CURRENT);
        }
        else {
            alarmIntent = PendingIntent.getService(this, 0, i, PendingIntent.FLAG_CANCEL_CURRENT);
        }

        if (Build.VERSION.SDK_INT >= 23) {
            alarmMgr.setExactAndAllowWhileIdle(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + Utils.constant.INTERVAL_MILLIS, alarmIntent);
        } else if (Build.VERSION.SDK_INT >= 19) {
            alarmMgr.setExact(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + Utils.constant.INTERVAL_MILLIS, alarmIntent);
        } else {
            alarmMgr.set(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + Utils.constant.INTERVAL_MILLIS, alarmIntent);
        }
    }

    private void displayPopup() {
        Intent i = new Intent(this, PopupActivity.class);
        i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(i);
    }

    private void updateLocation(Location location) {

        boolean isAlarmOn;
        isAlarmOn = Utils.getPreferences(this).getBoolean("isAlarmOn", false);
        if(!isAlarmOn) return;

        SharedPreferences preferences = Utils.getPreferences(this);
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
        Gson gson = new Gson();

        int count = preferences.getInt("cluster_count", 0);
        if(count == 0) {
            LocationEntry e = new LocationEntry();
            e.setLatitude(location.getLatitude());
            e.setLongitude(location.getLongitude());
            e.setDuration("00:00:00");
            e.setTime(sdf.format(new Date()));

            preferences.edit()
                    .putString("cluster_data", gson.toJson(e))
                    .putInt("cluster_count", 1)
                    .apply();
            return;
        }

        LocationEntry cluster = gson.fromJson(preferences.getString("cluster_data", ""), LocationEntry.class);

        Date start, end = new Date();
        try {
            start = sdf.parse(cluster.getTime());
            end = sdf.parse(sdf.format(end));
        } catch (Exception e) {
            Log.d(TAG, e.getMessage());
            return;
        }

        Double distance = distance(cluster.getLatitude(), cluster.getLongitude(), location.getLatitude(), location.getLongitude());
        Log.d(TAG, "distance: " + distance);
        if(distance < 30.0) {
            cluster.setLatitude(( (count*cluster.getLatitude()) + location.getLatitude()) / (count + 1));
            cluster.setLongitude(( (count*cluster.getLongitude()) + location.getLongitude()) / (count + 1));

            long duration = end.getTime() - start.getTime();

            String cluster_duration = String.format(Locale.getDefault(), "%02d:%02d:%02d",
                    TimeUnit.MILLISECONDS.toHours(duration),
                    TimeUnit.MILLISECONDS.toMinutes(duration) % TimeUnit.HOURS.toMinutes(1),
                    TimeUnit.MILLISECONDS.toSeconds(duration) % TimeUnit.MINUTES.toSeconds(1));
            Log.d(TAG, "duration: " + cluster_duration);

            cluster.setDuration(cluster_duration);
            preferences.edit()
                    .putString("cluster_data", gson.toJson(cluster))
                    .putInt("cluster_count", count+1)
                    .apply();
        } else {
            DatabaseManager.getInstance(this).insertEntry(cluster)
                    .subscribe(new CompletableObserver() {
                        @Override public void onSubscribe(Disposable d) { disposable = d; }
                        @Override public void onComplete() { }
                        @Override public void onError(Throwable e) { }
                    });

            LocationEntry e = new LocationEntry();
            e.setLatitude(location.getLatitude());
            e.setLongitude(location.getLongitude());
            e.setDuration("00:00:00");
            e.setTime(sdf.format(end));

            preferences.edit()
                    .putString("cluster_data", gson.toJson(e))
                    .putInt("cluster_count", 1)
                    .apply();
        }
    }

    private static double distance(double lat1, double lon1, double lat2, double lon2) {
        double theta = lon1 - lon2;
        double dist = Math.sin(deg2rad(lat1)) * Math.sin(deg2rad(lat2)) + Math.cos(deg2rad(lat1)) * Math.cos(deg2rad(lat2)) * Math.cos(deg2rad(theta));
        dist = Math.acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        dist = dist * 1.609344;
        return (dist*1000);
    }
    private static double deg2rad(double deg) {
        return (deg * Math.PI / 180.0);
    }
    private static double rad2deg(double rad) {
        return (rad * 180 / Math.PI);
    }

    @TargetApi(26)
    private void createChannel(NotificationManager notificationManager) {
        String name = Utils.constant.NOTIFICATION_CHANNEL;
        String description = "Notifications for location tracking";
        int importance = NotificationManager.IMPORTANCE_DEFAULT;

        NotificationChannel mChannel = new NotificationChannel(name, name, importance);
        mChannel.setDescription(description);
        mChannel.enableLights(true);
        mChannel.setLightColor(Color.BLUE);
        notificationManager.createNotificationChannel(mChannel);
    }

    private void stopMyService() {
        Log.d(TAG, "SERVICE STOPPED");
        if(Build.VERSION.SDK_INT >= 26) {
            stopForeground(true);
        }
        stopSelf();
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "SERVICE DESTROYED");
        if(disposable != null) disposable.dispose();
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

}

