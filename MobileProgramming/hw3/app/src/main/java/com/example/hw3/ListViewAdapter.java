package com.example.hw3;

import android.content.Context;
import android.graphics.Bitmap;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public class ListViewAdapter extends BaseAdapter {
    private ArrayList<MusicItem> items = new ArrayList<>();

    @Override
    public int getCount() {
        return items.size();
    }

    @Override
    public Object getItem(int position) {
        return items.get(position);
    }
    public ArrayList<MusicItem> getAllItems() { return items; }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final Context context = parent.getContext();

        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            MusicItem item = items.get(position);

            convertView = inflater.inflate(R.layout.listview_main, parent, false);

            // 이미지 세팅
            ImageView ivImage = convertView.findViewById(R.id.ivImage);
            Bitmap image = item.getImage(convertView.getContext());
            if (image == null) ivImage.setImageResource(R.drawable.ic_baseline_music_note_24);
            else ivImage.setImageBitmap(image);

            // 타이틀 세팅
            String title = item.getTitle().isEmpty() ? "<unknown>" : item.getTitle();
            ((TextView)convertView.findViewById(R.id.tvTitle)).setText(title);
        }

        return convertView;
    }

    public void addItem(MusicItem item) {
        items.add(item);
    }
}
