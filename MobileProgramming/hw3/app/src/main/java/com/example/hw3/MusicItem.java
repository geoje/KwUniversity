package com.example.hw3;

import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Parcel;
import android.os.ParcelFileDescriptor;
import android.os.Parcelable;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.Serializable;

public class MusicItem implements Parcelable {
    private static final BitmapFactory.Options bitmapOptionsCache = new BitmapFactory.Options();
    private static final Uri artworkUri = Uri.parse("content://media/external/audio/albumart");

    private Bitmap image;
    private String title, filename;
    private long albumId, duration;

    public MusicItem(String title, String filename, long albumId, long duration) {
        this.title = title;
        this.filename = filename;
        this.albumId = albumId;
        this.duration = duration;
    }

    protected MusicItem(Parcel in) {
        title = in.readString();
        filename = in.readString();
        albumId = in.readLong();
        duration = in.readLong();
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(title);
        dest.writeString(filename);
        dest.writeLong(albumId);
        dest.writeLong(duration);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    public static final Creator<MusicItem> CREATOR = new Creator<MusicItem>() {
        @Override
        public MusicItem createFromParcel(Parcel in) {
            return new MusicItem(in);
        }

        @Override
        public MusicItem[] newArray(int size) {
            return new MusicItem[size];
        }
    };

    public Bitmap bitmapFromAlbumId(Context context) {
        ContentResolver res = context.getContentResolver();
        Uri uri = ContentUris.withAppendedId(artworkUri, albumId);

        if (uri != null) {
            ParcelFileDescriptor fd = null;
            try {
                fd = res.openFileDescriptor(uri, "r");
                return BitmapFactory.decodeFileDescriptor(
                        fd.getFileDescriptor(),
                        null,
                        bitmapOptionsCache);
            } catch (FileNotFoundException ignored) {
            } finally {
                try {
                    if (fd != null)
                        fd.close();
                } catch (IOException ignored) {
                }
            }
        }

        return null;
    }

    public Bitmap getImage(Context context) {
        if (image == null)
            return image = bitmapFromAlbumId(context);
        else
            return image;
    }

    public void setImage(Bitmap image) {
        this.image = image;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getFilename() {
        return filename;
    }

    public void setFilename(String filename) {
        this.filename = filename;
    }

    public long getDuration() {
        return duration;
    }

    public void setDuration(long duration) {
        this.duration = duration;
    }
}
